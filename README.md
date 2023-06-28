# Introduction
## What are we Making?
Still figuring that out, for now just trying to get the basics of game setup going so we can extrapolate on that and make a 2D Platformer game

# Building
## Platforms
Currently we have no expected limitations on platform/operating system, though we are thus far both developing on Windows machines and generally gearing things towards a keyboard & mouse environment. Stay tuned for updates there.

## Languages & Tools
* C/C++ for most core logic
* CMake for project setup and build tooling
* GoogleTest for project unit testing
* Python for build scripting and convenience tools
* Lua for in-game scripting
* JSON for file-based data formatting

## Dependencies
* C++20
* CMake 3.23+
* SDL2
* SDL2_image
* GoogleTest

## Instructions
1. Create build directory 'build' at same level as src, doc, tests AKA {PROJECT_PATH}
2. cd {PROJECT_PATH}/build
3. cmake ..
4. cmake --build ./

NOTE: See root level CMakeLists.txt for possible build options - EG: cmake -DBUILD_UNIT_TESTS=ON ..

## Known Issues
* The first attempt to cmake --build will fail, rerun the build to correct the issue
* Only debug builds supported currently
* Lots of platform specific CMake code at the moment

# Contributing
## Folks
* Luke Soldano, new game dev, experienced C++ guy
* Colby Simpson, another new game dev, new to C++ (and killing it)

## Style Guide
This is a loose style guide to follow for consistency. It is not the only way to do things.

* Use spaces, not tabs (three spaces for indentation)
* As much as possible limit any lines length to 100 characters
* Minimize indentations on class definitions, switch statements, etc - if you can use class/public, and switch/case on the same column that would be kewl
* Define a functions return value, name, and (at minimum) first input on a single line
   * Only template definitions and arguments after the first should be on separate lines
* Use #pragma once at the start of ever header file
* Prefer name-spacing feature set classes to reusing terms across numerous class definitions
* Class names should use camel case with capital letters, EG: MyClass
* Start class names with the letter "I" if they are an interface class with solely pure virtual functions EG: IMyInterfaceClass
* Function names should use underscore separated camel case EG: MyClass::some_func()
* Variable names should use underscores to separate words, EG: my_varx
* If a variable is a static, prefix it with 's ' if it is global 'g ' if it is a class member 'm', optionally if its an input, output, or input and output use 'i', 'o', or 'io' respectively 
   * Follow all letter prefixes with an underscore  EG: i_my_input
* Constants should follow the format of being entirely capitalized and underscore separated EG: MY_CONSTANT
* Minimize the use of if, while, for, and other enclosure statements that don't use curly braces, E.G. Minimize while(condition) func(); if(condition) doThing();
   * Obviously there are cases where statements like this can be helpful, but it should not be the general preference

# Thanks
Thanks to lazyfoo and their game development guide as it was immensely helpful in this process.

http://lazyfoo.net/SDL_tutorials/index.php

# Resources that Helped
