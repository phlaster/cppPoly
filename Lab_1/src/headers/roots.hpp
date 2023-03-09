#include <vector>

#ifndef ROOTSTYPE_HPP
#define ROOTSTYPE_HPP
enum RootsType
{
    PAIR_OF_REAL,      // 0
    SINGLE_REAL,       // 1
    CONJUGATED_COMPLEX,// 2
    WRONG_COEFICIENTS, // 3
    ROOT_ERROR         // 4
};
#endif


#ifndef ROOTS_HPP
#define ROOTS_HPP
struct Roots
{
    RootsType rootsType = ROOT_ERROR;
    std::vector<double> roots{0.0,0.0};
};
#endif
