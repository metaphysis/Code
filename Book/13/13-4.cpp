#include <iostream>
#include <cmath>

using namespace std;

const double PI = 2.0 * acos(0.0);

double degreeToRadians(double degree)
{
    return degree / 180.0 * PI;
}

double radiansToDegree(double radians)
{
    return radians / PI * 180;
}

int main(int argc, char* argv[])
{
    double degree = 100.0;
    
    return 0;
}
