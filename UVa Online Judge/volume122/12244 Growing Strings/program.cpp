// Growing Strings
// UVa ID: 12244
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 1.680s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

namespace AhoCorasick {
    const int MAXN = 1e6 + 6;
    const int ALPHA = 26;
    const char BASE = 'a';
    
    int nxt[MAXN][ALPHA], fail[MAXN], out[MAXN], dp[MAXN];
    int nodeCnt;
    
    void initialize() {
        for (int i = 0; i < nodeCnt; ++i) {
            memset(nxt[i], 0, sizeof(nxt[i]));
            fail[i] = out[i] = dp[i] = 0;
        }
        nodeCnt = 1;
    }
    
    void insert(const string& s) {
        int u = 0;
        for (char c : s) {
            int idx = c - BASE;
            if (!nxt[u][idx]) nxt[u][idx] = nodeCnt++;
            u = nxt[u][idx];
        }
        out[u] = 1;
    }
    
    void build() {
        queue<int> q;
        for (int i = 0; i < ALPHA; ++i) {
            if (nxt[0][i]) {
                fail[nxt[0][i]] = 0;
                q.push(nxt[0][i]);
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            out[u] |= out[fail[u]];
            for (int i = 0; i < ALPHA; ++i) {
                int v = nxt[u][i];
                if (v) {
                    fail[v] = nxt[fail[u]][i];
                    q.push(v);
                } else {
                    nxt[u][i] = nxt[fail[u]][i];
                }
            }
        }
    }
    
    int solve(const string& s) {
        int u = 0, best = 1;
        for (char c : s) {
            u = nxt[u][c - BASE];
            for (int v = u; v; v = fail[v]) {
                if (out[v]) best = max(best, dp[v] + 1);
            }
        }
        dp[u] = max(dp[u], best);
        return best;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n, n) {
        vector<string> strs(n);
        for (int i = 0; i < n; ++i) cin >> strs[i];
        sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });
        AhoCorasick::initialize();
        for (const string& s : strs) AhoCorasick::insert(s);
        AhoCorasick::build();
        int ans = 0;
        for (const string& s : strs) ans = max(ans, AhoCorasick::solve(s));
        cout << ans << '\n';
    }
    return 0;
}
