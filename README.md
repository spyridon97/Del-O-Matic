                         ██████╗ ███████╗██╗      █████╗ ██╗   ██╗███╗   ██╗ █████╗ ██╗   ██╗               
                         ██╔══██╗██╔════╝██║     ██╔══██╗██║   ██║████╗  ██║██╔══██╗╚██╗ ██╔╝               
                         ██║  ██║█████╗  ██║     ███████║██║   ██║██╔██╗ ██║███████║ ╚████╔╝                
                         ██║  ██║██╔══╝  ██║     ██╔══██║██║   ██║██║╚██╗██║██╔══██║  ╚██╔╝                 
                         ██████╔╝███████╗███████╗██║  ██║╚██████╔╝██║ ╚████║██║  ██║   ██║                  
                         ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝   ╚═╝             
    
        ████████╗██████╗ ██╗ █████╗ ███╗   ██╗ ██████╗ ██╗   ██╗██╗      █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
        ╚══██╔══╝██╔══██╗██║██╔══██╗████╗  ██║██╔════╝ ██║   ██║██║     ██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
           ██║   ██████╔╝██║███████║██╔██╗ ██║██║  ███╗██║   ██║██║     ███████║   ██║   ██║██║   ██║██╔██╗ ██║
           ██║   ██╔══██╗██║██╔══██║██║╚██╗██║██║   ██║██║   ██║██║     ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
           ██║   ██║  ██║██║██║  ██║██║ ╚████║╚██████╔╝╚██████╔╝███████╗██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
           ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/9fef7ed014c24b2f84dbe6c6ccfc3733)](https://app.codacy.com/manual/spyridon97/DelaunayTriangulation?utm_source=github.com&utm_medium=referral&utm_content=spyridon97/DelaunayTriangulation&utm_campaign=Badge_Grade_Dashboard)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](./LICENSE)
![Latest release](https://img.shields.io/badge/version-1.0.0-blue)

--------------------------------------------------------------------------------
## Description

Given a set of vertices, using the [Randomized Incremental Algorithm](http://www.cs.uu.nl/geobook/interpolation.pdf) we can Delaunay-triangulate it with complexity = O(n log n).

![Example](https://i.imgur.com/Zlt6oUl.png)

--------------------------------------------------------------------------------
## Programming Language & Build System

*   C++, (v17 or newer)
*   CMAKE/CCMAKE, (v3.1 or newer)

--------------------------------------------------------------------------------
## Libraries

*   Predicates, (v1.0.0) : [Routines for Arbitrary Precision Floating-vertex Arithmetic and Fast Robust Geometric Predicates](https://www.cs.cmu.edu/~quake/robust.html)
*   CLI11, (V1.9.0) : [Command Line Parser for C++11 and above](https://github.com/CLIUtils/CLI11)

--------------------------------------------------------------------------------
## Structure of repository

*   include/src:
    *   This directory contains the header and sources files of the DelaunayTriangulation program.
    
*   inputFiles:
    *   This directory contains example input files.
    
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

*   create a build directory inside the root of this project
*   cd into the build directory
*   `cmake  ..`

--------------------------------------------------------------------------------
## Input and Output files

Input files:
*   [.node](http://www.cs.cmu.edu/~quake/triangle.node.html) which can be visualized using [ShowMe](http://www.cs.cmu.edu/~quake/showme.html).

Output files
*   [.node](http://www.cs.cmu.edu/~quake/triangle.node.html) for the vertices of the triangulation, which can be visualized using [ShowMe](http://www.cs.cmu.edu/~quake/showme.html).
*   [.ele](http://www.cs.cmu.edu/~quake/triangle.ele.html) for the triangles of the triangulation, which can be visualized using [ShowMe](http://www.cs.cmu.edu/~quake/showme.html).

--------------------------------------------------------------------------------
## Usage

    DelaunayTriangulation
    Usage: ./delaunayTriangulation [OPTIONS]
    
    Options:
      -h,--help                   Print this help message and exit
      -i,--input TEXT:FILE Excludes: --random
                                  Input Vertices file to triangulate.
                                  
      -r,--random UINT:POSITIVE Excludes: --input
                                  Generates and uniformly random set of N 2D Vertices.
                                  
      -p,--robust-predicates BOOLEAN
                                  Uses Robust Predicates. '0' doesn't use Robust Predicates, '1' uses Robust Predicates.
                                  (Default: 1)
                                  
      -d,--validate-delaunay      Validates the Delaunay Property of the triangulation.
                                  
      -o,--output TEXT REQUIRED   Output file that includes triangulation.
      
--------------------------------------------------------------------------------
## Performance Evaluation

Performance evaluation was performed with an [AMD Ryzen 5 3600 3.6GHz](https://www.amd.com/en/products/cpu/amd-ryzen-5-3600) using uniformly random distributed vertices and Robust Predicates.

|  vertices | [Triangle](https://www.cs.cmu.edu/~quake/triangle.html)'s incremental-algorithm | [DelaunayTriangulation](https://github.com/spyridon97/DelaunayTriangulation)'s incremental-algorithm |
|----------:|--------------------------------------------------------------------------------:|-----------------------------------------------------------------------------------------------------:|
|     2,500 |                                                                   0.002 seconds |                                                                                     0.012004 seconds |
|     5,000 |                                                                   0.004 seconds |                                                                                     0.024208 seconds |
|    10,000 |                                                                   0.018 seconds |                                                                                     0.041508 seconds |
|    25,000 |                                                                   0.042 seconds |                                                                                     0.105986 seconds |
|    50,000 |                                                                   0.095 seconds |                                                                                     0.239179 seconds |
|   100,000 |                                                                   0.208 seconds |                                                                                     0.512371 seconds |
|   250,000 |                                                                   1.009 seconds |                                                                                     1.510440 seconds |
|   500,000 |                                                                   3.770 seconds |                                                                                     3.361120 seconds |
| 1,000,000 |                                                                  11.825 seconds |                                                                                     7.401540 seconds |
| 2,500,000 |                                                                  47.039 seconds |                                                                                    21.639200 seconds |
| 5,000,000 |                                                                 124.060 seconds |                                                                                    46.717200 seconds |

**Results**: DelaunayTriangulation's incremental-algorithm scales better than Triangle's incremental-algorithm.

--------------------------------------------------------------------------------
## Contact Information

Author: Spiros Tsalikis (stsaliki@odu.edu)\
Department of Computer Science, Old Dominion University, 5115 Hampton Blvd, Norfolk, VA 23529, USA

--------------------------------------------------------------------------------
Copyright (C) Spiros Tsalikis
