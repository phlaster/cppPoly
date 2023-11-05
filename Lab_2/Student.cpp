#include "headers/Student.hpp"
#include "headers/funcs.hpp"
#include <string>

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

Student::Student() {
    if (rand()%2){
        int name_id = rand()%names_m.size();
        int surname_id = rand()%surnames.size();
        this->name = names_m[name_id] + " " + surnames[surname_id];

    } else{
        int name_id = rand()%names_f.size();
        int surname_id = rand()%surnames.size();
        this->name = names_f[name_id] + " " + surnames[surname_id]+"a";

    }
    // 0%, 50%, 100%
    this->goodness = rand()%3 / 2.0;
}

Student::Student(const std::string& name, double prob) :
    name(name), goodness(prob){}

void Student::takeTask(const std::string& eqLine){
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

void Student::_solve_task_exact(const std::vector<int>& eq){
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

void Student::try_solve_task(std::vector<int> eq){
    if (rand()%100 < 100*goodness){
        _solve_task_exact(eq);
    } else {
        std::vector<double> res = {0.0,0.0};
        solved.push_back(std::make_pair(eq, res));
    }
    return;
}

void Student::solve_all(){
    while (!assigned.empty()){
        try_solve_task(assigned.back());
        assigned.pop_back();
    }
}
void Student::publish(const std::string& dirname){
    while (!solved.empty()){
        auto the_solution = solved.back();
        std::string outname = dirname + SEP + name + "_" + randstr(10) + ".txt";
        std::ofstream outsream(outname);
        if (!outsream.is_open()) {
            std::cerr << "Не удалось открыть " << outname << " для записи..." << std::endl;
            exit(1);
        }
        outsream
            << std::to_string(the_solution.first[0]) << " "
            << std::to_string(the_solution.first[1]) << " "
            << std::to_string(the_solution.first[2]) << std::endl;
        outsream
            << std::to_string(the_solution.second[0]) << " "
            << std::to_string(the_solution.second[1]) << std::endl;
        outsream << name << std::flush;
        outsream.close();
        solved.pop_back();
    }
}

std::string Student::getname()const{
    return this->name;
}
double Student::getgood()const{
    return this->goodness;
}
