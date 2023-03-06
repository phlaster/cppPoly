#include <vector>

#ifndef SOLVE_HPP
#define SOLVE_HPP
std::vector<double> solve(double a, double b, double c);
#endif

#ifndef SWAP_HPP
#define SWAP_HPP
void swap(std::vector<double>& v, int i1, int i2);
#endif


#ifndef DISCR_HPP
#define DISCR_HPP
double discr(double a, double b, double c);
#endif

#ifndef COEFCHECK_HPP
#define COEFCHECK_HPP
int coefCheck(double a, double b, double c);
#endif

#ifndef REALROOTS_HPP
#define REALROOTS_HPP
std::vector<double> realRoots(double a, double b, double c);
#endif

#ifndef PAIRROOTS_HPP
#define PAIRROOTS_HPP
std::vector<double> pairRoots(double a, double b);
#endif

#ifndef COMPLEXROOTS_HPP
#define COMPLEXROOTS_HPP
std::vector<double> complexRoots(double a, double b, double c);
#endif
