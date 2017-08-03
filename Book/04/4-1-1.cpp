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

// 双向冒泡排序，减少了循环排序的次数。
void bidirectionalBubbleSort(int data[], int n)
{
    int left = 0, right = n - 1, shift;

    while(left < right)
    {
        // 将较大的值移到末尾
        for(int i = left; i < right; i++)
            if(data[i] > data[i + 1])
            {
                swap(data[i], data[i + 1]);
                shift = i;
            }

        right = shift;

        // 将较小的值移到开头
        for(int i = right - 1; i >= left; i--)
            if(data[i] > data[i + 1])
            {
                swap(data[i], data[i + 1]);
                shift = i + 1;
            }

        left = shift;
    }
}

void bubbleSort(int data[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < (n - i - 1); j++)
            if (data[j] > data[j + 1])
                swap(data[j], data[j + 1]);
}

int main(int argc, char *argv[])
{
    int data[MAX_SIZE];
    for (int i = MAX_SIZE; i >= 1; i--)
        data[MAX_SIZE - i] = i;

    random_shuffle(data, data + MAX_SIZE);

    output(data, MAX_SIZE);

    bubbleSort(data, MAX_SIZE);
    //bidirectionalBubbleSort(data, MAX_SIZE);
    
    output(data, MAX_SIZE);

    return 0;
}
