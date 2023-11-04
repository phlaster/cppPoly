#include "headers/TaskManagers.hpp"

void 
EQ_Manager::generate(int n, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < n; i++) {
            std::string equation = equationWithSolution(); // Функция для генерации уравнения
            file << equation << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Не удалось создать файл с заданиями" << std::endl;
    }
}

std::pair<std::string, bool>
EQ_Manager::check(const std::string& filename) {
    std::string line;
    std::vector<int> coeffs;
    std::vector<double> givenRoots;
    std::string name;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл с решением!" << std::endl;
        exit(1);
    }

    if (std::getline(file, line)) {
        std::stringstream ss(line);
        int num;
        while (ss >> num) {
            coeffs.push_back(num);
        }
    }

    if (std::getline(file, line)) {
        std::stringstream ss(line);
        double num;
        while (ss >> num) {
            givenRoots.push_back(num);
        }
    }

    if (std::getline(file, name)) {
        name.erase(0, name.find_first_not_of(" "));
        name.erase(name.find_last_not_of(" ") + 1);
    }
    file.close();

    bool result = isCorrectSolution(coeffs, givenRoots);

    return std::make_pair(name, result);
}

std::vector<int>
EQ_Manager::generateEq() {
    int a = (1 + rand() % 10) * std::pow(-1, (rand() % 2));
    int x1 = -(rand() % 5);
    int x2 = x1 + (rand() % 10);
    int b = -a*(x1+x2);
    int c = a*x1*x2;

    std::vector<int> eq({a,b,c});
    return eq;
}

std::string
EQ_Manager::equationWithSolution() {
    std::string equation_string;
    std::vector<int> eq = generateEq();
    for (int scalar : eq){
        equation_string += std::to_string(scalar) + " ";
    }
    equation_string.pop_back();
    return equation_string;
}

bool
EQ_Manager::isCorrectSolution(
    const std::vector<int>&coeffs, const std::vector<double>& givenRoots
    ){
    if (coeffs.size() != 3) {
        std::cerr << "Неверное количество коэффициентов в файле с решением!" << std::endl;
        exit(1);
    }
    if (givenRoots.size() != 2){
        std::cerr << "Решение должно состоять из двух корней, даже если они кратные!" << std::endl;
        exit(1);
    }
    bool good_x1 = std::fabs(coeffs[0] * givenRoots[0] * givenRoots[0] + coeffs[1] * givenRoots[0] + coeffs[2]) <= 1e-16;
    bool good_x2 = std::fabs(coeffs[0] * givenRoots[1] * givenRoots[1] + coeffs[1] * givenRoots[1] + coeffs[2]) <= 1e-16;

    return good_x1 && good_x2;
}