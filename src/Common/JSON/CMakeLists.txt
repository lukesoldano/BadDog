message("%% Entering JSON")

####################################################################################################
# Set source files
set(JSON_PARSING_SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/JsonFileReader.cpp

    CACHE INTERNAL "JSON_SOURCE_FILES")

####################################################################################################
# Set header files
set(JSON_PARSING_HEADER_FILES
    ${CMAKE_CURRENT_LIST_DIR}/JsonFileReader.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JsonTypes.hpp

    CACHE INTERNAL "JSON_HEADER_FILES")

####################################################################################################
# Set include dirs
set(JSON_PARSING_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "JSON_INCLUDE_DIRS")