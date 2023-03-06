#include <assert.h>
#include <iostream>
#include "../src/headers/sqrt.hpp"
#include "testfuncs.hpp"


int main() {
    assert(abs(3) == 3);
    assert(abs(-2.4) == 2.4);

    assert(min(3, 0) == 0);
    assert(min(-2, 4) == -2);

    assert(max(3, 0) == 3);
    assert(max(10, 2.5) == 10);

    assert(sqr(5) == 25);
    assert(isapprox(sqr(-3.3), 10.89));

    assert(isapprox(average(3,5), 4));
    
    assert(isapprox(improve(1,10), 5.5));
    assert(isapprox(improve(10,1), 5.05));

    assert(goodGuess(5.099, 26, 1e-2));
    assert(!goodGuess(2, 4.5, 0.1));

    assert(isapprox(sqrt(9), 3));
    assert(!isapprox(sqrt(9), 3+1e-7));
        
    std::cout << "sqrt: All tests passed!" << std::endl;    
    return 0;
}
