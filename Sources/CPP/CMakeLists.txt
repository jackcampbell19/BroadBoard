cmake_minimum_required(VERSION 3.28)
project(BroadBoard CXX C ASM)

set(CMAKE_CXX_STANDARD 17)

add_library(BroadBoard STATIC
    <board-path>/BroadBoard.cpp
)

target_include_directories(BroadBoard PUBLIC
        Core
)
