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
EQ_Manager::check(const std::string& filename) const {
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
    ) const{
    if (coeffs.size() != 3) {
        std::cerr << "Неверное количество коэффициентов в файле с решением!" << std::endl;
        exit(1);
    }
    if (givenRoots.size() != 2){
        std::cerr << "Решение должно состоять из двух корней, даже если они кратные!" << std::endl;
        exit(1);
    }
    double _x1 =  givenRoots[0], _x2 = givenRoots[1],
        a = coeffs[0], b = coeffs[1], c = coeffs[2];
    double D = b*b - 4*a*c;

    if (D<0){
        return fabs(_x1) + fabs(_x2) < 1e-16;
    } else {
        double x1 = (-b+std::sqrt(D))/2/a;
        double x2 = (-b-std::sqrt(D))/2/a;

        return std::abs(std::max(x1,x2)-std::max(_x1,_x2)) < 1e-16 &&
            std::abs(std::min(x1,x2)-std::min(_x1,_x2)) < 1e-16;
    }
}