// Grinding GridGrinding Grid
// UVa ID: 12766
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Block {
    int lr, rr, lc, rc;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> p(N + 1);
        for (int i = 1; i <= N; ++i) cin >> p[i];
        vector<Block> stk;
        stk.reserve(N);
        for (int i = 1; i <= N; ++i) {
            Block cur = {i, i, p[i], p[i]};
            stk.push_back(cur);
            while (stk.size() >= 2) {
                Block &b1 = stk[stk.size() - 2];
                Block &b2 = stk[stk.size() - 1];
                bool rowAdj = (b1.rr + 1 == b2.lr);
                bool colAdj = (b1.rc + 1 == b2.lc) || (b2.rc + 1 == b1.lc);
                if (rowAdj && colAdj) {
                    Block merged;
                    merged.lr = b1.lr;
                    merged.rr = b2.rr;
                    merged.lc = min(b1.lc, b2.lc);
                    merged.rc = max(b1.rc, b2.rc);
                    stk.pop_back();
                    stk.pop_back();
                    stk.push_back(merged);
                } else {
                    break;
                }
            }
        }
        bool ok = false;
        if (stk.size() == 1) {
            Block &b = stk[0];
            if (b.lr == 1 && b.rr == N && b.lc == 1 && b.rc == N) ok = true;
        }
        cout << (ok ? "yes" : "no") << '\n';
    }
    return 0;
}
