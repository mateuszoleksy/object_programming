cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/c++.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/c++.exe")

project(object_programming VERSION 0.1.0 LANGUAGES C CXX)

include_directories(
        ${PROJECT_SOURCE_DIR}/movies
        ${PROJECT_SOURCE_DIR}/clients
)

add_executable(object_programming
        main.cpp
)

include_directories(${googletest_SOURCE_DIR}/googletest/include)
include_directories(${googletest_SOURCE_DIR}/googlemock/include)
add_subdirectory(tests)