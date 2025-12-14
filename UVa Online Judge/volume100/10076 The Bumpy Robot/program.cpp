// The Bumpy Robot
// UVa ID: 10076
// Verdict: Accepted
// Submission Date: 2025-12-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct State {
    int row, col, energy;
    int time;
    State(int r, int c, int e, int t) : row(r), col(c), energy(e), time(t) {}
    // 优先队列按时间从小到大排序
    bool operator<(const State& other) const {
        return time > other.time;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int INF = 1e9;
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    
    int M, N;
    while (cin >> M >> N, M || N) {
        double alpha1, alpha2, beta1, beta2;
        int gamma, delta;
        cin >> alpha1 >> alpha2 >> gamma;
        cin >> beta1 >> beta2 >> delta;
        
        vector<vector<int>> height(M, vector<int>(N));
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                cin >> height[i][j];
        
        int rs, cs, rt, ct, E;
        cin >> rs >> cs >> rt >> ct >> E;
        rs--; cs--; rt--; ct--; // 转为0-based索引
        
        // minTime[r][c][e] = 到达(r,c)且消耗能量e的最小时间
        vector<vector<vector<int>>> minTime(M, vector<vector<int>>(N, vector<int>(E + 1, INF)));
        priority_queue<State> pq;
        
        if (rs == rt && cs == ct) {
            cout << "0\n";
            continue;
        }
        
        minTime[rs][cs][0] = 0;
        pq.emplace(rs, cs, 0, 0);
        
        int ans = INF;
        
        while (!pq.empty()) {
            State cur = pq.top(); pq.pop();
            int r = cur.row, c = cur.col, e = cur.energy, t = cur.time;
            
            if (t > minTime[r][c][e]) continue; // 已有更优状态
            
            // 尝试四个方向
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir], nc = c + dc[dir];
                if (nr < 0 || nr >= M || nc < 0 || nc >= N) continue;
                
                int h1 = height[r][c], h2 = height[nr][nc];
                int deltaE, deltaT;
                
                // 计算能量增量
                if (h1 > h2) {
                    deltaE = ceil(alpha1 * (h1 - h2)) + gamma;
                    deltaT = ceil(beta1 * (h1 - h2)) + delta;
                } else if (h1 == h2) {
                    deltaE = gamma;
                    deltaT = delta;
                } else {
                    deltaE = ceil(alpha2 * (h2 - h1)) + gamma;
                    deltaT = ceil(beta2 * (h2 - h1)) + gamma; // 注意原文中时间公式第三项为 gamma，实际应为 delta
                }
                
                int ne = e + deltaE;
                int nt = t + deltaT;
                
                if (ne > E) continue; // 能量超限
                if (nt >= minTime[nr][nc][ne]) continue; // 已有更优
                
                minTime[nr][nc][ne] = nt;
                pq.emplace(nr, nc, ne, nt);
                
                if (nr == rt && nc == ct) {
                    ans = min(ans, nt);
                }
            }
        }
        
        if (ans == INF) cout << "failed\n";
        else cout << ans << "\n";
    }
    
    return 0;
}
