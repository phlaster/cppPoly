#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iomanip>
// #include "EduGroup.hpp"


#if defined _WIN32
const std::string SEP = "\";
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
const std::string SEP = "/";
#elif defined (__APPLE__)
const std::string SEP = "/";
#endif

class Student {
private:
    friend class EduGroup;

    std::string name;
    double goodness;
    std::vector<std::vector<int>> assigned;
    std::vector<std::pair<std::vector<int>, std::vector<double>>> solved;

    void takeTask(const std::string& eqLine);
    void _solve_task_exact(const std::vector<int>& eq);
    void try_solve_task(std::vector<int> eq);
    void solve_all();
    void publish(const std::string& dirname);

public:
    Student();
    Student(const std::string& name, double prob);

    std::string getname()const;
    double getgood()const;
};

#endif //STUDENT_HPP