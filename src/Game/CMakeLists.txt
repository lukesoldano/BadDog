message("%% Entering Game")

####################################################################################################
# Set source files
set(GAME_SOURCE_FILES
   #  ${GAME_ENTITIES_SOURCE_FILES}
   #  ${GAME_LEVELS_SOURCE_FILES}

    ${CMAKE_CURRENT_LIST_DIR}/GameEngine.cpp
   #  ${CMAKE_CURRENT_LIST_DIR}/GameState.cpp

    CACHE INTERNAL "GAME_SOURCE_FILES")

####################################################################################################
# Set header files
set(GAME_HEADER_FILES
   #  ${GAME_ENTITIES_HEADER_FILES}
   #  ${GAME_LEVELS_HEADER_FILES}

    ${CMAKE_CURRENT_LIST_DIR}/GameEngine.hpp
   #  ${CMAKE_CURRENT_LIST_DIR}/GameState.hpp

    CACHE INTERNAL "GAME_HEADER_FILES")

####################################################################################################
# Set include dirs
set(GAME_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

   #  ${GAME_ENTITIES_INCLUDE_DIRS}
   #  ${GAME_LEVELS_INCLUDE_DIRS}

    CACHE INTERNAL "GAME_INCLUDE_DIRS")