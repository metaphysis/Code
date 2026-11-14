#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string line = "the quick brown fox jumps over the lazy dog.";
    cout.setf(ios::uppercase);
    cout << line << endl;

    int number = 0x1af;
    cout.setf(ios::hex, ios::basefield);
    cout.setf(ios::showbase);
    cout << number << endl;
    
    return 0;
}
