# ########## dynet library ##########
# Sources:

set(dynet_library_SRCS
    devices.cpp
)

# Headers:
set(dynet_library_HDRS
    devices.hpp
)

# build CPU library
add_library(dynet ${dynet_library_SRCS} ${dynet_library_HDRS})
install(FILES ${dynet_library_HDRS} DESTINATION include/dynet)
install(TARGETS dynet DESTINATION lib)
# target_link_libraries(dynet ${LIBS})