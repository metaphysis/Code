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

void selectionSort(int data[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (data[i] > data[j])
                swap(data[i], data[j]);
}

int main(int argc, char *argv[])
{
    int data[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) data[i] = i;

    random_shuffle(data, data + MAX_SIZE);

    output(data, MAX_SIZE);

    selectionSort(data, MAX_SIZE);
    
    output(data, MAX_SIZE);

    return 0;
}
