cmake_minimum_required(VERSION 3.10)
project(flirAcquisition)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include(cotire)

find_package(Flir REQUIRED)

include_directories(${Flir_INCLUDE_DIRS})
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

file(GLOB allSources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(flirAcquisition ${allSources})
target_link_libraries(flirAcquisition ${Flir_LIBRARIES})
cotire(flirAcquisition)