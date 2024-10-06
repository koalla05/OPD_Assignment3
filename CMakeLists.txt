cmake_minimum_required(VERSION 3.28)
project(OPD_Assignment3)

set(CMAKE_CXX_STANDARD 17)

add_executable(OPD_Assignment3 main.cpp
        Figure.h
        Board.h
        Grid.h
        Board.cpp
        Triangle.cpp
        Line.cpp
        Square.cpp
        Circle.cpp
)
