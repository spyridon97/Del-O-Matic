/*
 * Filename:    Simplex.cxx
 * 
 * Description: Source file of Simplex class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#include "Triangle.hxx"


Triangle::Triangle(std::array<VertexHandle, 3> points)
{
    for (size_t i = 0; i < points.size(); ++i) {
        this->vertices[i] = points[i];
    }
    isBad = false;
    id = std::numeric_limits<size_t>::max();
}

Triangle::~Triangle() = default;

Triangle::Triangle(const Triangle& otherTriangle)
{
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i] = otherTriangle.vertex(i);
    }
    isBad = otherTriangle.isBad;
    id = otherTriangle.id;
}

VertexHandle Triangle::vertex(unsigned char index) const
{
    if (index > 2 || index < 0) {
        throw std::out_of_range(
                "index is bigger compared to what Triangle Supports, where max = " +
                std::to_string(2));
    }

    return vertices[index];
}

VertexHandle& Triangle::vertex(unsigned char index)
{
    if (index > 2 || index < 0) {
        throw std::out_of_range(
                "index is bigger compared to what Triangle Supports, where max = " +
                std::to_string(2));
    }

    return vertices[index];
}

bool Triangle::inCircleTest(const VertexHandle& vertex) const
{
    // double pa[2] = {vertices[0]->point()[0], vertices[0]->point()[1]};
    // double pb[2] = {vertices[1]->point()[0], vertices[1]->point()[1]};
    // double pc[2] = {vertices[2]->point()[0], vertices[2]->point()[1]};
    // double pd[2] = {vertex->point()[0], vertex->point()[1]};
    //  std::cout << pa[0] << " " << pa[1] << std::endl;
    // double* pa = vertices[0]->point().toArray();
    // double* pb = vertices[1]->point().toArray();
    // double* pc = vertices[2]->point().toArray();
    // double* pd = vertex->point().toArray();

    //double orientResult = orient2d(pa, pb, pc);
    double orientResult = orient2d(vertices[0]->toArray(), vertices[1]->toArray(),
                                   vertices[2]->toArray());
    // std::cout << orientResult << " " << orientResult2 << vertices[0]->point() << vertices[1]->point()
    //           << vertices[2]->point() << std::endl;

    if (orientResult > 0) { //  ClockWise order
        double inCircleResult = incircle(vertices[0]->toArray(), vertices[1]->toArray(),
                                         vertices[2]->toArray(),
                                         vertex->toArray());
        //double inCircleResult = incircle(pa, pb, pc, pd);
        return inCircleResult > 0;
    } else if (orientResult < 0) { //  Counter-ClockWise order
        double inCircleResult = incircle(vertices[0]->toArray(), vertices[1]->toArray(),
                                         vertices[2]->toArray(),
                                         vertex->toArray());
        //double inCircleResult = incircle(pa, pb, pc, pd);
        return inCircleResult < 0;
    } else {
        return false;
    }
}

bool Triangle::containsVertex(const VertexHandle& vertex) const
{
    return *vertices[0] == *vertex || *vertices[1] == *vertex || *vertices[2] == *vertex;
}
