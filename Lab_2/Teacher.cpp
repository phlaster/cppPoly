#include "headers/Teacher.hpp"
#include "headers/EduGroup.hpp"
#include "headers/funcs.hpp"


void Teacher::check(const EQ_Manager& eqm, const EduGroup& group){
    std::string groupname = group.getname();
    std::map<std::string, std::pair<int,int>> journal;
    for (const auto & [name, account] : group.students) {
        journal[name] = std::make_pair(0, 0);
    }

    for (const auto& file : allfiles(groupname)){
        auto [name, correct] = eqm.check(groupname+SEP+file);
        if (group.hasStudent(name)){
            auto& [score, total] = journal[name];
            score += (int)correct;
            total++;
        } else {
            std::cerr << "Студент " << name << " не из этой группы." << std::endl;
        }
    }
    groupJournals[groupname] = journal;  
}


void Teacher::printScore(const EduGroup& group){
    std::cout << "Результаты группы " << group.getname() << ":" << std::endl;
    for (auto &[student_name, results] : groupJournals[group.getname()]){
        std::cout << student_name << ": " << results.first<<"/"<<results.second << " ("<<group.students.at(student_name).getgood()<<")" << std::endl;
    }
}