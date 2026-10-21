// Reconstructing Binary Forests
// UVa ID: 11397
// Verdict: Accepted
// Submission Date: 2026-10-22
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, mod;
    while (cin >> n >> mod) {
        vector<int> cnt(n + 1, 0);
        int maxHeight = 0;
        for (int i = 0; i < n; i++) {
            int height;
            cin >> height;
            if (height > 0) {
                cnt[height]++;
                maxHeight = max(maxHeight, height);
            }
        }
        if (maxHeight == 0) {
            cout << 1 % mod << '\n';
            continue;
        }
        vector<vector<long long>> comb(n + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            comb[i][0] = comb[i][i] = 1 % mod;
            for (int j = 1; j < i; j++)
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
        }
        vector<long long> powerTwo(n + 1, 1 % mod);
        for (int i = 1; i <= n; i++)
            powerTwo[i] = powerTwo[i - 1] * 2 % mod;
        long long answer = 1 % mod;
        for (int height = 1; height < maxHeight; height++) {
            int parentCount = cnt[height + 1], nodeCount = cnt[height];
            if (parentCount == 0) continue;
            if (nodeCount < parentCount) {
                answer = 0;
                break;
            }
            long long levelWays = 0;
            for (int doubleCount = 0; doubleCount <= parentCount; doubleCount++) {
                int usedCount = parentCount + doubleCount;
                if (usedCount > nodeCount) continue;
                long long nodeWays = 1;
                for (int i = 0; i < usedCount; i++)
                    nodeWays = nodeWays * (nodeCount - i) % mod;
                long long positionWays = comb[parentCount][doubleCount] * powerTwo[parentCount - doubleCount] % mod;
                levelWays = (levelWays + nodeWays * positionWays) % mod;
            }
            answer = answer * levelWays % mod;
        }
        cout << answer << '\n';
    }
    return 0;
}
