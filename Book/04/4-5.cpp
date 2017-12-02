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

void countingSort(int data[], int n, int C)
{
    int *bucket = new int[C];
    
    for (int i = 0; i < n; i++) bucket[data[i]]++;
    
    for (int i = 0, index = 0; i < C; i++)
        while (bucket[i]-- > 0)
            data[index++] = i;
            
    delete [] bucket;
}

int main(int argc, char *argv[])
{
    int data[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) data[i] = i;

    random_shuffle(data, data + MAX_SIZE);

    output(data, MAX_SIZE);

    countingSort(data, MAX_SIZE, MAX_SIZE + 1);
    
    output(data, MAX_SIZE);

    return 0;
}
