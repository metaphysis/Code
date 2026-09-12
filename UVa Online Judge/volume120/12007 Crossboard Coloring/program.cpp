#include <bits/stdc++.h>
using namespace std;

const int maxN = 55;
const int maxV = 2 * maxN + 5;

int n, r, c, k;
int board[maxN][maxN];
bool graph[maxN][maxN];
int matchRight[maxN], visitTag[maxN], tagId;

struct Edge {
    int to, rev, cap;
};

struct Dinic {
    vector<Edge> edgeList[maxV];
    int level[maxV], current[maxV];

    void clear(int nodeCount) {
        for (int i = 0; i < nodeCount; i++)
            edgeList[i].clear();
    }

    int addEdge(int from, int to, int cap) {
        int index = (int)edgeList[from].size();
        Edge forward = {to, (int)edgeList[to].size(), cap};
        Edge backward = {from, index, 0};
        edgeList[from].push_back(forward);
        edgeList[to].push_back(backward);
        return index;
    }

    bool bfs(int source, int target, int nodeCount) {
        fill(level, level + nodeCount, -1);
        queue<int> que;
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (const Edge &edge : edgeList[u]) {
                if (edge.cap > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[u] + 1;
                    que.push(edge.to);
                }
            }
        }
        return level[target] != -1;
    }

    int dfs(int u, int target, int flow) {
        if (u == target)
            return flow;
        for (int &i = current[u]; i < (int)edgeList[u].size(); i++) {
            Edge &edge = edgeList[u][i];
            if (edge.cap > 0 && level[edge.to] == level[u] + 1) {
                int nextFlow = dfs(edge.to, target, min(flow, edge.cap));
                if (nextFlow > 0) {
                    edge.cap -= nextFlow;
                    edgeList[edge.to][edge.rev].cap += nextFlow;
                    return nextFlow;
                }
            }
        }
        return 0;
    }

    int maxFlow(int source, int target, int nodeCount) {
        int result = 0;
        while (bfs(source, target, nodeCount)) {
            fill(current, current + nodeCount, 0);
            while (true) {
                int flow = dfs(source, target, INT_MAX);
                if (flow == 0)
                    break;
                result += flow;
            }
        }
        return result;
    }
};

Dinic dinic;

bool findMatch(int u, int rightCount) {
    for (int v = 0; v < rightCount; v++) {
        if (graph[u][v] && visitTag[v] != tagId) {
            visitTag[v] = tagId;
            if (matchRight[v] == -1 || findMatch(matchRight[v], rightCount)) {
                matchRight[v] = u;
                return true;
            }
        }
    }
    return false;
}

bool getPerfectMatching(int leftCount, int rightCount, int result[]) {
    fill(matchRight, matchRight + rightCount, -1);
    for (int u = 0; u < leftCount; u++) {
        tagId++;
        if (!findMatch(u, rightCount))
            return false;
    }
    for (int v = 0; v < rightCount; v++)
        result[matchRight[v]] = v;
    return true;
}

bool completeFirstRows() {
    int colorCount[maxN] = {};
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            colorCount[board[i][j]]++;
    for (int color = 0; color < n; color++)
        if (r - colorCount[color] > k)
            return false;
    for (int i = 0; i < n; i++)
        for (int color = 0; color < n; color++)
            graph[i][color] = false;
    for (int i = 0; i < r; i++) {
        bool used[maxN] = {};
        for (int j = 0; j < c; j++)
            used[board[i][j]] = true;
        for (int color = 0; color < n; color++)
            if (!used[color])
                graph[i][color] = true;
    }
    int dummyCount = n - r;
    if (dummyCount > 0) {
        int source = 0, dummyBegin = 1, colorBegin = dummyBegin + dummyCount, target = colorBegin + n;
        int nodeCount = target + 1;
        int edgeIndex[maxN][maxN];
        dinic.clear(nodeCount);
        for (int i = 0; i < dummyCount; i++)
            dinic.addEdge(source, dummyBegin + i, k);
        for (int i = 0; i < dummyCount; i++)
            for (int color = 0; color < n; color++)
                edgeIndex[i][color] = dinic.addEdge(dummyBegin + i, colorBegin + color, 1);
        for (int color = 0; color < n; color++) {
            int degree = r - colorCount[color];
            dinic.addEdge(colorBegin + color, target, k - degree);
        }
        int need = dummyCount * k;
        if (dinic.maxFlow(source, target, nodeCount) != need)
            return false;
        for (int i = 0; i < dummyCount; i++)
            for (int color = 0; color < n; color++)
                if (dinic.edgeList[dummyBegin + i][edgeIndex[i][color]].cap == 0)
                    graph[r + i][color] = true;
    }
    int match[maxN];
    for (int step = 0; step < k; step++) {
        if (!getPerfectMatching(n, n, match))
            return false;
        for (int i = 0; i < r; i++) {
            board[i][c + step] = match[i];
            graph[i][match[i]] = false;
        }
        for (int i = r; i < n; i++)
            graph[i][match[i]] = false;
    }
    return true;
}

bool completeRemainingRows() {
    for (int row = r; row < n; row++) {
        for (int col = 0; col < n; col++)
            for (int color = 0; color < n; color++)
                graph[col][color] = true;
        for (int col = 0; col < n; col++)
            for (int oldRow = 0; oldRow < row; oldRow++)
                graph[col][board[oldRow][col]] = false;
        int match[maxN];
        if (!getPerfectMatching(n, n, match))
            return false;
        for (int col = 0; col < n; col++)
            board[row][col] = match[col];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        cin >> n >> r >> c;
        k = n - c;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                cin >> board[i][j];
        tagId = 0;
        bool possible = completeFirstRows();
        if (possible)
            possible = completeRemainingRows();
        if (!possible) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j > 0)
                    cout << ' ';
                cout << board[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
