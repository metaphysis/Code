#include <bits/stdc++.h>

using namespace std;

void partition(int A[], int left, int right, int rank)
{
    int i = left, j = right, middle = A[(left + right) / 2];
    do {
        while (A[i] < middle) i++;
        while (A[j] > middle) j--;
        if (i <= j) {
            swap(A[i], A[j]);
            i++, j--;
        }
    } while (i <= j);
    if (left <= j && rank <= j - left + 1) partition(A, left, j, rank);
    if (i <= right && rank >= i - left + 1) partition(A, i, right, rank - (i - left));
}

int quickSelect(int A[], int n, int k)
{
    partition(A, 0, n - 1, k - 1);
    return A[k - 1];
}

int partition(int A[], int left, int right)
{
    int pivot = A[left];
    while (true) {
        while (left < right && pivot <= A[right]) right--;
        if (left >= right) break;
        A[left++] = A[right];
        while (left < right && A[left] <= pivot) left++;
        if (left >= right) break;
        A[right--] = A[left];
    }
    A[right] = pivot;
    return right;
}

int kth_element(int A[], int left, int right, int k)
{
    while (true) {
        int middle = partition(A, left, right);
        if(middle == k) return A[k];
        else
        {
            if(middle < k) left = middle + 1;
            else right = middle - 1;
        }
    }
}

int main(int argc, char *argv[])
{
    int A[32];
    int n = 20;
    for (int i = 0; i < n; i++)
        cin >> A[i];
    double m = 0;
    m += kth_element(A, 0, n - 1, (n - 1) / 2);
    m += kth_element(A, 0, n - 1, n / 2);
    m /= 2.0;
    cout << m << '\n';
    for (int i = 0, k; i < n; i++)
    {
        cin >> k;
        cout << kth_element(A, 0, n - 1, k - 1) << ' ';
        nth_element(A, A + k - 1, A + n);
        cout << A[k - 1] << '\n';
    }
    return 0;
}
