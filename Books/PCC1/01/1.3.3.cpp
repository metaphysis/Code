#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    int n = 60;

    cout.setf(ios::showbase);
    cout.setf(ios::dec, ios::basefield);

    cout << "dec: " << n << endl;
    cout << oct << "oct: " << n << endl;
    cout << hex << "hex: " << n << endl;

    cout.setf(ios::uppercase);
    cout << "hex | uppercase: " << n << endl;

    return 0;
}
