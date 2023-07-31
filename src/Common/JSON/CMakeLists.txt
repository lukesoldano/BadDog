message("%% Entering JSONParser")

####################################################################################################
# Set source files
set(JSON_SOURCE_FILES

    CACHE INTERNAL "JSON_SOURCE_FILES")

####################################################################################################
# Set header files
set(JSON_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/JsonDefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JsonFileReader.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JsonUtilities.hpp

    CACHE INTERNAL "JSON_HEADER_FILES")

####################################################################################################
# Set include dirs
set(JSON_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "JSON_INCLUDE_DIRS")