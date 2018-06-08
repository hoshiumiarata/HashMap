cmake_minimum_required(VERSION 2.8)
project(hashmap)

include_directories(include)
add_library(hashmap src/hashmap.c)

enable_testing()
add_subdirectory(test)