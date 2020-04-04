/*
 * Filename:    Point.hxx
 * 
 * Description: Header file of Point class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#ifndef DELAUNAY_TRIANGULATION_POINT_HXX
#define DELAUNAY_TRIANGULATION_POINT_HXX


#include <array>
#include <iostream>


/**
 * @brief Facilitates a 2D cartesian Point.
 */
class Point : public std::array<double, 2>
{
public:
    /**
     * @brief Constructor of Point class which sets all dimensions to 0.
     */
    Point();

    /**
     * @brief Constructor of Point class which set all dimensions using a specific array.
     *
     * @param coordinates is the array that includes the coordinates of the vertex
     */
    explicit Point(std::array<double, 2> coordinates);

    /**
     * @brief Copy Constructor of Point class.
     *
     * @param point is the vertex of which its coordinates will be extracted
     */
    Point(const Point& point);

    /**
     * @brief Destructor of Point class.
     */
    ~Point();

    /**
     * @brief Converts vertex to an array of double coordinates.
     *
     * @return an array of double coordinates
     */
    double* toArray();

    /**
     * @brief Overloads operator "*".
     *
     * @param constant which will be used to multiply the coordinates of the Point
     * @return a vertex whose coordinates have be multiplied by the given constant
     */
    Point operator*(double constant) const;

    /**
     * @brief Overloads operator "/".
     *
     * @param constant which will be used to divide the coordinates of the Point
     * @return a vertex whose coordinates have be divided by the given constant
     */
    Point operator/(double constant) const;

    /**
     * @brief Overloads operator "+".
     *
     * @param otherPoint is a vertex whose coordinates will be added to the current object's ones
     * @return a vertex whose coordinates are the sum of the coordinates of the 2 Points
     */
    Point operator+(const Point& otherPoint) const;

    /**
     * @brief Overloads operator "-".
     *
     * @tparam Dimensions is the dimensions of the vertex
     * @param otherPoint is a vertex whose coordinates will be subtracted from the current object's ones
     * @return a vertex whose coordinates are the subtraction of the coordinates of the 2 Points
     */
    Point operator-(const Point& otherPoint) const;

    #define coord _AT_Type::_S_ptr(_M_elems)
};

/**
 * @brief Overloads operator ">>".
 *
 * @param input is the stream which is used to read a vertex
 * @param point is a vertex in which the input coordinates will be saved to
 * @return a vertex with the input coordinates
 */
std::istream& operator>>(std::istream& input, Point& point);

/**
 * @brief Overloads operator "<<".
 *
 * @param output is the stream which is used to output a vertex
 * @param point is a vertex whose coordinated will be outputed
 * @return the output coordinates
 */
std::ostream& operator<<(std::ostream& output, const Point& point);


#endif /* DELAUNAY_TRIANGULATION_POINT_HXX */
