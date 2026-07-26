// Restaurant 
// UVa ID: 1468
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.100s
// https://blog.csdn.net/metaphysis/article/details/163173912

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int M, n;
        cin >> M >> n;
        vector<pair<int,int>> pts(n);
        for (int i = 0; i < n; ++i) cin >> pts[i].first >> pts[i].second;
        // 公寓坐标，水平线为 Y
        int Y = pts[0].second;
        int a = pts[0].first, b = pts[1].first;
        if (a > b) swap(a, b);
        // 计算每个餐厅的 (D, E)
        vector<pair<int,int>> vals;
        vals.reserve(n);
        for (auto &p : pts) {
            int x = p.first, y = p.second;
            int D = abs(x - a) + abs(y - Y);
            int E = abs(x - b) + abs(y - Y);
            vals.emplace_back(D, E);
        }
        // 排序并筛选 Pareto 边界点
        sort(vals.begin(), vals.end(), [](const pair<int,int>& u, const pair<int,int>& v) {
            if (u.first != v.first) return u.first < v.first;
            return u.second < v.second;
        });
        vector<pair<int,int>> boundary;
        int minE = INT_MAX;
        for (auto &pr : vals) {
            if (pr.second < minE) {
                boundary.push_back(pr);
                minE = pr.second;
            }
        }
        int k = (int)boundary.size();
        long long ans = 0;
        // 枚举每个可能的 x
        for (int x = 0; x < M; ++x) {
            int g = abs(x - a);
            int h = abs(x - b);
            // 二分查找最后一个满足 A_j <= B_j 的索引
            int lo = 0, hi = k - 1, idx = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                int D = boundary[mid].first;
                int E = boundary[mid].second;
                int Aj = D - g;
                int Bj = E - h;
                if (Aj <= Bj) {
                    idx = mid;
                    lo = mid + 1;
                } else hi = mid - 1;
            }
            long long Tval = LLONG_MAX;
            if (idx >= 0) {
                int D = boundary[idx].first;
                int E = boundary[idx].second;
                Tval = min(Tval, (long long)max(D - g, E - h));
            }
            if (idx + 1 < k) {
                int D = boundary[idx + 1].first;
                int E = boundary[idx + 1].second;
                Tval = min(Tval, (long long)max(D - g, E - h));
            }
            // 统计满足 |y - Y| < Tval 的 y 的个数
            if (Tval > 0) {
                int left = max(0, Y - (int)Tval + 1);
                int right = min(M - 1, Y + (int)Tval - 1);
                if (left <= right) ans += (right - left + 1);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
