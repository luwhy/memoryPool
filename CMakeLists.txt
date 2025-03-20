cmake_minimum_required(VERSION 3.0)

project(memoryPool)
set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

add_library(mPool SHARED ${SRC})

add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cc)
add_dependencies(test mPool)
target_link_libraries(test public mPool)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)