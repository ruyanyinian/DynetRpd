cmake_minimum_required(VERSION 3.10)
project(dynet)
set(CMAKE_CXX_STANDARD 11)
<<<<<<< HEAD
add_library(init SHARED ${CMAKE_CURRENT_SOURCE_DIR}/dynet/init.cpp)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/dynet/example.cpp)
target_link_libraries(${PROJECT_NAME} init)
target_include_directories(init PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
=======
# add_library(init SHARED ${CMAKE_CURRENT_SOURCE_DIR}/dynet/init.cpp)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/dynet/example.cpp)
# target_link_libraries(${PROJECT_NAME} PRIVATE init)
# target_include_directories(init PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


>>>>>>> e793a8ce8a2990aa03e1a0e5f32bb00214db72cb
