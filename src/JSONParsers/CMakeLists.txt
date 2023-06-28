message("%% Entering JSONParser")

####################################################################################################
# Set source files
set(JSON_PARSER_SOURCE_FILES

   ${CMAKE_CURRENT_LIST_DIR}/JsonDefs.cpp
   ${CMAKE_CURRENT_LIST_DIR}/JsonLevelParser.cpp

    CACHE INTERNAL "JSON_PARSER_SOURCE_FILES")

####################################################################################################
# Set header files
set(JSON_PARSER_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/JsonDefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JsonFileReader.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JsonLevelParser.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JsonUtilities.hpp

    CACHE INTERNAL "JSON_PARSER_HEADER_FILES")

####################################################################################################
# Set include dirs
set(JSON_PARSER_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "JSON_PARSER_INCLUDE_DIRS")