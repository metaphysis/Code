#include <iostream>
#include <algorithm>

using namespace std;

int binary_search(int data[], int n, int number)
{
    int low = 0, high = n - 1, middle;
    
    while (low <= high)
    {
        middle = (low + high) / 2;
        
        if (data[middle] == number)
            return middle;
            
        if (data[middle] < number)
            low = middle + 1;
        else
            high = middle - 1;
    }
    
    return -1;
}

int main(int argc, char* argv[])
{
    int numbers[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    
    cout << binary_search(numbers, 10, 0) << endl;
    cout << binary_search(numbers, 10, 9) << endl;
    cout << binary_search(numbers, 10, 11) << endl;
    cout << binary_search(numbers, 10, -1) << endl;
    
    cout.setf(ios::boolalpha);
    cout << binary_search(numbers, numbers + 10, 5) << endl;
    cout << binary_search(numbers, numbers + 10, 100) << endl;
    
    return 0;
}
