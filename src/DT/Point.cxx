/*
 * Filename:    Point.cxx
 * 
 * Description: Source file of Point class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#include "Point.hxx"


Point::Point()
{
    this->fill(0);
}

Point::Point(std::array<double, 2> coordinates)
{
    for (size_t i = 0; i < 2; i++) {
        coord[i] = coordinates[i];
    }
}

Point::Point(const Point& point)
{
    for (size_t i = 0; i < 2; i++) {
        coord[i] = point[i];
    }
}

Point::~Point() = default;

double* Point::toArray()
{
    return coord;
}

Point Point::operator*(double constant) const
{
    std::array<double, 2> temporaryCoordinates{};
    for (size_t i = 0; i < 2; i++) {
        temporaryCoordinates[i] = coord[i] * constant;
    }
    return Point(temporaryCoordinates);
}

Point Point::operator/(double constant) const
{
    std::array<double, 2> temporaryCoordinates{};
    for (size_t i = 0; i < 2; i++) {
        temporaryCoordinates[i] = coord[i] / constant;
    }
    return Point(temporaryCoordinates);
}

Point Point::operator+(const Point& otherPoint) const
{
    std::array<double, 2> temporaryCoordinates{};
    for (size_t i = 0; i < 2; i++) {
        temporaryCoordinates[i] = coord[i] + otherPoint[i];
    }
    return Point(temporaryCoordinates);
}

Point Point::operator-(const Point& otherPoint) const
{
    std::array<double, 2> temporaryCoordinates{};
    for (size_t i = 0; i < 2; i++) {
        temporaryCoordinates[i] = coord[i] - otherPoint[i];
    }
    return Point(temporaryCoordinates);
}

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