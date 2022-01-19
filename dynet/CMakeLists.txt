# ########## dynet library ##########
# Sources:
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(dynet_library_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/tensor.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/tensor.cpp
)
message(STATUS ${PROJECT_SOURCE_DIR})
# Headers:
# set(dynet_library_HDRS
#     devices.hpp
#     tensor.hpp
# )

# build CPU library
message(STATUS ${dynet_library_SRCS})
message(STATUS ${LIBRARY_OUTPUT_PATH})

add_library(dynet SHARED ${dynet_library_SRCS}) # FIXME: 为什么创建不了库?
get_filename_component(LAST_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_include_directories(dynet PRIVATE ${LAST_DIR})
