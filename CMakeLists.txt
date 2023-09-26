cmake_minimum_required(VERSION 3.26)
project(SP1)

set(CMAKE_CXX_STANDARD 20)

add_executable(SP1 main.cpp
        BufferedWriter.h
        BufferedReader.h
        Shape.h
        Canvas.h
        SVGCanvas.h
        Utils.h
)
