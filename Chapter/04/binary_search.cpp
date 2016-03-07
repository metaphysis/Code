#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
    int numbers[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    
    cout.setf(ios::boolalpha);
    
    cout << binary_search(numbers, numbers + 10, 5) << endl;
    cout << binary_search(numbers, numbers + 10, 100) << endl;
    
    return 0;
}
