message("%% Entering Common")

####################################################################################################
# Make necessary inclusions and add relevant subdirectories
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/EventPublisher)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Queues)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Utilities)

####################################################################################################
# Set source files
set(COMMON_SOURCE_FILES
    ${EVENT_PUBLISHER_SOURCE_FILES}
    ${QUEUES_SOURCE_FILES}
    ${UTILITIES_SOURCE_FILES}

    CACHE INTERNAL "COMMON_SOURCE_FILES")

####################################################################################################
# Set header files
set(COMMON_HEADER_FILES
    ${EVENT_PUBLISHER_HEADER_FILES}
    ${QUEUES_HEADER_FILES}
    ${UTILITIES_HEADER_FILES}

    ${CMAKE_CURRENT_LIST_DIR}/ILogicEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ProjectDefs.hpp

    CACHE INTERNAL "COMMON_HEADER_FILES")

####################################################################################################
# Set include dirs
set(COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${EVENT_PUBLISHER_INCLUDE_DIRS}
    ${QUEUES_INCLUDE_DIRS}
    ${UTILITIES_INCLUDE_DIRS}

    CACHE INTERNAL "COMMON_INCLUDE_DIRS")