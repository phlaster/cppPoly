#include <vector>
#include <iostream>
#include "headers/solve.hpp"
#include "headers/print.hpp"
using namespace std;


int main(){
	double a = 0;
	double b = 0;
	double c = 0;
    input(&a,&b,&c);
    print(solve(a,b,c));
	return 0;
}
