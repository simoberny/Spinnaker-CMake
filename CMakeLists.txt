cmake_minimum_required(VERSION 3.10)
project(spinnakerExamples)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory(examples/aquisition)
add_subdirectory(examples/listCameras)