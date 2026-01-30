// Ironman Race in Treeland
// UVa ID: 12161
// Verdict: Accepted
// Submission Date: 2026-01-19
// UVa Run Time: 0.240s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 30005;
const long long INF = 1e18;

struct Edge {
    int to, damage, length;
    Edge(int t, int d, int l) : to(t), damage(d), length(l) {}
};

vector<Edge> tree[MAX_N];
bool visited[MAX_N];
int subtreeSize[MAX_N];
int maxSubtree[MAX_N];
int center;
long long globalM;
long long bestLength;

void dfsSize(int u, int parent) {
    subtreeSize[u] = 1;
    maxSubtree[u] = 0;
    for (Edge &e : tree[u]) {
        if (e.to == parent || visited[e.to]) continue;
        dfsSize(e.to, u);
        subtreeSize[u] += subtreeSize[e.to];
        maxSubtree[u] = max(maxSubtree[u], subtreeSize[e.to]);
    }
}

void dfsCenter(int u, int parent, int total) {
    maxSubtree[u] = max(maxSubtree[u], total - subtreeSize[u]);
    if (center == -1 || maxSubtree[u] < maxSubtree[center]) center = u;
    for (Edge &e : tree[u]) {
        if (e.to == parent || visited[e.to]) continue;
        dfsCenter(e.to, u, total);
    }
}

void collectPaths(int u, int parent, long long curDamage, long long curLength, vector<pair<long long, long long>> &paths) {
    paths.push_back({curDamage, curLength});
    for (Edge &e : tree[u]) {
        if (e.to == parent || visited[e.to]) continue;
        collectPaths(e.to, u, curDamage + e.damage, curLength + e.length, paths);
    }
}

void processPaths(vector<pair<long long, long long>> &paths, vector<pair<long long, long long>> &sortedWithMax) {
    sort(paths.begin(), paths.end());
    long long maxLen = -INF;
    for (auto &p : paths) {
        maxLen = max(maxLen, p.second);
        sortedWithMax.push_back({p.first, maxLen});
    }
}

void combinePaths(vector<pair<long long, long long>> &pathsA, vector<pair<long long, long long>> &pathsB) {
    vector<pair<long long, long long>> sortedA, sortedB;
    processPaths(pathsA, sortedA);
    processPaths(pathsB, sortedB);
    
    int j = sortedA.size() - 1;
    for (int i = 0; i < sortedB.size(); ++i) {
        long long damageB = sortedB[i].first;
        long long lengthB = sortedB[i].second;
        if (damageB <= globalM) bestLength = max(bestLength, lengthB);
        while (j >= 0 && sortedA[j].first + damageB > globalM) j--;
        if (j >= 0) bestLength = max(bestLength, sortedA[j].second + lengthB);
    }
}

void solve(int u) {
    visited[u] = true;
    vector<vector<pair<long long, long long>>> allPaths;
    
    for (Edge &e : tree[u]) {
        if (visited[e.to]) continue;
        vector<pair<long long, long long>> paths;
        collectPaths(e.to, u, e.damage, e.length, paths);
        allPaths.push_back(paths);
    }
    
    vector<pair<long long, long long>> combined;
    for (auto &paths : allPaths) {
        combinePaths(combined, paths);
        for (auto &p : paths) combined.push_back(p);
    }
    
    bestLength = max(bestLength, 0LL);
    for (auto &p : combined) if (p.first <= globalM) bestLength = max(bestLength, p.second);
    
    for (Edge &e : tree[u]) {
        if (visited[e.to]) continue;
        center = -1;
        dfsSize(e.to, u);
        dfsCenter(e.to, u, subtreeSize[e.to]);
        solve(center);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n;
        long long m;
        cin >> n >> m;
        globalM = m;
        
        for (int i = 1; i <= n; ++i) {
            tree[i].clear();
            visited[i] = false;
        }
        
        for (int i = 0; i < n - 1; ++i) {
            int a, b, D, L;
            cin >> a >> b >> D >> L;
            tree[a].emplace_back(b, D, L);
            tree[b].emplace_back(a, D, L);
        }
        
        bestLength = 0;
        center = -1;
        dfsSize(1, -1);
        dfsCenter(1, -1, n);
        solve(center);
        
        cout << "Case " << caseNo << ": " << bestLength << "\n";
    }
    return 0;
}
