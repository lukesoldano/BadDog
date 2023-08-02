message("%% Entering Entities")

####################################################################################################
# Set source files
set(ENTITES_SOURCE_FILES

   ${CMAKE_CURRENT_LIST_DIR}/EntityIdManager.cpp

    CACHE INTERNAL "ENTITES_SOURCE_FILES")

####################################################################################################
# Set header files
set(ENTITES_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/EntityIdManager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/EntityUtilities.hpp
    ${CMAKE_CURRENT_LIST_DIR}/EntityTypes.hpp

    CACHE INTERNAL "ENTITES_HEADER_FILES")

####################################################################################################
# Set include dirs
set(ENTITES_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "ENTITES_INCLUDE_DIRS")