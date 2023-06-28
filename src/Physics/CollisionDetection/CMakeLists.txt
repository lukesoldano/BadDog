message("%% Entering CollisionDetection")

####################################################################################################
# Set source files
set(COLLISION_DETECTION_SOURCE_FILES

    ${CMAKE_CURRENT_LIST_DIR}/CollisionDetector.cpp

    CACHE INTERNAL "COLLISION_DETECTION_SOURCE_FILES")

####################################################################################################
# Set header files
set(COLLISION_DETECTION_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/CollisionDetector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SpatialHashMap.hpp

    CACHE INTERNAL "COLLISION_DETECTION_HEADER_FILES")

####################################################################################################
# Set include dirs
set(COLLISION_DETECTION_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "COLLISION_DETECTION_INCLUDE_DIRS")