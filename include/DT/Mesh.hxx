/*
 * Filename:    Mesh.hxx
 *
 * Description: Header file of Mesh struct.
 *
 * Author:      Spiros Tsalikis
 * Created on   3/2/2020.
 */

#ifndef DELOMATIC_MESH_HXX
#define DELOMATIC_MESH_HXX


#include "Triangle.hxx"


struct Mesh
{
    std::vector<VertexHandle> vertices;
    std::vector<TriangleHandle> triangles;
};


#endif /* DELOMATIC_MESH_HXX */
