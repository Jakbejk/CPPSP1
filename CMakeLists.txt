cmake_minimum_required(VERSION 3.26)
project(SP1)

set(CMAKE_CXX_STANDARD 20)

add_executable(SP1 src/main.cpp
        src/BufferedWriter.h
        src/BufferedReader.h
        src/Shape.h
        src/Canvas.h
        src/SVGCanvas.h
        src/Utils.h
        src/PmgCanvas.h
        src/Position.h
)
