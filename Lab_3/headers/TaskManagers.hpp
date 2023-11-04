#ifndef TASKMNGR_HPP
#define TASKMNGR_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

class AbstractTaskManager {
public:
    virtual void generate(int n, const std::string& filename) = 0;
    virtual std::pair<std::string, bool> check(const std::string& filename) = 0;
};

class EQ_Manager : public AbstractTaskManager {
public:
    void generate(int n, const std::string& filename) override;
    std::pair<std::string, bool> check(const std::string& filename) override;

private:
    std::vector<int> generateEq();
    std::string equationWithSolution();
    bool isCorrectSolution(const std::vector<int>&coeffs, const std::vector<double>& givenRoots);
};

#endif // TASKMNGR_HPP