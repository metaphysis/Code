// Count Equation Solutions
// UVa ID: 13262
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 12.000s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    while (cin >> m) {
        int a1, a2, a3, a4, a5, a6;
        cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
        vector<long long> right;
        right.reserve(m * m * m);
        right.max_load_factor(0.7);
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 1; k <= m; k++) {
                    int sum = a2 * i + a4 * j + a6 * k;
                    rightCnt[sum]++;
                }
            }
        }
        sort(right.begin(), right.end());
        long long ans = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 1; k <= m; k++) {
                    int sum = a1 * i + a3 * j + a5 * k;
                    auto it = rightCnt.find(sum);
                    if (it != rightCnt.end())
                        ans += it->second;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
