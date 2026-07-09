// Program Modules
// UVa ID: 792
// Verdict: Accepted
// Submission Date: 2026-07-09
// UVa Run Time: 0.300s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<string> splitByWhitespace(const string& s) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (ss >> token) tokens.push_back(token);
    return tokens;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string data, token;
    while (cin >> token) {
        data = token;
        while (1) {
            if (token.back() == '.') break;
            cin >> token;
            data += ' ' + token;
        }
        vector<string> names;
        unordered_map<string, int> idMap;
        vector<vector<int>> g;
        auto getNode = [&](const string& name) -> int {
            auto it = idMap.find(name);
            if (it != idMap.end()) return it->second;
            int newId = (int)names.size();
            idMap[name] = newId;
            names.push_back(name);
            g.push_back({});
            return newId;
        };
        size_t pos = 0;
        while (true) {
            size_t left = data.find('(', pos);
            if (left == string::npos) break;
            size_t right = data.find(')', left + 1);
            string inner = data.substr(left + 1, right - left - 1);
            vector<string> tokens = splitByWhitespace(inner);
            if (tokens.empty()) {
                pos = right + 1;
                continue;
            }
            int srcId = getNode(tokens[0]);
            for (size_t i = 1; i < tokens.size(); ++i) {
                int tId = getNode(tokens[i]);
                g[srcId].push_back(tId);
            }
            pos = right + 1;
        }
        int n = names.size();
        vector<int> dfn(n, 0), low(n, 0), sccId(n, -1), stk;
        vector<char> inStack(n, 0);
        int timer = 0, sccCnt = 0;
        function<void(int)> tarjan = [&](int u) {
            dfn[u] = low[u] = ++timer;
            stk.push_back(u);
            inStack[u] = 1;
            for (int v : g[u]) {
                if (!dfn[v]) {
                    tarjan(v);
                    low[u] = min(low[u], low[v]);
                } else if (inStack[v]) {
                    low[u] = min(low[u], dfn[v]);
                }
            }
            if (low[u] == dfn[u]) {
                ++sccCnt;
                while (true) {
                    int v = stk.back(); stk.pop_back();
                    inStack[v] = 0;
                    sccId[v] = sccCnt;
                    if (v == u) break;
                }
            }
        };
        for (int i = 0; i < n; ++i) if (!dfn[i]) tarjan(i);
        vector<vector<string>> sccNodes(sccCnt + 1);
        for (int i = 0; i < n; ++i) sccNodes[sccId[i]].push_back(names[i]);
        for (int i = 1; i <= sccCnt; ++i) sort(sccNodes[i].begin(), sccNodes[i].end());
        vector<int> order(sccCnt);
        iota(order.begin(), order.end(), 1);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return sccNodes[a][0] < sccNodes[b][0];
        });
        for (int idx : order) {
            for (int j = 0; j < (int)sccNodes[idx].size(); ++j) {
                if (j) cout << ' ';
                cout << sccNodes[idx][j];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
