#include <iostream>
#include <bitset>

using namespace std;

int main(int argc, char *argv[])
{
    float f1 = 123456789.0;
    unsigned int *ui1 = (unsigned int *)(&f1);
    bitset<32> uis1(*ui1);
    cout << fixed << f1 << " = " << uis1.to_string() << endl;

    float f2 = 1234567.0;
    unsigned int *ui2 = (unsigned int *)(&f2);
    bitset<32> uis2(*ui2);
    cout << fixed << f2 << " = " << uis2.to_string() << endl;

    return 0;
}
