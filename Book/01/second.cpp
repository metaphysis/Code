#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
int main(int argc, char *argv[])
{
    cout << setw(24) << right << "bool:" << setw(3) << right << sizeof(bool) << "B, " << setw(20) << right << (int)numeric_limits<bool>::min() << " ~ " << left << (int)numeric_limits<bool>::max() << endl;
    cout << setw(24) << right << "char:" << setw(3) << right << sizeof(char) << "B, " << setw(20) << right << (int)numeric_limits<char>::min() << " ~ " << left << (int)numeric_limits<char>::max() << endl;
    cout << setw(24) << right << "unsigned char:" << setw(3) << right << sizeof(unsigned char) << "B, " << setw(20) << right << (int)numeric_limits<unsigned char>::min() << " ~ " << left << (int)numeric_limits<unsigned char>::max() << endl;
    cout << setw(24) << right << "short int:" << setw(3) << right << sizeof(short int) << "B, " << setw(20) << right << numeric_limits<short int>::min() << " ~ " << left << numeric_limits<short int>::max() << endl;
    cout << setw(24) << right << "unsigned short int:" << setw(3) << right << sizeof(unsigned short int) << "B, " << setw(20) << right << numeric_limits<unsigned short int>::min() << " ~ " << left << numeric_limits<unsigned short int>::max() << endl;
    cout << setw(24) << right << "int:" << setw(3) << right << sizeof(int) << "B, " << setw(20) << right << numeric_limits<int>::min() << " ~ " << left << numeric_limits<int>::max() << endl;
    cout << setw(24) << right << "unsigned int:" << setw(3) << right << sizeof(unsigned int) << "B, " << setw(20) << right << numeric_limits<unsigned int>::min() << " ~ " << left << numeric_limits<unsigned int>::max() << endl;
    cout << setw(24) << right << "long int:" << setw(3) << right << sizeof(long int) << "B, " << setw(20) << right << numeric_limits<long int>::min() << " ~ " << left << numeric_limits<long int>::max() << endl;
    cout << setw(24) << right << "unsigned long int:" << setw(3) << right << sizeof(unsigned long int) << "B, " << setw(20) << right << numeric_limits<unsigned long int>::min() << " ~ " << left << numeric_limits<unsigned long int>::max() << endl;
    cout << setw(24) << right << "long long int:" << setw(3) << right << sizeof(long long int) << "B, " << setw(20) << right << numeric_limits<long long int>::min() << " ~ " << left << numeric_limits<long long int>::max() << endl;
    cout << setw(24) << right << "unsigned long long int:" << setw(3) << right << sizeof(unsigned long long int) << "B, " << setw(20) << right << numeric_limits<unsigned long long int>::min() << " ~ " << left << numeric_limits<unsigned long long int>::max() << endl;
    cout << setw(24) << right << "float:" << setw(3) << right << sizeof(float) << "B, " << setw(20) << right << numeric_limits<float>::min() << " ~ " << left << numeric_limits<float>::max() << endl;
    cout << setw(24) << right << "double:" << setw(3) << right << sizeof(double) << "B, " << setw(20) << right << numeric_limits<double>::min() << " ~ " << left << numeric_limits<double>::max() << endl;
    cout << setw(24) << right << "long double:" << setw(3) << right << sizeof(long double) << "B, " << setw(20) << right << numeric_limits<long double>::min() << " ~ " << left << numeric_limits<long double>::max() << endl;
    return 0;
}
