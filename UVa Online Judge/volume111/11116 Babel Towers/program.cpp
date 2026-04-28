// Babel Towers
// UVa ID: 11116
// Verdict: Accepted
// Submission Date: 2026-04-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Block {
    long long x, y, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N, N) {
        vector<Block> blocks(N);
        for (int i = 0; i < N; ++i)
            cin >> blocks[i].x >> blocks[i].y >> blocks[i].r;
        
        vector<long long> cumW(N + 1, 0);
        vector<long long> cumX(N + 1, 0);
        vector<long long> cumY(N + 1, 0);
        
        bool feasible = true;
        int collapseIdx = -1;
        
        for (int t = 0; t < N; ++t) {
            long long w = (long long)blocks[t].r * blocks[t].r;
            cumW[t + 1] = cumW[t] + w;
            cumX[t + 1] = cumX[t] + w * blocks[t].x;
            cumY[t + 1] = cumY[t] + w * blocks[t].y;
            
            for (int s = 1; s <= t; ++s) {
                long long subW = cumW[t + 1] - cumW[s];
                long long subX = cumX[t + 1] - cumX[s];
                long long subY = cumY[t + 1] - cumY[s];
                
                // 使用 long double 避免溢出
                long double cx = (long double)subX / subW;
                long double cy = (long double)subY / subW;
                long double dx = cx - blocks[s - 1].x;
                long double dy = cy - blocks[s - 1].y;
                long double dist2 = dx * dx + dy * dy;
                
                // 边界视为不稳定，加上微小容差
                if (dist2 >= (long double)blocks[s - 1].r * blocks[s - 1].r - 1e-12) {
                    feasible = false;
                    collapseIdx = t;
                    break;
                }
            }
            if (!feasible) break;
        }
        
        if (feasible) cout << "Feasible\n";
        else cout << "Unfeasible " << collapseIdx << "\n";
    }
    
    return 0;
}
