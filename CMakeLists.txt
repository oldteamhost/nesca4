cmake_minimum_required(VERSION 3.18.4)
project(nesca4)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)
link_directories(lib/platform/linux)
file(GLOB SRCS src/*.cc)
add_executable(nesca4 ${SRCS})
target_link_libraries(nesca4 curl pthread boost_system boost_thread hcnetsdk)

# set(CMAKE_CXX_FLAGS "-g")


