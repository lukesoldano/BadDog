message("%% Entering Common")

####################################################################################################
# Make necessary inclusions and add relevant subdirectories
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Utilities)

####################################################################################################
# Set source files
set(COMMON_SOURCE_FILES
    ${UTILITIES_SOURCE_FILES}

    CACHE INTERNAL "COMMON_SOURCE_FILES")

####################################################################################################
# Set header files
set(COMMON_HEADER_FILES
    ${UTILITIES_HEADER_FILES}

    ${CMAKE_CURRENT_LIST_DIR}/ILogicEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ProjectDefs.hpp

    CACHE INTERNAL "COMMON_HEADER_FILES")

####################################################################################################
# Set include dirs
set(COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${UTILITIES_INCLUDE_DIRS}

    CACHE INTERNAL "COMMON_INCLUDE_DIRS")