cmake_minimum_required(VERSION 3.23)
project(sippo)

set(CMAKE_CXX_STANDARD 14)

include_directories(task_no1)

add_executable(sippo
        task_no1/Point2D.h
        task_no1/QuadraticInterpolation.cpp
        task_no1/QuadraticInterpolation.h
        task_no1/Test.cpp)

add_executable(Test task_no1/Test.cpp)