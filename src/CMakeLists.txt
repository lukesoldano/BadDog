message("%% Entering src")

####################################################################################################
# Make necessary inclusions and add relevant subdirectories
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/ControlScheme)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Command)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Common)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Graphics)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Logging)

####################################################################################################
# Set source files
set(${PROJECT_NAME}_SOURCE_FILES
    ${CONTROL_SCHEME_SOURCE_FILES}
    ${COMMAND_SOURCE_FILES}
    ${COMMON_SOURCE_FILES}
    ${GRAPHICS_SOURCE_FILES}
    ${LOGGING_SOURCE_FILES}
    
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ProjectDefs.cpp

    CACHE INTERNAL "${PROJECT_NAME}_SOURCE_FILES")

####################################################################################################
# Set header files
set(${PROJECT_NAME}_HEADER_FILES
    ${CONTROL_SCHEME_HEADER_FILES}
    ${COMMAND_HEADER_FILES}
    ${COMMON_HEADER_FILES}
    ${GRAPHICS_HEADER_FILES}
    ${LOGGING_HEADER_FILES}

    ${CMAKE_CURRENT_LIST_DIR}/ProjectDefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/GlobalState.hpp

    CACHE INTERNAL "${PROJECT_NAME}_HEADER_FILES")

####################################################################################################
# Set include dirs
set(${PROJECT_NAME}_INCLUDE_DIRS
    ${CONTROL_SCHEME_INCLUDE_DIRS}
    ${COMMAND_INCLUDE_DIRS}
    ${COMMON_INCLUDE_DIRS}
    ${GRAPHICS_INCLUDE_DIRS}
    ${LOGGING_INCLUDE_DIRS}

    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "${PROJECT_NAME}_INCLUDE_DIRS")