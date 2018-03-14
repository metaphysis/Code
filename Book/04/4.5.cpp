#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010, UP = 1000000;

void display(int data[], int n)
{
    for (int i = 0; i < n; i++) cout << data[i] << " ";
    cout << endl;
}

void countingSort(int data[], int n, int C)
{
    int *bucket = new int[C]();
    
    for (int i = 0; i < n; i++) bucket[data[i]]++;
    
    for (int i = 0, index = 0; i < C; i++)
        while (bucket[i]-- > 0)
            data[index++] = i;
            
    delete [] bucket;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int data[MAXN];
    for (int i = 0; i < MAXN; i++)  data[i] = rand() % UP;

    display(data, MAXN);
    countingSort(data, MAXN, UP);
    display(data, MAXN);

    return 0;
}
