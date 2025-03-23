# Project
This is a starter CMake project to use as a basis for any SFML project without needing to fiddle with XCode or Visual Studio. This is taken wholesale from the [SFML CMake Template](https://github.com/SFML/cmake-sfml-project) with minor modifications.

# Building

To build the project and generate a binary run the following in your command line from the root of the project:
```bash
cmake -B build
cmake --build build
```
In the lines above, the `-B` paramter allows [specify the path to the root build diectory](https://cmake.org/cmake/help/latest/manual/ccmake.1.html#cmdoption-ccmake-B) and the `--build` flag allows us to [specify where the project binary directory is to be built](https://cmake.org/cmake/help/latest/manual/cmake.1.html#cmdoption-cmake-build).

# Modifications

To access other SFML Libraries other than the default of graphics add a `target_link_libraries` line to the `CMakeLists.txt` file.

For more info on build flags and configurations see the [CMake Build Documentation](https://cmake.org/cmake/help/latest/manual/cmake.1.html#build-a-project).

# Resources
CMake:
- [CMake Examples](https://github.com/ttroy50/cmake-examples)
- [CMake Build Documentation](https://cmake.org/cmake/help/latest/manual/cmake.1.html#build-a-project)

SFML:
- [SFML CMake Project Template](https://github.com/SFML/cmake-sfml-project)
- [SFML 2D Documentation](https://www.sfml-dev.org/tutorials/3.0/graphics/draw/)
