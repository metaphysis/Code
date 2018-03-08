#include <iostream>
#include <algorithm>

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

int partition(int data[], int n, int k)
{
    int left = 0, right = 0;

    for (int i = 0; i < n; i++) right += data[i];
    
    while (left <= right)
    {
        int middle = (left + right) / 2;
        int j = 0, p = 0, sum = 0, ok = 1;

        while (j < n && p <= k)
        {
            if (sum + data[j] <= middle)
            {
                sum += data[j];
                j++;
            }
            else
            {
                sum = 0;
                p++;
            }
        }

        if (sum > 0) p++;

        if (p > k)
            left = middle + 1;
        else
            right = middle - 1;
    }
    
    return left;
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
