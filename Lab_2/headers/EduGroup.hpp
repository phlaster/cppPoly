#ifndef EDUGROUP_HPP
#define EDUGROUP_HPP

#include <map>
#include <string>
#include <fstream>
#include "Student.hpp"

class AbstractGroup {};

class EduGroup : public AbstractGroup {
    friend class Teacher;
    std::map<std::string, Student> students;
    std::string groupname;
public:
    EduGroup(const std::string& groupname);
    EduGroup(int n, const std::string& groupname);
    size_t size() const;
    std::string getname() const;
    bool hasStudent(const std::string& name) const;
    void add(const std::string& name, double prob);
    void remove(const std::string& name);
    void assign(const std::string& filename);
    void solve();
};

#endif //EDUGROUP_HPP