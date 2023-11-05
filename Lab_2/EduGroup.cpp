#include "headers/EduGroup.hpp"
#include "headers/Student.hpp"
#include "headers/funcs.hpp"

EduGroup::EduGroup(const std::string& groupname) : students(), groupname(groupname){
    checkdir(groupname);
}
EduGroup::EduGroup(int n, const std::string& groupname) : groupname(groupname) {
    checkdir(groupname);
    for (int i=0; i<n; i++){
        Student newstudent;
        students[newstudent.getname()] = newstudent;
    }
}
size_t EduGroup::size()const{
    return students.size();
};
std::string EduGroup::getname()const{
    return groupname;
};
bool EduGroup::hasStudent(const std::string& name) const{
    return students.count(name) > 0;
}
void EduGroup::add(const std::string& name, double prob) {
    if (!students.count(name)){
        students[name] = Student(name, prob);
    } else {
        std::cerr << "Такой студент уже есть в журнале!";
    }
}
void EduGroup::remove(const std::string& name){
    if (!students.count(name)){
        std::cerr << "Нельзя удалить отсутствующего студента!" << std::endl;
    } else {
        students.erase(name);
    }
}
void EduGroup::assign(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Файл с заданиями " << filename << " не найден" << std::endl;
        exit(1);
    }

    std::vector<std::string> names;
    for (const auto& pair : students) {
        names.push_back(pair.first);
    }
    int n = names.size(), i=0;
    std::string eq;
    while (std::getline(file, eq)) {
        students[names[i++%n]].takeTask(eq);
    }
    file.close();
}
void EduGroup::solve(){
    for (auto& pair : students){
        pair.second.solve_all();
        pair.second.publish(groupname);
    }
}
