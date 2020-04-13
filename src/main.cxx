/*
 * Filename:    main.cxx
 *
 * Description: File that contains the main function.
 *
 * Author:      Spyridon Tsalikis
 * Created on   02/26/20.
 */

#include <sys/resource.h>
#include <bits/unique_ptr.h>
#include <iostream>
#include "Args.hxx"
#include "DelaunayTriangulation.hxx"
#include "IO.hxx"


int main(int argc, char** argv)
{
    //  Parse CLI arguments
    int result = Args::parseArguments(argc, argv);
    if (result != 0) {
        return EXIT_FAILURE;
    }
    Args::display(std::cout);

    Timer timer{};
    timer.startTimer();

    Timer readingInputTimer{};
    readingInputTimer.startTimer();

    std::vector<Vertex> inputVertices;
    if (!Args::inputFileName.empty()) {
        inputVertices = Io::readInput(Args::inputFileName);
    } else {
        inputVertices = Io::generateUniformRandomInput(Args::numberOfRandomVertices);
    }

    readingInputTimer.stopTimer();

    std::unique_ptr<DelaunayTriangulation> triangulation =
            std::make_unique<DelaunayTriangulation>(Args::robustPredicates);

    triangulation->setInputVertices(inputVertices);

    triangulation->generateMesh();

    if (Args::validateDelaunayProperty) {
        triangulation->validateDelaunayTriangulation();
    }

    Mesh outputMesh = triangulation->getOutputMesh();

    Timer writingMeshTimer{};
    writingMeshTimer.startTimer();

    Io::printMesh(outputMesh, Args::outputFileName);

    writingMeshTimer.stopTimer();

    //  print timers
    timer.stopTimer();

    std::cout << std::endl << "DelaunayTriangulion Times" << std::endl;
    std::cout << "================================================" << std::endl;
    if (!Args::inputFileName.empty()) {
        std::cout << "Reading Input I/O time: " << readingInputTimer.getSeconds() << " seconds" << std::endl;
    } else {
        std::cout << "Generating uniformly random Input time: " << readingInputTimer.getSeconds() << " seconds"
                  << std::endl;
    }
    std::cout << "Computing Boundary Triangle time: "
              << triangulation->computeBoundaryTriangleTimer.getSeconds() << " seconds" << std::endl;
    std::cout << "Meshing time: " << triangulation->meshingTimer.getSeconds() << " seconds" << std::endl;
    if (Args::validateDelaunayProperty) {
        std::cout << "Validating Delaunay Property time: "
                  << triangulation->validateDelaunayTriangulationTimer.getSeconds() << " seconds" << std::endl;
    }
    std::cout << "Writing Mesh I/O time: " << writingMeshTimer.getSeconds() << " seconds" << std::endl;
    std::cout << std::endl << "Execution Wall time: " << timer.getSeconds() << " seconds" << std::endl;
    std::cout << "================================================" << std::endl;

    //  print memory used
    struct rusage usage{};
    int usageResult = getrusage(RUSAGE_SELF, &usage);
    if (usageResult != 0) {
        std::cerr << std::endl << "Failed to get memory usage information" << std::endl;
    } else {
        std::cout << std::endl << "Main reports " << static_cast<double>(usage.ru_maxrss) / 1024.0
                  << " MB of memory used" << std::endl;
    }

    std::cout << std::endl << "PROGRAM FINISHED NORMALLY" << std::endl << std::endl;

    return EXIT_SUCCESS;
}
