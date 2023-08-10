message("%% Entering SpatialHashMap")

####################################################################################################
# Set source files
set(SPATIAL_HASH_MAP_SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/SpatialHashMap.cpp

    CACHE INTERNAL "SPATIAL_HASH_MAP_SOURCE_FILES")

####################################################################################################
# Set header files
set(SPATIAL_HASH_MAP_HEADER_FILES
    ${CMAKE_CURRENT_LIST_DIR}/SpatialHashMap.hpp

    CACHE INTERNAL "SPATIAL_HASH_MAP_HEADER_FILES")

####################################################################################################
# Set include dirs
set(SPATIAL_HASH_MAP_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "SPATIAL_HASH_MAP_INCLUDE_DIRS")