CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)

SET(pfs_sources
	main.cpp
)

SET(pfs_headers
)

ADD_EXECUTABLE(pfs ${pfs_sources} ${pfs_headers})

INSTALL(TARGETS pfs RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

TARGET_LINK_LIBRARIES(pfs PRIVATE common)
TARGET_LINK_LIBRARIES(pfs PRIVATE log)
TARGET_LINK_LIBRARIES(pfs PRIVATE ZLIB::ZLIB)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)