#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 20;

void output(int data[], int n)
{
    for (int i = 0; i < n; i++)
        cout << data[i] << " ";
    cout << endl;
}

int temp[MAX_SIZE];

void merge(int data[], int first, int middle, int last)
{
    int i = first, j = middle + 1, k = 0;
    
    while (i <= middle && j <= last)
        temp[k++] = data[i] < data[j] ? data[i++] : data[j++];
        
    while (i <= middle)
        temp[k++] = data[i++];
        
    while (j <= last)
        temp[k++] = data[j++];
        
    for (int i = 0; i < k; i++)
        data[first + i] = temp[i];
}

void mergeSort(int data[], int first, int last)
{
    if (first < last)
    {
        int middle = (first + last) / 2;
        mergeSort(data, first, middle);
        mergeSort(data, middle + 1, last);
        merge(data, first, middle, last);
    }
}

int main(int argc, char *argv[])
{
    int data[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) data[i] = i;

    random_shuffle(data, data + MAX_SIZE);

    output(data, MAX_SIZE);

    mergeSort(data, 0, MAX_SIZE - 1);

    output(data, MAX_SIZE);

    return 0;
}
