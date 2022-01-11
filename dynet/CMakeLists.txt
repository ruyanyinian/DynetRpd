# ########## dynet library ##########
# Sources:

set(dynet_library_SRCS
    devices.cpp
    tensor.cpp
)

# Headers:
set(dynet_library_HDRS
    devices.hpp
    tensor.hpp
)

# build CPU library
add_library(dynet ${dynet_library_SRCS})
