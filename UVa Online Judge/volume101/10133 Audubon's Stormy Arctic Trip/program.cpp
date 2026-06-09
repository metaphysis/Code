// Audubon's Stormy Arctic Trip
// UVa ID: 10133
// Verdict: Accepted
// Submission Date: 2026-06-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000;

vector<int> g[MAXN];
long long dp[MAXN];

long long dfs(int u) {
    if (~dp[u]) return dp[u];
    long long r = 0;
    if (g[u].size()) for (int v : g[u]) r += dfs(v);
    else r = 1;
    return dp[u] = r;
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    string line;
    getline(cin, line);
    int t = stoi(line);
    getline(cin, line);
    for (int cs = 0; cs < t; cs++) {
        if (cs) cout << '\n';
        for (int i = 0; i < MAXN; i++) g[i].clear();
        map<int, string> idxer;
        vector<long long> queries;
        int nodeIdx = -1, subNodeIdx = 101;
        while (getline(cin, line)) {
            if (line.back() == ':') nodeIdx = stoi(line.substr(0, 2));
            else if (line.front() == ' ') {
                istringstream iss(line);
                string block;
                while (iss >> block) {
                    int p = block.find(':');
                    string nodeName = block.substr(0, p);
                    idxer[subNodeIdx] = nodeName;
                    g[nodeIdx].push_back(subNodeIdx);
                    if (block.back() != '$') {
                        int v = stoi(block.substr(p + 1));
                        g[subNodeIdx].push_back(v);
                    }
                    subNodeIdx++;
                }
            } else {
                queries.push_back(stoll(line));
                while (getline(cin, line)) {
                    if (line.empty()) break;
                    queries.push_back(stoll(line));
                }
                break;
            }
        }
        memset(dp, -1, sizeof dp);
        dfs(0);
        for (long long q : queries) {
            int u = 0;
            vector<int> r;
            r.push_back(u);
            while (g[u].size()) {
                for (auto v : g[u]) {
                    if (q > dp[v]) q -= dp[v];
                    else {
                        u = v;
                        break;
                    }
                }
                r.push_back(u);
            }
            int printed = 0;
            for (int i = 0; i < r.size(); i++) {
                if (idxer.count(r[i])) {
                    if (printed) cout << '-';
                    printed = 1;
                    cout << idxer[r[i]];
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
