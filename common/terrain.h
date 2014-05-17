#ifndef EQEMU_COMMON_TERRAIN_H
#define EQEMU_COMMON_TERRAIN_H

#include <memory>
#include <map>
#include "terrain_tile.h"
#include "water_sheet.h"
#include "invis_wall.h"
#include "placeable_group.h"
#include "eqg_model_loader.h"

namespace EQEmu
{

class Terrain
{
public:
	Terrain() { }
	~Terrain() { }

	void AddTile(std::shared_ptr<TerrainTile> t) { tiles.push_back(t); }
	void SetQuadsPerTile(uint32_t value) { quads_per_tile = value; }
	void SetUnitsPerVertex(float value) { units_per_vertex = value; }
	void AddWaterSheet(std::shared_ptr<WaterSheet> s) { water_sheets.push_back(s); }
	void AddInvisWall(std::shared_ptr<InvisWall> w) { invis_walls.push_back(w); }
	void AddPlaceableGroup(std::shared_ptr<PlaceableGroup> p) { placeable_groups.push_back(p); }

	std::vector<std::shared_ptr<TerrainTile>>& GetTiles() { return tiles; }
	uint32_t GetQuadsPerTile() { return quads_per_tile; }
	float GetUnitsPerVertex() { return units_per_vertex; }
	std::vector<std::shared_ptr<WaterSheet>>& GetWaterSheets() { return water_sheets; }
	std::vector<std::shared_ptr<InvisWall>>& GetInvisWalls() { return invis_walls; }
	std::vector<std::shared_ptr<PlaceableGroup>>& GetPlaceableGroups() { return placeable_groups; }
	std::map<std::string, std::shared_ptr<EQG::Geometry>>& GetModels() { return models; }
private:
	std::vector<std::shared_ptr<TerrainTile>> tiles;
	uint32_t quads_per_tile;
	float units_per_vertex;
	
	std::vector<std::shared_ptr<WaterSheet>> water_sheets;
	std::vector<std::shared_ptr<InvisWall>> invis_walls;
	std::vector<std::shared_ptr<PlaceableGroup>> placeable_groups;
	std::map<std::string, std::shared_ptr<EQG::Geometry>> models;
};

}

#endif
