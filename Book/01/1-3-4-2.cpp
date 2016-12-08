#include <iostream>
#include <iomanip>

using namespace std;

const double EPSILON = 1e-7;

int main(int argc, char *argv[])
{
    double number = 1.005;
    
    cout << fixed << setprecision(2) << number << endl; // 1.00
    cout << fixed << setprecision(2) << (number + EPSILON) << endl; // 1.01
    
    return 0;
}
