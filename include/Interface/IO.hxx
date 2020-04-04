/*
 * Filename:    Io.hxx
 * 
 * Description: Header file of namespace IO.
 *
 * Author:      Spyridon Tsalikis
 * Created on   2/25/2020.
 */

#ifndef DELAUNAY_TRIANGULATION_IO_HXX
#define DELAUNAY_TRIANGULATION_IO_HXX


#include <string>
#include <vector>
#include "Mesh.hxx"
#include "Point.hxx"


namespace Io
{
    /**
     * @brief Reads input .node file.
     *
     * @param filename is the file name of the .node file
     * @return return a set of input vertices
     */
    std::vector<Point> readInput(const std::string& filename);

    /**
     * @brief Generates a set of random uniform points.
     *
     * @param numberOfRandomPoints is the amount of points that will be created
     *
     * @return a set of random uniform points
     */
    std::vector<Point> generateUniformRandomInput(const size_t& numberOfRandomPoints);

    /**
     * @brief Prints output .node, .edge, and .ele files.
     *
     * @param mesh the triangulated mesh
     * @param filename the filename of outputFiles.
     */
    void printMesh(const Mesh& mesh, const std::string& filename);
}


#endif /* TRIANGULATEMONOTONEPOLYGON_IO_HXX */
