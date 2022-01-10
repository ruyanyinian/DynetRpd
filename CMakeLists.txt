cmake_minimum_required(VERSION 3.10)
project(dynet)
set(CMAKE_CXX_STANDARD 11)
# add_library(dim SHARED ${CMAKE_CURRENT_SOURCE_DIR}/dynet/dim.cpp)
add_executable(${PROJECT_NAME}  ${CMAKE_CURRENT_SOURCE_DIR}/exec.cpp)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/exec.hpp)
target_include_directories(${PROJECT_NAME} PRIVATE "~/third_party/eigen/")
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dynet)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(${PROJECT_NAME} PRIVATE dim)


