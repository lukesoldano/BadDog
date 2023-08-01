####################################################################################################
# Set up unit test project
message("%% Entering ${PROJECT_NAME} tests (UNIT TESTING ENABLED)")
set(TEST_PROJECT_NAME ${PROJECT_NAME}_tests)
project(${TEST_PROJECT_NAME})

####################################################################################################
# Pull in GTest and setup environment
# For more, see: https://github.com/google/googletest/blob/main/googletest/README.md
include(FetchContent)
FetchContent_Declare(
   googletest
   URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing and setup tests
enable_testing()

####################################################################################################
# Create test executable
add_executable(${TEST_PROJECT_NAME}
               ${CMAKE_CURRENT_LIST_DIR}/TestUtilities.cpp
               ${CMAKE_CURRENT_LIST_DIR}/TestQueues.cpp
               ${CMAKE_CURRENT_LIST_DIR}/TestEventPublisher.cpp
               # ${CMAKE_CURRENT_LIST_DIR}/TestCamera.cpp
               # ${CMAKE_CURRENT_LIST_DIR}/TestCollisionDetector.cpp
               # ${CMAKE_CURRENT_LIST_DIR}/TestSpatialHashMap.cpp
               # ${CMAKE_CURRENT_LIST_DIR}/TestJsonParsers.cpp
               # ${CMAKE_CURRENT_LIST_DIR}/TestGameLevel.cpp
               ${CMAKE_CURRENT_LIST_DIR}/TestEntityIdManager.cpp
               ${CMAKE_CURRENT_LIST_DIR}/TestGameState.cpp
               ${CMAKE_CURRENT_LIST_DIR}/TestGameEngine.cpp
)

target_link_libraries(${TEST_PROJECT_NAME}
                      ${PROJECT_SOURCE_LIB_NAME}
                      ${${PROJECT_NAME}_DEPENDENCY_LIBRARIES}
                      gtest 
                      gtest_main)

target_include_directories(${TEST_PROJECT_NAME}
                           PRIVATE 
                           ${${PROJECT_NAME}_DEPENDENCY_INCLUDE_DIRS}
                           ${${PROJECT_NAME}_INCLUDE_DIRS})

add_test(NAME ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})

####################################################################################################
# Specify custom build steps
## Move the gmockd.dll into the build directory
add_custom_command(TARGET ${TEST_PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   ${CMAKE_CURRENT_BINARY_DIR}/../bin/Debug/gtestd.dll
                   ${CMAKE_CURRENT_BINARY_DIR}/Debug)

## Move the SDL2_image.dll into the build directory
add_custom_command(TARGET ${TEST_PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   ${CMAKE_CURRENT_BINARY_DIR}/../bin/Debug/gtest_maind.dll
                   ${CMAKE_CURRENT_BINARY_DIR}/Debug)

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