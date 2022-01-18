cmake_minimum_required(VERSION 3.10)
project(DynetReproduction)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(EIGEN3_INCLUDE_DIR "~/codes/third_party/eigen/")
include_directories(${EIGEN3_INCLUDE_DIR})
message(STATUS "the eigen libs are ${EIGEN3_INCLUDE_DIR}")
add_subdirectory(dynet)


