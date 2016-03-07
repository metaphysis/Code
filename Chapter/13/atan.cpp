#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{
    cout << fixed << setprecision(6);
    
    cout << atan(0.0) << endl;
    cout << atan(1E20) << endl;
    cout << atan(-1E20) << endl;
    cout << atan2(0, 9) << endl;
    cout << atan2(9, 0) << endl;
    cout << atan2(-9, 0) << endl;
    cout << atan2(0, -9) << endl;
    cout << atan2(-1E-10, -9) << endl;
    cout << atan2(0, 0) << endl;
    
    return 0;
}
