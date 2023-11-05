#include "StudentModel.hpp"

bool answer::operator == (const answer ans) const {
        if (this->cnt == ans.cnt && this->x1 == ans.x1 && this->x2 == ans.x2)
                return true;
        else
                return false;
}

string student :: getname() {
        return _fullname;
}
vector <answer> student :: getroots() {
        return _roots;
}
void student :: sendAnswers(queue <student*>& q) {
        q.push(this);
}
void goodStudent :: solveEq(vector <equation>& eqList) {
        for (size_t i = 0; i < eqList.size(); ++i) {
                answer ans;
                solver(eqList.at(i), ans);
                _roots.push_back(ans);
        }
}
void badStudent :: solveEq(vector <equation>& eqList) {
        for (size_t i = 0; i < eqList.size(); ++i) {
                answer ans;
                ans.cnt = 1;
                ans.x1 = ans.x2 = 0;
                _roots.push_back(ans);
        }
}
void normStudent :: solveEq(vector <equation>& eqList) {
        for (size_t i = 0; i < eqList.size(); ++i) {
                if (rand() % 2 == 1) {
                        answer ans;
                        solver(eqList.at(i), ans);
                        _roots.push_back(ans);
                }
                else {
                        answer ans;
                        ans.cnt = 1;
                        ans.x1 = ans.x2 = 0;
                        _roots.push_back(ans);
                }
        }
}