project(leveldb_trace)
cmake_minimum_required(VERSION 2.8.10)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -o0")
# set(CMAKE_CXX_FLAGS_MINSIZEREL "put your flags")
# set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "put your flags")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -O2")

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(deps/leveldb)
include_directories(deps/leveldb/include)

add_executable(test01 test01_simpleput.cc)
target_link_libraries(test01 leveldb)