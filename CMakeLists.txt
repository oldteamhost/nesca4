cmake_minimum_required(VERSION 3.18.4)
project(nesca4)

set(CMAKE_CXX_STANDARD 20)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
    "CMakeCache.txt;CMakeFiles;Makefile;cmake_install.cmake")

include_directories(lib)
link_directories(lib/platform/linux)
file(GLOB SRCS src/*.cc)
add_executable(nesca4 ${SRCS})
target_link_libraries(nesca4 curl pthread boost_system boost_thread hcnetsdk)

# set(CMAKE_CXX_FLAGS "-g")


