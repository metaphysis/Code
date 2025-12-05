// Canvas Painting
// UVa ID: 13017
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 0.180s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        // 使用最小堆存储所有画布的大小
        priority_queue<long long, vector<long long>, greater<long long>> minHeap;
        for (int i = 0; i < n; ++i) {
            long long size;
            cin >> size;
            minHeap.push(size);
        }

        long long totalInk = 0;
        // 哈夫曼合并过程
        while (minHeap.size() > 1) {
            long long a = minHeap.top(); minHeap.pop();
            long long b = minHeap.top(); minHeap.pop();
            long long sum = a + b;
            totalInk += sum;
            minHeap.push(sum);
        }

        cout << totalInk << "\n";
    }

    return 0;
}
