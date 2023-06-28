message("%% Entering GetDependencies.cmake")

####################################################################################################
# Declare dependency versions
## https://github.com/libsdl-org/SDL/releases/tag/release-2.24.0
set(SDL2_RELEASE_VERSION "2.24.0")

## https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.2
set(SDL2_IMAGE_RELEASE_VERSION "2.6.2")

####################################################################################################
# Include for dynamically pulling dependencies
include(FetchContent)

####################################################################################################
# SDL2
## Pull library
FetchContent_Declare(SDL2
                     URL "https://github.com/libsdl-org/SDL/archive/refs/tags/release-${SDL2_RELEASE_VERSION}.zip")
FetchContent_MakeAvailable(SDL2)

# Prepare dependency variables
set(SDL2_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl2-src/include)
set(SDL2_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl2-build/Debug)
set(SDL2_LIBRARIES 
    ${SDL2_LIBRARY_DIR}/SDL2d.lib
    ${SDL2_LIBRARY_DIR}/SDL2maind.lib)

####################################################################################################
# SDL Image2
## Configure options for library
option(SDL2IMAGE_INSTALL "" OFF)
option(SDL2IMAGE_AVIF "" OFF) 
option(SDL2IMAGE_BMP "" OFF)
option(SDL2IMAGE_GIF "" OFF)
option(SDL2IMAGE_JPG "" ON) 
option(SDL2IMAGE_JXL "" OFF)
option(SDL2IMAGE_LBM "" OFF)
option(SDL2IMAGE_PCX "" OFF)
option(SDL2IMAGE_PNG "" ON)
option(SDL2IMAGE_PNM "" OFF)
option(SDL2IMAGE_QOI "" OFF)
option(SDL2IMAGE_SVG "" OFF)
option(SDL2IMAGE_TGA "" OFF)
option(SDL2IMAGE_TIF "" OFF) 
option(SDL2IMAGE_WEBP "" OFF)
option(SDL2IMAGE_XCF "" OFF)
option(SDL2IMAGE_XPM "" OFF)
option(SDL2IMAGE_XV "" OFF)

## Pull library
FetchContent_Declare(SDL2_IMAGE
                     URL "https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-${SDL2_IMAGE_RELEASE_VERSION}.zip")
FetchContent_MakeAvailable(SDL2_IMAGE)

# Prepare dependency variables
set(SDL2_IMAGE_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl2_image-src)
set(SDL2_IMAGE_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl2_image-build/Debug)
set(SDL2_IMAGE_LIBRARIES  ${SDL2_IMAGE_LIBRARY_DIR}/SDL2_imaged.lib)

####################################################################################################
# Set overall project dependency variables
set(${PROJECT_NAME}_DEPENDENCY_INCLUDE_DIRS

    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    
    CACHE INTERNAL "${PROJECT_NAME}_DEPENDENCY_INCLUDE_DIRS")

set(${PROJECT_NAME}_DEPENDENCY_LIBRARIES

    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    
    CACHE INTERNAL "${PROJECT_NAME}_DEPENDENCY_LIBRARIES")
