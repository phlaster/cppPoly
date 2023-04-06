#include <string>
#include <fstream>
#include <iostream>
#include <limits>
#include <tclap/CmdLine.h>

#include "headers/solve.hpp"
#include "headers/print.hpp"
#include "headers/roots.hpp"

void interactive()
{
    double a, b, c;
    input(&a,&b,&c);
    print(solve(a,b,c));
}


int main(int argc, char **argv)
{
try
{
    // Comand line arguments parser
    TCLAP::CmdLine cmd
    (
        "Quadratic solver",
        ' ',
        "0.1.0"
    );
	TCLAP::ValueArg<std::string> inputName
	(
	    "f",
	    "file",
	    "Name of file to get the coefficients from.\nIf not given, the program will work in interactive mode\n(no output file).",
	    false,
	    "input.txt",
	    "string"
	);
	TCLAP::ValueArg<std::string> outputName
    (
        "o",
        "output",
        "Name of file to write the results to. 'results.txt' by default.",
        false,
        "results.txt",
        "string"
    );
	cmd.add(inputName);
	cmd.add(outputName);
	cmd.parse( argc, argv );

	// Begin of logic (REPL)
    if (!inputName.isSet())
    {
        std::cout << "Entering REPL, to terminate press Ctrl+C\n";
        while (true)
        {
            if (std::cin.fail())
            {
                std::cout << "Invalid input. Try again.\n\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else interactive();
        }
    }

    // File mode
    else
    {
        std::ifstream inputFile(inputName.getValue());
        if (inputFile.is_open())
        {
            std::string line;
            std::ofstream outputFile;
            outputFile.open(outputName.getValue(), std::ios::out);
            
            while (std::getline(inputFile, line))
            {
                std::vector<double> abc = parseLine(line);
                if (abc.empty())
                {
                    Roots emptyRoot;
                    printLineToFile(outputFile, emptyRoot);
                    continue;
                } 
                Roots roots = solve(abc[0], abc[1], abc[2]);
                printLineToFile(outputFile, roots);                           
            }
            inputFile.close();
            outputFile.close();
            std::cout << "File written successfully." << std::endl;
        } else {
            std::cerr\
            << "Error: could not open "\
            << inputName.getValue()\
            << std::endl;
        }
    }
}

catch (TCLAP::ArgException &e)
{
    std::cerr\
    << "Error: "\
    << e.error()\
    << " for arg "\
    << e.argId()\
    << std::endl;
}
}
