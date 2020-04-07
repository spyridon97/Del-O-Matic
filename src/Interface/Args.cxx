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
    size_t numberOfRandomPoints = 0;
    bool validateDelaunayProperty = false;
    std::string outputFileName;
    ////////////////////////////////////////////

    /**
     * @brief Parse Command line Arguments.
     *
     * @return 0 on success , otherwise CLI11 error code
     */
    int parseArguments(int argc, char** argv)
    {
        constexpr char DESCRIPTION[] = "DelaunayTriangulation";

        // Initialize CLI application
        std::unique_ptr<CLI::App> app = std::make_unique<CLI::App>(DESCRIPTION);

        ////////////////////////////////////////////
        // Add CLI Argument Options
        ////////////////////////////////////////////
        //  --------------------------------------------------------------------------  *

        auto inputFileOption = app->add_option("-i,--input", inputFileName, "Input file to triangulate.\n")
                ->check(CLI::ExistingFile);

        auto randomPointSetOption = app->add_option("-r, --random", numberOfRandomPoints,
                                                    "Generates and uniformly random set of N 2D points.\n")
                ->check(CLI::PositiveNumber);

        inputFileOption->excludes(randomPointSetOption);
        randomPointSetOption->excludes(inputFileOption);

        app->add_flag("-d,--validate-delaunay", validateDelaunayProperty,
                      "Validates the Delaunay Property of the triangulation.\n");

        app->add_option("-o,--output", outputFileName,
                        "Output file that includes triangulation.\n")
                ->required();

        app->final_callback([]() {
            if (numberOfRandomPoints == 0 && inputFileName.empty()) {
                throw (CLI::ValidationError("Use ither --input or --random options"));
            }
        });

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

    /**
     * @brief Display DelaunayTriangulation argument values.
     *
     * @param out Output stream to pipe output to
     */
    void display(std::ostream& out = std::cout)
    {
        out << std::endl
            << "  _____       _                                 _______   _                         _       _   _                        \n"
            << " |  __ \\     | |                               |__   __| (_)                       | |     | | (_)                      \n"
            << " | |  | | ___| | __ _ _   _ _ __   __ _ _   _     | |_ __ _  __ _ _ __   __ _ _   _| | __ _| |_ _  ___  _ __             \n"
            << " | |  | |/ _ \\ |/ _` | | | | '_ \\ / _` | | | |    | | '__| |/ _` | '_ \\ / _` | | | | |/ _` | __| |/ _ \\| '_ \\       \n"
            << " | |__| |  __/ | (_| | |_| | | | | (_| | |_| |    | | |  | | (_| | | | | (_| | |_| | | (_| | |_| | (_) | | | |           \n"
            << " |_____/ \\___|_|\\__,_|\\__,_|_| |_|\\__,_|\\__, |    |_|_|  |_|\\__,_|_| |_|\\__, |\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|\n"
            << "                                         __/ |                           __/ |                                           \n"
            << "                                        |___/                           |___/                                            \n"
            << std::endl << std::endl;

        constexpr char SEPARATOR[] = "================================================";
        out << "DelaunayTriangulation Argument Values" << std::endl;;
        out << SEPARATOR << std::endl;;

        const auto yesNo = [](bool val) -> std::string {
            return val ? "yes" : "no";
        };

        if (!inputFileName.empty()) {
            out << "Input Points file: " << inputFileName << std::endl;;
        } else {
            out << "Number of random uniform points: " << numberOfRandomPoints << std::endl;
        }
        out << "Validate Delaunay property: " << yesNo(validateDelaunayProperty) << std::endl;
        out << "Output Mesh file: " << outputFileName << std::endl;;
        out << SEPARATOR << std::endl;;
    }
}

