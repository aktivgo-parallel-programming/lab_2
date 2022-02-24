cmake_minimum_required(VERSION 3.21)
project(lab_2)

set(CMAKE_CXX_STANDARD 20)

include_directories(task1)
include_directories(task2)
include_directories(task3)
include_directories(task4)

add_executable(task1 task1/task1.cpp)
add_executable(task2 task2/task2.cpp)
add_executable(task3 task3/task3.cpp)
add_executable(task4 task4/task4.cpp)