cmake_minimum_required(VERSION 3.27)
project(improve-cpp17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(practice before.cpp)
add_executable(practice thread_muti.cpp)
