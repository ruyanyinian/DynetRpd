# ########## dynet library ##########
# Sources:
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(dynet_library_SRCS
    tensor.cpp
    devices.cpp
    aligned-mem-pool.cpp
    mem.cpp
    dim.cpp
    globals.cpp)

message(STATUS ${PROJECT_SOURCE_DIR})


# build CPU library
message(STATUS ${dynet_library_SRCS})
message(STATUS ${LIBRARY_OUTPUT_PATH})

add_library(tensor SHARED ${dynet_library_SRCS})
get_filename_component(LAST_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_include_directories(tensor PRIVATE ${LAST_DIR})
