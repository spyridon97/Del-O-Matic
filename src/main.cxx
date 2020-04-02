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
    timer.start_seconds_timer();

    Timer readingInputTimer{};
    readingInputTimer.start_seconds_timer();

    std::vector<Point> inputPoints = Io::readInput(Args::inputFileName);

    readingInputTimer.stop_seconds_timer();

    std::unique_ptr<DelaunayTriangulation> triangulator = std::make_unique<DelaunayTriangulation>();

    triangulator->setInputPoints(inputPoints);

    triangulator->generateMesh();

    Mesh outputMesh = triangulator->getCleanMesh();

    Timer writingMeshTimer{};
    writingMeshTimer.start_seconds_timer();

    Io::printMesh(outputMesh, Args::outputFileName);

    writingMeshTimer.stop_seconds_timer();

    //  print timers
    timer.stop_seconds_timer();

    std::cout << std::endl << "DelaunayTriangulion Times" << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "Reading Input I/O time: " << readingInputTimer.get_seconds() << " seconds" << std::endl;
    std::cout << "Computing Boundary Triangle time: "
              << triangulator->computeBoundaryTriangleTimer.get_seconds() << " seconds" << std::endl;
    std::cout << "Meshing time: " << triangulator->meshingTimer.get_seconds() << " seconds" << std::endl;
    std::cout << "Computing Mesh Results time: " << triangulator->computeMeshResultsTimer.get_seconds()
              << " seconds" << std::endl;
    std::cout << "Writing Mesh I/O time: " << writingMeshTimer.get_seconds() << " seconds" << std::endl;
    std::cout << std::endl << "Execution Wall time: " << timer.get_seconds() << " seconds" << std::endl;
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
