/*
 * Filename:    Mesh.hxx
 *
 * Description: Header file of Mesh struct.
 *
 * Author:      Spyridon Tsalikis
 * Created on   3/2/2020.
 */

#ifndef TRIANGULATEMONOTONEPOLYGON_MESH_HXX
#define TRIANGULATEMONOTONEPOLYGON_MESH_HXX


#include <array>
#include <vector>
#include "Point.hxx"


struct Mesh
{
    struct Triangle
    {
        std::array<size_t, 3> indices;
    };

    size_t numberOfPoints;

    std::vector<Point> points;
    std::vector<Triangle> triangles;
};


#endif /* TRIANGULATEMONOTONEPOLYGON_MESH_HXX */
