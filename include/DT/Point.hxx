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
     * @brief Copy Constructor of Point class.
     *
     * @param point is the vertex of which its coordinates will be extracted
     */
    Point(const Point& point);

    /**
     * @brief Constructor of Point class which set all dimensions using a specific array.
     *
     * @param coord is the array that includes the coordinates of the vertex
     */
    explicit Point(std::array<double, 2> coord);

    /**
     * @brief Destructor of Point class.
     */
    ~Point();

public:
    #define coordinates _M_elems
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
