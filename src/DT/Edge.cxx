/*
 * Filename:    Edge.cxx
 * 
 * Description: Source file of Edge class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/2/20.
 */

#include "Edge.hxx"

////////////////////////////////////////////////////////////
//                 Triangles Information                  //
////////////////////////////////////////////////////////////

#define leftTriangleId 0
#define rightTriangleId 1

#define leftTriangleInfo adjacentTrianglesInfo[leftTriangleId]
#define rightTriangleInfo adjacentTrianglesInfo[rightTriangleId]

#define leftTriangle leftTriangleInfo.first
#define rightTriangle rightTriangleInfo.first

#define leftTriangleEdgeId leftTriangleInfo.second
#define rightTriangleEdgeId rightTriangleInfo.second

//  Fast lookup arrays to speed some of the mesh manipulation primitives
int plus1mod3[3] = {1, 2, 0};
int minus1mod3[3] = {2, 0, 1};

Edge::Edge(int originVertexId, int destinationVertexId)
{
    adjacentTrianglesInfo.reserve(2);
    this->originVertexId = originVertexId;
    this->destinationVertexId = destinationVertexId;
}

Edge::~Edge() = default;

void Edge::addAdjacentTriangle(TrianglePair adjacentTriangleWithEdgeId)
{
    adjacentTrianglesInfo.push_back(adjacentTriangleWithEdgeId);
}

void Edge::replaceAdjacentTriangle(const TriangleHandle& oldTriangle, const TrianglePair& newTriangleInfo)
{
    if (leftTriangle == oldTriangle) {
        leftTriangleInfo = newTriangleInfo;
    } else {
        rightTriangleInfo = newTriangleInfo;
    }
}

void Edge::checkNeighbors(int apexVertexTriangleId)
{
    if (leftTriangle->vertices[minus1mod3[leftTriangleEdgeId]]->id != apexVertexTriangleId) {
        //  swap trianglesInfo
        auto temp = leftTriangleInfo;
        leftTriangleInfo = rightTriangleInfo;
        rightTriangleInfo = temp;
    }
}

////////////////////////////////////////////////////////////////
//                 Left Triangle Primitives                   //
////////////////////////////////////////////////////////////////

TriangleHandle Edge::getLeftTriangle()
{
    return leftTriangle;
}

VertexHandle Edge::getOriginVertexLeftTriangle()
{
    return leftTriangle->vertices[leftTriangleEdgeId];
}

VertexHandle Edge::getDestinationVertexLeftTriangle()
{
    return leftTriangle->vertices[plus1mod3[leftTriangleEdgeId]];
}

VertexHandle Edge::getApexVertexLeftTriangle()
{
    return leftTriangle->vertices[minus1mod3[leftTriangleEdgeId]];
}

EdgeHandle Edge::getOriginEdgeLeftTriangle()
{
    return leftTriangle->edges[leftTriangleEdgeId];
}

EdgeHandle Edge::getDestinationEdgeLeftTriangle()
{
    return leftTriangle->edges[plus1mod3[leftTriangleEdgeId]];
}

EdgeHandle Edge::getApexEdgeLeftTriangle()
{
    return leftTriangle->edges[minus1mod3[leftTriangleEdgeId]];
}

////////////////////////////////////////////////////////////////
//                Right Triangle Primitives                   //
////////////////////////////////////////////////////////////////

TriangleHandle Edge::getRightTriangle()
{
    return rightTriangle;
}

VertexHandle Edge::getOriginVertexRightTriangle()
{
    return rightTriangle->vertices[plus1mod3[rightTriangleEdgeId]];
}

VertexHandle Edge::getDestinationVertexRightTriangle()
{
    return rightTriangle->vertices[minus1mod3[rightTriangleEdgeId]];
}

VertexHandle Edge::getApexVertexRightTriangle()
{
    return rightTriangle->vertices[rightTriangleEdgeId];
}

EdgeHandle Edge::getOriginEdgeRightTriangle()
{
    return rightTriangle->edges[plus1mod3[rightTriangleEdgeId]];
}

EdgeHandle Edge::getDestinationEdgeRightTriangle()
{
    return rightTriangle->edges[minus1mod3[rightTriangleEdgeId]];
}

EdgeHandle Edge::getApexEdgeRightTriangle()
{
    return rightTriangle->edges[rightTriangleEdgeId];
}

bool Edge::isBoundaryTriangle() const
{
    return adjacentTrianglesInfo.size() == 1;
}
