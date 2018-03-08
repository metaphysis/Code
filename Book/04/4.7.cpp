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

void bucketSort(int data[], int n, int K)
{
    int B = 100;
    vector<int> buckets[B];

    for (int i = 0; i < n; i++)
    {
        int bi = data[i] * B / K;
        buckets[bi].push_back(data[i]);
    }

    for (int i = 0; i < B; i++) sort(buckets[i].begin(), buckets[i].end());

    int k = 0;
    for (int i = 0; i < B; i++)
        for (int j = 0; j < buckets[i].size(); j++)
            data[k++] = buckets[i][j];
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int data[MAXN];
    for (int i = 0; i < MAXN; i++)  data[i] = rand() % UP;

    display(data, MAXN);
    bucketSort(data, MAXN, UP);
    display(data, MAXN);

    return 0;
}
