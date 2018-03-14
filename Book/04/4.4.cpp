#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010, UP = 1000000;

void display(int data[], int n)
{
    for (int i = 0; i < n; i++) cout << data[i] << " ";
    cout << endl;
}

int tmp[MAXN];

void merge(int data[], int left, int middle, int right)
{
    int i = left, j = middle + 1, k = 0;
    
    while (i <= middle && j <= right)
        tmp[k++] = data[i] <= data[j] ? data[i++] : data[j++];
        
    while (i <= middle) tmp[k++] = data[i++];
        
    while (j <= right) tmp[k++] = data[j++];
        
    for (int i = 0; i < k; i++)  data[left + i] = tmp[i];
}

void mergeSort(int data[], int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) >> 1;
        mergeSort(data, left, middle);
        mergeSort(data, middle + 1, right);
        merge(data, left, middle, right);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int data[MAXN];
    for (int i = 0; i < MAXN; i++)  data[i] = rand() % UP;

    display(data, MAXN);
    mergeSort(data, 0, MAXN - 1);
    display(data, MAXN);

    return 0;
}
