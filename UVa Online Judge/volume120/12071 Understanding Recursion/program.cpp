// Understanding Recursion
// UVa ID: 12071
// Verdict: Accepted
// Submission Date: 2021-12-29
// UVa Run Time: 0.080s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 40010;

int n, data[MAXN], data1[MAXN], tmp[MAXN];

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
    int cases = 0;
    while (cin >> n, n > 0) {
        for (int i = 0; i < n; i++)
        {
            cin >> data[i];
            data1[i] = data[i];
        }
        cout << "Case " << ++cases << ": ";
        long long cnt = mergeSort(0, n - 1);
        for (int i = 0; i < n; i++) data[i] = data1[n - 1 - i];
        cnt += mergeSort(0, n - 1);
        cout << cnt << '\n';
    }
}
