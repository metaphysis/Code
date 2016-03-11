#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    cout.setf(ios::showbase);
    
    cout.setf(ios::dec, ios::basefield);
    cout << "dec: " << 60 << endl;
    cout.setf(ios::oct, ios::basefield);
    cout << "oct: " << 60 << endl;
    cout.setf(ios::hex, ios::basefield);
    cout << "hex: " << 60 << endl;
    
    cout.setf(ios::uppercase);
    cout << "hex | uppercase: " << 60 << endl;
    
    return 0;
}
