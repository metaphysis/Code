#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = 3.1415926535847;

int main(int argc, char* argv[])
{
    cout.setf(ios::fixed | ios::showpoint);
    
    cout << setprecision(17) << cos(0.01 / 180.0 * PI) << endl;
    cout << acos(1.01) << endl;
    
    return 0;
}
