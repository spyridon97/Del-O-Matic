/*
 * Filename:    Simplex.hxx
 * 
 * Description: Header file of Simplex class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#ifndef DELAUNAYTRIANGULATION_SIMPLEX_HXX
#define DELAUNAYTRIANGULATION_SIMPLEX_HXX


#include <cmath>
#include "Point.hxx"
#include "Predicates.hxx"


/**
 * @brief Facilitates a k-simplex.
 *
 * @tparam k is the k value of simplex
 */
template<size_t k>
class Simplex
{
public:
    static_assert(1 <= k && k <= 2);

    /**
     * @brief Constructor of Simplex class.
     *
     * @param points are the vertices that are used to define the simplex
     */
    explicit Simplex(std::array<Vertex, k + 1> points)
    {
        for (size_t i = 0; i < points.size(); ++i) {
            this->vertices[i] = points[i];
        }
        isBad = false;
    }

    /**
     * @brief Destructor of Simplex class
     */
    ~Simplex() = default;

    /**
     * @brief Copy Constructor.
     *
     * @param otherSimplex to be copied
     */
    Simplex(const Simplex& otherSimplex)
    {
        for (size_t i = 0; i < vertices.size(); i++) {
            vertices[i] = otherSimplex.vertex(i);
        }
        isBad = otherSimplex.isBad;
    }

    /**
     * @brief Gets a vertex of the simplex.
     *
     * @param index is the index of the vertex of the simplex that is requested
     * @return a vertex of the simplex
     */
    [[nodiscard]] Vertex vertex(unsigned char index) const
    {
        if (index > k || index < 0) {
            throw std::out_of_range(
                    "index is bigger compared to what Simplex Supports, where max = " +
                    std::to_string(k));
        }

        return vertices[index];
    }

    /**
     * @brief Gets a vertex of the simplex.
     *
     * @param index is the index of the vertex of the simplex that is requested
     * @return a vertex of the simplex
     */
    Vertex& vertex(unsigned char index)
    {
        if (index > k || index < 0) {
            throw std::out_of_range(
                    "index is bigger compared to what Simplex Supports, where max = " +
                    std::to_string(k));
        }

        return vertices[index];
    }

    //////////////////////////////////////////////////////////////////////////
    //                          Triangle Functions                          //
    //////////////////////////////////////////////////////////////////////////

    /**
     * @brief Checks if a vertex lies in the circumcircle of a triangle.
     *
     * @param vertex is the checked vertex
     * @return a boolean value which indicates if a vertex lies in the circumcircle of a triangle
     */
    template<size_t kSimplex = k>
    typename std::enable_if<kSimplex == 2, bool>::type
    inCircleTest(const Vertex& vertex) const
    {
        double orientResult = orient2d(vertices[0]->toArray(), vertices[1]->toArray(), vertices[2]->toArray());

        if (orientResult > 0) { //  ClockWise order
            double inCircleResult = incircle(vertices[0]->toArray(), vertices[1]->toArray(), vertices[2]->toArray(),
                                             vertex->toArray());
            return inCircleResult > 0;
        } else if (orientResult < 0) { //  Counter-ClockWise order
            double inCircleResult = incircle(vertices[0]->toArray(), vertices[1]->toArray(), vertices[2]->toArray(),
                                             vertex->toArray());
            return inCircleResult < 0;
        } else {
            return false;
        }
    }

    /**
     * @brief Checks if a vertex is part of a triangle.
     *
     * @param vertex is the checked vertex
     * @return a boolean value which indicates if a vertex is part of a triangle.
     */
    template<size_t kSimplex = k>
    typename std::enable_if<kSimplex == 2, bool>::type
    containsVertex(const Vertex& vertex) const
    {
        return vertices[0] == vertex || vertices[1] == vertex || vertices[2] == vertex;
    }

    //////////////////////////////////////////////////////////////////////////
    //                            Edge Functions                            //
    //////////////////////////////////////////////////////////////////////////

    /**
     * @brief Compares Edges.
     *
     * @return a boolean value which indicates if edges are the same
     */
    template<size_t kSimplex = k>
    typename std::enable_if<kSimplex == 1, bool>::type
    compareEdges(const Simplex<kSimplex>& simplex) const
    {
        return (vertices[0] == simplex.vertex(0) && vertices[1] == simplex.vertex(1)) ||
               (vertices[0] == simplex.vertex(1) && vertices[1] == simplex.vertex(0));
    }

    /**
     * @brief Gets squared length of the 1-simplex.
     *
     * @tparam kSimplex is used to enable getSquaredLength only for k = 1
     * @return squared length of the 1-simplex
     */
    template<size_t kSimplex = k>
    typename std::enable_if<kSimplex == 1, double>::type
    getSquaredLength() const
    {
        double squaredLength = 0;
        for (size_t i = 0; i < 2; i++) {
            squaredLength += std::pow(vertices[1][i] - vertices[0][i]);
        }

        return squaredLength;
    }

private:
    std::array<Vertex, k + 1> vertices;
public:
    bool isBad;
};

using Edge = Simplex<1>;
using Triangle = Simplex<2>;


#endif /* DELAUNAYTRIANGULATION_SIMPLEX_HXX */
