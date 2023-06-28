message("%% Entering UserInput")

####################################################################################################
# Set source files
set(USER_INPUT_SOURCE_FILES

    ${CMAKE_CURRENT_LIST_DIR}/UserInputEngine.cpp

    CACHE INTERNAL "USER_INPUT_SOURCE_FILES")

####################################################################################################
# Set header files
set(USER_INPUT_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/UserInputDefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/UserInputEngine.hpp

    CACHE INTERNAL "USER_INPUT_HEADER_FILES")

####################################################################################################
# Set include dirs
set(USER_INPUT_INCLUDE_DIRS

    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "USER_INPUT_INCLUDE_DIRS")