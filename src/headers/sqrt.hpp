#ifndef SQRT_HPP
#define SQRT_HPP
double sqrt(double x, double eps=1e-9, double init_guess=1.0);
#endif

#ifndef SQR_HPP
#define SQR_HPP
double sqr(double x);
#endif

#ifndef ABS_HPP
#define ABS_HPP
double abs(double x);
#endif

#ifndef MIN_HPP
#define MIN_HPP
double min(double a, double b);
#endif

#ifndef MAX_HPP
#define MAX_HPP
double max(double a, double b);
#endif

#ifndef AVERAGE_HPP
#define AVERAGE_HPP
double average(double a, double b);
#endif

#ifndef IMPROVE_HPP
#define IMPROVE_HPP
double improve(double guess, double x);
#endif

#ifndef GOODGUESS_HPP
#define GOODGUESS_HPP
bool goodGuess(double guess, double x, double eps=1e-9);
#endif

#ifndef SQRT_ITER
#define SQRT_ITER
double sqrtIter(double guess, double x, double eps=1e-9);
#endif
