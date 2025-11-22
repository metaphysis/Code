// Beehives
// UVa ID: 12544
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.620s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int INF = 1e9;

vector<int> graph[MAXN];
int low[MAXN], dfn[MAXN], dfsClock;
bool isBridge[MAXN][MAXN];
vector<int> comp;
int n, m;

void findBridges(int u, int p) {
    low[u] = dfn[u] = ++dfsClock;
    for (int v : graph[u]) {
        if (v == p) continue;
        if (!dfn[v]) {
            findBridges(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                isBridge[u][v] = isBridge[v][u] = true;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void dfsComp(int u) {
    comp.push_back(u);
    dfn[u] = 1;
    for (int v : graph[u]) {
        if (!dfn[v] && !isBridge[u][v]) {
            dfsComp(v);
        }
    }
}

int findMinCycleInComponent(const vector<int>& component) {
    if (component.size() < 2) return INF;
    
    // 构建子图
    unordered_map<int, int> idMap;
    int compSize = component.size();
    for (int i = 0; i < compSize; ++i) {
        idMap[component[i]] = i;
    }
    
    vector<vector<int>> compGraph(compSize);
    for (int u : component) {
        for (int v : graph[u]) {
            if (idMap.count(v)) {
                compGraph[idMap[u]].push_back(idMap[v]);
            }
        }
    }
    
    // 在子图中找最小环
    int minCycle = INF;
    for (int start = 0; start < compSize; ++start) {
        vector<int> dist(compSize, -1);
        vector<int> parent(compSize, -1);
        queue<int> q;
        
        dist[start] = 0;
        q.push(start);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : compGraph[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                } else if (parent[u] != v) {
                    minCycle = min(minCycle, dist[u] + dist[v] + 1);
                }
            }
        }
    }
    
    return minCycle;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            graph[i].clear();
            dfn[i] = 0;
            for (int j = 0; j < n; ++j) {
                isBridge[i][j] = false;
            }
        }
        
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        // 找桥
        dfsClock = 0;
        for (int i = 0; i < n; ++i) {
            if (!dfn[i]) {
                findBridges(i, -1);
            }
        }
        
        // 找边双连通分量
        memset(dfn, 0, sizeof(dfn));
        int answer = INF;
        
        for (int i = 0; i < n; ++i) {
            if (!dfn[i]) {
                comp.clear();
                dfsComp(i);
                
                if (comp.size() >= 2) {
                    int minCycle = findMinCycleInComponent(comp);
                    if (minCycle == INF) {
                        // 如果没有环但是有边，答案是2
                        answer = min(answer, 2);
                    } else {
                        answer = min(answer, minCycle);
                    }
                }
            }
        }
        
        cout << "Case " << caseNum << ": ";
        if (answer == INF) {
            cout << "impossible\n";
        } else {
            cout << answer << "\n";
        }
    }
    
    return 0;
}
