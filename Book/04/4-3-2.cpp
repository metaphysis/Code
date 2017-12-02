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

// 将数组进行调整，使之具有堆的性质。
void heapify(int data[], int parent, int n)
{
    int left = 2 * parent + 1, right = 2 * parent + 2, max = parent;
    
    if (left < n && data[left] > data[max])
        max = left;
    if (right < n && data[right] > data[max])
        max = right;
        
    if (max != parent)
    {
        swap(data[parent], data[max]);
        heapify(data, max, n);
    }
}

// 构建堆。
void buildHeap(int data[], int n)
{
    for (int parent = n / 2 - 1; parent >= 0; parent--)
        heapify(data, parent, n);
}

// 堆排序。先构建堆，然后每次取一个最小元素，调整剩下元素继续构成堆。
void heapSort(int data[], int n)
{
    buildHeap(data, n);
    
    for (int parent = n - 1; parent > 0; parent--)
    {
        swap(data[0], data[parent]);
        heapify(data, 0, parent);
    }
}

int main(int argc, char *argv[])
{
    int data[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) data[i] = i;

    random_shuffle(data, data + MAX_SIZE);

    output(data, MAX_SIZE);

    heapSort(data, MAX_SIZE);
    
    output(data, MAX_SIZE);

    return 0;
}
