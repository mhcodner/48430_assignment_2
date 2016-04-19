cmake_minimum_required(VERSION 3.5)
project(assignment_2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES studentlist.c)
add_executable(assignment_2 ${SOURCE_FILES})