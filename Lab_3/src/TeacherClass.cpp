#include "StudentModel.hpp"
#include "Teacher.hpp"
#include <iostream>

void teacher::checkWorks(vector <equation>& eqList, queue <student*>& completed) {
        for (size_t i = 0; i < eqList.size(); ++i) {
                answer ans;
                solver(eqList.at(i), ans);
                _rightAns.push_back(ans);
        }
        _totalCntOfEqs = eqList.size();
        while (!completed.empty()) {
                result res;
                res.studentName = completed.front()->getname();
                for (size_t i = 0; i < eqList.size(); ++i)
                        if (_rightAns.at(i) == completed.front()->getroots().at(i))
                                res.rightAns++;
                double percent = res.rightAns / (double)eqList.size() * 100;
                if (percent < 50)
                        res.grade = 2;
                else if (percent >= 50 && percent < 65)
                        res.grade = 3;
                else if (percent >= 65 && percent < 90)
                        res.grade = 4;
                else
                        res.grade = 5;
                _resAllStudents.push_back(res);
                delete completed.front();
                completed.pop();
        }
}


// void teacher::printTable() {
//     using namespace std;
//     int nameLen = 0;
//     for (const auto& student : _resAllStudents) {
//         nameLen = max(nameLen, static_cast<int>(student.studentName.length()));
//     }
//     int tableWidth = nameLen + 16;
    
//     cout << "+" << setfill('-') << setw(tableWidth) << "+" << endl;
//     cout << "| " << setfill(' ') << setw(nameLen) << left << "Name" << " |  Solved  |  Grade  |" << endl;
//     cout << "+" << setfill('-') << setw(tableWidth) << "+" << endl;
//     for (const auto& student : _resAllStudents) {
//         cout << "| " << setw(nameLen) << left << student.studentName << " |  " << setw(7) << setfill(' ') << student.rightAns << "/" << _totalCntOfEqs << "  |    " << setw(3) << setfill(' ') << student.grade << "   |" << endl;
//         cout << "+" << setfill('-') << setw(tableWidth) << "+" << endl;
//     }
// }

void teacher :: printTable() {
        using namespace std;
        int nameLen = 40;
        cout << "+" << setfill('-') << setw(74) << "+" << endl;
        cout << "||" << setfill(' ') << setw(20) << "Имя" << setfill(' ') << setw(50)<< "| Решено  | Оценка || " << endl;
        cout << "+" << setfill('-') << setw(74) << "+" << endl;
        for (size_t i = 0; i < _resAllStudents.size(); ++i) {
                cout << "|| " << _resAllStudents.at(i).studentName << setfill(' ') << setw(nameLen - _resAllStudents.at(i).studentName.length()) << "|   " << _resAllStudents.at(i).rightAns << "/" << _totalCntOfEqs << "   |    " << _resAllStudents.at(i).grade << "   ||" << endl;
                cout << "+" << setfill('-') << setw(74) << "+" << endl;
        }
}