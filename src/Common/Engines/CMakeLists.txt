message("%% Entering Engines")

####################################################################################################
# Set source files
set(ENGINES_SOURCE_FILES

    CACHE INTERNAL "ENGINES_SOURCE_FILES")

####################################################################################################
# Set header files
set(ENGINES_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/IEngine.hpp

    CACHE INTERNAL "ENGINES_HEADER_FILES")

####################################################################################################
# Set include dirs
set(ENGINES_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "ENGINES_INCLUDE_DIRS")