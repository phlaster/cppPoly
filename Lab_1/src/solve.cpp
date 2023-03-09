#include <vector>
#include "headers/sqrt.hpp"
#include "headers/roots.hpp"


void swap(std::vector<double>& v, int i, int j)
{
    v[i] = v[i] + v[j];
    v[j] = v[i] - v[j];
    v[i] = v[i] - v[j];
}


double discr(double a, double b, double c)
{
    return sqr(b) - 4.0 * a * c;
}


RootsType coefCheck(double a, double b, double c, double eps=1e-9)
{
    if (abs(a) < eps)
        return WRONG_COEFICIENTS;
    double d = discr(a,b,c);
    if (abs(d) < eps)
        return SINGLE_REAL;
    if (d > eps)
        return PAIR_OF_REAL;
    if (d < -eps)
        return CONJUGATED_COMPLEX;
    return ROOT_ERROR;
}


std::vector<double> realRoots(double a, double b, double c)
{
    double d = discr(a, b, c);
    double sqrtd = sqrt(d);
    
    std::vector<double> roots
    {
        (-b - sqrtd)/(2.0 * a),
        c != 0 ? (-b + sqrtd)/(2.0 * a) : 0.0
    };
    if (roots[0] > roots[1]) swap(roots, 0,1);
    return roots;
}


std::vector<double> pairRoots(double a, double b)
{
    std::vector<double> roots(2.0 , -b/(2.0 * a));
    return roots;
}


std::vector<double> complexRoots(double a, double b, double c)
{
    double d = discr(a, b, c);
    
    std::vector<double> roots
    {
        -b/(2.0 * a),
        sqrt(abs(d))/(2.0 * a)
    };
        return roots;
}


Roots solve(double a, double b, double c)
{
    switch (coefCheck(a,b,c))
    {
        case PAIR_OF_REAL:
            return Roots({PAIR_OF_REAL,  realRoots(a, b, c)});
        case CONJUGATED_COMPLEX:
            return Roots({CONJUGATED_COMPLEX, complexRoots(a,b,c)});
        case SINGLE_REAL:
            return Roots({SINGLE_REAL, pairRoots(a,b)});
        case WRONG_COEFICIENTS:
            return Roots({.rootsType=WRONG_COEFICIENTS});
        default:
            return Roots({.rootsType=ROOT_ERROR});
    }
}
