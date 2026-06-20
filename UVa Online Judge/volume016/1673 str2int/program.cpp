// str2int
// UVa ID: 1673
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 2012;
const int ALPHA = 11;          // 0~9 和 '#'（映射为 10）

struct State {
    int next[ALPHA];
    int link, len;
    State() { memset(next, -1, sizeof(next)); link = -1; len = 0; }
};

vector<State> st;
int last;

void sam_init() {
    st.clear();
    st.push_back(State());
    last = 0;
}

void sam_extend(int c) {
    int cur = (int)st.size();
    st.push_back(State());
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && st[p].next[c] == -1) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = (int)st.size();
            st.push_back(State());
            st[clone].len = st[p].len + 1;
            memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        string total;
        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            total += s;
            total += '#';          // 分隔符，不与数字混淆
        }

        sam_init();
        for (char ch : total) {
            int c = (ch == '#') ? 10 : (ch - '0');
            sam_extend(c);
        }

        int sz = (int)st.size();
        vector<int> order(sz);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return st[a].len > st[b].len;
        });

        vector<int> A(sz, 0), B(sz, 0);
        for (int v : order) {
            A[v] = 1;          // 空路径：10^0 = 1
            B[v] = 0;          // 空路径数值为 0
            for (int c = 0; c <= 9; ++c) {   // 只处理数字转移
                int u = st[v].next[c];
                if (u == -1) continue;
                A[v] = (A[v] + 10 * A[u]) % MOD;
                B[v] = (B[v] + c * A[u] + B[u]) % MOD;
            }
        }

        int ans = 0;
        for (int c = 1; c <= 9; ++c) {   // 首位不能为 '0'
            int u = st[0].next[c];
            if (u == -1) continue;
            ans = (ans + c * A[u] + B[u]) % MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}
