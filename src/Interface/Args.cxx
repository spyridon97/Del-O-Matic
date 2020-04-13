/*
 * Filename:    Args.cxx
 *
 * Description: Source file of namespace Args.
 *
 * Author:      Spyridon Tsalikis.
 * Created on   6/10/19.
 */

#include <iostream>
#include "CLI11.hpp"
#include "Args.hxx"


namespace Args
{
    ////////////////////////////////////////////
    // CLI Arguments
    ////////////////////////////////////////////
    std::string inputFileName;
    size_t numberOfRandomVertices = 0;
    bool robustPredicates = true;
    bool validateDelaunayProperty = false;
    std::string outputFileName;
    ////////////////////////////////////////////

    int parseArguments(int argc, char** argv)
    {
        constexpr char DESCRIPTION[] = "DelaunayTriangulation";

        // Initialize CLI application
        std::unique_ptr<CLI::App> app = std::make_unique<CLI::App>(DESCRIPTION);

        ////////////////////////////////////////////
        // Add CLI Argument Options
        ////////////////////////////////////////////
        //  --------------------------------------------------------------------------  *

        auto inputFileOption = app->add_option("-i,--input", inputFileName, "Input Vertices file to triangulate.\n")
                ->check(CLI::ExistingFile);

        auto randomVerticesSetOption = app->add_option("-r, --random", numberOfRandomVertices,
                                                       "Generates and uniformly random set of N 2D Vertices.\n")
                ->check(CLI::PositiveNumber);

        inputFileOption->excludes(randomVerticesSetOption);
        randomVerticesSetOption->excludes(inputFileOption);

        //  ensure that input vertices will be provided or randomly produced
        app->final_callback([]() {
            if (numberOfRandomVertices == 0 && inputFileName.empty()) {
                throw (CLI::ValidationError("Use either --input or --random options"));
            }
        });

        app->add_option("-p,--robust-predicates", robustPredicates,
                        "Uses Robust Predicates. '0' doesn't use Robust Predicates, '1' uses Robust Predicates.\n"
                        "(Default: 1)\n");

        app->add_flag("-d,--validate-delaunay", validateDelaunayProperty,
                      "Validates the Delaunay Property of the triangulation.\n");

        app->add_option("-o,--output", outputFileName,
                        "Output file that includes triangulation.\n")
                ->required();

        try {
            app->parse(argc, argv);
        }
        catch (const CLI::CallForHelp& e) {
            std::cout << app->help();
            return 1;
        }
        catch (const CLI::CallForAllHelp& e) {
            std::cout << app->help();
            return 1;
        }
        catch (const CLI::ParseError& e) {
            return app->exit(e);
        }

        return 0;
    }

    void display(std::ostream& out = std::cout)
    {
        out << std::endl
            << "                         ██████╗ ███████╗██╗      █████╗ ██╗   ██╗███╗   ██╗ █████╗ ██╗   ██╗                \n"
            << "                         ██╔══██╗██╔════╝██║     ██╔══██╗██║   ██║████╗  ██║██╔══██╗╚██╗ ██╔╝                \n"
            << "                         ██║  ██║█████╗  ██║     ███████║██║   ██║██╔██╗ ██║███████║ ╚████╔╝                 \n"
            << "                         ██║  ██║██╔══╝  ██║     ██╔══██║██║   ██║██║╚██╗██║██╔══██║  ╚██╔╝                  \n"
            << "                         ██████╔╝███████╗███████╗██║  ██║╚██████╔╝██║ ╚████║██║  ██║   ██║                   \n"
            << "                         ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝   ╚═╝                   \n"
            << "                                                                                                             \n"
            << "      ████████╗██████╗ ██╗ █████╗ ███╗   ██╗ ██████╗ ██╗   ██╗██╗      █████╗ ████████╗██╗ ██████╗ ███╗   ██╗\n"
            << "      ╚══██╔══╝██╔══██╗██║██╔══██╗████╗  ██║██╔════╝ ██║   ██║██║     ██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║\n"
            << "         ██║   ██████╔╝██║███████║██╔██╗ ██║██║  ███╗██║   ██║██║     ███████║   ██║   ██║██║   ██║██╔██╗ ██║\n"
            << "         ██║   ██╔══██╗██║██╔══██║██║╚██╗██║██║   ██║██║   ██║██║     ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║\n"
            << "         ██║   ██║  ██║██║██║  ██║██║ ╚████║╚██████╔╝╚██████╔╝███████╗██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║\n"
            << "         ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝\n"
            << std::endl;

        constexpr char SEPARATOR[] = "================================================";
        out << "DelaunayTriangulation Argument Values" << std::endl;;
        out << SEPARATOR << std::endl;;

        const auto yesNo = [](bool val) -> std::string {
            return val ? "yes" : "no";
        };

        if (!inputFileName.empty()) {
            out << "Input vertices file: " << inputFileName << std::endl;;
        } else {
            out << "Number of random uniform vertices: " << numberOfRandomVertices << std::endl;
        }
        out << "Use Robust Predicates: " << yesNo(robustPredicates) << std::endl;
        out << "Validate Delaunay property: " << yesNo(validateDelaunayProperty) << std::endl;
        out << "Output Mesh file: " << outputFileName << std::endl;;
        out << SEPARATOR << std::endl;;
    }
}

