#ifndef TEACHER_HPP
#define TEACHER_HPP
#include "StudentsMetods.hpp"
#include "StudentModel.hpp"

struct result {
    string studentName;
    int rightAns = 0, grade = 2;
};

class teacher {
public:
    teacher(string name) : _totalCntOfEqs(0), _name(name) {};
    void checkWorks(vector <equation>& eqList, queue <student*>& completed);
    void printTable();
private:
    vector <result> _resAllStudents;
    int _totalCntOfEqs;
    string _name;
    vector <answer> _rightAns;
};

#endif