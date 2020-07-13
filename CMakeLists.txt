cmake_minimum_required(VERSION 3.17)
project(Battleships CXX)

set(CMAKE_CXX_STANDARD 14)

# location of source code files
include_directories(${CMAKE_SOURCE_DIR})

# tell cmake where to put the executables that it creates
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin) 

# where to put the object files it creates
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/lib)

add_library(
	grid
	grid.h
	grid.cpp
)

add_library(
	gridLocation
	gridLocation.h
	gridLocation.cpp
)

add_library(
	ship
	ship.h
	ship.cpp
)

target_link_libraries(ship gridLocation)