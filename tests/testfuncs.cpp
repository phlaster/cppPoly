#include <cmath>
#include <vector>
using namespace std;

bool isapprox(double a, double b, double tolerance=1e-9){
    return abs(a-b) <= tolerance;
}

bool isapprox(const vector<double>& v1, const vector<double>& v2, double tolerance=1e-9) {
    if (v1.size() != v2.size()) return false;

    for (int i = 0; i < (int)v1.size(); i++){
        if (!isapprox(v1[i],v2[i],tolerance)) return false;
    }
    return true;
}
