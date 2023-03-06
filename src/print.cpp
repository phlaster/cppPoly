#include <vector>
#include <iostream>
using namespace std;

void input(double * a, double * b, double * c){
    cout << "Enter coefficients" << endl;
    cin >> *a >> *b >> *c;
    cout << "Your quadratic is:" << endl;
    cout <<*a<<"x²+"<<*b<<"x+"<<*c<<"=0"<<endl;
}

void print(vector<double> roots){
    switch (int(roots[2])){
        case 1:
            cout <<"Your quadratic has 2 real roots:\n"<<roots[0]<<", "<<roots[1]<<endl;
            break;
        case -1:
            cout <<"Your quadratic has 2 complex conjugated roots:\n"<<roots[0]<<"±"<<roots[1]<<'i'<<endl;
            break;
        case 2:
            cout << "Your quadratic has real root of multiplicity 2:\n"<<roots[0]<<endl;
            break;
        default:
            cout << "Incorrect coefficients" << endl;
    }
}
