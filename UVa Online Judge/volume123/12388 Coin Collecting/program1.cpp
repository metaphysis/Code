#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, roundId;
};

vector<int> setParent;
vector<vector<pair<int, int>>> forest;

int findRoot(int x) {
    return setParent[x] == x ? x : setParent[x] = findRoot(setParent[x]);
}

void mergeSet(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);
    if (x != y)
        setParent[x] = y;
}

bool findAugment(const vector<Edge>& edges, int vertexCount, int roundCount, vector<char>& selectedEdge) {
    int edgeCount = edges.size();
    int i, j;
    setParent.resize(vertexCount);
    forest.resize(vertexCount);
    for (i = 0; i < vertexCount; ++i) {
        setParent[i] = i;
        forest[i].clear();
    }
    for (i = 0; i < edgeCount; ++i)
        if (selectedEdge[i]) {
            mergeSet(edges[i].u, edges[i].v);
            forest[edges[i].u].push_back(make_pair(edges[i].v, i));
            forest[edges[i].v].push_back(make_pair(edges[i].u, i));
        }
    vector<int> treeParent(vertexCount, -1), parentEdge(vertexCount, -1), depth(vertexCount, 0);
    for (i = 0; i < vertexCount; ++i)
        if (treeParent[i] == -1) {
            treeParent[i] = i;
            vector<int> stackVertex;
            stackVertex.push_back(i);
            while (!stackVertex.empty()) {
                int x = stackVertex.back();
                stackVertex.pop_back();
                for (j = 0; j < forest[x].size(); ++j) {
                    int y = forest[x][j].first, id = forest[x][j].second;
                    if (treeParent[y] != -1)
                        continue;
                    treeParent[y] = x;
                    parentEdge[y] = id;
                    depth[y] = depth[x] + 1;
                    stackVertex.push_back(y);
                }
            }
        }
    vector<bitset<605> > exchangeEdge(edgeCount);
    for (i = 0; i < edgeCount; ++i) {
        if (selectedEdge[i])
            continue;
        int u = edges[i].u, v = edges[i].v;
        if (findRoot(u) != findRoot(v)) {
            for (j = 0; j < edgeCount; ++j)
                if (selectedEdge[j])
                    exchangeEdge[i].set(j);
            continue;
        }
        while (depth[u] > depth[v]) {
            exchangeEdge[i].set(parentEdge[u]);
            u = treeParent[u];
        }
        while (depth[v] > depth[u]) {
            exchangeEdge[i].set(parentEdge[v]);
            v = treeParent[v];
        }
        while (u != v) {
            exchangeEdge[i].set(parentEdge[u]);
            exchangeEdge[i].set(parentEdge[v]);
            u = treeParent[u];
            v = treeParent[v];
        }
    }
    vector<int> selectedRound(roundCount, -1);
    for (i = 0; i < edgeCount; ++i)
        if (selectedEdge[i])
            selectedRound[edges[i].roundId] = i;
    vector<char> visited(edgeCount, false);
    vector<int> nodeParent(edgeCount, -1);
    queue<int> que;
    for (i = 0; i < edgeCount; ++i) {
        if (selectedEdge[i])
            continue;
        if (findRoot(edges[i].u) == findRoot(edges[i].v))
            continue;
        visited[i] = true;
        nodeParent[i] = -2;
        que.push(i);
    }
    int finish = -1;
    while (!que.empty() && finish == -1) {
        int x = que.front();
        que.pop();
        if (!selectedEdge[x]) {
            int mate = selectedRound[edges[x].roundId];
            if (mate == -1) {
                finish = x;
                break;
            }
            if (!visited[mate]) {
                visited[mate] = true;
                nodeParent[mate] = x;
                que.push(mate);
            }
        } else {
            for (i = 0; i < edgeCount; ++i) {
                if (selectedEdge[i] || visited[i])
                    continue;
                if (!exchangeEdge[i].test(x))
                    continue;
                visited[i] = true;
                nodeParent[i] = x;
                que.push(i);
            }
        }
    }
    if (finish == -1)
        return false;
    int x = finish;
    while (x != -2) {
        selectedEdge[x] = !selectedEdge[x];
        x = nodeParent[x];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int roundCount;
    while (cin >> roundCount && roundCount) {
        vector<Edge> edges;
        vector<int> values;
        int i;
        edges.reserve(2 * roundCount);
        values.reserve(4 * roundCount);
        for (i = 0; i < roundCount; ++i) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            edges.push_back({a, b, i});
            edges.push_back({c, d, i});
            values.push_back(a);
            values.push_back(b);
            values.push_back(c);
            values.push_back(d);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        for (i = 0; i < edges.size(); ++i) {
            edges[i].u = lower_bound(values.begin(), values.end(), edges[i].u) - values.begin();
            edges[i].v = lower_bound(values.begin(), values.end(), edges[i].v) - values.begin();
        }
        vector<char> selectedEdge(edges.size(), false);
        while (findAugment(edges, values.size(), roundCount, selectedEdge))
            ;
        int answer = 0;
        for (i = 0; i < selectedEdge.size(); ++i)
            if (selectedEdge[i])
                answer += 2;
        cout << answer << '\n';
    }
    return 0;
}
