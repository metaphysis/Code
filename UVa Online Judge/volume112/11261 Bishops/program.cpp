// Bishops
// UVa ID: 11261
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int L;
    scanf("%d", &L);
    for (int caseId = 1; caseId <= L; ++caseId) {
        int n, m;
        scanf("%d %d", &n, &m);
        
        // 存储被占用的主对角线
        unordered_set<int> mainDiagSet;
        // 按奇偶性分组存储被占用的副对角线
        unordered_map<int, unordered_set<int>> antiDiagByParity;
        
        // 读入象的位置并收集对角线信息
        for (int i = 0; i < m; ++i) {
            int r, c;
            scanf("%d %d", &r, &c);
            // 主对角线：r - c
            mainDiagSet.insert(r - c);
            
            // 副对角线：r + c
            int d2 = r + c;
            // 计算奇偶性（0 或 1）
            int parity = (d2 % 2 + 2) % 2;
            antiDiagByParity[parity].insert(d2);
        }
        
        // 棋盘总格子数
        long long totalCells = (long long)n * n;
        
        // 计算主对角线上的被攻击格子数
        long long attackedByMain = 0;
        for (int d1 : mainDiagSet) {
            int len = n - abs(d1);
            attackedByMain += len;
        }
        
        // 计算副对角线上的被攻击格子数
        long long attackedByAnti = 0;
        for (auto& entry : antiDiagByParity) {
            for (int d2 : entry.second) {
                int len = n - abs(d2 - (n + 1));
                attackedByAnti += len;
            }
        }
        
        // 计算交点数量
        long long intersections = 0;
        for (int d1 : mainDiagSet) {
            // 获取主对角线的奇偶性
            int parity = ((d1 % 2) + 2) % 2;
            // 如果没有同奇偶的副对角线，跳过
            if (antiDiagByParity.find(parity) == antiDiagByParity.end()) continue;
            
            // 遍历所有同奇偶的副对角线
            for (int d2 : antiDiagByParity[parity]) {
                // 计算交点坐标
                int r = (d1 + d2) / 2;
                int c = (d2 - d1) / 2;
                
                // 检查交点是否在棋盘内
                if (r >= 1 && r <= n && c >= 1 && c <= n) {
                    intersections++;
                }
            }
        }
        
        // 计算最终结果
        long long attacked = attackedByMain + attackedByAnti - intersections;
        long long safe = totalCells - attacked;
        printf("Case #%d: %lld\n", caseId, safe);
    }
    return 0;
}
