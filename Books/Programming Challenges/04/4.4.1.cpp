#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

int n, data[MAXN], tmp[MAXN];

long long mergeAndCount(int left, int middle, int right)
{
    long long count = 0;
    int i = left, j = middle + 1, k = 0;
    while (i <= middle && j <= right)
        tmp[k++] = data[i] <= data[j] ? data[i++] : (count += (middle - i + 1), data[j++]);
    while (i <= middle) tmp[k++] = data[i++];
    while (j <= right) tmp[k++] = data[j++];
    for (int i = 0; i < k; i++) data[left + i] = tmp[i];
    return count;
}

long long mergeSort(int left, int right)
{
    long long count = 0;
    if (left < right) {
        int middle = (left + right) >> 1;
        count += mergeSort(left, middle);
        count += mergeSort(middle + 1, right);
        count += mergeAndCount(left, middle, right);
    }
    return count;
}

int main(int argc, char *argv[])
{
    while (cin >> n, n > 0) {
        for (int i = 0; i < n; i++) cin >> data[i];
        cout << mergeSort(data, 0, n - 1) << '\n';
    }
}
