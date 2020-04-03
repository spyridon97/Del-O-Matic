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
    coordinates.fill(0);
}

Point::Point(std::array<double, 2> coordinates)
{
    for (size_t i = 0; i < 2; i++) {
        this->coordinates[i] = coordinates[i];
    }
}

Point::Point(const Point& point)
{
    for (size_t i = 0; i < 2; i++) {
        this->coordinates[i] = point[i];
    }
}

Point::~Point() = default;

double* Point::toArray()
{
    return coordinates.data();
}

Point& Point::operator=(const Point& point)
{
    if (this == &point) {
        return *this;
    }
    for (size_t i = 0; i < 2; i++) {
        this->coordinates[i] = point[i];
    }

    return *this;
}

bool Point::operator==(const Point& point) const
{
    for (size_t i = 0; i < 2; i++) {
        if (coordinates[i] != point[i]) {
            return false;
        }
    }

    return true;
}

bool Point::operator!=(const Point& point) const
{
    return !((*this) == point);
}

bool Point::operator<(const Point& point) const
{
    for (size_t i = 0; i < 2; i++) {
        if (coordinates[i] < point[i]) {
            return true;
        }
        if (coordinates[i] > point[i]) {
            return false;
        }
    }
    return false;
}

bool Point::operator>(const Point& point) const
{
    for (size_t i = 0; i < 2; i++) {
        if (coordinates[i] > point[i]) {
            return true;
        }
        if (coordinates[i] < point[i]) {
            return false;
        }
    }
    return false;
}

Point Point::operator*(double constant) const
{
    std::array<double, 2> temporaryCoordinates{};
    for (size_t i = 0; i < 2; i++) {
        temporaryCoordinates[i] = coordinates[i] * constant;
    }
    return Point(temporaryCoordinates);
}

Point Point::operator/(double constant) const
{
    std::array<double, 2> temporaryCoordinates{};
    for (size_t i = 0; i < 2; i++) {
        temporaryCoordinates[i] = coordinates[i] / constant;
    }
    return Point(temporaryCoordinates);
}

Point Point::operator+(const Point& otherPoint) const
{
    std::array<double, 2> temporaryCoordinates{};
    for (size_t i = 0; i < 2; i++) {
        temporaryCoordinates[i] = coordinates[i] + otherPoint[i];
    }
    return Point(temporaryCoordinates);
}

Point Point::operator-(const Point& otherPoint) const
{
    std::array<double, 2> temporaryCoordinates{};
    for (size_t i = 0; i < 2; i++) {
        temporaryCoordinates[i] = coordinates[i] - otherPoint[i];
    }
    return Point(temporaryCoordinates);
}

double Point::operator[](size_t index) const
{
    if (index > coordinates.size() - 1) {
        throw std::out_of_range(
                &"Index is bigger compared to what the Point Supports, where max = "[coordinates.size()] - 1);
    }
    return this->coordinates[index];
}

double& Point::operator[](size_t index)
{
    if (index > coordinates.size() - 1) {
        throw std::out_of_range(
                &"Index is bigger compared to what the Point Supports, where max = "[coordinates.size()] - 1);
    }
    return this->coordinates[index];
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