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

               ${${PROJECT_NAME}_SOURCE_FILES}
               ${${PROJECT_NAME}_HEADER_FILES}

               ${CMAKE_CURRENT_LIST_DIR}/TestGraphicsDefs.cpp
               ${CMAKE_CURRENT_LIST_DIR}/TestRenderer.cpp
               ${CMAKE_CURRENT_LIST_DIR}/TestSurface.cpp
               ${CMAKE_CURRENT_LIST_DIR}/TestTexture.cpp
               ${CMAKE_CURRENT_LIST_DIR}/TestWindow.cpp
)

target_link_libraries(${TEST_PROJECT_NAME}
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