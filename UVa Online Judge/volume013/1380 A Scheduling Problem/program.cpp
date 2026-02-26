// A Scheduling Problem
// UVa ID: 1380
// Verdict: Accepted
// Submission Date: 2026-02-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> outE, inE;
vector<pair<int,int>> undE;
vector<int> dp, col;
vector<vector<int>> paths;
vector<set<int>> pos;
int n, k;
bool changed;

int dfs(int u) {
    if (dp[u] != -1) return dp[u];
    dp[u] = 1;
    for (int v : outE[u]) dp[u] = max(dp[u], 1 + dfs(v));
    return dp[u];
}

void getPaths(int u, vector<int>& p) {
    p.push_back(u);
    if (p.size() == k) paths.push_back(p);
    else for (int v : outE[u]) if (dp[v] == k - p.size()) getPaths(v, p);
    p.pop_back();
}

bool check() {
    changed = false;
    // 有向边
    for (int u = 1; u <= n; u++) for (int v : outE[u]) {
        if (col[u] != -1 && col[v] != -1) { if (col[u] >= col[v]) return false; continue; }
        if (col[u] != -1) {
            for (int c = 1; c <= col[u]; c++) if (pos[v].erase(c)) changed = true;
            if (pos[v].empty()) return false;
        } else if (col[v] != -1) {
            for (int c = col[v]; c <= k; c++) if (pos[u].erase(c)) changed = true;
            if (pos[u].empty()) return false;
        } else {
            bool ok = false;
            for (int cu : pos[u]) for (int cv : pos[v]) if (cu < cv) { ok = true; break; }
            if (!ok) return false;
        }
    }
    // 无向边
    for (auto& e : undE) {
        int a = e.first, b = e.second;
        if (col[a] != -1 && col[b] != -1) { if (col[a] == col[b]) return false; continue; }
        if (col[a] != -1) {
            if (pos[b].erase(col[a])) changed = true;
            if (pos[b].empty()) return false;
        } else if (col[b] != -1) {
            if (pos[a].erase(col[b])) changed = true;
            if (pos[a].empty()) return false;
        } else {
            bool ok = false;
            for (int ca : pos[a]) for (int cb : pos[b]) if (ca != cb) { ok = true; break; }
            if (!ok) return false;
        }
    }
    return true;
}

bool solve() {
    col.assign(n + 1, -1);
    pos.assign(n + 1, set<int>());
    for (int i = 1; i <= n; i++) for (int c = 1; c <= k; c++) pos[i].insert(c);
    
    for (auto& p : paths) for (int i = 0; i < p.size(); i++) {
        int node = p[i], c = i + 1;
        if (col[node] != -1 && col[node] != c) return false;
        if (col[node] == -1) {
            col[node] = c;
            pos[node] = {c};
        }
    }
    
    do {
        changed = false;
        if (!check()) return false;
        for (int i = 1; i <= n; i++) if (col[i] == -1 && pos[i].size() == 1) {
            col[i] = *pos[i].begin();
            changed = true;
        }
    } while (changed);
    
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line == "0") break;
        
        outE.assign(210, vector<int>());
        inE.assign(210, vector<int>());
        undE.clear();
        set<int> vertices;
        
        while (true) {
            if (line == "0") break;
            stringstream ss(line);
            int f; ss >> f;
            vertices.insert(f);
            string token;
            while (ss >> token) {
                if (token == "0") break;
                int s; char t = 0;
                if (token.back() == 'd' || token.back() == 'u') {
                    t = token.back();
                    token.pop_back();
                    s = stoi(token);
                } else s = stoi(token);
                vertices.insert(s);
                if (t == 'd') { outE[f].push_back(s); inE[s].push_back(f); }
                else if (t == 'u') { outE[s].push_back(f); inE[f].push_back(s); }
                else undE.push_back({f, s});
            }
            getline(cin, line);
        }
        
        n = *max_element(vertices.begin(), vertices.end());
        dp.assign(n + 1, -1);
        paths.clear();
        k = 0;
        for (int i = 1; i <= n; i++) k = max(k, dfs(i));
        for (int i = 1; i <= n; i++) if (dp[i] == k) {
            vector<int> p;
            getPaths(i, p);
        }
        cout << (solve() ? k : k + 1) << "\n";
    }
    return 0;
}
