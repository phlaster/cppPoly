#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "headers/roots.hpp"


void input(double * a, double * b, double * c)
{
    std::cout << "Enter coefficients" << std::endl;
    std::cin >> *a >> *b >> *c;
    std::cout << "Your quadratic is:\n" <<\
    *a << "x²+" << *b << "x+" << *c << "=0" << std::endl; // sry for unicode
}

void print(Roots roots)
{
    switch (roots.rootsType)
    {
        case PAIR_OF_REAL:
            std::cout <<"Your quadratic has 2 real roots:\n"\
            <<roots.roots[0]<<", "<<roots.roots[1]<<std::endl;
            break;
        case CONJUGATED_COMPLEX:
            std::cout <<"Your quadratic has 2 complex conjugated roots:\n"\
            <<roots.roots[0]<<" ± "<<roots.roots[1]<<'i'<<std::endl;
            break;
        case SINGLE_REAL:
            std::cout << "Your quadratic has real root of multiplicity 2:\n"\
            <<roots.roots[0] << std::endl;
            break;
        case WRONG_COEFICIENTS:
            std::cout << "Incorrect coefficients:\n"\
            "a must be nonzero" << std::endl;
            break;
        default:
            std::cout << "Some error ocurred..." << std::endl;
            
    }
}

void printLineToFile(std::ofstream &outputFile, Roots roots)
{
    if (outputFile.is_open())
    {
        switch(roots.rootsType)
        {
            case PAIR_OF_REAL:
                outputFile << roots.roots[0] << "," << roots.roots[1] << std::endl;
                break;
            case SINGLE_REAL:
                outputFile << roots.roots[0] << "," << roots.roots[0] << std::endl;
                break;
            case CONJUGATED_COMPLEX:
                outputFile\
                << roots.roots[0] << "+" << roots.roots[1] << "i,"\
                << roots.roots[0] << "-" << roots.roots[1] << "i"\
                << std::endl;
                break;
            case WRONG_COEFICIENTS:
                outputFile << "Wrong coefficients!" << std::endl;
                break;
            default:
                outputFile << "Error!" << std::endl;
                break;
        }
    }
    else{
        std::cerr << "Failed to open output file." << std::endl;
    }
}

std::vector<double> parseLine(std::string line, char sepSymb=',')
{
    std::stringstream ss(line);
    double a, b, c;
    char sep;
    ss >> a >> sep >> b >> sep >> c;
    if (sep!=sepSymb)
    {
        std::cout << "Only lines with '"<< sepSymb << "' separator can be parsed!\n";
        return {};
    }
    std::vector<double> result = {a, b, c};
    return result;
}
