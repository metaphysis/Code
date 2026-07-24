// Pair of Touching Circles
// UVa ID: 12373
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 1.220s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    // 预处理所有可能的偏移向量 (dx, dy) 及其对应的距离 D = sqrt(dx^2+dy^2)
    const int MAXD = 1000;
    vector<pair<int,int>> offsets[MAXD + 1];
    for (int dx = -MAXD; dx <= MAXD; ++dx) {
        for (int dy = -MAXD; dy <= MAXD; ++dy) {
            int s = dx * dx + dy * dy;
            if (s == 0) continue;
            int r = (int)sqrt(s);
            while ((r + 1) * (r + 1) <= s) ++r;
            while (r * r > s) --r;
            if (r * r == s && r <= MAXD) {
                offsets[r].push_back({dx, dy});
            }
        }
    }
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int H, W;
        scanf("%d %d", &H, &W);
        int R = min(H, W) / 2;          // 最大可能半径
        long long ordered = 0;
        for (int r1 = 1; r1 <= R; ++r1) {
            for (int r2 = 1; r2 <= R; ++r2) {
                int D = r1 + r2;
                // 遍历所有满足 dx^2+dy^2 = D^2 的偏移
                for (auto &p : offsets[D]) {
                    int dx = p.first, dy = p.second;
                    // 计算 x 方向可行位置数
                    int Lx = max(r1, r2 - dx);
                    int Ux = min(W - r1, W - r2 - dx);
                    if (Lx > Ux) continue;
                    int cntX = Ux - Lx + 1;
                    // 计算 y 方向可行位置数
                    int Ly = max(r1, r2 - dy);
                    int Uy = min(H - r1, H - r2 - dy);
                    if (Ly > Uy) continue;
                    int cntY = Uy - Ly + 1;
                    ordered += (long long)cntX * cntY;
                }
            }
        }
        // 有序对除以 2 得到无序对
        long long ans = ordered / 2;
        printf("Case %d: %lld\n", caseNo, ans);
    }
    return 0;
}
