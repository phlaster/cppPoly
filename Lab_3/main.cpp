#include "headers/TaskManagers.hpp"
#include "headers/EduGroup.hpp"
#include "headers/Teacher.hpp"
#include "headers/funcs.hpp"

int main(int argc, char** argv){
    srand( (unsigned)time(NULL) );
    int n_tasks = 5;
    int n_studs = 5;
    if (argc == 3){
        n_studs = std::stoi(argv[1]);
        n_tasks = std::stoi(argv[2]);
    }

    EQ_Manager& eqm = EQ_Manager::getInstance();
    eqm.generate(n_tasks, "eqs.txt");

    EduGroup group(n_studs, "gdir");
    group.assign("eqs.txt");
    group.solve();


    Teacher teacher;
    teacher.check(eqm, group);
    teacher.printScore(group);

    // for (auto & filename : allfiles("gdir")){
    //     auto [name, res] = eqm.check("gdir/"+filename);
    //     std::cout <<filename <<"  "<< res << std::endl;
    // }

    return 0;
}