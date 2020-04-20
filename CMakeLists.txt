cmake_minimum_required(VERSION 3.15)
project(Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project src/headers/Point.h main.cpp src/sources/Point.cpp src/headers/Segment.h src/sources/Segment.cpp
        src/headers/Polygon.h src/headers/ConvexPolygon.h src/sources/Polygon.cpp src/sources/ConvexPolygon.cpp
        TestRunner.h include/LGeometry.h)