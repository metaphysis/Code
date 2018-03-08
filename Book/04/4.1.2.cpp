#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1010, UP = 1000000;

void display(int data[], int n)
{
    for (int i = 0; i < n; i++) cout << data[i] << " ";
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
    srand(time(NULL));

    int data[MAXN];
    for (int i = 0; i < MAXN; i++)  data[i] = rand() % UP;

    display(data, MAXN);
    quickSort(data, 0, MAXN - 1);
    display(data, MAXN);

    return 0;
}
