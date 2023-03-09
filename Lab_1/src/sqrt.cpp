double abs(double x)
{
	return x < 0.0 ? -x : x;
}

double min(double a, double b)
{
    return a < b ? a : b;
}

double max(double a, double b)
{
    return a < b ? b : a;
}

double sqr(double x)
{
	return x * x;
}

double average(double a, double b)
{
	return (a + b) / 2.0;
}

double improve(double guess, double x)
{
	return average(guess, x/guess);
}

bool goodGuess(double guess, double x, double eps=1e-9)
{
	return abs( sqr(guess) - x ) < eps;
}

double sqrtIter(double guess, double x, double eps=1e-9)
{
	return goodGuess(guess, x, eps) ? guess : sqrtIter(improve(guess,x),x,eps);
}

double sqrt(double x, double eps=1e-9, double initGuess=1.0)
{
	return sqrtIter(initGuess, x, eps);
}
