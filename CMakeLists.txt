cmake_minimum_required (VERSION 2.6)

# Add project
project (rt)

SET(SFML_ROOT "C:/Program Files (x86)/Maze Reload/SFML" CACHE PATH "Path to SFML root directory")
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
#SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED System window graphics audio)
find_package(JSONCPP REQUIRED)

# Include headers directory
include_directories (includes)

# Create a variable containing sources files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(rt ${SOURCES})

# Compile with c++11
target_compile_features (rt PRIVATE cxx_range_for)

if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wextra")
endif()

if (SFML_FOUND)
    if (JSONCPP_FOUND)
        # Link SFML Include DIR
        include_directories(${SFML_INCLUDE_DIR} ${JSONCPP_INCLUDE_DIR})
        # Link the lib to the binary.
        target_link_libraries(rt ${SFML_LIBRARIES} ${JSONCPP_LIBRARY})
    endif (JSONCPP_FOUND)
endif (SFML_FOUND)
