#include "headers/solve.hpp"
#include "headers/print.hpp"
#include "headers/roots.hpp"


int main()
{
    double a, b, c;
    input(&a,&b,&c);
    print(solve(a,b,c));
    return 0;
}
