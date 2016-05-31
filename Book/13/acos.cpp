#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = 2.0 * acos(0.0);

int main(int argc, char* argv[])
{
    cout.setf(ios::fixed | ios::showpoint);
    
    cout << setprecision(17) << cos(0.01 / 180.0 * PI) << endl;
    cout << acos(-0.456) << endl;
    cout << acos(1.01) << endl;
    
    return 0;
}
