// #include ".headers/roots.hpp"

// struct Task
// {
//     int n;
//     double a, b, c;

// private:

//     Task()
//     Roots solve(double a, double b, double c)
//     {
//         switch (coefCheck(a,b,c))
//         {
//             case PAIR_OF_REAL:
//                 return Roots({PAIR_OF_REAL,  realRoots(a, b, c)});
//             case CONJUGATED_COMPLEX:
//                 return Roots({CONJUGATED_COMPLEX, complexRoots(a,b,c)});
//             case SINGLE_REAL:
//                 return Roots({SINGLE_REAL, pairRoots(a,b)});
//             case WRONG_COEFICIENTS:
//                 return Roots({.rootsType=WRONG_COEFICIENTS});
//             default:
//                 return Roots({.rootsType=ROOT_ERROR});
//         }
//     }

//     Roots solution = solve(Task->a, Task->b, Taskc);
// }