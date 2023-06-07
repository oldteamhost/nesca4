cmake_minimum_required(VERSION 3.18.4)
project(nesca4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-g")

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
    "CMakeCache.txt;CMakeFiles;Makefile;cmake_install.cmake")

include_directories(lib)
link_directories(lib/platform/linux)

file(GLOB SRCS src/*.cc)
file(GLOB C_SRCS ncsock/src/*.c)
file(GLOB C_PING ncping/src/*.c)
file(GLOB MODULE_SRCS modules/src/*.cc)

add_executable(nesca4 ${SRCS} ${MODULE_SRCS} ${C_SRCS} ${C_PING})
target_link_libraries(nesca4 curl pthread hcnetsdk ssh)

