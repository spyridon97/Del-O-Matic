/*
 * Filename:    Io.cxx
 * 
 * Description: Source file of namespace IO.
 *
 * Author:      Spyridon Tsalikis.
 * Created on   2/25/2020.
 */

#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include "IO.hxx"


namespace Io
{
    bool hasComments(std::string& line)
    {
        return line == "#" || line.empty();
    }

    std::vector<Vertex> readInput(const std::string& filename)
    {
        std::cout << std::endl << "Reading Input file..." << std::endl;

        std::vector<Vertex> vertices;

        std::ifstream inputFile;
        inputFile.open(filename.c_str());

        if (inputFile) {
            size_t numberOfVertices = 0;
            std::string line, restLine;

            do {
                inputFile >> line;
                if (!hasComments(line)) {
                    numberOfVertices = stoi(line);
                    vertices.reserve(numberOfVertices);

                    size_t numberOfDimensions, numberOfAttributes, boundaryMarker;
                    inputFile >> numberOfDimensions >> numberOfAttributes >> boundaryMarker;
                    if (numberOfDimensions != 2) {
                        std::cerr << "The number of Dimensions must be 2\n";
                    }
                    assert(numberOfDimensions == 2);
                }
                std::getline(inputFile, restLine);
            } while (hasComments(line));

            do {
                inputFile >> line;
                if (!hasComments(line)) {
                    //  defining the first vertex
                    size_t vertexId = std::stoi(line);
                    Vertex vertex;
                    inputFile >> vertex[0] >> vertex[1];
                    vertices.push_back(vertex);
                    std::getline(inputFile, restLine);

                    //  defining the rest of the vertices
                    for (size_t i = 0; i < numberOfVertices - 1; i++) {
                        inputFile >> vertexId >> vertex[0] >> vertex[1];
                        vertices.push_back(vertex);
                    }
                }
                std::getline(inputFile, restLine);
            } while (hasComments(line));
        } else {
            std::cerr << "Could not open " << filename << " file" << std::endl;
            exit(EXIT_FAILURE);
        }

        return vertices;
    }

    std::vector<Vertex> generateUniformRandomInput(const size_t& numberOfRandomVertices)
    {

        std::cout << std::endl << "Generating " << numberOfRandomVertices << " uniformly random vertices..."
                  << std::endl;

        std::default_random_engine randomGenerator(std::random_device{}());
        std::uniform_real_distribution<double> distributionX(0, 1000000);
        std::uniform_real_distribution<double> distributionY(0, 1000000);

        std::vector<Vertex> vertices;
        vertices.reserve(numberOfRandomVertices);
        for (size_t i = 0; i < numberOfRandomVertices; ++i) {
            vertices.push_back(Vertex({distributionX(randomGenerator), distributionY(randomGenerator)}));
        }

        return vertices;
    }

    void printMesh(const Mesh& mesh, const std::string& filename)
    {
        std::cout << std::endl << "Printing mesh... " << std::endl;

        std::string rawFilename;
        size_t lastdot = filename.find_last_of('.');
        if (lastdot == std::string::npos) {
            rawFilename = filename;
        } else {
            rawFilename = filename.substr(0, lastdot);
        }
        std::string verticesFilename = rawFilename + ".node";
        std::string trianglesFilename = rawFilename + ".ele";

        //  vertices
        std::ofstream verticesOutputFile;
        verticesOutputFile.open(verticesFilename.c_str());

        if (verticesOutputFile) {
            verticesOutputFile << mesh.numberOfVertices << " 2 0 0" << std::endl;

            //  print vertices
            for (size_t i = 0; i < mesh.vertices.size(); i++) {
                verticesOutputFile << i + 1 << " " << mesh.vertices[i][0] << " " << mesh.vertices[i][1]
                                   << std::endl;
            }
        } else {
            std::cerr << "Could not open " << verticesFilename << " file" << std::endl;
            exit(EXIT_FAILURE);
        }
        verticesOutputFile.close();

        std::cout << std::endl << "Vertices are stored in: " << verticesFilename << std::endl;

        //  triangles
        std::ofstream trianglesOutputFile;
        trianglesOutputFile.open(trianglesFilename.c_str());

        if (trianglesOutputFile) {
            trianglesOutputFile << mesh.triangles.size() << " 3 0" << std::endl;

            //  print triangles
            for (size_t i = 0; i < mesh.triangles.size(); i++) {
                trianglesOutputFile << i + 1 << " " << mesh.triangles[i].indices[0] << " "
                                    << mesh.triangles[i].indices[1]
                                    << " " << mesh.triangles[i].indices[2] << std::endl;
            }
        } else {
            std::cerr << "Could not open " << trianglesFilename << " file" << std::endl;
            exit(EXIT_FAILURE);
        }
        trianglesOutputFile.close();

        std::cout << "Triangles are stored in: " << trianglesFilename << std::endl;
    }
}
