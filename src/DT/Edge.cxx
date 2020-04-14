/*
 * Filename:    Edge.cxx
 * 
 * Description: Source file of Edge class.
 *
 * Author:      Spiros Tsalikis
 * Created on   4/2/20.
 */

#include "Edge.hxx"

////////////////////////////////////////////////////////////
//                 Triangles Information                  //
////////////////////////////////////////////////////////////

#define leftTriangle adjacentTrianglesInfo[leftTriangleId].first
#define rightTriangle adjacentTrianglesInfo[rightTriangleId].first

#define leftTriangleEdgeId adjacentTrianglesInfo[leftTriangleId].second
#define rightTriangleEdgeId adjacentTrianglesInfo[rightTriangleId].second

//  Fast lookup arrays to speed up the mesh manipulation primitives
int plus1mod3[3] = {1, 2, 0};
int minus1mod3[3] = {2, 0, 1};

Edge::Edge()
{
    adjacentTrianglesInfo.reserve(2);
    this->leftTriangleId = 0;
    this->rightTriangleId = 1;
}

Edge::~Edge() = default;

void Edge::addAdjacentTriangle(TrianglePair adjacentTriangleWithEdgeId)
{
    adjacentTrianglesInfo.push_back(adjacentTriangleWithEdgeId);
}

void Edge::replaceAdjacentTriangle(const TriangleHandle& oldTriangle, const TrianglePair& newTriangleInfo)
{
    if (adjacentTrianglesInfo[0].first == oldTriangle) {
        adjacentTrianglesInfo[0] = newTriangleInfo;
        this->leftTriangleId = 0;
        this->rightTriangleId = 1;
    } else {
        adjacentTrianglesInfo[1] = newTriangleInfo;
        this->leftTriangleId = 1;
        this->rightTriangleId = 0;
    }
}

void Edge::determineAdjacentTriangles(int apexVertexLeftTriangleId)
{
    if (adjacentTrianglesInfo[0].first->vertices[minus1mod3[adjacentTrianglesInfo[0].second]]->id ==
        apexVertexLeftTriangleId) {
        this->leftTriangleId = 0;
        this->rightTriangleId = 1;
    } else {
        this->leftTriangleId = 1;
        this->rightTriangleId = 0;
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

bool Edge::isBoundaryEdge() const
{
    return adjacentTrianglesInfo.size() == 1;
}
