cmake_minimum_required(VERSION 3.10)
project(DynetRpd)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(EIGEN3_INCLUDE_DIR "~/third_party/eigen")
include_directories(${EIGEN3_INCLUDE_DIR})
message(STATUS "the eigen libs are ${EIGEN3_INCLUDE_DIR}")

add_subdirectory(dynet)

# target_include_directories(dynet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(${PROJECT_NAME} PRIVATE dynet)
# add_executable(${PROJECT_NAME}  ${CMAKE_CURRENT_SOURCE_DIR}/exec.cpp)