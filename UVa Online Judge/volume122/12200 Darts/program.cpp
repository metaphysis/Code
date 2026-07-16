// Darts
// UVa ID: 12200
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    // 标准飞镖盘顺序（从顶部顺时针）
    const int scores[20] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5};
    
    vector<int> queries;
    int N;
    while (cin >> N && N != 0) queries.push_back(N);
    if (queries.empty()) return 0;
    
    int maxN = *max_element(queries.begin(), queries.end());
    
    // f[sA][sB]: 轮到A投时A的胜率；g[sA][sB]: 轮到B投时A的胜率
    vector<vector<double>> f(maxN + 1, vector<double>(maxN + 1, 0.0));
    vector<vector<double>> g(maxN + 1, vector<double>(maxN + 1, 0.0));
    
    // 边界条件
    for (int sB = 0; sB <= maxN; ++sB) {
        f[0][sB] = 1.0;
        g[0][sB] = 1.0;
    }
    for (int sA = 0; sA <= maxN; ++sA) {
        f[sA][0] = 0.0;
        g[sA][0] = 0.0;
    }
    f[0][0] = 1.0; // 实际上不会用到
    
    // 按 sA, sB 递增递推
    for (int sA = 1; sA <= maxN; ++sA) {
        for (int sB = 1; sB <= maxN; ++sB) {
            // 计算 A 投掷时的 C_A 和 P_A
            double CA = 0.0, PA = 0.0;
            for (int v = 1; v <= 20; ++v) {
                if (sA == v) {
                    CA += 1.0 / 20.0;
                } else if (sA < v) {
                    PA += 1.0 / 20.0;
                } else { // sA > v
                    CA += g[sA - v][sB] / 20.0;
                }
            }
            
            double bestX = 0.0, bestY = 1e100;
            // 枚举 B 的所有瞄准目标
            for (int target = 0; target < 20; ++target) {
                int left = (target - 1 + 20) % 20;
                int right = (target + 1) % 20;
                int hits[3] = {scores[target], scores[left], scores[right]};
                
                double Ct = 0.0, Pt = 0.0;
                for (int i = 0; i < 3; ++i) {
                    int v = hits[i];
                    if (sB == v) {
                        // B 获胜，贡献 0
                        continue;
                    } else if (sB < v) {
                        Pt += 1.0 / 3.0;
                    } else { // sB > v
                        Ct += f[sA][sB - v] / 3.0;
                    }
                }
                
                double denom = 1.0 - PA * Pt;
                double xt = (CA + PA * Ct) / denom;
                double yt = (Ct + Pt * CA) / denom;
                
                if (yt < bestY) {
                    bestY = yt;
                    bestX = xt;
                }
            }
            
            f[sA][sB] = bestX;
            g[sA][sB] = bestY;
        }
    }
    
    cout << fixed << setprecision(12);
    for (int n : queries) {
        double ansAFirst = f[n][n];
        double ansBFirst = 1.0 - g[n][n];
        cout << ansAFirst << ' ' << ansBFirst << '\n';
    }
    
    return 0;
}
