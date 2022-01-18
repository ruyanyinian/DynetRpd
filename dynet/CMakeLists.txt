# ########## dynet library ##########
# Sources:
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(dynet_library_SRCS
    devices.cpp
    tensor.cpp
)
message(STATUS ${PROJECT_SOURCE_DIR})
# Headers:
set(dynet_library_HDRS
    devices.hpp
    tensor.hpp
)

# build CPU library
add_library(dynet SHARED ${dynet_library_SRCS} ${dynet_library_HDRS})
get_filename_component(TOP_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_include_directories(dynet PRIVATE ${TOP_DIR})

# add_library(test SHARED ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)