// Food Portion Size
// UVa ID: 11633
// Verdict: Accepted
// Submission Date: 2026-01-09
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, long long> Frac;

// 比较两个分数的大小，a < b
bool cmp(const Frac& a, const Frac& b) {
    return a.first * b.second < b.first * a.second;
}

// 约分分数
Frac reduce(const Frac& f) {
    long long g = __gcd(f.first, f.second);
    return {f.first / g, f.second / g};
}

int main() {
    int n;
    while (cin >> n, n) {
        int a, b;
        cin >> a >> b;
        vector<int> food(n);
        // 收集所有候选S：每个食量的1, 1/2, 1/3
        set<Frac> candidates;
        for (int i = 0; i < n; ++i) {
            cin >> food[i];
            for (int k = 1; k <= 3; ++k) {
                long long g = __gcd(food[i], k);
                candidates.insert({food[i] / g, k / g});
            }
        }
        // 排序食量用于提前剪枝
        sort(food.begin(), food.end());
        Frac bestCost = {LLONG_MAX, 1};
        for (const auto& s : candidates) {
            long long u = s.first, d = s.second;
            // 提前剪枝：检查最大食量的学生
            if ((food.back() * d + u - 1) / u > 3) continue;
            long long totalWaste = 0;
            long long totalTrips = 0;
            bool valid = true;
            for (int yi : food) {
                long long portions = (yi * d + u - 1) / u;
                if (portions > 3) {
                    valid = false;
                    break;
                }
                totalTrips += portions;
                totalWaste += portions * u - yi * d;
            }
            if (!valid) continue;
            // 计算成本
            Frac cost = {a * totalWaste + b * totalTrips * d, d};
            cost = reduce(cost);
            if (cmp(cost, bestCost)) bestCost = cost;
        }
        // 输出结果
        if (bestCost.second == 1) cout << bestCost.first;
        else cout << bestCost.first << " / " << bestCost.second;
        cout << '\n';
    }
    return 0;
}
