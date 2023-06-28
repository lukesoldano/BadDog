message("%% Entering Physics")

####################################################################################################
# Make necessary inclusions and add relevant subdirectories
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/CollisionHandling)

####################################################################################################
# Set source files
set(PHYSICS_SOURCE_FILES
    ${COLLISION_HANDLING_SOURCE_FILES}

    ${CMAKE_CURRENT_LIST_DIR}/PhysicsDefs.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsEngine.cpp

    CACHE INTERNAL "PHYSICS_SOURCE_FILES")

####################################################################################################
# Set header files
set(PHYSICS_HEADER_FILES
    ${COLLISION_HANDLING_HEADER_FILES}

    ${CMAKE_CURRENT_LIST_DIR}/PhysicsDefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsEventTypes.hpp

    CACHE INTERNAL "PHYSICS_HEADER_FILES")

####################################################################################################
# Set include dirs
set(PHYSICS_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${COLLISION_HANDLING_INCLUDE_DIRS}

    CACHE INTERNAL "PHYSICS_INCLUDE_DIRS")