#include <bits/stdc++.h>

using namespace std;

int binarySearch(int data[], int n, int x)
{
    int left = 0, right = n - 1, middle;
    
    while (left <= right)
    {
        middle = (left + right) / 2;
        
        if (data[middle] == x) return middle;

        if (data[middle] < x) left = middle + 1;
        else right = middle - 1;
    }
    
    return -1;
}

int binarySearch1(int data[], int n, int x)
{
    int left = -1, right = n, middle;

    while ((left + 1) != right)
    {
        middle = left + (right - left) / 2;

        if (data[middle] < x) left = middle;
        else right = middle;
    }

    if (right >= n || data[right] != x) right = -1;

    return right;
}

int main(int argc, char* argv[])
{
    int numbers[10] = {1, 1, 2, 2, 2, 5, 6, 7, 8, 9};
    
    cout << binarySearch(numbers, 10, 1) << endl;
    cout << binarySearch(numbers, 10, 2) << endl;
    cout << binarySearch(numbers, 10, 11) << endl;
    cout << binarySearch(numbers, 10, -1) << endl;
    
    cout.setf(ios::boolalpha);
    cout << binary_search(numbers, numbers + 10, 5) << endl;
    cout << binary_search(numbers, numbers + 10, 100) << endl;
    
    return 0;
}
