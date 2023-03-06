#include <vector>
#include "headers/sqrt.hpp"


void swap(std::vector<double>& v, int i1, int i2) {
    double temp = v[i1];
    v[i1] = v[i2];
    v[i2] = temp;
}


double discr(double a, double b, double c){
    return sqr(b) -4*a*c;
}


int coefCheck(double a, double b, double c){
    if (a == 0) return 0;
    double d = discr(a,b,c);
    if (d == 0) return 2;
    if (d > 0) return 1;
    if (d < 0) return -1;
    return 0;
}


std::vector<double> realRoots(double a, double b, double c){
    double d = discr(a, b, c);
    double sqrtd = sqrt(d);
    
    std::vector<double> roots {
        (-b - sqrtd)/(2*a),
        (-b + sqrtd)/(2*a)
    };
    if (roots[0] > roots[1]) swap(roots, 0,1);
    return roots;
}


std::vector<double> pairRoots(double a, double b){
    std::vector<double> roots(2, -b/(2*a));
    return roots;
}


std::vector<double> complexRoots(double a, double b, double c){
    double d = discr(a, b, c);
    
    std::vector<double> roots {
            -b/(2*a),
            sqrt(abs(d))/(2*a)
        };
        return roots;
}


std::vector<double> solve(double a, double b, double c){
    std::vector<double> ans(2);
    int check = coefCheck(a,b,c);
    switch (check) {
        case 1:
            ans = realRoots(a, b, c);
            ans.push_back(1);
            break;
        case -1:
            ans = complexRoots(a,b,c);
            ans.push_back(-1);
            break;
        case 2:
            ans = pairRoots(a,b);
            ans.push_back(2);
            break;
        default:
            ans.push_back(0);
    }
    return ans;
}
