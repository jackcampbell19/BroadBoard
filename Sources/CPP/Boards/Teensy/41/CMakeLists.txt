cmake_minimum_required(VERSION 3.28)
project(BroadBoard CXX C ASM)

set(CMAKE_CXX_STANDARD 17)

add_executable(BroadBoard
        BroadBoard.cpp
        ../../../Drivers/Stepper.cpp
        ../../../Drivers/MotorDriver.cpp
)

target_include_directories(BroadBoard PUBLIC
        ../../../Core
        ../../../Drivers
)
