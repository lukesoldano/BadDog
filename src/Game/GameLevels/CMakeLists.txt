message("%% Entering Game Levels")

####################################################################################################
# Set source files
set(GAME_LEVELS_SOURCE_FILES

    ${CMAKE_CURRENT_LIST_DIR}/GameLevel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TestLevel.cpp

    CACHE INTERNAL "GAME_LEVELS_SOURCE_FILES")

####################################################################################################
# Set header files
set(GAME_LEVELS_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/GameLevel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/TestLevel.hpp

    CACHE INTERNAL "GAME_LEVELS_HEADER_FILES")

####################################################################################################
# Set include dirs
set(GAME_LEVELS_INCLUDE_DIRS

    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "GAME_LEVELS_INCLUDE_DIRS")