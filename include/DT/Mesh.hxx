/*
 * Filename:    Mesh.hxx
 *
 * Description: Header file of Mesh struct.
 *
 * Author:      Spyridon Tsalikis
 * Created on   3/2/2020.
 */

#ifndef DELAUNAY_TRIANGULATION_MESH_HXX
#define DELAUNAY_TRIANGULATION_MESH_HXX


#include "Triangle.hxx"


struct Mesh
{
    std::vector<VertexHandle> vertices;
    std::vector<TriangleHandle> triangles;
};


#endif /* DELAUNAY_TRIANGULATION_MESH_HXX */
