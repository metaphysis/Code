#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAX_SIZE = 20;

void output(int data[], int n)
{
    for (int i = 0; i < n; i++)
        cout << data[i] << " ";
    cout << endl;
}


void quickSort(int data[], int left, int right)
{
    if (left < right)
    {
        int pivot = data[left], low = left, high = right;
        while (low < high)
        {
            while (low < high && data[high] > pivot)
                high--;
            data[low] = data[high];

            while (low < high && data[low] < pivot)
                low++;
            data[high] = data[low];
        }
        data[low] = pivot;
        quickSort(data, left, low - 1);
        quickSort(data, low + 1, right);
    }
}

int main(int argc, char *argv[])
{
    int data[MAX_SIZE];
    for (int i = MAX_SIZE; i >= 1; i--)
        data[MAX_SIZE - i] = i;

    random_shuffle(data, data + MAX_SIZE);

    output(data, MAX_SIZE);

    quickSort(data, 0, MAX_SIZE - 1);

    output(data, MAX_SIZE);

    return 0;
}
