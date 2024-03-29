####################################################################################################
# Fundamental project setup
cmake_minimum_required(VERSION 3.23)
set(PROJECT_NAME "BadDog")
message("%% Entering ${PROJECT_NAME} cmake project")
project(${PROJECT_NAME})

####################################################################################################
# List and handle project options
## Enables message logging
option(MESSAGE_LOGGING "Allow message ${PROJECT_NAME} logging" ON)
message("%% MESSAGE_LOGGING set to ${MESSAGE_LOGGING}")
add_definitions(-DMESSAGE_LOGGING=$<BOOL:${MESSAGE_LOGGING}>)

## Enables warning logging
option(WARNING_LOGGING "Allow warning ${PROJECT_NAME} logging" ON)
message("%% WARNING_LOGGING set to ${WARNING_LOGGING}")
add_definitions(-DWARNING_LOGGING=$<BOOL:${WARNING_LOGGING}>)

## Enables error logging
option(ERROR_LOGGING "Allow error ${PROJECT_NAME} logging" ON)
message("%% ERROR_LOGGING set to ${ERROR_LOGGING}")
add_definitions(-DERROR_LOGGING=$<BOOL:${ERROR_LOGGING}>)

## Enables verbose logging
option(VERBOSE_LOGGING "Allow verbose ${PROJECT_NAME} logging" OFF)
message("%% VERBOSE_LOGGING set to ${VERBOSE_LOGGING}")
add_definitions(-DVERBOSE_LOGGING=$<BOOL:${VERBOSE_LOGGING}>)

## Turns off all logging
option(SILENCE_LOGGING "Silence ${PROJECT_NAME} logging" OFF)
message("%% SILENCE_LOGGING set to ${SILENCE_LOGGING}")
add_definitions(-DSILENCE_LOGGING=$<BOOL:${SILENCE_LOGGING}>)

## Enables unit testing in build
option(BUILD_UNIT_TESTS "Build ${PROJECT_NAME} unit tests" ON)
message("%% BUILD_UNIT_TESTS set to ${BUILD_UNIT_TESTS}")

####################################################################################################
# Establish project standards
message("%% Using C++20")
set(CMAKE_CXX_STANDARD 20)

####################################################################################################
# Set compiler and linker flags
SET(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS}")

SET(CMAKE_EXE_LINKER_FLAGS 
    "${CMAKE_EXE_LINKER_FLAGS}")

####################################################################################################
# Make necessary inclusions and add relevant subdirectories
include(${CMAKE_CURRENT_LIST_DIR}/GetDependencies.cmake)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)

####################################################################################################
# Ensure known directories included to ensure flat file structure in source code includes
include_directories(${${PROJECT_NAME}_DEPENDENCY_INCLUDE_DIRS}
                    ${${PROJECT_NAME}_INCLUDE_DIRS})

####################################################################################################
# Add required definition
add_definitions(-DASSETS_DIRECTORY="${CMAKE_CURRENT_LIST_DIR}/assets"
                -DJSON_ASSETS_DIRECTORY="${CMAKE_CURRENT_LIST_DIR}/assets/JSON"
                -DJSON_LEVEL_ASSETS_DIRECTORY="${CMAKE_CURRENT_LIST_DIR}/assets/JSON/Levels")

####################################################################################################
# Make source code a static library that can be linked to, link it to dependencies
set(PROJECT_SOURCE_LIB_NAME ${PROJECT_NAME}_Lib)
add_library(${PROJECT_SOURCE_LIB_NAME}
            STATIC
            ${${PROJECT_NAME}_SOURCE_FILES}
            ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${PROJECT_NAME}_Lib
                      ${${PROJECT_NAME}_DEPENDENCY_LIBRARIES})

####################################################################################################
# Create executable and make necessary library linkages
add_executable(${PROJECT_NAME} 
               ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)
target_link_libraries(${PROJECT_NAME} 
                      ${PROJECT_SOURCE_LIB_NAME}
                      ${${PROJECT_NAME}_DEPENDENCY_LIBRARIES})

####################################################################################################
# Specify custom build steps
## Move the SDL.dll into the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   ${SDL2_LIBRARY_DIR}/SDL2d.dll
                   ${CMAKE_CURRENT_BINARY_DIR}/Debug)

## Move the SDL2_image.dll into the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   ${SDL2_IMAGE_LIBRARY_DIR}/SDL2_imaged.dll
                   ${CMAKE_CURRENT_BINARY_DIR}/Debug)

# ## Move the SDL2_ttf.dll into the build directory
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                    ${SDL2_TTF_LIBRARY_DIR}/SDL2_ttfd.dll
#                    ${CMAKE_CURRENT_BINARY_DIR}/Debug)

####################################################################################################
# Add unit tests if specified
if (BUILD_UNIT_TESTS)
   add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests)
endif ()