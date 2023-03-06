#include <assert.h>
#include <iostream>
#include <vector>
#include "testfuncs.hpp"
#include "../src/headers/solve.hpp"


int main() {
    assert(isapprox(discr(0,0,0),0));
    assert(isapprox(discr(1,1,1),-3));
    assert(isapprox(discr(5,-6,7),-104));
    
    assert(coefCheck(0,0,0) == 0);
    assert(coefCheck(2,4,2) == 2);
    assert(coefCheck(1,2,3) == -1);
    assert(coefCheck(-3,2,1) == 1);

    assert(isapprox(realRoots(-5,4,5)[0], -0.6770329614269));
    assert(isapprox(realRoots(-5,4,5)[1], 1.4770329614269));

    assert(isapprox(complexRoots(5,4,5)[0], -0.4));
    assert(isapprox(complexRoots(5,4,5)[1], 0.91651513899117));

    assert(isapprox(pairRoots(1,0)[0], 0));
    assert(isapprox(pairRoots(1, -0.5)[0], 0.25));

    std::vector<double> roots {-3, 1, 1};
    assert(isapprox(solve(1,2,-3), roots));

    roots = {-1, 1.4142135623731, -1};
    assert(isapprox(solve(1,2,3), roots));

    roots = {1, 1, 2};
    assert(isapprox(solve(1,-2,1), roots));

    roots = {0,0,0};
    assert(isapprox(solve(0,2,3), roots));

    roots = {1,0,0,1};
    swap(roots, 0,2);
    assert(isapprox(roots, {0,0,1,1}));

    
    std::cout << "solve: All tests passed!" << std::endl;    
    return 0;
}
