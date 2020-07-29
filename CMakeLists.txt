######################### START - CMake adapted from 4003CEM codio tasks taken as an example to build my files #########################
################################################################################################################################

cmake_minimum_required(VERSION 3.17)
project(Battleships CXX)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_VERBOSE_MAKEFILE ON) # Line taken from https://bytefreaks.net/programming-2/make-building-with-cmake-verbose  - Makes the build output more detailed

# location of source code files
include_directories(${CMAKE_SOURCE_DIR})

# tell cmake where to put the executables that it creates
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin) 

# where to put the object files it creates
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/lib)

add_library(
	textInterface
	textInterface.h
	textInterface.cpp
)

add_library(
	grid
	grid.h
	grid.cpp
)

add_library(
	ship
	ship.h
	ship.cpp
)

add_library(
	player
	player.h
	player.cpp
)

add_library(
	battleUserPlayer
	battleUserPlayer.h
	battleUserPlayer.cpp
)

add_library(
	playerVsPlayer
	playerVsPlayer.h
	playerVsPlayer.cpp
)

# CMake Documentation - https://cmake.org/cmake/help/v3.0/command/add_executable.html
add_executable(
    Game game.cpp
)

target_link_libraries(player ship grid battleUserPlayer)
target_link_libraries(battleUserPlayer player)
target_link_libraries(playerVsPlayer player)

target_link_libraries(Game playerVsPlayer textInterface)

################################################################################################################################
######################### END - CMake adapted from codio tasks taken as an example to build my files #########################