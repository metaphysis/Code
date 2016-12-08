#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    double number = 123456789.0123456789;

    cout << number << endl;     // 1.23457e+08
    cout << fixed << setprecision(4) << number << endl; // 123456789.0123
    cout << setprecision(8) << number << endl;  // 123456789.01234567
    cout << scientific << number << endl;   // 1.23456789e+08

    return 0;
}
