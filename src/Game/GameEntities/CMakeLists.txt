message("%% Entering Game Entities")

####################################################################################################
# Set source files
set(GAME_ENTITIES_SOURCE_FILES

   #  ${CMAKE_CURRENT_LIST_DIR}/StaticEntity.cpp

    CACHE INTERNAL "GAME_ENTITIES_SOURCE_FILES")

####################################################################################################
# Set header files
set(GAME_ENTITIES_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/ActiveEntity.hpp
    ${CMAKE_CURRENT_LIST_DIR}/GameEntityDefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StaticEntity.hpp

    CACHE INTERNAL "GAME_ENTITIES_HEADER_FILES")

####################################################################################################
# Set include dirs
set(GAME_ENTITIES_INCLUDE_DIRS

    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "GAME_ENTITIES_INCLUDE_DIRS")