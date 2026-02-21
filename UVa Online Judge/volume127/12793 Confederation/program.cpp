// Confederation
// UVa ID: 12793
// Verdict: Accepted
// Submission Date: 2026-02-02
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    while (cin >> m >> n) {
        // 存储 M 个平面的系数 A, B, C, D
        vector<vector<int>> planes(m, vector<int>(4));
        for (int i = 0; i < m; ++i) 
            for (int j = 0; j < 4; ++j) 
                cin >> planes[i][j];

        // 统计每个区域编码出现的次数
        map<string, int> regionCount;
        for (int i = 0; i < n; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            string key = "";
            // 对每个平面计算行星在哪一侧
            for (int j = 0; j < m; ++j) {
                // 使用 long long 防止乘法溢出
                long long val = (long long)planes[j][0] * x + 
                                (long long)planes[j][1] * y + 
                                (long long)planes[j][2] * z - 
                                planes[j][3];
                // 大于 0 为正侧，否则为负侧
                key.push_back(val > 0 ? '1' : '0');
            }
            // 该区域计数加一
            ++regionCount[key];
        }

        // 找出最大行星数
        int maxPlanets = 0;
        for (auto &p : regionCount) 
            maxPlanets = max(maxPlanets, p.second);
        cout << maxPlanets << endl;
    }
    return 0;
}
