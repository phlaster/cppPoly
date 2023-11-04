#include <iostream>
#include "headers/TaskManagers.hpp"

int main(int argc, char** argv){
    int n = 5;
    if (argc == 2){
        n = std::stoi(argv[1]);
    }
    EQ_Manager eqm;
    eqm.generate(n, "eqs.txt");

    // EDU_Group group(n, "gdir");
    // group.assign("eqs.txt");
    // group.solve();

    // Teacher teacher;
    // teacher.check(eqm, "gdir");
    // teacher.printScore("score.txt");


    return 0;
}