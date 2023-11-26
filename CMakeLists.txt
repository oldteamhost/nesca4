cmake_minimum_required(VERSION 3.18.4)
set(CMAKE_CXX_STANDARD 20)

project(nesca4)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
    "CMakeCache.txt;CMakeFiles;Makefile;cmake_install.cmake;resources/data")

include_directories(lib)
link_directories(lib/platform/linux)

file(GLOB SRCS *.cc)
file(GLOB MODULE_SRCS modules/*.cc)
file(GLOB C_NCSOCK_SRCS ncsock/*.c)
file(GLOB C_NCBASE_SRCS ncbase/*.c)
file(GLOB C_DNET_SRCS ncsock/libdnet/*.c)

add_executable(nesca4 ${SRCS} ${C_NCSOCK_SRCS} ${MODULE_SRCS} ${C_NCBASE_SRCS} ${C_DNET_SRCS})
target_link_libraries(nesca4 pthread hcnetsdk)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
