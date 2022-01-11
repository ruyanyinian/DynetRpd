# ########## dynet library ##########
# Sources:

set(dynet_library_SRCS
    devices.cpp
)

# Headers:
set(dynet_library_HDRS
    devices.hpp
)
set(BUILD_SHARED_LIBS ON)
message(STATUS "the dynet libs are ${LIBS}")
# build CPU library
add_library(dynet ${dynet_library_SRCS} ${dynet_library_HDRS})
# target_link_libraries(dynet ${LIBS})

# message(STATUS ${CMAKE_CURRENT_SOURCE_DIR}/${dynet_library_HDRS})
# target_link_libraries(dynet ${LIBS})
# install(FILES ${dynet_library_HDRS} DESTINATION include/dynet)
# install(TARGETS dynet DESTINATION lib)