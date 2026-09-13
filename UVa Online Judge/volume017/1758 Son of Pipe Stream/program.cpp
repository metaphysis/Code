#include <bits/stdc++.h>
using namespace std;

const int maxN = 205;
const int maxP = 20005;
const double eps = 1e-10;
const double inf = 1e100;

struct Edge {
    int to, rev;
    double cap, initCap;
};

struct Dinic {
    vector<Edge> graph[maxN + 2];
    int level[maxN + 2], iter[maxN + 2];

    int addEdge(int from, int to, double cap) {
        int index = graph[from].size();
        Edge edge1 = {to, (int)graph[to].size(), cap, cap};
        Edge edge2 = {from, index, 0.0, 0.0};
        graph[from].push_back(edge1);
        graph[to].push_back(edge2);
        return index;
    }

    void addUndirectedEdge(int from, int to, double cap) {
        addEdge(from, to, cap);
        addEdge(to, from, cap);
    }

    bool bfs(int source, int sink, int nodeCount) {
        int i;
        for (i = 0; i < nodeCount; i++)
            level[i] = -1;
        queue<int> que;
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (const Edge &edge : graph[u])
                if (edge.cap > eps && level[edge.to] < 0) {
                    level[edge.to] = level[u] + 1;
                    que.push(edge.to);
                }
        }
        return level[sink] >= 0;
    }

    double dfs(int u, int sink, double flow) {
        if (u == sink)
            return flow;
        for (int &i = iter[u]; i < (int)graph[u].size(); i++) {
            Edge &edge = graph[u][i];
            if (edge.cap > eps && level[edge.to] == level[u] + 1) {
                double result = dfs(edge.to, sink, min(flow, edge.cap));
                if (result > eps) {
                    edge.cap -= result;
                    graph[edge.to][edge.rev].cap += result;
                    return result;
                }
            }
        }
        return 0.0;
    }

    double maxFlow(int source, int sink, int nodeCount) {
        double result = 0.0;
        while (bfs(source, sink, nodeCount)) {
            int i;
            for (i = 0; i < nodeCount; i++)
                iter[i] = 0;
            while (true) {
                double flow = dfs(source, sink, inf);
                if (flow <= eps)
                    break;
                result += flow;
            }
        }
        return result;
    }

    double getFlow(int from, int index) {
        return graph[from][index].initCap - graph[from][index].cap;
    }
};

struct Pipe {
    int u, w, uvIndex, vuIndex;
    double cap;
};

struct AdjEdge {
    int to, id, dir;
};

int n, p, superSource, sinkNode;
double viscosity, alpha;
Pipe pipes[maxP];
vector<AdjEdge> adj[maxN];
double remainFlow[maxP], flubberFlow[maxP], waterFlow[maxP];

double getMaxFlow(int type) {
    Dinic dinic;
    int source = 0, nodeCount = n + 1;
    int i;
    for (i = 0; i < p; i++) {
        dinic.addUndirectedEdge(pipes[i].u, pipes[i].w, pipes[i].cap);
    }
    if (type == 1)
        dinic.addEdge(source, 1, inf);
    else if (type == 2)
        dinic.addEdge(source, 2, inf);
    else {
        dinic.addEdge(source, 1, inf);
        dinic.addEdge(source, 2, inf);
    }
    return dinic.maxFlow(source, 3, nodeCount);
}

bool findPath(int start, vector<int> &preNode, vector<int> &preEdge, vector<int> &preDir) {
    int i;
    for (i = 0; i <= n; i++)
        preNode[i] = -1;
    queue<int> que;
    que.push(start);
    preNode[start] = start;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (u == 3)
            return true;
        for (const AdjEdge &edge : adj[u]) {
            if (remainFlow[edge.id] <= eps)
                continue;
            if (preNode[edge.to] != -1)
                continue;
            preNode[edge.to] = u;
            preEdge[edge.to] = edge.id;
            preDir[edge.to] = edge.dir;
            que.push(edge.to);
        }
    }
    return false;
}

void buildFlow(double x, double y) {
    Dinic dinic;
    int source = 0, nodeCount = n + 1;
    int i;
    for (i = 0; i <= n; i++)
        adj[i].clear();
    vector<int> uvIndex(p), vuIndex(p);
    for (i = 0; i < p; i++) {
        uvIndex[i] = dinic.addEdge(pipes[i].u, pipes[i].w, pipes[i].cap);
        vuIndex[i] = dinic.addEdge(pipes[i].w, pipes[i].u, pipes[i].cap);
        adj[pipes[i].u].push_back({pipes[i].w, i, 1});
        adj[pipes[i].w].push_back({pipes[i].u, i, -1});
    }
    dinic.addEdge(source, 1, x);
    dinic.addEdge(source, 2, y);
    dinic.maxFlow(source, 3, nodeCount);
    for (i = 0; i < p; i++) {
        double flow1 = dinic.getFlow(pipes[i].u, uvIndex[i]);
        double flow2 = dinic.getFlow(pipes[i].w, vuIndex[i]);
        if (flow1 >= flow2) {
            remainFlow[i] = flow1 - flow2;
            pipes[i].u = pipes[i].u;
        } else {
            remainFlow[i] = flow2 - flow1;
            pipes[i].u = pipes[i].u;
        }
    }
}

void splitFlow(int start, double need, bool isFlubber) {
    vector<int> preNode(n + 1), preEdge(n + 1), preDir(n + 1);
    while (need > eps) {
        bool found = findPath(start, preNode, preEdge, preDir);
        if (!found)
            break;
        double pathFlow = need;
        int current = 3;
        while (current != start) {
            int id = preEdge[current];
            pathFlow = min(pathFlow, remainFlow[id]);
            current = preNode[current];
        }
        current = 3;
        while (current != start) {
            int id = preEdge[current];
            if (isFlubber)
                flubberFlow[id] += preDir[current] * pathFlow / viscosity;
            else
                waterFlow[id] += preDir[current] * pathFlow;
            remainFlow[id] -= pathFlow;
            current = preNode[current];
        }
        need -= pathFlow;
    }
}

void solveCase() {
    int i;
    double c1 = getMaxFlow(1), c2 = getMaxFlow(2), c12 = getMaxFlow(3);
    double x, y;
    if (c1 + c2 <= c12 + eps) {
        x = c1;
        y = c2;
    } else {
        x = min(c1, alpha * c12);
        x = max(x, c12 - c2);
        y = c12 - x;
    }
    buildFlow(x, y);
    for (i = 0; i < p; i++) {
        flubberFlow[i] = 0.0;
        waterFlow[i] = 0.0;
    }
    splitFlow(1, x, true);
    splitFlow(2, y, false);
    for (i = 0; i < p; i++)
        cout << fixed << setprecision(9) << flubberFlow[i] << " " << waterFlow[i] << "\n";
    double finalFlubber = x / viscosity;
    double finalWater = y;
    double answer = pow(finalFlubber, alpha) * pow(finalWater, 1.0 - alpha);
    cout << fixed << setprecision(11) << answer << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> p >> viscosity >> alpha) {
        int i;
        for (i = 0; i < p; i++) {
            cin >> pipes[i].u >> pipes[i].w >> pipes[i].cap;
        }
        solveCase();
    }
    return 0;
}
