/*
 * Filename:    Args.hxx
 *
 * Description: Header file of namespace Args.
 *
 * Author:      Spyridon Tsalikis
 * Created on   9/10/19.
 */

#ifndef DELAUNAY_TRIANGULATION_ARGS_HXX
#define DELAUNAY_TRIANGULATION_ARGS_HXX


#include <iosfwd>
#include <string>

/**
 * @brief Facilitates CLI argument parsing
 * and holds CLI argument and configuration values.
 */
namespace Args
{
    ////////////////////////////////////////////
    // CLI Arguments
    ////////////////////////////////////////////
    extern std::string inputFileName;
    extern size_t numberOfRandomVertices;
    extern bool robustPredicates;
    extern bool validateDelaunayProperty;
    extern std::string outputFileName;

    /**
     * @brief Parse Command line Arguments.
     *
     * @return 0 on success , otherwise CLI11 error code
     */
    int parseArguments(int argc, char** argv);

    /**
     * @brief Display DelaunayTriangulation argument values.
     *
     * @param out Output stream to pipe output to
     */
    void display(std::ostream& out);
}


#endif /* DELAUNAY_TRIANGULATION_ARGS_HXX */
