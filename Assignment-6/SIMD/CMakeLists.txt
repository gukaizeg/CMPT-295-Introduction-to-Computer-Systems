cmake_minimum_required(VERSION 3.2)
project(array_vec.bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -g -std=c++11 -O3 -Wall")


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/)

add_executable(array_vec.bin ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp 
                          ${CMAKE_CURRENT_SOURCE_DIR}/intrin.cpp 
                          ${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp 
                          ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(array_vec.bin pthread m)