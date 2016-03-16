cmake_minimum_required (VERSION 2.6)

# Add project
project (rt)

# Locate all libraries
find_library(sfml_graphics_dir sfml-graphics)
find_library(sfml_window_dir sfml-window)
find_library(sfml_system_dir sfml-system)
find_library(jsoncpp_dir jsoncpp)

# Include headers directory
include_directories (includes)

# Create a variable containing sources files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(rt ${SOURCES})

# Compile with c++11
target_compile_features (rt PRIVATE cxx_range_for)

# Link to sfml and jsoncpp libraries to rt executable
target_link_libraries(rt LINK_PUBLIC ${sfml_graphics_dir} ${sfml_window_dir} ${sfml_system_dir} ${jsoncpp_dir})