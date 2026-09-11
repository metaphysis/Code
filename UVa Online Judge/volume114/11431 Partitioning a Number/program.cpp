// Partitioning a Number
// UVa ID: 11431
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

// 帕累托剪枝，移除被支配的状态
void prune(vector<pair<int64, int64>>& states) {
    vector<pair<int64, int64>> kept;
    for (auto& p : states) {
        bool dominated = false;
        for (auto& q : states) {
            if (&p == &q) continue;
            if (q.first >= p.first && q.second >= p.second) {
                dominated = true;
                break;
            }
        }
        if (!dominated) kept.push_back(p);
    }
    states = kept;
}

// 计算 max_{0 <= x <= n} f(x)
int64 maxPrefixF(int64 n) {
    if (n == 0) return 1;
    string s;
    while (n > 0) {
        s.push_back(char('0' + (n & 1)));
        n >>= 1;
    }
    reverse(s.begin(), s.end()); // 从高位到低位
    int L = (int)s.size();

    // 两个集合：tight = true 和 false
    vector<pair<int64, int64>> tight, loose;
    tight.push_back({1, 0}); // 初始状态 k=0: f(0)=1, f(-1)=0

    for (int i = 0; i < L; ++i) {
        int c = s[i] - '0';
        vector<pair<int64, int64>> nextTight, nextLoose;

        auto addState = [&](bool isTight, int64 a, int64 b) {
            if (isTight) nextTight.push_back({a, b});
            else nextLoose.push_back({a, b});
        };

        // 处理当前tight集合
        for (auto& st : tight) {
            int64 a = st.first, b = st.second;
            // 选0
            int64 na0 = a + b, nb0 = b;
            bool newTight0 = (c == 0); // 若c==0则保持tight，否则变为loose
            addState(newTight0, na0, nb0);
            // 选1（只有c==1时才能保持tight，若c==0则只能进入loose）
            if (c == 1) {
                int64 na1 = a, nb1 = a + b;
                addState(true, na1, nb1); // 选1且c==1，保持tight
            }
        }

        // 处理当前loose集合
        for (auto& st : loose) {
            int64 a = st.first, b = st.second;
            // 选0
            int64 na0 = a + b, nb0 = b;
            addState(false, na0, nb0);
            // 选1
            int64 na1 = a, nb1 = a + b;
            addState(false, na1, nb1);
        }

        prune(nextTight);
        prune(nextLoose);
        tight = nextTight;
        loose = nextLoose;
    }

    int64 ans = 0;
    for (auto& st : tight) ans = max(ans, st.first);
    for (auto& st : loose) ans = max(ans, st.first);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNo = 1;
    int64 n;
    while (cin >> n && n != 0) {
        int64 ans = maxPrefixF(n);
        cout << "Case " << caseNo++ << ": " << ans << "\n";
    }
    return 0;
}
