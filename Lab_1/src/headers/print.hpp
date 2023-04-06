#include <vector>
#include <fstream>
#include <string>
#include "roots.hpp"

#ifndef PRINT_HPP
#define PRINT_HPP
void print(Roots roots);
#endif

#ifndef INPUT_HPP
#define INPUT_HPP
void input(double * a, double * b, double * c);
#endif

#ifndef PRINT_LINE_TO_FILE_HPP
#define PRINT_LINE_TO_FILE_HPP
void printLineToFile(std::ofstream &outputFile, Roots roots);
#endif

#ifndef PARSELINE_HPP
#define PARSELINE_HPP
std::vector<double> parseLine(std::string line, char sepSymb=',');
#endif
