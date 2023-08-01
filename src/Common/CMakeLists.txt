message("%% Entering Common")

# ####################################################################################################
# # Make necessary inclusions and add relevant subdirectories
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Engines)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Entities)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Events)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Queues)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Logging)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Utilities)

####################################################################################################
# Set source files
set(COMMON_SOURCE_FILES
    ${ENGINES_SOURCE_FILES}
    ${ENTITES_SOURCE_FILES}
    ${EVENTS_SOURCE_FILES}
    ${LOGGING_SOURCE_FILES}
    ${QUEUES_SOURCE_FILES}
    ${UTILITIES_SOURCE_FILES}

    CACHE INTERNAL "COMMON_SOURCE_FILES")

####################################################################################################
# Set header files
set(COMMON_HEADER_FILES
    ${ENGINES_HEADER_FILES}
    ${ENTITES_HEADER_FILES}
    ${EVENTS_HEADER_FILES}
    ${LOGGING_HEADER_FILES}
    ${QUEUES_HEADER_FILES}
    ${UTILITIES_HEADER_FILES}

    ${CMAKE_CURRENT_LIST_DIR}/ProjectConcepts.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ProjectDefaults.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ProjectMacros.hpp

    CACHE INTERNAL "COMMON_HEADER_FILES")

####################################################################################################
# Set include dirs
set(COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    ${ENGINES_INCLUDE_DIRS}
    ${ENTITES_INCLUDE_DIRS}
    ${EVENTS_INCLUDE_DIRS}
    ${LOGGING_INCLUDE_DIRS}
    ${QUEUES_INCLUDE_DIRS}
    ${UTILITIES_INCLUDE_DIRS}

    CACHE INTERNAL "COMMON_INCLUDE_DIRS")