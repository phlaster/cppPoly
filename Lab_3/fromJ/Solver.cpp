#include "StudentsMetods.hpp"

void solver(equation& eq, answer& roots) {
    double discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
    if (discriminant < 0) {
        roots.cnt = 0;
        roots.x1 = roots.x2 = 0;
        return;
    }
    else if (fabs(discriminant) < 1e-6){
        roots.cnt = 1;
        roots.x1 = roots.x2 = -eq.b / (2.0 * eq.a);
        if (fabs(roots.x1) < 1e-6)
            roots.x1 = roots.x2 = 0;
        return;
    }
    else{
        roots.cnt = 2;
        roots.x1 = (-eq.b + sqrt(discriminant)) / (2.0 * eq.a);
        if (fabs(roots.x1) < 1e-6)
            roots.x1 = 0;
        roots.x2 = (-eq.b - sqrt(discriminant)) / (2.0 * eq.a);
        if (fabs(roots.x2) < 1e-6)
            roots.x2 = 0;
        return;
    }
}
