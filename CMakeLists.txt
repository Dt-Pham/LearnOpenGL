cmake_minimum_required(VERSION 3.10)

project(LearnOpenGL)

include(third_party/build_files/common_packages.cmake)

set(TARGET_NAME LearnOpenGL)


add_executable(${TARGET_NAME} 
        src/main.cpp)

# set target properties
include(third_party/build_files/common_target.cmake)