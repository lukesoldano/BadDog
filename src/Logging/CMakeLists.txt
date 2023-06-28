message("%% Entering Logging")

####################################################################################################
# Set source files
set(LOGGING_SOURCE_FILES

    CACHE INTERNAL "LOGGING_SOURCE_FILES")

####################################################################################################
# Set header files
set(LOGGING_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/Logger.hpp

    CACHE INTERNAL "LOGGING_HEADER_FILES")

####################################################################################################
# Set include dirs
set(LOGGING_INCLUDE_DIRS

    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "LOGGING_INCLUDE_DIRS")