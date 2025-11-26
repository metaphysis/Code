// Arranging Heaps
// UVa ID: 12524
// Verdict: Accepted
// Submission Date: 2025-11-26
// UVa Run Time: 0.700s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1005;
const ll INF = 1e18;

ll x[MAXN], w[MAXN];
ll sumW[MAXN], sumXW[MAXN];
ll dp[MAXN][MAXN];

struct Line {
    ll m, b;
    ll eval(ll x) const { return m * x + b; }
};

bool bad(const Line& l1, const Line& l2, const Line& l3) {
    return (l3.b - l1.b) * (l1.m - l2.m) <= (l2.b - l1.b) * (l1.m - l3.m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    while (cin >> n >> k) {
        for (int i = 1; i <= n; i++) {
            cin >> x[i] >> w[i];
            sumW[i] = sumW[i-1] + w[i];
            sumXW[i] = sumXW[i-1] + w[i] * x[i];
        }

        for (int i = 1; i <= n; i++) {
            dp[i][1] = x[i] * sumW[i] - sumXW[i];
            for (int j = 2; j <= k; j++)
                dp[i][j] = INF;
        }

        for (int j = 2; j <= k; j++) {
            deque<Line> dq;
            
            for (int i = j; i <= n; i++) {
                Line newLine = {-sumW[i-1], dp[i-1][j-1] + sumXW[i-1]};
                
                while (dq.size() >= 2 && bad(dq[dq.size()-2], dq.back(), newLine))
                    dq.pop_back();
                dq.push_back(newLine);
                
                while (dq.size() >= 2 && dq[0].eval(x[i]) >= dq[1].eval(x[i]))
                    dq.pop_front();
                
                dp[i][j] = dq.front().eval(x[i]) + (x[i] * sumW[i] - sumXW[i]);
            }
        }

        cout << dp[n][k] << "\n";
    }
    return 0;
}
