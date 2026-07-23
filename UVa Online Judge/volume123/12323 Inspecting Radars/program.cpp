// Inspecting Radars
// UVa ID: 12323
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.260s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, R;
    while (cin >> N >> R) {
        if (N == 0 && R == 0) break;
        // 按半径分组存储每个物体角度
        vector<vector<int>> byRadius(R); // 半径 0 ~ R-1，实际物体半径 >=1
        for (int i = 0; i < N; ++i) {
            int r, theta;
            cin >> r >> theta;
            byRadius[r].push_back(theta);
        }
        int E;
        cin >> E;
        while (E--) {
            int H, A;
            cin >> H >> A;
            int W = A + 1; // 角度窗口包含的整数角度个数
            int ans = 0;
            // 枚举内半径 h
            for (int h = 0; h < R; ++h) {
                int cnt[360] = {0}; // 当前半径区间内各角度出现次数
                // 半径区间 [h, h+H) 且不超过 R-1
                int maxR = min(R - 1, h + H - 1);
                for (int r = h; r <= maxR; ++r) {
                    for (int theta : byRadius[r]) {
                        cnt[theta]++;
                    }
                }
                // 在环形角度上求长度为 W 的窗口最大和
                if (W >= 360) { // 覆盖所有角度，直接求和
                    int total = 0;
                    for (int i = 0; i < 360; ++i) total += cnt[i];
                    ans = max(ans, total);
                } else {
                    // 复制数组便于处理环形
                    int doubled[720];
                    for (int i = 0; i < 360; ++i) {
                        doubled[i] = cnt[i];
                        doubled[i + 360] = cnt[i];
                    }
                    // 初始窗口 [0, W-1]
                    int cur = 0;
                    for (int i = 0; i < W; ++i) cur += doubled[i];
                    int maxWin = cur;
                    // 滑动窗口，起始角度从 1 到 359
                    for (int start = 1; start < 360; ++start) {
                        cur = cur - doubled[start - 1] + doubled[start + W - 1];
                        if (cur > maxWin) maxWin = cur;
                    }
                    ans = max(ans, maxWin);
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
