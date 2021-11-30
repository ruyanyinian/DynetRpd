cmake_minimum_required(VERSION 3.10)
project(dynet)
set(CMAKE_CXX_STANDARD 11)
add_library(init SHARED ${CMAKE_CURRENT_SOURCE_DIR}/dynet/init.cpp)
target_include_directories(init PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/dynet/example.cpp)
target_link_libraries(${PROJECT_NAME} init)

