message("%% Entering Utilities")

####################################################################################################
# Set source files
set(UTILITIES_SOURCE_FILES

    CACHE INTERNAL "UTILITIES_SOURCE_FILES")

####################################################################################################
# Set header files
set(UTILITIES_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/ExtendedOptional.hpp

    CACHE INTERNAL "UTILITIES_HEADER_FILES")

####################################################################################################
# Set include dirs
set(UTILITIES_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "UTILITIES_INCLUDE_DIRS")