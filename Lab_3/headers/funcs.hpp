#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <iostream>
#include <dirent.h>
#include <random>
#include <string>
#include <filesystem>
#include <sys/stat.h>

void checkdir(const std::string& dirname);
std::string randstr(int n);
std::vector<std::string> allfiles(const std::string& path);

#endif //FUNCS_HPP