cmake_minimum_required(VERSION 3.18.4)
project(nesca4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-g")

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
    "CMakeCache.txt;CMakeFiles;Makefile;cmake_install.cmake")

include_directories(lib)
link_directories(lib/platform/linux)

file(GLOB SRCS *.cc)
file(GLOB MODULE_SRCS modules/src/*.cc)
file(GLOB PLUS_NCSOCK_SRCS ncsock/src/*.cc)

file(GLOB C_NCSOCK_SRCS ncsock/src/*.c)
file(GLOB C_NCPING_SRCS ncping/src/*.c)

add_executable(nesca4 ${SRCS} ${C_NCPING_SRCS} ${C_NCSOCK_SRCS} ${PLUS_NCSOCK_SRCS} ${MODULE_SRCS})
target_link_libraries(nesca4 curl pthread hcnetsdk ssh)

