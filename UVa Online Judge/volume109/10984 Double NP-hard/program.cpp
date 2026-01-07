// Double NP-hard
// UVa ID: 10984
// Verdict: Accepted
// Submission Date: 2026-01-03
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
vector<int> graph[MAXN];
int color[MAXN];
int n, m;

// 染色判断二分图
bool isBipartite(vector<int>& partX, vector<int>& partY) {
    memset(color, -1, sizeof(color));
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                if (color[u] == 0) partX.push_back(u);
                else partY.push_back(u);
                for (int v : graph[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        q.push(v);
                    } else if (color[v] == color[u]) return false;
                }
            }
        }
    }
    return true;
}

// Hopcroft-Karp 最大匹配
class HopcroftKarp {
    vector<int> graph[MAXN];
    int matchX[MAXN], matchY[MAXN];
    int distX[MAXN], distY[MAXN];
    int n;
    
public:
    HopcroftKarp(int size) : n(size) {
        memset(matchX, -1, sizeof(matchX));
        memset(matchY, -1, sizeof(matchY));
    }
    
    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }
    
    bool bfs() {
        queue<int> q;
        memset(distX, -1, sizeof(distX));
        memset(distY, -1, sizeof(distY));
        
        for (int u = 1; u <= n; u++) 
            if (matchX[u] == -1) {
                distX[u] = 0;
                q.push(u);
            }
        
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                if (distY[v] == -1) {
                    distY[v] = distX[u] + 1;
                    if (matchY[v] == -1) found = true;
                    else {
                        distX[matchY[v]] = distY[v] + 1;
                        q.push(matchY[v]);
                    }
                }
            }
        }
        return found;
    }
    
    bool dfs(int u) {
        for (int v : graph[u]) {
            if (distY[v] == distX[u] + 1) {
                distY[v] = 0;  // 标记已访问
                if (matchY[v] == -1 || dfs(matchY[v])) {
                    matchX[u] = v;
                    matchY[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    
    int maxMatch() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= n; u++) 
                if (matchX[u] == -1 && dfs(u)) matching++;
        }
        return matching;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        cin >> n >> m;
        
        // 初始化
        for (int i = 1; i <= n; i++) graph[i].clear();
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        cout << "Case #" << caseNum << ": ";
        
        // 特殊情况：空图
        if (n == 0) {
            cout << "0\n\n";
            continue;
        }
        
        // n必须是偶数
        if (n % 2 != 0) {
            cout << "Impossible\n";
            continue;
        }
        
        // 检查是否为二分图
        vector<int> partX, partY;
        if (!isBipartite(partX, partY)) {
            cout << "Impossible\n";
            continue;
        }
        
        // 检查两部分大小是否相等
        if (partX.size() != partY.size()) {
            cout << "Impossible\n";
            continue;
        }
        
        // 检查是否存在完美匹配
        HopcroftKarp hk(n);
        // 构建二分图的单向边（从X部到Y部）
        for (int u : partX) 
            for (int v : graph[u]) 
                if (color[v] == 1) hk.addEdge(u, v);  // v在Y部
        
        int matching = hk.maxMatch();
        
        if (matching * 2 != n) {  // 需要完美匹配
            cout << "Impossible\n";
            continue;
        }
        
        // 选择字典序小的部分
        vector<int> result = min(partX, partY);
        cout << result.size() << '\n';
        
        // 输出结果
        if (!result.empty()) {
            sort(result.begin(), result.end());
            for (size_t i = 0; i < result.size(); i++) {
                if (i > 0) cout << ' ';
                cout << result[i];
            }
            cout << '\n';
        }
    }
    
    return 0;
}
