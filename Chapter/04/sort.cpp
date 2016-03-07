#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 20;

void display(int data[], int n)
{
    for (int i = 0; i < n; i++)
        cout << data[i] << " ";
    cout << endl;
}

void shellSort(int data[], int n)
{
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 && data[j] > data[j + gap]; j -= gap)
            {
                temp = data[j];
                data[j] = data[j + gap];
                data[j + gap] = temp;
            }
}

void countingSort(int data[], int n, int ceiling)
{
    int i, index = 0;
    int *bucket = new int[ceiling];
    
    for (int i = 0; i < n; i++)
        bucket[data[i]]++;
    
    for (int i = 0; i < ceiling; i++)
        while (bucket[i]-- > 0)
            data[index++] = i;
            
    delete [] bucket;
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

void quickSort(int data[], int left, int right)
{
    if (left < right)
    {
        int pivot = data[left], low = left, high = right;
        while (low < high)
        {
            while (low < high && data[high] > pivot)
                high--;
            data[low] = data[high];

            while (low < high && data[low] < pivot)
                low++;
            data[high] = data[low];
        }
        data[low] = pivot;
        quickSort(data, left, low - 1);
        quickSort(data, low + 1, right);
    }
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

void selectionSort(int data[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            if (data[i] > data[j])
            {
                int temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
}

void bubbleSort(int data[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < (n - i - 1); j++)
        {
            if (data[j] > data[j + 1])
            {
                int temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
}

int main(int argc, char *argv[])
{
    int data[MAX_SIZE];
    for (int i = MAX_SIZE; i >= 1; i--)
        data[MAX_SIZE - i] = i;

    random_shuffle(data, data + MAX_SIZE);

    display(data, MAX_SIZE);

    //bubbleSort(data, MAX_SIZE);
    //selectionSort(data, MAX_SIZE);
    //insertionSort(data, MAX_SIZE);
    //quickSort(data, 0, MAX_SIZE - 1);
    //mergeSort(data, 0, MAX_SIZE - 1);
    //heapSort(data, MAX_SIZE);
    //countingSort(data, MAX_SIZE, MAX_SIZE + 1);
    shellSort(data, MAX_SIZE);
    
    display(data, MAX_SIZE);

    return 0;
}
