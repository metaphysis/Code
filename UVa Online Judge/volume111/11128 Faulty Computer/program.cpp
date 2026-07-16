// Faulty Computer
// UVa ID: 11128
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Entry {
    long double val;
    int x1, x2, x3;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    for (int caseNo = 1; caseNo <= N; ++caseNo) {
        int a[7];
        for (int i = 1; i <= 6; ++i) cin >> a[i];
        long double sq[7];
        for (int i = 1; i <= 6; ++i) sq[i] = sqrtl((long double)a[i]);
        vector<Entry> left;
        left.reserve(19 * 19 * 19);
        for (int x1 = -9; x1 <= 9; ++x1)
            for (int x2 = -9; x2 <= 9; ++x2)
                for (int x3 = -9; x3 <= 9; ++x3) {
                    long double v = x1 * sq[1] + x2 * sq[2] + x3 * sq[3];
                    left.push_back({v, x1, x2, x3});
                }
        sort(left.begin(), left.end(), [](const Entry& p, const Entry& q) {
            return p.val < q.val;
        });
        bool found = false;
        int ans[7];
        for (int x4 = -9; x4 <= 9 && !found; ++x4)
            for (int x5 = -9; x5 <= 9 && !found; ++x5)
                for (int x6 = -9; x6 <= 9 && !found; ++x6) {
                    long double B = x4 * sq[4] + x5 * sq[5] + x6 * sq[6];
                    for (int x0 = -9; x0 <= 9 && !found; ++x0) {
                        long double target = -x0 - B;
                        auto it = lower_bound(left.begin(), left.end(), target,
                            [](const Entry& e, const long double& v) {
                                return e.val < v;
                            });
                        auto check = [&](const Entry& e) -> bool {
                            long double expr = e.val + B + x0;
                            if (fabsl(expr) >= 1e-4L) return false;
                            if (e.x1 == 0 && e.x2 == 0 && e.x3 == 0 &&
                                x4 == 0 && x5 == 0 && x6 == 0 && x0 == 0)
                                return false;
                            ans[0] = x0;
                            ans[1] = e.x1;
                            ans[2] = e.x2;
                            ans[3] = e.x3;
                            ans[4] = x4;
                            ans[5] = x5;
                            ans[6] = x6;
                            return true;
                        };
                        if (it != left.end() && check(*it)) found = true;
                        if (!found && it != left.begin()) {
                            --it;
                            if (check(*it)) found = true;
                        }
                    }
                }
        if (found) {
            cout << "Case " << caseNo << ":";
            for (int i = 0; i < 7; ++i) cout << ' ' << ans[i];
            cout << '\n';
        } else {
            cout << "Case " << caseNo << ": No Solution.\n";
        }
    }
    return 0;
}
