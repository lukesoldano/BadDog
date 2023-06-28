message("%% Entering Common")

####################################################################################################
# Set source files
set(COMMON_SOURCE_FILES

    CACHE INTERNAL "COMMON_SOURCE_FILES")

####################################################################################################
# Set header files
set(COMMON_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/CommonDefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/FileSystem.hpp

    CACHE INTERNAL "COMMON_HEADER_FILES")

####################################################################################################
# Set include dirs
set(COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "COMMON_INCLUDE_DIRS")