cmake_minimum_required(VERSION 3.10)
project(dynet)
set(CMAKE_CXX_STANDARD 11)
# add_library(init SHARED ${CMAKE_CURRENT_SOURCE_DIR}/dynet/init.cpp)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/dynet/dim.cpp)
# target_link_libraries(${PROJECT_NAME} PRIVATE init)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


