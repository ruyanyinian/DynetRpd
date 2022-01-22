cmake_minimum_required(VERSION 3.10)
project(DynetReproduction)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(EIGEN3_INCLUDE_DIR "~/third_party/eigen/")
# include_directories(${EIGEN3_INCLUDE_DIR})
message(STATUS "the eigen libs are ${EIGEN3_INCLUDE_DIR}")
add_subdirectory(dynet)
add_executable(${PROJECT_NAME}  ${CMAKE_CURRENT_SOURCE_DIR}/exec.cpp)
target_link_libraries(${PROJECT_NAME} tensor)

target_include_directories(tensor PUBLIC ${EIGEN3_INCLUDE_DIR})
target_include_directories(tensor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# add include_dir to execuatable target.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})