# Introduction
## What are we Making?
Still figuring that out, for now just trying to get the basics of game setup going so we can extrapolate on that and make a 2D-Isometric game

# Building
## Platforms
Currently we have no expected limitations on platform/operating system, though we are thus far both developing on Windows machines and generally gearing things towards a keyboard & mouse environment. Stay tuned for updates there.

## Languages & Tools
* C/C++ for most core logic
* CMake for project setup and build tooling
* GoogleTest for project unit testing
* Python for build scripting and convenience tools
* JSON for file-based data formatting

## Dependencies
* C++20
* CMake 3.23+
* SDL2
* SDL2_image
* nlohmann JSON
* GoogleTest

## Instructions
1. Create build directory 'build' at same level as src, doc, tests AKA {PROJECT_PATH}
2. cd {PROJECT_PATH}/build
3. cmake ..
4. cmake --build ./

NOTE: See root level CMakeLists.txt for possible build options - EG: cmake -DBUILD_UNIT_TESTS=ON ..

## Known Issues
* Only debug builds supported currently
* Lots of platform specific CMake code at the moment

# Contributing
## Folks
* Luke Soldano, new game dev, experienced C++ guy

