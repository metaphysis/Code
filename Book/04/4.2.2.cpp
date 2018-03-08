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

void shellSort(int data[], int n)
{
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 && data[j] > data[j + gap]; j -= gap)
                swap(data[j], data[j + gap]);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int data[MAXN];
    for (int i = 0; i < MAXN; i++)  data[i] = rand() % UP;

    display(data, MAXN);
    shellSort(data, MAXN);
    display(data, MAXN);

    return 0;
}
