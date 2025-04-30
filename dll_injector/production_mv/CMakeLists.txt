cmake_minimum_required(VERSION 3.10)
project(TESTProgram)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
add_executable(Tester test.cpp)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")  # /MD
endif()

target_compile_options(Tester PRIVATE /Od) 