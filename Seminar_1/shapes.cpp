#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Shape
{
    public:
    string color;
    string name;
};

class Triangle : public Shape
{
    public:
    double perim;
};

class Circle : public Shape
{
    public:
    double radius;
};

class Square : public Shape
{
    public:
    double side;
    vector<double> dims;
};


int main() {
    int length = 10;
    vector<Square> theZoo;
    for (int i = 0; i<length; i++){
        Square sqr;
        sqr.name = "Good Name";
        sqr.dims.push_back((i+1)*1.4);
        sqr.dims.push_back((i+5.0)/7);
        theZoo.push_back(sqr);
    }

    for (int i = 0; i<length; i++){
        cout << theZoo[i].name << "\n";
        cout << theZoo[i].dims[0] << " x "<< theZoo[i].dims[1] << "\n";
    }
    
  return 0;
}
