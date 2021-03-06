cmake_minimum_required(VERSION 3.10)

project(LearnOpenGL)

configure_file(src/helpers/root_dir.h.in src/helpers/root_dir.h)
include_directories(${CMAKE_BINARY_DIR}/src/helpers)
include_directories(${CMAKE_BINARY_DIR}/src/shaders)
include_directories(${CMAKE_BINARY_DIR}/src/model_loading)
include_directories(third_party)

include(third_party/build_files/common_packages.cmake)

set(TARGET_NAME LearnOpenGL)


add_executable(${TARGET_NAME} 
        src/main.cpp
        src/shaders/shader.cpp
        src/shaders/shader.hpp
        src/camera/camera.cpp
        src/camera/camera.hpp
        src/model_loading/mesh.cpp
        src/model_loading/mesh.hpp
        src/model_loading/model.cpp
        src/model_loading/model.hpp
        )

# set target properties
include(third_party/build_files/common_target.cmake)