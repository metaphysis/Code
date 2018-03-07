#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout.setf(ios::showbase);
    cout.setf(ios::dec, ios::basefield);

    cout << "dec: " << 60 << endl;
    cout << oct << "oct: " << 60 << endl;
    cout << hex << "hex: " << 60 << endl;

    cout.setf(ios::uppercase);
    cout << "hex | uppercase: " << 60 << endl;

    return 0;
}
