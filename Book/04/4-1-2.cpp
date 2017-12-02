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
        int pivot = data[(left + right) >> 1];
        int i = left - 1, j = right + 1;
        while (i < j)
        {
            do i++; while (data[i] < pivot);
            do j--; while (data[j] > pivot);
            if (i < j) swap(data[i], data[j]);
        }
        quickSort(data, left, i - 1);
        quickSort(data, j + 1, right);
    }
}

int main(int argc, char *argv[])
{
    int data[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) data[i] = i;
    random_shuffle(data, data + MAX_SIZE);
    output(data, MAX_SIZE);
    quickSort(data, 0, MAX_SIZE - 1);
    output(data, MAX_SIZE);

    return 0;
}
