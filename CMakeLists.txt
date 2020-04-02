cmake_minimum_required(VERSION 3.1)
project(DelaunayTriangulation)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

set(DT_SOURCE_FILES
        src/DT/DelaunayTriangulation.cxx
        src/DT/Edge.cxx
        src/DT/Point.cxx
        src/DT/Predicates.c
        src/DT/Triangle.cxx
        src/DT/Timer.cxx
        src/DT/Vertex.cxx
        )

set(INTERFACE_SOURCE_FILES
        src/Interface/Args.cxx
        src/Interface/IO.cxx
        )

add_executable(delaunayTriangulation ./src/main.cxx ${INTERFACE_SOURCE_FILES} ${DT_SOURCE_FILES})
target_include_directories(delaunayTriangulation PUBLIC ./include/DT)
target_include_directories(delaunayTriangulation PUBLIC ./include/Interface)
