// Jurassic Remains
// UVa ID: 1326
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    while (cin >> N) {
        vector<int> bones(N);
        for (int i = 0; i < N; i++) {
            string s;
            cin >> s;
            int mask = 0;
            for (char c : s) {
                mask |= (1 << (c - 'A'));
            }
            bones[i] = mask;
        }

        int maxSize = 0;
        int bestMask = 0;

        // 折半搜索
        int half = N / 2;
        
        // 存储前半部分异或值 -> (size, mask)
        map<int, pair<int, int>> firstHalf;
        
        // 枚举前半部分
        for (int mask = 0; mask < (1 << half); mask++) {
            int xorSum = 0;
            int size = 0;
            for (int i = 0; i < half; i++) {
                if (mask & (1 << i)) {
                    xorSum ^= bones[i];
                    size++;
                }
            }
            // 如果当前异或值没出现过，或者出现但size更小，则更新
            if (firstHalf.find(xorSum) == firstHalf.end() || firstHalf[xorSum].first < size) {
                firstHalf[xorSum] = make_pair(size, mask);
            }
            // 如果前半部分自己就能满足条件
            if (xorSum == 0 && size > maxSize) {
                maxSize = size;
                bestMask = mask;
            }
        }

        // 枚举后半部分
        int secondHalf = N - half;
        for (int mask = 0; mask < (1 << secondHalf); mask++) {
            int xorSum = 0;
            int size = 0;
            for (int i = 0; i < secondHalf; i++) {
                if (mask & (1 << i)) {
                    xorSum ^= bones[half + i];
                    size++;
                }
            }
            // 查找前半部分是否有相同的异或值
            auto it = firstHalf.find(xorSum);
            if (it != firstHalf.end()) {
                int totalSize = it->second.first + size;
                if (totalSize > maxSize) {
                    maxSize = totalSize;
                    // 合并前后两部分的掩码
                    bestMask = (it->second.second) | (mask << half);
                }
            }
            // 如果后半部分自己就能满足条件
            if (xorSum == 0 && size > maxSize) {
                maxSize = size;
                bestMask = mask << half;
            }
        }

        // 输出结果
        cout << maxSize << endl;
        if (maxSize > 0) {
            bool first = true;
            for (int i = 0; i < N; i++) {
                if (bestMask & (1 << i)) {
                    if (!first) cout << " ";
                    cout << (i + 1);
                    first = false;
                }
            }
            cout << endl;
        } else {
            cout << endl;
        }
    }
    return 0;
}
