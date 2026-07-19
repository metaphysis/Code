// Interesting Calculator
// UVa ID: 12664
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

const long long INF_COST = 4e18;
const int INF_PRESS = INT_MAX;

struct State {
    long long cost;
    int presses;
};

void updateState(State &cur, long long newCost, int newPress) {
    if (newCost < cur.cost || (newCost == cur.cost && newPress < cur.presses)) {
        cur.cost = newCost;
        cur.presses = newPress;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y;
    int caseNo = 1;
    while (cin >> x >> y) {
        vector<int> appendCost(10), addCost(10), mulCost(10);
        for (int i = 0; i < 10; ++i) cin >> appendCost[i];
        for (int i = 0; i < 10; ++i) cin >> addCost[i];
        for (int i = 0; i < 10; ++i) cin >> mulCost[i];
        int n = y;
        // dp0[i]：从0到i，不使用乘0的最优（成本，步数）
        vector<State> dp0(n + 1, {INF_COST, INF_PRESS});
        dp0[0] = {0, 0};
        for (int i = 0; i <= n; ++i) {
            if (dp0[i].cost == INF_COST) continue;
            for (int d = 0; d <= 9; ++d) {
                long long j = 1LL * i * 10 + d;
                if (j > n) continue;
                long long newCost = dp0[i].cost + appendCost[d];
                int newPress = dp0[i].presses + 1;
                updateState(dp0[j], newCost, newPress);
            }
            for (int d = 1; d <= 9; ++d) {
                long long j = i + d;
                if (j > n) continue;
                long long newCost = dp0[i].cost + addCost[d];
                int newPress = dp0[i].presses + 1;
                updateState(dp0[j], newCost, newPress);
            }
            for (int d = 2; d <= 9; ++d) {
                long long j = 1LL * i * d;
                if (j > n) continue;
                long long newCost = dp0[i].cost + mulCost[d];
                int newPress = dp0[i].presses + 1;
                updateState(dp0[j], newCost, newPress);
            }
        }
        // dpx[i]：从x到i，不使用乘0的最优（成本，步数）
        vector<State> dpx(n + 1, {INF_COST, INF_PRESS});
        if (x <= n) dpx[x] = {0, 0};
        for (int i = x; i <= n; ++i) {
            if (dpx[i].cost == INF_COST) continue;
            for (int d = 0; d <= 9; ++d) {
                long long j = 1LL * i * 10 + d;
                if (j > n) continue;
                long long newCost = dpx[i].cost + appendCost[d];
                int newPress = dpx[i].presses + 1;
                updateState(dpx[j], newCost, newPress);
            }
            for (int d = 1; d <= 9; ++d) {
                long long j = i + d;
                if (j > n) continue;
                long long newCost = dpx[i].cost + addCost[d];
                int newPress = dpx[i].presses + 1;
                updateState(dpx[j], newCost, newPress);
            }
            for (int d = 2; d <= 9; ++d) {
                long long j = 1LL * i * d;
                if (j > n) continue;
                long long newCost = dpx[i].cost + mulCost[d];
                int newPress = dpx[i].presses + 1;
                updateState(dpx[j], newCost, newPress);
            }
        }
        // 方案1：完全不使用乘0
        long long bestCost = dpx[y].cost;
        int bestPress = dpx[y].presses;
        // 方案2：先按一次乘0（从x变为0），再从0到y
        long long candCost = mulCost[0] + dp0[y].cost;
        int candPress = 1 + dp0[y].presses;
        if (candCost < bestCost || (candCost == bestCost && candPress < bestPress)) {
            bestCost = candCost;
            bestPress = candPress;
        }
        cout << "Case " << caseNo++ << ": " << bestCost << " " << bestPress << '\n';
    }
    return 0;
}
