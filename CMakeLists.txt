cmake_minimum_required(VERSION 3.10)
project(IsingModel2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(OBJ_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/obj)


include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(Ising2D ${SOURCES})

install(TARGETS Ising2D DESTINATION ${OBJ_OUTPUT_PATH})