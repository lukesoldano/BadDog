message("%% Entering Command")

####################################################################################################
# Set source files
set(COMMAND_SOURCE_FILES

    ${CMAKE_CURRENT_LIST_DIR}/InitJump.cpp
    ${CMAKE_CURRENT_LIST_DIR}/InitMoveRight.cpp
    ${CMAKE_CURRENT_LIST_DIR}/InitMoveLeft.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StopMoveRight.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StopMoveLeft.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NullCommand.cpp


    CACHE INTERNAL "COMMAND_SOURCE_FILES")

####################################################################################################
# Set header files
set(COMMAND_HEADER_FILES

    ${CMAKE_CURRENT_LIST_DIR}/Command.hpp
    ${CMAKE_CURRENT_LIST_DIR}/InitJump.hpp
    ${CMAKE_CURRENT_LIST_DIR}/InitMoveRight.hpp
    ${CMAKE_CURRENT_LIST_DIR}/InitMoveLeft.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StopMoveRight.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StopMoveLeft.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NullCommand.hpp

    CACHE INTERNAL "COMMAND_HEADER_FILES")

####################################################################################################
# Set include dirs
set(COMMAND_INCLUDE_DIRS

    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "COMMAND_INCLUDE_DIRS")