cmake_minimum_required (VERSION 2.6)
project (rt)

find_library(sfml_graphics_dir sfml-graphics)
find_library(sfml_window_dir sfml-window)
find_library(sfml_system_dir sfml-system)

find_library(jsoncpp_dir jsoncpp)

include_directories (includes)

file(GLOB SOURCES "src/*.cpp")

add_executable(rt ${SOURCES})

target_compile_features (rt PRIVATE cxx_range_for)
target_link_libraries(rt LINK_PUBLIC ${sfml_graphics_dir} ${sfml_window_dir} ${sfml_system_dir} ${jsoncpp_dir})