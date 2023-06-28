message("%% Entering Physics")

####################################################################################################
# Set source files
set(PHYSICS_SOURCE_FILES

    ${CMAKE_CURRENT_LIST_DIR}/CollisionDetector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsEngine.cpp

    CACHE INTERNAL "PHYSICS_SOURCE_FILES")

####################################################################################################
# Set header files
set(PHYSICS_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/CollisionDetector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsDefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsEngine.hpp

    CACHE INTERNAL "PHYSICS_HEADER_FILES")

####################################################################################################
# Set include dirs
set(PHYSICS_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "PHYSICS_INCLUDE_DIRS")