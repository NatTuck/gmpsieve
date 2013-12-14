cmake_minimum_required(VERSION 2.5)

project(mpisieve)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)
SET(CMAKE_CXX_FLAGS "-g -Wall -DDEBUG")

add_subdirectory(src)
