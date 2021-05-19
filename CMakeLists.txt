cmake_minimum_required(VERSION 3.13.4)

set(PROJECT_NAME libcsv)
project(${PROJECT_NAME} CXX)

add_library(libcsv INTERFACE)
target_include_directories(libcsv INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
