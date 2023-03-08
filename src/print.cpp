#include <vector>
#include <iostream>
#include "headers/roots.hpp"
using namespace std;

void input(double * a, double * b, double * c){
    cout << "Enter coefficients" << endl;
    cin >> *a >> *b >> *c;
    cout << "Your quadratic is:\n" <<\
    *a << "x²+" << *b << "x+" << *c << "=0" <<endl;
}

void print(Roots roots){
    switch (roots.rootsType){
        case PAIR_OF_REAL:
            cout <<"Your quadratic has 2 real roots:\n"\
            <<roots.roots[0]<<", "<<roots.roots[1]<<endl;
            break;
        case CONJUGATED_COMPLEX:
            cout <<"Your quadratic has 2 complex conjugated roots:\n"\
            <<roots.roots[0]<<" ± "<<roots.roots[1]<<'i'<<endl;
            break;
        case SINGLE_REAL:
            cout << "Your quadratic has real root of multiplicity 2:\n"\
            <<roots.roots[0]<<endl;
            break;
        case WRONG_COEFICIENTS:
            cout << "Incorrect coefficients:\n"\
            "a must be nonzero" << endl;
            break;
        default:
            cout << "Some error ocurred..." << endl;
            
    }
}
