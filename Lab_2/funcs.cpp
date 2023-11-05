#include "headers/funcs.hpp"

void checkdir(const std::string& dirname) {
    DIR* dir = opendir(dirname.c_str());
    if (dir == nullptr) {
        int status = mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (status == 0) {
            std::cout << "Создана директория для группы " << dirname << std::endl;
        } else {
            std::cerr << "Не удалось создать директорию для группы " << dirname << std::endl;
            exit(1);
        }
    } else {
        std::cout << "Директория группы " << dirname << " уже существует" << std::endl;
    }
    closedir(dir);
}

std::string randstr(int n) {
    const std::string alphanumeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, alphanumeric.length() - 1);

    std::string result;
    for (int i = 0; i < n; ++i) {
        result += alphanumeric[dis(gen)];
    }
    return result;
}


std::vector<std::string> allfiles(const std::string& path) {
    std::vector<std::string> res;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            res.push_back(entry.path().filename().string());
        }
    }
    return res;
}