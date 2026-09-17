#include <bits/stdc++.h>
using namespace std;

const int maxV = 905;
const long long inf = (1LL << 60);

struct Edge {
    int to, rev;
    long long cap;
};

struct Dinic {
    int n;
    vector<vector<Edge>> graph;
    vector<int> level, cur;
    Dinic(int nodeCnt) : n(nodeCnt), graph(nodeCnt), level(nodeCnt), cur(nodeCnt) {}

    void addEdge(int from, int to, long long cap) {
        Edge forward = {to, (int)graph[to].size(), cap};
        Edge backward = {from, (int)graph[from].size(), 0};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
    }

    bool buildLevel(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            int node = que.front();
            que.pop();
            for (const Edge &edge : graph[node]) {
                if (edge.cap > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[node] + 1;
                    que.push(edge.to);
                }
            }
        }
        return level[sink] != -1;
    }

    long long sendFlow(int node, int sink, long long flow) {
        if (node == sink) return flow;
        for (int &index = cur[node]; index < (int)graph[node].size(); index++) {
            Edge &edge = graph[node][index];
            if (edge.cap > 0 && level[edge.to] == level[node] + 1) {
                long long sent = sendFlow(edge.to, sink, min(flow, edge.cap));
                if (sent > 0) {
                    edge.cap -= sent;
                    graph[edge.to][edge.rev].cap += sent;
                    return sent;
                }
            }
        }
        return 0;
    }

    long long maxFlow(int source, int sink) {
        long long result = 0, sent;
        while (buildLevel(source, sink)) {
            fill(cur.begin(), cur.end(), 0);
            while ((sent = sendFlow(source, sink, inf)) > 0) result += sent;
        }
        return result;
    }
};

vector<int> resGraph[maxV], revGraph[maxV];
vector<int> finishOrder;
bool visited[maxV];
int component[maxV];
bitset<maxV> reachBits[maxV], suffixIn[maxV], suffixOut[maxV];

void dfsOrder(int node) {
    visited[node] = true;
    for (int next : resGraph[node])
        if (!visited[next]) dfsOrder(next);
    finishOrder.push_back(node);
}

void dfsComponent(int node, int componentId) {
    component[node] = componentId;
    for (int next : revGraph[node])
        if (component[next] == -1) dfsComponent(next, componentId);
}

void solveCase(int caseNum) {
    int rowCnt, colCnt;
    cin >> rowCnt >> colCnt;
    int cellCnt = rowCnt * colCnt;
    vector<vector<long long>> value(rowCnt, vector<long long>(colCnt));
    vector<vector<bool>> green(rowCnt, vector<bool>(colCnt, false)), red(rowCnt, vector<bool>(colCnt, false));
    for (int row = 0; row < rowCnt; row++)
        for (int col = 0; col < colCnt; col++) cin >> value[row][col];
    int greenCnt;
    cin >> greenCnt;
    for (int index = 0; index < greenCnt; index++) {
        int row, col;
        cin >> row >> col;
        green[row][col] = true;
    }
    int redCnt;
    cin >> redCnt;
    for (int index = 0; index < redCnt; index++) {
        int row, col;
        cin >> row >> col;
        red[row][col] = true;
    }
    if (greenCnt == 0) {
        long long maxValue = -inf;
        int bestId = -1;
        for (int row = 0; row < rowCnt; row++) {
            for (int col = 0; col < colCnt; col++) {
                if (!red[row][col] && value[row][col] > maxValue) {
                    maxValue = value[row][col];
                    bestId = row * colCnt + col;
                }
            }
        }
        if (maxValue <= 0) {
            cout << "Case " << caseNum << ": " << maxValue << '\n';
            cout << bestId / colCnt << ' ' << bestId % colCnt << '\n';
            return;
        }
    }
    int moveRow[8] = {-3, -3, -1, -1, 1, 1, 3, 3};
    int moveCol[8] = {-1, 1, -3, 3, -3, 3, -1, 1};
    vector<vector<bool>> blocked(rowCnt, vector<bool>(colCnt, false));
    for (int row = 0; row < rowCnt; row++) {
        for (int col = 0; col < colCnt; col++) {
            if (!green[row][col]) continue;
            for (int move = 0; move < 8; move++) {
                int nextRow = row + moveRow[move], nextCol = col + moveCol[move];
                if (nextRow >= 0 && nextRow < rowCnt && nextCol >= 0 && nextCol < colCnt && !green[nextRow][nextCol]) blocked[nextRow][nextCol] = true;
            }
        }
    }
    vector<bool> optional(cellCnt, false), selected(cellCnt, false);
    for (int row = 0; row < rowCnt; row++) {
        for (int col = 0; col < colCnt; col++) {
            int id = row * colCnt + col;
            if (!red[row][col] && !green[row][col] && !blocked[row][col] && value[row][col] >= 0) optional[id] = true;
            if (green[row][col]) selected[id] = true;
        }
    }
    int source = cellCnt, sink = cellCnt + 1, nodeCnt = cellCnt + 2;
    Dinic dinic(nodeCnt);
    for (int row = 0; row < rowCnt; row++) {
        for (int col = 0; col < colCnt; col++) {
            int id = row * colCnt + col;
            if (!optional[id]) continue;
            if (row % 2 == 0) dinic.addEdge(source, id, value[row][col]);
            else dinic.addEdge(id, sink, value[row][col]);
        }
    }
    for (int row = 0; row < rowCnt; row++) {
        if (row % 2 != 0) continue;
        for (int col = 0; col < colCnt; col++) {
            int id = row * colCnt + col;
            if (!optional[id]) continue;
            for (int move = 0; move < 8; move++) {
                int nextRow = row + moveRow[move], nextCol = col + moveCol[move];
                if (nextRow < 0 || nextRow >= rowCnt || nextCol < 0 || nextCol >= colCnt) continue;
                int nextId = nextRow * colCnt + nextCol;
                if (optional[nextId]) dinic.addEdge(id, nextId, inf);
            }
        }
    }
    dinic.maxFlow(source, sink);
    for (int node = 0; node < nodeCnt; node++) {
        resGraph[node].clear();
        revGraph[node].clear();
        reachBits[node].reset();
    }
    for (int node = 0; node < nodeCnt; node++) {
        for (const Edge &edge : dinic.graph[node]) {
            if (edge.cap > 0) {
                resGraph[node].push_back(edge.to);
                revGraph[edge.to].push_back(node);
            }
        }
    }
    fill(visited, visited + nodeCnt, false);
    fill(component, component + nodeCnt, -1);
    finishOrder.clear();
    for (int node = 0; node < nodeCnt; node++)
        if (!visited[node]) dfsOrder(node);
    int componentCnt = 0;
    reverse(finishOrder.begin(), finishOrder.end());
    for (int node : finishOrder) {
        if (component[node] == -1) {
            dfsComponent(node, componentCnt);
            componentCnt++;
        }
    }
    vector<vector<int>> dag(componentCnt);
    vector<int> inDegree(componentCnt, 0), topOrder;
    for (int node = 0; node < nodeCnt; node++) {
        reachBits[component[node]].set(node);
        for (int next : resGraph[node]) {
            int fromComponent = component[node], toComponent = component[next];
            if (fromComponent != toComponent) dag[fromComponent].push_back(toComponent);
        }
    }
    for (int node = 0; node < componentCnt; node++) {
        sort(dag[node].begin(), dag[node].end());
        dag[node].erase(unique(dag[node].begin(), dag[node].end()), dag[node].end());
        for (int next : dag[node]) inDegree[next]++;
    }
    queue<int> que;
    for (int node = 0; node < componentCnt; node++)
        if (inDegree[node] == 0) que.push(node);
    while (!que.empty()) {
        int node = que.front();
        que.pop();
        topOrder.push_back(node);
        for (int next : dag[node]) {
            inDegree[next]--;
            if (inDegree[next] == 0) que.push(next);
        }
    }
    for (int index = componentCnt - 1; index >= 0; index--) {
        int node = topOrder[index];
        for (int next : dag[node]) reachBits[node] |= reachBits[next];
    }
    suffixIn[cellCnt].reset();
    suffixOut[cellCnt].reset();
    vector<int> greenSuffix(cellCnt + 1, 0);
    for (int id = cellCnt - 1; id >= 0; id--) {
        suffixIn[id] = suffixIn[id + 1];
        suffixOut[id] = suffixOut[id + 1];
        greenSuffix[id] = greenSuffix[id + 1] + (green[id / colCnt][id % colCnt] ? 1 : 0);
        if (!optional[id]) continue;
        if ((id / colCnt) % 2 == 0) suffixOut[id].set(id);
        else suffixIn[id] |= reachBits[component[id]];
    }
    bitset<maxV> inClosure = reachBits[component[source]], outSet;
    outSet.reset();
    outSet.set(sink);
    bool selectedAny = false, stopped = false;
    for (int id = 0; id < cellCnt; id++) {
        int row = id / colCnt;
        if (green[row][id % colCnt]) {
            selectedAny = true;
            continue;
        }
        if (!optional[id]) continue;
        if (selectedAny && greenSuffix[id] == 0) {
            bitset<maxV> allIn = inClosure | suffixIn[id];
            bitset<maxV> allOut = outSet | suffixOut[id];
            if ((allIn & allOut).none()) {
                stopped = true;
                break;
            }
        }
        bool canSelect;
        if (row % 2 == 0) canSelect = (reachBits[component[id]] & outSet).none();
        else canSelect = !inClosure.test(id);
        if (canSelect) {
            selected[id] = true;
            selectedAny = true;
            if (row % 2 == 0) inClosure |= reachBits[component[id]];
            else outSet.set(id);
        } else {
            if (row % 2 == 0) outSet.set(id);
            else inClosure |= reachBits[component[id]];
        }
    }
    if (stopped) {
        for (int id = 0; id < cellCnt; id++)
            if (optional[id] && !selected[id]) selected[id] = false;
    }
    long long answer = 0;
    for (int id = 0; id < cellCnt; id++)
        if (selected[id]) answer += value[id / colCnt][id % colCnt];
    cout << "Case " << caseNum << ": " << answer << '\n';
    for (int id = 0; id < cellCnt; id++)
        if (selected[id]) cout << id / colCnt << ' ' << id % colCnt << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    for (int caseNum = 1; caseNum <= testCnt; caseNum++) solveCase(caseNum);
    return 0;
}
