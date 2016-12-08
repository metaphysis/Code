#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout.setf(ios::showbase);
    cout.setf(ios::dec, ios::basefield);

    cout << "dec: " << 60 << endl;              // dec: 60
    cout << oct << "oct: " << 60 << endl;       // oct: 074
    cout << hex << "hex: " << 60 << endl;       // hex: 0x3c

    cout.setf(ios::uppercase);
    cout << "hex | uppercase: " << 60 << endl;  // hex | uppercase: 0X3C

    return 0;
}
