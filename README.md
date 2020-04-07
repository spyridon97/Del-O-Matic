# Delaunay Triangulation

--------------------------------------------------------------------------------
## Description

Given a set of vertices, using the [Randomized Incremental Algorithm](http://www.cs.uu.nl/geobook/interpolation.pdf) we can Delaunay-triangulate it with complexity = O(n log n).

There is no warranty whatsoever. Use at your own risk.

--------------------------------------------------------------------------------
## Programming Language & Build System
* C++, (v17 or newer)
* CMAKE/CCMAKE, (v3.1 or newer)

--------------------------------------------------------------------------------
## Libraries
* Predicates, (v1.0.0) : [Routines for Arbitrary Precision Floating-vertex Arithmetic and Fast Robust Geometric Predicates](https://www.cs.cmu.edu/~quake/robust.html)
* CLI11, (V1.9.0) : [Command Line Parser for C++11 and above](https://github.com/CLIUtils/CLI11)

--------------------------------------------------------------------------------
## Structure of repository
*   include/src:
    *   This directory contains the header and sources files of the DelaunayTriangulation program.
*   .gitignore
    *   This file includes what git should ignore.
*   CmakeLists.txt
    *   This file defines the building properties of this Repository.
*   LICENCE
    *   The file which includes the GNU 3 Licence.
*   README.md            
    *   This file.

--------------------------------------------------------------------------------
## Installation & Compilation
* create a build directory inside the root of this project
* cd into the build directory
* `cmake  ..`

--------------------------------------------------------------------------------
## Input and Output files of PODM
Input files:
* [.node](http://www.cs.cmu.edu/~quake/triangle.node.html) which can be visualized using [ShowMe](http://www.cs.cmu.edu/~quake/showme.html).

Output files
* [.node](http://www.cs.cmu.edu/~quake/triangle.node.html) for the vertices of the triangulation, which can be visualized using [ShowMe](http://www.cs.cmu.edu/~quake/showme.html).
* [.ele](http://www.cs.cmu.edu/~quake/triangle.ele.html) for the triangles of the triangulation, which can be visualized using [ShowMe](http://www.cs.cmu.edu/~quake/showme.html).

--------------------------------------------------------------------------------
## Usage
```
DelaunayTriangulation
Usage: ./delaunayTriangulation [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -i,--input TEXT:FILE Excludes: --random
                              Input Vertices file to triangulate.
                              
  -r,--random UINT:POSITIVE Excludes: --input
                              Generates and uniformly random set of N 2D Vertices.
                              
  -p,--robust-predicates BOOLEAN
                              Uses Robust Predicates. '0' doesn't use robust predicates, '1' uses Robust Predicates.
                              (Default: 1)
                              
  -d,--validate-delaunay      Validates the Delaunay Property of the triangulation.
                              
  -o,--output TEXT REQUIRED   Output file that includes triangulation.

```

--------------------------------------------------------------------------------
## Contact Information
```
Maintainers:
    Spyridon Tsalikis
    Department of Computer Science,
    Old Dominion University,
    5115 Hampton Blvd, Norfolk, VA 23529, USA,
    email: stsaliki@odu.edu

Supervisor:
    Nikos P. Chrisochoides,
    Department of Computer Science,
    Old Dominion University,
    5115 Hampton Blvd, Norfolk, VA 23529, USA,
    phone: +1-757-683-7715,
    email: nchrisoc@odu.edu
```
--------------------------------------------------------------------------------
Copyright (C) 2020 Spyridon Tsalikis
