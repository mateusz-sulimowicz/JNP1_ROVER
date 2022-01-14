cmake_minimum_required(VERSION 3.21)
project(rover)

set(CMAKE_CXX_STANDARD 20)

add_executable(rover main.cpp sensor.h rover.h command.h instruction.h position.h)
