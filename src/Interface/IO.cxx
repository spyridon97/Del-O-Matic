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

    std::vector<Point> readInput(const std::string& filename)
    {
        std::cout << std::endl << "Reading Input file..." << std::endl;

        std::vector<Point> points;

        std::ifstream inputFile;
        inputFile.open(filename.c_str());

        if (inputFile) {
            size_t numberOfPoints = 0;
            std::string line, restLine;

            do {
                inputFile >> line;
                if (!hasComments(line)) {
                    numberOfPoints = stoi(line);
                    points.reserve(numberOfPoints);

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
                    //defining the first vertex
                    size_t pointId = std::stoi(line);
                    Point point;
                    inputFile >> point[0] >> point[1];
                    points.push_back(point);
                    std::getline(inputFile, restLine);

                    //defining the rest of the vertices
                    for (size_t i = 0; i < numberOfPoints - 1; i++) {
                        Point point;
                        inputFile >> pointId >> point[0] >> point[1];
                        points.push_back(point);
                    }
                }
                std::getline(inputFile, restLine);
            } while (hasComments(line));
        } else {
            std::cerr << "Could not open " << filename << " file" << std::endl;
            exit(EXIT_FAILURE);
        }

        return points;
    }

    std::vector<Point> generateUniformRandomInput(const size_t& numberOfRandomPoints)
    {
        std::default_random_engine randomGenerator(std::random_device{}());
        std::uniform_real_distribution<double> distributionX(0, 1000000);
        std::uniform_real_distribution<double> distributionY(0, 1000000);

        std::cout << std::endl << "Generating " << numberOfRandomPoints << " uniformly random points..." << std::endl;

        std::vector<Point> points;
        points.reserve(numberOfRandomPoints);
        for (size_t i = 0; i < numberOfRandomPoints; ++i) {
            points.push_back(Point({distributionX(randomGenerator), distributionY(randomGenerator)}));
        }

        return points;
    }

    void printMesh(const Mesh& mesh, const std::string& filename)
    {
        std::string rawFilename;
        size_t lastdot = filename.find_last_of('.');
        if (lastdot == std::string::npos) {
            rawFilename = filename;
        } else {
            rawFilename = filename.substr(0, lastdot);
        }
        std::string pointsFilename = rawFilename + ".node";
        std::string cellsFilename = rawFilename + ".ele";

        //  vertices
        std::ofstream pointsOutputFile;
        pointsOutputFile.open(pointsFilename.c_str());

        if (pointsOutputFile) {
            pointsOutputFile << mesh.numberOfPoints << " 2 0 0" << std::endl;

            //  print vertices
            for (size_t i = 0; i < mesh.points.size(); i++) {
                pointsOutputFile << i + 1 << " " << mesh.points[i][0] << " " << mesh.points[i][1]
                                 << std::endl;
            }
        } else {
            std::cerr << "Could not open " << pointsFilename << " file" << std::endl;
            exit(EXIT_FAILURE);
        }
        pointsOutputFile.close();

        //  cells
        std::ofstream cellsOutputFile;
        cellsOutputFile.open(cellsFilename.c_str());

        if (cellsOutputFile) {
            cellsOutputFile << mesh.triangles.size() << " 3 0" << std::endl;

            //  print triangles
            for (size_t i = 0; i < mesh.triangles.size(); i++) {
                cellsOutputFile << i + 1 << " " << mesh.triangles[i].indices[0] << " " << mesh.triangles[i].indices[1]
                                << " " << mesh.triangles[i].indices[2] << std::endl;
            }
        } else {
            std::cerr << "Could not open " << cellsFilename << " file" << std::endl;
            exit(EXIT_FAILURE);
        }
        cellsOutputFile.close();
    }
}
