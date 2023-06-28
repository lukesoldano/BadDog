message("%% Entering Physics")

####################################################################################################
# Make necessary inclusions and add relevant subdirectories
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/CollisionDetection)

####################################################################################################
# Set source files
set(PHYSICS_SOURCE_FILES
    ${COLLISION_DETECTION_SOURCE_FILES}

    ${CMAKE_CURRENT_LIST_DIR}/PhysicsEngine.cpp

    CACHE INTERNAL "PHYSICS_SOURCE_FILES")

####################################################################################################
# Set header files
set(PHYSICS_HEADER_FILES
    ${COLLISION_DETECTION_HEADER_FILES}

    ${CMAKE_CURRENT_LIST_DIR}/PhysicsDefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsEngine.hpp

    CACHE INTERNAL "PHYSICS_HEADER_FILES")

####################################################################################################
# Set include dirs
set(PHYSICS_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${COLLISION_DETECTION_INCLUDE_DIRS}

    CACHE INTERNAL "PHYSICS_INCLUDE_DIRS")