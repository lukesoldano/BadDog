message("%% Entering GetDependencies.cmake")

####################################################################################################
# Include for dynamically pulling dependencies
include(FetchContent)

####################################################################################################
# SDL2
## Pull library
FetchContent_Declare(SDL2
                     GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
                     GIT_TAG "adf31f6ec0be0f9ba562889398f71172c7941023")
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
                     GIT_REPOSITORY "https://github.com/libsdl-org/SDL_image.git"
                     GIT_TAG "d3c6d5963dbe438bcae0e2b6f3d7cfea23d02829")
FetchContent_MakeAvailable(SDL2_IMAGE)

# Prepare dependency variables
set(SDL2_IMAGE_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl2_image-src)
set(SDL2_IMAGE_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl2_image-build/Debug)
set(SDL2_IMAGE_LIBRARIES  ${SDL2_IMAGE_LIBRARY_DIR}/SDL2_imaged.lib)

####################################################################################################
# # SDL TTF
# ## Configure options for library
# set(SDL2TTF_INSTALL "" OFF)

# ## Pull library
# FetchContent_Declare(SDL2_TTF
#                      GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf.git"
#                      GIT_TAG "89d1692fd8fe91a679bb943d377bfbd709b52c23")
# FetchContent_MakeAvailable(SDL2_TTF)

# # Prepare dependency variables
# set(SDL2TTF_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl2_ttf-src/include)
# set(SDL2TTF_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl2_ttf-build/Debug)
# set(SDL2TTF_LIBRARIES ${SDL2_LIBRARY_DIR}/SDL2_ttfd.lib)

####################################################################################################
# Set overall project dependency variables
set(${PROJECT_NAME}_DEPENDENCY_INCLUDE_DIRS

    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
   #  ${SDL2TTF_INCLUDE_DIRS}
    
    CACHE INTERNAL "${PROJECT_NAME}_DEPENDENCY_INCLUDE_DIRS")

set(${PROJECT_NAME}_DEPENDENCY_LIBRARIES

    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
   #  ${SDL2TTF_LIBRARIES}
    
    CACHE INTERNAL "${PROJECT_NAME}_DEPENDENCY_LIBRARIES")
