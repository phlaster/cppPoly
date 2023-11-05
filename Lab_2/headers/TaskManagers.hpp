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
    virtual std::pair<std::string, bool> check(const std::string& filename) const = 0;
};

// class EQ_Manager : public AbstractTaskManager {
// public:
//     void generate(int n, const std::string& filename) override;
//     std::pair<std::string, bool> check(const std::string& filename) override;

// private:
//     std::vector<int> generateEq();
//     std::string equationWithSolution();
//     bool isCorrectSolution(const std::vector<int>&coeffs, const std::vector<double>& givenRoots);
// };

class EQ_Manager : public AbstractTaskManager {
public:
    static EQ_Manager& getInstance() {
        static EQ_Manager instance;
        return instance;
    }

    void generate(int n, const std::string& filename) override;
    std::pair<std::string, bool>
    check(const std::string& filename) const override;

    EQ_Manager(const EQ_Manager&) = delete;
    EQ_Manager& operator=(const EQ_Manager&) = delete;

private:
    EQ_Manager() = default;

    std::vector<int> generateEq();
    std::string equationWithSolution();
    bool isCorrectSolution(
    const std::vector<int>& coeffs, const std::vector<double>& givenRoots) const;
};


#endif // TASKMNGR_HPP