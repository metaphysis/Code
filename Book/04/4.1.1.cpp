#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010, UP = 1000000;

void display(int data[], int n)
{
    for (int i = 0; i < n; i++) cout << data[i] << " ";
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
    srand(time(NULL));

    int data[MAXN];
    for (int i = 0; i < MAXN; i++)  data[i] = rand() % UP;

    display(data, MAXN);
    bubbleSort(data, MAXN);
    display(data, MAXN);

    return 0;
}
