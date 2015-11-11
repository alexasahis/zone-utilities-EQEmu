#ifndef EQEMU_MAP_VIEW_MODULE_NAVIGATION_H
#define EQEMU_MAP_VIEW_MODULE_NAVIGATION_H

#include <vector>

#include <Recast.h>
#include <DetourNavMesh.h>
#include <DebugDraw.h>
#include <DetourDebugDraw.h>

#include "module.h"
#include "scene.h"
#include "line_model.h"
#include "rc_chunky_tri_mesh.h"
#include "thread_pool.h"
#include "nav_mesh_model.h"

enum NavigationPartitionType
{
	NAVIGATION_PARTITION_WATERSHED = 0,
	NAVIGATION_PARTITION_MONOTONE,
	NAVIGATION_PARTITION_LAYERS,
};

enum NavigationPolyFlags
{
	NavigationPolyFlagWalk = 0x01,
	NavigationPolyFlagSwim = 0x02,
	NavigationPolyFlagDisabled = 0x10,
	NavigationPolyFlagAll = 0xFFFF
};

class ModuleNavigation;
class NavigationDebugDraw : public duDebugDraw
{
public:
	virtual void depthMask(bool state) { }
	virtual void texture(bool state) { }
	virtual void begin(duDebugDrawPrimitives prim, float size = 1.0f);
	virtual void vertex(const float* pos, unsigned int color);
	virtual void vertex(const float x, const float y, const float z, unsigned int color);
	virtual void vertex(const float* pos, unsigned int color, const float* uv);
	virtual void vertex(const float x, const float y, const float z, unsigned int color, const float u, const float v);
	virtual void end() { mode = 0; verts_in_use = 0; }

	ModuleNavigation *nav_module;
private:
	void CreatePrimitive();
	int mode;
	glm::vec3 verts[4];
	int verts_in_use;
};

class ModuleNavigation : public Module, public SceneHotkeyListener
{
public:
	enum Mode
	{
		ModeNone = 0,
		ModeNavMeshGen,
		ModeTestNavigation,
	};

	ModuleNavigation();
	virtual ~ModuleNavigation();

	virtual const char *GetName() { return "Navigation"; };
	virtual void OnLoad(Scene *s);
	virtual void OnShutdown();
	virtual void OnDrawMenu();
	virtual void OnDrawUI();
	virtual void OnSceneLoad(const char *zone_name);
	virtual void OnSuspend();
	virtual void OnResume();
	virtual bool HasWork();
	virtual bool CanSave();
	virtual void Save();
	virtual void OnHotkey(int ident);
	virtual void OnClick(int mouse_button, const glm::vec3 *collide_hit, const glm::vec3 *non_collide_hit);
private:
	friend class ModuleNavigationBuildTile;
	friend class NavigationDebugDraw;
	void UpdateBoundingBox();
	void DrawNavMeshGenerationUI();
	void BuildNavigationMesh();
	void CreateChunkyTriMesh(std::shared_ptr<ZoneMap> zone_geo);
	void CreateNavMeshModel();

	Scene *m_scene;
	std::shared_ptr<rcChunkyTriMesh> m_chunky_mesh;

	int m_mode;

	//bounds
	std::unique_ptr<LineModel> m_bounding_box_renderable;
	glm::vec3 m_bounding_box_min;
	glm::vec3 m_bounding_box_max;

	//nav mesh generation vars
	float m_cell_size;
	float m_cell_height;
	float m_agent_height;
	float m_agent_radius;
	float m_agent_max_climb;
	float m_agent_max_slope;
	float m_region_min_size;
	float m_region_merge_size;
	float m_edge_max_len;
	float m_edge_max_error;
	float m_verts_per_poly;
	float m_detail_sample_dist;
	float m_detail_sample_max_error;
	int m_partition_type;
	int m_max_tiles;
	int m_max_polys_per_tile;
	float m_tile_size;

	dtNavMesh *m_nav_mesh;
	std::unique_ptr<NavMeshModel> m_nav_mesh_renderable;

	//debug
	std::unique_ptr<LineModel> m_debug_renderable;

	int m_tiles_building;
	ThreadPool m_thread_pool;
};

#endif
