cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project(denoising)

include_directories(include)

set(DENOISING 
src/main.cpp
include/PlyParser.hpp
src/PlyParser.cpp)


add_executable(denoise ${DENOISING})




