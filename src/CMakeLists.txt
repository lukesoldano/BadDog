message("%% Entering src")

####################################################################################################
# Make necessary inclusions and add relevant subdirectories
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Common)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Game)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Gameplay)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Graphics)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/JSONParsers)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Logging)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Physics)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/UserInput)

####################################################################################################
# Set source files
set(${PROJECT_NAME}_SOURCE_FILES
    ${COMMON_SOURCE_FILES}
    ${GAME_SOURCE_FILES}
    ${GAMEPLAY_SOURCE_FILES}
    ${GRAPHICS_SOURCE_FILES}
    ${JSON_PARSER_SOURCE_FILES}
    ${LOGGING_SOURCE_FILES}
    ${PHYSICS_SOURCE_FILES}
    ${USER_INPUT_SOURCE_FILES}

    CACHE INTERNAL "${PROJECT_NAME}_SOURCE_FILES")

####################################################################################################
# Set header files
set(${PROJECT_NAME}_HEADER_FILES
    ${COMMON_HEADER_FILES}
    ${GAME_HEADER_FILES}
    ${GAMEPLAY_HEADER_FILES}
    ${GRAPHICS_HEADER_FILES}
    ${JSON_PARSER_HEADER_FILES}
    ${LOGGING_HEADER_FILES}
    ${PHYSICS_HEADER_FILES}
    ${USER_INPUT_HEADER_FILES}

    CACHE INTERNAL "${PROJECT_NAME}_HEADER_FILES")

####################################################################################################
# Set include dirs
set(${PROJECT_NAME}_INCLUDE_DIRS
    ${COMMON_INCLUDE_DIRS}
    ${GAME_INCLUDE_DIRS}
    ${GAMEPLAY_INCLUDE_DIRS}
    ${GRAPHICS_INCLUDE_DIRS}
    ${JSON_PARSER_INCLUDE_DIRS}
    ${LOGGING_INCLUDE_DIRS}
    ${PHYSICS_INCLUDE_DIRS}
    ${USER_INPUT_INCLUDE_DIRS}

    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "${PROJECT_NAME}_INCLUDE_DIRS")