cmake_minimum_required(VERSION 3.26)
project(Tetris2_0)

find_package(OpenCV REQUIRED)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS
        src/*.cpp
        include/*.hpp
)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tetris2_0 ${sources}
        include/Color.hpp)

target_include_directories(Tetris2_0 PRIVATE src include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(Tetris2_0 PRIVATE ${OpenCV_LIBRARIES})