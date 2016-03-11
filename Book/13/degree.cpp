#include <iostream>

using namespace std;

const double PI = 3.1415926535;

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
