// Floor Tiles
// UVa ID: 10644
// Verdict: Wrong Answer
// Submission Date: 2025-12-13
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1010;
bool dp[MAX][MAX] = {false};

void preprocess() {
    // 初始可铺的矩形
    dp[2][3] = true;
    dp[3][2] = true;
    for (int l = 2; l <= 1000; ++l) {
        for (int w = 2; w <= 1000; ++w) {
            if (dp[l][w]) {
                // 沿长度方向加 3×2 块
                if (w % 2 == 0 && l + 3 < MAX) dp[l + 3][w] = true;
                // 沿长度方向加 2×3 块
                if (w % 3 == 0 && l + 2 < MAX) dp[l + 2][w] = true;
                // 沿宽度方向加 3×2 块
                if (l % 3 == 0 && w + 2 < MAX) dp[l][w + 2] = true;
                // 沿宽度方向加 2×3 块
                if (l % 2 == 0 && w + 3 < MAX) dp[l][w + 3] = true;
            }
        }
    }
}

int main() {
    preprocess();
    int k;
    cin >> k;
    while (k--) {
        int l1, l2, w1, w2;
        cin >> l1 >> l2 >> w1 >> w2;
        if (l1 > l2) swap(l1, l2);
        if (w1 > w2) swap(w1, w2);
        int count = 0;
        for (int l = l1; l <= l2; ++l)
            for (int w = w1; w <= w2; ++w)
                if (dp[l][w]) count++;
        cout << count << endl;
    }
    return 0;
}
