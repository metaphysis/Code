// Planet of the Rock Paper and Scissors
// UVa ID: 10822
// Verdict: Accepted
// Submission Date: 2025-11-30
// UVa Run Time: 0.130s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

vector<int> graph[MAXN];      // 有向图的邻接表
vector<int> undirectedGraph[MAXN];  // 无向图的邻接表（底图）
int race[MAXN];               // 记录每个节点的种族：0=未确定，1=石头，2=布，3=剪刀
bool visited[MAXN];           // 记录节点是否被访问
int n, m;                     // 节点数和边数

// 根据当前种族和支配关系确定下一个种族
int getNextRace(int currentRace) {
    if (currentRace == 1) return 3;  // 石头支配剪刀
    if (currentRace == 2) return 1;  // 布支配石头
    if (currentRace == 3) return 2;  // 剪刀支配布
    return 0;
}

// 构建无向底图
void buildUndirectedGraph() {
    for (int i = 1; i <= n; i++) {
        undirectedGraph[i].clear();
    }
    for (int u = 1; u <= n; u++) {
        for (int v : graph[u]) {
            undirectedGraph[u].push_back(v);
            undirectedGraph[v].push_back(u);
        }
    }
}

// DFS遍历无向图找到连通分量
void dfsUndirected(int u, vector<int>& component) {
    visited[u] = true;
    component.push_back(u);
    for (int v : undirectedGraph[u]) {
        if (!visited[v]) {
            dfsUndirected(v, component);
        }
    }
}

// 在连通分量内进行BFS种族分配，返回是否发现冲突
bool bfsInComponent(const vector<int>& component) {
    if (component.empty()) return false;
    
    queue<int> q;
    int start = component[0];
    q.push(start);
    
    // 任意分配起始节点为石头
    race[start] = 1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : graph[u]) {
            int expectedRace = getNextRace(race[u]);
            
            if (race[v] == 0) {
                // 如果邻居未分配，根据支配关系分配
                race[v] = expectedRace;
                q.push(v);
            } else if (race[v] != expectedRace) {
                // 如果邻居已分配但与预期不符，发现冲突
                return true;
            }
        }
        
        // 处理指向当前节点的边（反向传播）
        for (int w : component) {
            for (int v : graph[w]) {
                if (v == u) {  // 如果w指向u
                    // 根据u的种族推断w应该是什么（反向推理）
                    int expectedRaceForW;
                    if (race[u] == 1) expectedRaceForW = 2;  // 石头被布支配
                    else if (race[u] == 2) expectedRaceForW = 3;  // 布被剪刀支配
                    else if (race[u] == 3) expectedRaceForW = 1;  // 剪刀被石头支配
                    else expectedRaceForW = 0;
                    
                    if (expectedRaceForW != 0) {
                        if (race[w] == 0) {
                            race[w] = expectedRaceForW;
                            q.push(w);
                        } else if (race[w] != expectedRaceForW) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    int communities;
    cin >> communities;
    
    for (int comm = 1; comm <= communities; comm++) {
        cin >> n >> m;
        
        // 初始化
        for (int i = 1; i <= n; i++) {
            graph[i].clear();
            race[i] = 0;
            visited[i] = false;
        }
        
        // 读取边信息
        string line;
        getline(cin, line);  // 读取换行符
        
        int edgesRead = 0;
        while (edgesRead < m) {
            getline(cin, line);
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '(') {
                    int u = 0, v = 0;
                    i++;  // 跳过 '('
                    
                    // 读取第一个数字
                    while (isdigit(line[i])) {
                        u = u * 10 + (line[i] - '0');
                        i++;
                    }
                    
                    i++;  // 跳过 '>'
                    
                    // 读取第二个数字  
                    while (isdigit(line[i])) {
                        v = v * 10 + (line[i] - '0');
                        i++;
                    }
                    
                    graph[u].push_back(v);
                    edgesRead++;
                }
            }
        }
        
        // 构建无向底图并找到所有连通分量
        buildUndirectedGraph();
        for (int i = 1; i <= n; i++) visited[i] = false;
        
        vector<vector<int>> components;
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                vector<int> component;
                dfsUndirected(i, component);
                components.push_back(component);
            }
        }
        
        // 重置种族状态
        for (int i = 1; i <= n; i++) race[i] = 0;
        
        bool hasConflict = false;
        
        // 对每个连通分量进行检查，优先检测冲突
        for (const auto& component : components) {
            if (hasConflict) break;
            if (bfsInComponent(component)) {
                hasConflict = true;
            }
        }
        
        // 输出结果（冲突检测优先级最高）
        cout << "Community " << comm << ": ";
        if (hasConflict) 
            cout << "Conflicting Records" << endl;
        else if (components.size() == 1) 
            cout << "Observation Complete" << endl;
        else 
            cout << "Not Enough Data" << endl;
    }
    
    return 0;
}
