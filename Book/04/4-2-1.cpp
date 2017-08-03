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

void insertionSort(int data[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int temp = data[i], j = i - 1;
        while (j >= 0 && data[j] > temp)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = temp;
    }
}


int main(int argc, char *argv[])
{
    int data[MAX_SIZE];
    for (int i = MAX_SIZE; i >= 1; i--)
        data[MAX_SIZE - i] = i;

    random_shuffle(data, data + MAX_SIZE);

    output(data, MAX_SIZE);

    insertionSort(data, MAX_SIZE);
    
    output(data, MAX_SIZE);

    return 0;
}
