#include <vector>

#ifndef ISAPPROX_HPP
#define ISAPPROX_HPP
bool isapprox(double a, double b, double tolerance=1e-9);
bool isapprox(const std::vector<double>& v1, const std::vector<double>& v2, double tolerance=1e-9);
#endif
