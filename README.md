# Delaunay Triangulation

--------------------------------------------------------------------------------
## Description

Given a vertex set, using the [Randomized Incremental Delaunay Triangulation](http://www.wias-berlin.de/people/si/course/files/Guibas92-RandomizeIncr.pdf) we can delaunay-triangulate it with complexity = O(n^2).

There is no warranty whatsoever. Use at your own risk.

--------------------------------------------------------------------------------
## Programming Language & Build System
* C++, (v17 or newer)
* CMAKE/CCMAKE, (v3.1 or newer)

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
  -i,--input TEXT:FILE REQUIRED
                              Input file to triangulate.

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
