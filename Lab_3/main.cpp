#include <iostream>
#include <set>
#include <utility>
#include "headers/TaskManagers.hpp"

class AbstractGroup {
protected:
    std::set<std::string> students;

public:
    AbstractGroup() : students() {}
    size_t size(){
        return students.size();
    };

    void add(const std::string& name) {
        students.insert(name);
    }

    void remove(const std::string& name){
        if (!students.count(name)){
            std::cerr << "Нельзя удалить отсутствующего студента!" << std::endl;
        } else {
            students.erase(name);
        }
    }
};

class EduGroup : protected AbstractGroup {
public:
    
};



const std::vector<std::string> names_m = {
    "Егор",
    "Арсений",
    "Дмитрий",
    "Тимофей",
    "Артём",
    "Михаил",
    "Даниил",
    "Григорий",
    "Матвей",
    "Тигран",
    "Тихон",
    "Максим",
    "Фёдор",
    "Всеволод",
    "Александр"
};
const std::vector<std::string> names_f = {
    "Василиса",
    "Варвара",
    "Алёна",
    "Полина",
    "Ульяна",
    "Милана",
    "Алисия",
    "Виктория",
    "Екатерина",
    "Валерия",
    "Карина",
    "Елизавета",
    "Александра",
    "Людмила",
    "Таисия"
};
const std::vector<std::string> surnames = {
    "Баранов",
    "Семенов",
    "Гущин",
    "Гончаров",
    "Поляков",
    "Михайлов",
    "Фокин",
    "Кузнецов",
    "Дорохов",
    "Дьяков",
    "Корнев",
    "Никонов",
    "Иванов",
    "Черепанов",
    "Дегтярев",
    "Жуков",
    "Ермаков",
    "Иванов",
    "Зайцев",
    "Куликов",
    "Акимов",
    "Шувалов",
    "Третьяков",
    "Богомолов",
    "Борисов",
    "Максимов",
    "Попов",
    "Панкратов",
    "Гусев",
    "Прокофьев"
};

class Student {
    std::string name;
    double goodness;
    std::vector<std::vector<int>> assigned;
    std::vector<std::pair<std::vector<int>, std::vector<double>>> solved;

    void takeTask(const std::string& eqLine){
        std::stringstream ss(eqLine);
        std::vector<int> task;
        int num;
        while (ss >> num) {
            task.push_back(num);
        }
        if (task.size() != 3){
            std::cerr << "В задании должно быть 3 коэффициента!" << std::endl;
            exit(1);
        }
        assigned.push_back(task);
    }

    void _solve_task_exact(const std::vector<int>& eq){
        std::vector<double> res = {0.0,0.0};
        double D = eq[1]*eq[1] - 4*eq[0]*eq[2];
        if (D < 0.0){
            solved.push_back(std::make_pair(eq, res));
        } else {
            res[0] = (-eq[1] + std::sqrt(D))/2/eq[0];
            res[1] = (-eq[1] - std::sqrt(D))/2/eq[0];
            solved.push_back(std::make_pair(eq, res));
        }
        return;
    }

    void try_solve_task(std::vector<int> eq){
        if (rand()%100 < 100*goodness){
            _solve_task_exact(eq);
        } else {
            std::vector<double> res = {0.0,0.0};
            solved.push_back(std::make_pair(eq, res));
        }
        return;
    }

    void solve_all(){
        while (!assigned.empty()){
            try_solve_task(assigned.back());
            assigned.pop_back();
        }
    }

    friend EduGroup;

public:
    Student() {
        if (rand()%2){
            int name_id = rand()%names_m.size();
            int surname_id = rand()%surnames.size();
            this->name = names_m[name_id] + " " + surnames[surname_id];

        } else{
            int name_id = rand()%names_f.size();
            int surname_id = rand()%surnames.size();
            this->name = names_m[name_id] + " " + surnames[surname_id]+"a";

        }
        // 0%, 50%, 100%
        this->goodness = rand()%3 / 2.0;
    }
    Student(const std::string& name, double prob) : name(name), goodness(prob){}

    std::string getname(){
        return this->name;
    }
    double getgood(){
        return this->goodness;
    }
};


int main(int argc, char** argv){
    int n = 5;
    if (argc == 2){
        n = std::stoi(argv[1]);
    }

    EQ_Manager eqm;
    eqm.generate(n, "eqs.txt");

    // EduGroup group(n, "gdir");
    // group.assign("eqs.txt");
    // group.solve();

    // Teacher teacher;
    // teacher.check(eqm, "gdir");
    // teacher.printScore("score.txt");


    return 0;
}