/*
 * Filename:    Io.hxx
 * 
 * Description: Header file of namespace IO.
 *
 * Author:      Spiros Tsalikis
 * Created on   2/25/2020.
 */

#ifndef DELOMATIC_IO_HXX
#define DELOMATIC_IO_HXX


#include <string>
#include <vector>
#include "Mesh.hxx"
#include "Vertex.hxx"


namespace Io
{
    /**
     * @brief Reads input .node file.
     *
     * @param filename is the file name of the .node file
     * @return return a set of input vertices
     */
    std::vector<Vertex> readInput(const std::string& filename);

    /**
     * @brief Generates a set of random uniform vertices.
     *
     * @param numberOfRandomVertices is the amount of vertices that will be created
     *
     * @return a set of random uniform vertices
     */
    std::vector<Vertex> generateUniformRandomInput(const size_t& numberOfRandomVertices);

    /**
     * @brief Prints output .node, .edge, and .ele files.
     *
     * @param mesh the triangulated mesh
     * @param filename the filename of outputFiles.
     */
    void printMesh(const Mesh& mesh, const std::string& filename);
}


#endif /* DELOMATIC_IO_HXX */
