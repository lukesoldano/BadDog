message("%% Entering CollisionHandling")

####################################################################################################
# Set source files
set(COLLISION_HANDLING_SOURCE_FILES

    ${CMAKE_CURRENT_LIST_DIR}/CollisionDetector.cpp

    CACHE INTERNAL "COLLISION_DHANDLINGSOURCE_FILES")

####################################################################################################
# Set header files
set(COLLISION_HANDLING_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/CollisionDetector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SpatialHashMap.hpp

    CACHE INTERNAL "COLLISION_HANDLING_HEADER_FILES")

####################################################################################################
# Set include dirs
set(COLLISION_HANDLING_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "COLLISION_HANDLING_INCLUDE_DIRS")