cmake_minimum_required(VERSION 3.18.4)
set(CMAKE_CXX_STANDARD 20)

project(nesca4)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
    "CMakeCache.txt;CMakeFiles;Makefile;cmake_install.cmake;resources/data")

include_directories(lib)
link_directories(lib/platform/linux)

file(GLOB SRCS *.cc)
file(GLOB MODULE_SRCS modules/*.cc)
file(GLOB PLUS_NCSOCK_SRCS ncsock/*.cc)

file(GLOB C_NCSOCK_SRCS ncsock/*.c)
file(GLOB PLUS_NCPING_SRCS ncping/*.cc)

add_executable(nesca4 ${SRCS} ${C_NCSOCK_SRCS} ${PLUS_NCSOCK_SRCS} ${MODULE_SRCS} ${PLUS_NCPING_SRCS})
target_link_libraries(nesca4 curl pthread hcnetsdk ssh)

