#ifndef TEACHER_HPP
#define TEACHER_HPP

#include "EduGroup.hpp"
#include "TaskManagers.hpp"
#include <string>
#include <map>

class Teacher {
    std::map<std::string,std::map<std::string, std::pair<int,int>>> groupJournals;
    std::pair<std::string, bool> _check(const EQ_Manager& eqm, const std::string& filename);
public:
    // Teacher();
    void check(const EQ_Manager& eqm, const EduGroup& group);
    void printScore(const EduGroup& group);
};

#endif