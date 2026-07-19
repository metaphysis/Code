// Professor Monotonic's Networks
// UVa ID: 1007
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

int main() {
    int caseNo = 1;
    int n, k;
    while (cin >> n >> k) {
        if (n == 0 && k == 0) break;
        vector<pair<int,int>> comps;
        for (int i = 0; i < k; ++i) {
            int x, y;
            cin >> x >> y;
            comps.push_back({x, y});
        }
        // 计算运行时间
        map<int,int> timeMap;
        for (int i = 1; i <= n; ++i) timeMap[i] = 0;
        int maxTime = 0;
        for (auto &p : comps) {
            int x = p.first, y = p.second;
            int t = max(timeMap[x], timeMap[y]) + 1;
            timeMap[x] = t;
            timeMap[y] = t;
            if (t > maxTime) maxTime = t;
        }
        // 判断是否为排序网络（枚举所有 0-1 序列）
        bool isSort = true;
        int total = 1 << n;
        for (int mask = 0; mask < total; ++mask) {
            vector<int> val(n + 1);
            for (int i = 1; i <= n; ++i)
                val[i] = (mask >> (i - 1)) & 1;
            for (auto &p : comps) {
                int x = p.first, y = p.second;
                if (val[x] > val[y]) swap(val[x], val[y]);
            }
            for (int i = 2; i <= n; ++i)
                if (val[i - 1] > val[i]) { isSort = false; break; }
            if (!isSort) break;
        }
        cout << "Case " << caseNo << " is "
             << (isSort ? "a sorting network" : "not a sorting network")
             << " and operates in " << maxTime << " time units.\n";
        ++caseNo;
    }
    return 0;
}
