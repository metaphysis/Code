#include <iostream>
#include <bitset>

using namespace std;

int main(int argc, char *argv[])
{
    bitset < 16 > empty;
    bitset < 16 > some(64);
    bitset < 16 > integer(0x64);
    bitset < 16 > other(string("1010101010101010"));

    cout << empty << endl;
    cout << some << endl;
    cout << some.to_string() << endl;
    cout << integer << endl;
    cout << other.to_ulong() << endl;

    return 0;
}
