#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010, UP = 1000000;

void display(int data[], int n)
{
    for (int i = 0; i < n; i++) cout << data[i] << " ";
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
    srand(time(NULL));

    int data[MAXN];
    for (int i = 0; i < MAXN; i++)  data[i] = rand() % UP;

    display(data, MAXN);
    selectionSort(data, MAXN);
    display(data, MAXN);

    return 0;
}
