#include <fstream>
#include "StudentModel.hpp"
#include "Teacher.hpp"


const vector <string> firstName = {
        "Иван Иванов",
        "Пётр Петров",
        "Илья Ильин",
        "Александра Александрова",
        "Евгения Евгеньева",
};

void readFile(vector<equation>& eqList) {
        std::ifstream input("Eqs.txt");
        if (!input.is_open())
                return;
        equation eq;
        while (input >> eq.a >> eq.b >> eq.c) {
                eqList.push_back(eq);
        }
        input.close();
        return;
}

void fillStudentQueue(queue <student*>& completed, vector <equation>& eqList) {
        goodStudent* stud1;
        normStudent* stud2;
        badStudent* stud3;
        int random;
        for (size_t i = 0; i < firstName.size(); ++i) {
                random = rand() % 3;
                switch (random) {
                case 0:
                        stud1 = new goodStudent(firstName.at(i));
                        stud1->solveEq(eqList);
                        stud1->sendAnswers(completed);
                        break;
                case 1:
                        stud2 = new normStudent(firstName.at(i));
                        stud2->solveEq(eqList);
                        stud2->sendAnswers(completed);
                        break;
                case 2:
                        stud3 = new badStudent(firstName.at(i));
                        stud3->solveEq(eqList);
                        stud3->sendAnswers(completed);
                        break;
                }
        }
}

int main() {
        setlocale(LC_ALL, "Russian");
        queue <student*> completed;
        vector <equation> eqList;
        readFile(eqList);
        fillStudentQueue(completed, eqList);
        teacher teach("teacher");
        teach.checkWorks(eqList, completed);
        teach.printTable();
        return 0;
}