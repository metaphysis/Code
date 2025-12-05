// The Strange Research
// UVa ID: 10732
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNo = 1;
    int N;
    while (cin >> N && N != 0) {
        vector<double> vals(N);
        for (int i = 0; i < N; ++i) cin >> vals[i];
        sort(vals.begin(), vals.end());
        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            double a = vals[i];
            if (a > 0) {
                // 情况1: b > -a 且 b < 1/a
                double low = -a;
                double high = 1.0 / a;
                auto itLow = upper_bound(vals.begin(), vals.end(), low);
                auto itHigh = lower_bound(vals.begin(), vals.end(), high);
                long long cnt = max(0LL, (long long)(itHigh - itLow));
                if (low < a && a < high) cnt--;
                ans += cnt;
            }
            else if (a == 0) {
                // 情况1: b > 0
                auto it = upper_bound(vals.begin(), vals.end(), 0.0);
                ans += (vals.end() - it);
            }
            else { // a < 0
                // 情况1: b > -a
                double low1 = -a;
                auto itLow1 = upper_bound(vals.begin(), vals.end(), low1);
                ans += (vals.end() - itLow1);

                // 情况2: b < 1/a
                double high2 = 1.0 / a;
                auto itHigh2 = lower_bound(vals.begin(), vals.end(), high2);
                long long cnt2 = itHigh2 - vals.begin();
                if (a < high2) cnt2--; // 去掉自身
                ans += cnt2;
            }
        }
        // 每个无序对被统计两次
        ans /= 2;
        cout << "Case " << caseNo++ << ": " << ans << "\n";
    }
    return 0;
}
