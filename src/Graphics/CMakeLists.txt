message("%% Entering Graphics")

####################################################################################################
# Set source files
set(GRAPHICS_SOURCE_FILES

   #  ${CMAKE_CURRENT_LIST_DIR}/Camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GraphicsEngine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Renderer.cpp
   #  ${CMAKE_CURRENT_LIST_DIR}/Surface.cpp
   #  ${CMAKE_CURRENT_LIST_DIR}/Texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Window.cpp

    CACHE INTERNAL "GRAPHICS_SOURCE_FILES")

####################################################################################################
# Set header files
set(GRAPHICS_HEADER_FILES

   #  ${CMAKE_CURRENT_LIST_DIR}/Camera.hpp
    ${CMAKE_CURRENT_LIST_DIR}/GraphicsEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Renderer.hpp    
   #  ${CMAKE_CURRENT_LIST_DIR}/SpriteSheet.hpp
   #  ${CMAKE_CURRENT_LIST_DIR}/Surface.hpp
   #  ${CMAKE_CURRENT_LIST_DIR}/Texture.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Window.hpp

    CACHE INTERNAL "GRAPHICS_HEADER_FILES")

####################################################################################################
# Set include dirs
set(GRAPHICS_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}

    CACHE INTERNAL "GRAPHICS_INCLUDE_DIRS")