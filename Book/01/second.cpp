#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
int main(int argc, char *argv[])
{
    cout << "bool: " << sizeof(bool) << "Byte(s), " << (int)numeric_limits<bool>::min() << "~" << (int)numeric_limits<bool>::max() << endl;
    cout << "char: " << sizeof(char) << "Byte(s), " << (int)numeric_limits<char>::min() << "~" << (int)numeric_limits<char>::max() << endl;
    cout << "unsigned char: " << sizeof(unsigned char) << "Byte(s), " << (int)numeric_limits<unsigned char>::min() << "~" << (int)numeric_limits<unsigned char>::max() << endl;
    cout << "short int: " << sizeof(short int) << "Byte(s), " << numeric_limits<short int>::min() << "~" << numeric_limits<short int>::max() << endl;
    cout << "unsigned short int: " << sizeof(unsigned short int) << "Byte(s), " << numeric_limits<unsigned short int>::min() << "~" << numeric_limits<unsigned short int>::max() << endl;
    cout << "int: " << sizeof(int) << "Byte(s), " << numeric_limits<int>::min() << "~" << numeric_limits<int>::max() << endl;
    cout << "unsigned int: " << sizeof(unsigned int) << "Byte(s), " << numeric_limits<unsigned int>::min() << "~" << numeric_limits<unsigned int>::max() << endl;
    cout << "long int: " << sizeof(long int) << "Byte(s), " << numeric_limits<long int>::min() << "~" << numeric_limits<long int>::max() << endl;
    cout << "unsigned long int: " << sizeof(unsigned long int) << "Byte(s), " << numeric_limits<unsigned long int>::min() << "~" << numeric_limits<unsigned long int>::max() << endl;
    cout << "long long int: " << sizeof(long long int) << "Byte(s), " << numeric_limits<long long int>::min() << "~" << numeric_limits<long long int>::max() << endl;
    cout << "unsigned long long int: " << sizeof(unsigned long long int) << "Byte(s), " << numeric_limits<unsigned long long int>::min() << "~" << numeric_limits<unsigned long long int>::max() << endl;
    cout << "float: " << sizeof(float) << "Byte(s), " << numeric_limits<float>::min() << "~" << numeric_limits<float>::max() << endl;
    cout << "double: " << sizeof(double) << "Byte(s), " << numeric_limits<double>::min() << "~" << numeric_limits<double>::max() << endl;
    cout << "long double: " << sizeof(long double) << "Byte(s), " << numeric_limits<long double>::min() << "~" << numeric_limits<long double>::max() << endl;
    return 0;
}
