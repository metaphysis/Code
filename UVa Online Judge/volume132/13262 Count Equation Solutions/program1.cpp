// Count Equation Solutions 
// UVa ID: 13262
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 4.560s

#include <bits/stdc++.h>
using namespace std;

void radixSort(vector<int>& a) {
    int n = a.size();
    vector<int> buffer(n);
    const int BASE = 1 << 16;
    static int cnt[BASE];
    memset(cnt, 0, sizeof(cnt));
    for (int x : a)
        cnt[x & 65535]++;
    for (int i = 1; i < BASE; i++)
        cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        int x = a[i];
        buffer[--cnt[x & 65535]] = x;
    }
    memset(cnt, 0, sizeof(cnt));
    for (int x : buffer)
        cnt[(unsigned int)x >> 16]++;
    for (int i = 1; i < BASE; i++)
        cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        int x = buffer[i];
        a[--cnt[(unsigned int)x >> 16]] = x;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    while (cin >> m) {
        int a1, a2, a3, a4, a5, a6;
        cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
        int size = m * m * m;
        vector<int> left(size), right(size);
        int pos = 0;
        for (int x1 = 1; x1 <= m; x1++) {
            int part1 = a1 * x1;
            for (int x3 = 1; x3 <= m; x3++) {
                int part13 = part1 + a3 * x3;
                for (int x5 = 1; x5 <= m; x5++)
                    left[pos++] = part13 + a5 * x5;
            }
        }
        pos = 0;
        for (int x2 = 1; x2 <= m; x2++) {
            int part2 = a2 * x2;
            for (int x4 = 1; x4 <= m; x4++) {
                int part24 = part2 + a4 * x4;
                for (int x6 = 1; x6 <= m; x6++)
                    right[pos++] = part24 + a6 * x6;
            }
        }
        radixSort(left);
        radixSort(right);
        long long ans = 0;
        int i = 0, j = 0;
        while (i < size && j < size) {
            if (left[i] < right[j]) {
                i++;
            } else if (left[i] > right[j]) {
                j++;
            } else {
                int value = left[i];
                int leftCount = 0, rightCount = 0;
                while (i < size && left[i] == value) {
                    i++;
                    leftCount++;
                }
                while (j < size && right[j] == value) {
                    j++;
                    rightCount++;
                }
                ans += 1LL * leftCount * rightCount;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
