// Escape
// UVa ID: 11784
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int M, N, L;

// 计算边界位置 (r, c) 的顺时针序号
int getIndex(int r, int c) {
    if (r == 0) return c;                                 	// 上边
    if (c == N - 1) return N + (r - 1);                   	// 右边
    if (r == M - 1) return N + (M - 1) + (N - 2 - c);    	// 下边
    return L - r;                                         	// 左边 (c == 0)
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int H;
    while (cin >> M >> N >> H) {
        if (M == 0 && N == 0 && H == 0) break;
        L = 2 * M + 2 * N - 4;
        vector<int> holes;
        for (int i = 0; i < H; ++i) {
            int r, c;
            cin >> r >> c;
            holes.push_back(getIndex(r, c));
        }
        int r0, c0;
        cin >> r0 >> c0;
        int target[4], d[4];
        target[0] = getIndex(0, c0);        d[0] = r0;            // 上
        target[1] = getIndex(M - 1, c0);    d[1] = M - 1 - r0;    // 下
        target[2] = getIndex(r0, 0);        d[2] = c0;            // 左
        target[3] = getIndex(r0, N - 1);    d[3] = N - 1 - c0;    // 右
        int bestTime = INT_MAX, bestDist = INT_MAX;
        for (int dir = 0; dir < 4; ++dir) {
            int tar = target[dir];
            int dist = d[dir];
            int minTotal = INT_MAX; // 到达门洞格子的最小时间（不含最后一步）
            for (int s : holes) {
                int r = (tar - s) % L;
                if (r < 0) r += L;
                int total;
                if (r >= dist) total = r;
                else {
                    int add = (dist - r + L - 1) / L;
                    total = r + add * L;
                }
                if (total < minTotal) minTotal = total;
            }
            int candTime = minTotal + 1; // 最后一步跨出需要额外 1 秒
            int candDist = dist + 1;     // 跑动距离包含最后一步
            if (candTime < bestTime || (candTime == bestTime && candDist < bestDist)) {
                bestTime = candTime;
                bestDist = candDist;
            }
        }
        cout << bestTime << " " << bestDist << "\n";
    }
    return 0;
}
