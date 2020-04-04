/*
 * Filename:    Point.cxx
 * 
 * Description: Source file of Point class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#include "Point.hxx"


Point::Point() : array()
{
    this->fill(0);
}

Point::Point(const Point& point) : array(point)
{
    for (size_t i = 0; i < 2; i++) {
        this->coordinates[i] = point[i];
    }
}

Point::Point(std::array<double, 2> coord) : array()
{
    for (size_t i = 0; i < 2; i++) {
        this->coordinates[i] = coord[i];
    }
}

Point::~Point() = default;

std::istream& operator>>(std::istream& input, Point& point)
{
    char c;
    input >> c;

    if (!input.eof()) {
        std::array<double, 2> coordinates{};
        for (size_t i = 0; i < 2; i++) {
            input >> coordinates[i] >> c;
        }
        point = Point(coordinates);
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const Point& point)
{
    output << "(";
    for (size_t i = 0; i < 2 - 1; i++) {
        output << point[i] << ", ";
    }
    output << point[2 - 1] << ")";

    return output;
}