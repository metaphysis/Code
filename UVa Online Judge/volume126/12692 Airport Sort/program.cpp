// Airport Sort
// UVa ID: 12692
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 归并排序求逆序对
long long mergeSort(vector<int>& arr, vector<int>& tmp, int left, int right) {
    if (left >= right) return 0;
    int mid = (left + right) / 2;
    long long inv = mergeSort(arr, tmp, left, mid) + mergeSort(arr, tmp, mid + 1, right);
    int i = left, j = mid + 1, idx = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) tmp[idx++] = arr[i++];
        else {
            tmp[idx++] = arr[j++];
            inv += (mid - i + 1);
        }
    }
    while (i <= mid) tmp[idx++] = arr[i++];
    while (j <= right) tmp[idx++] = arr[j++];
    for (int p = left; p <= right; ++p) arr[p] = tmp[p];
    return inv;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n, k;
        scanf("%d %d", &n, &k);
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

        // 1. 计算每个位置的区域编号
        vector<int> zone(n + 1);
        for (int i = 1; i <= n; ++i) zone[i] = (a[i] - 1) / k + 1;

        // 2. 计算每个区域的大小
        int m = (n + k - 1) / k;
        vector<int> len(m + 1);
        int curStart = 1;
        for (int r = 1; r <= m; ++r) {
            len[r] = min(k, n - (r - 1) * k);
        }

        // 3. 收集每个区域的初始位置（升序）
        vector<vector<int>> pos(m + 1);
        for (int i = 1; i <= n; ++i) pos[zone[i]].push_back(i);

        // 4. 计算 Y
        int Y = 0;
        int curPos = 1;
        for (int r = 1; r <= m; ++r) {
            int L = curPos;
            int sizeR = len[r];
            for (int j = 0; j < sizeR; ++j) {
                int target = L + j;
                int dist = abs(pos[r][j] - target);
                if (dist > Y) Y = dist;
            }
            curPos += sizeR;
        }

        // 5. 计算 X（逆序对数量）
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; ++i) arr[i] = zone[i];
        vector<int> tmp(n + 1);
        long long X = mergeSort(arr, tmp, 1, n);

        // 6. 输出结果
        printf("Case %d: %lld\n", caseNo, X - Y);
    }
    return 0;
}
