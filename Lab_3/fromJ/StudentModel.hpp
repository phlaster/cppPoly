#ifndef STUDMODEL_HPP
#define STUDMODEL_HPP
#include "StudentsMetods.hpp"

class student {
public:
        student(string& fullname) : _fullname(fullname) {}
        string getname();
        vector <answer> getroots();
        void sendAnswers(queue <student*>& q);
protected:
        string _fullname;
        vector <answer> _roots;
};

class goodStudent : public student {
public:
        goodStudent(string fullname) : student(fullname) {};
        void solveEq(vector <equation>& eqList);
};

class badStudent : public student {
public:
        badStudent(string fullname) : student(fullname) {};
        void solveEq(vector <equation>& eqList);
};

class normStudent : public student {
public:
        normStudent(string fullname) : student(fullname) {};
        void solveEq(vector <equation>& eqList);
};

#endif