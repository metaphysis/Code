#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    double number = 123456789.0123456789;

    cout << number << endl;
    cout << fixed << setprecision(4) << number << endl;
    cout << setprecision(8) << number << endl;
    cout << scientific << number << endl;

    return 0;
}
