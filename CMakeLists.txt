# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.28)

# Set the project name and language
project(MyProject LANGUAGES CXX)

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include the FetchContent module so we can fetch SFML Dependencies
# These will be downloaded at build time
include(FetchContent)

# Declares content details for SFML
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.0
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)

# This will actually populate the content, and add it to the main build
FetchContent_MakeAvailable(SFML)

# Create a SOURCES variable with a link to all cpp files to compile
# ADD NEW FILES HERE!!!!!
set(
  SOURCES
  src/main.cpp
  src/grid.cpp
  src/grid.hpp
  src/tile.cpp
  src/tile.hpp
  src/grid_color_manager.cpp
  src/grid_color_manager.hpp
  src/level_manager.cpp
  src/level_manager.hpp
  src/inventory_item.hpp
  src/inventory_item.cpp
  src/inventory_manager.hpp
  src/inventory_manager.cpp
  src/player.hpp
  src/player.cpp
)

# Add an executable with the above SOURCES
add_executable(main ${SOURCES})

# Create a RESOURCES variable with a link to all the resources to configure
# ADD NEW RESOURCES HERE!!!!!
set(
  RESOURCES
  res/level_config.txt
  res/objects_config.txt
)

# Copy file resources
foreach(RESOURCE_FILE ${RESOURCES})
  configure_file(${RESOURCE_FILE} ${RESOURCE_FILE} COPYONLY)
endforeach()

# Set compiler version for main project to C++ 17
target_compile_features(main PRIVATE cxx_std_17)

# Set directories that should be included in the build command for this target
# ADD OTHER SFML LIBS HERE AS NEEDED!!!!
target_link_libraries(main PRIVATE SFML::Graphics)
