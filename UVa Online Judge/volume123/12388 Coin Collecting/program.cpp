#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, roundId;
};

int setParent[605], nodeParent[605], selectedRound[305];
bool selectedEdge[605], visited[605], exchangeEdge[605][605];
vector<pair<int, int> > forest[605];

int findRoot(int x) {
    return setParent[x] == x ? x : setParent[x] = findRoot(setParent[x]);
}

void mergeSet(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);
    if (x != y)
        setParent[x] = y;
}

bool findAugment(int edgeCount, int vertexCount, int roundCount, const vector<Edge>& edges) {
    int i, j;
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
    memset(exchangeEdge, 0, sizeof(exchangeEdge));
    for (i = 0; i < edgeCount; ++i) {
        if (selectedEdge[i])
            continue;
        if (findRoot(edges[i].u) != findRoot(edges[i].v)) {
            for (j = 0; j < edgeCount; ++j)
                if (selectedEdge[j])
                    exchangeEdge[i][j] = true;
            continue;
        }
        int pathParent[605], pathEdge[605], queueVertex[605];
        fill(pathParent, pathParent + vertexCount, -1);
        int head = 0, tail = 0;
        queueVertex[tail++] = edges[i].u;
        pathParent[edges[i].u] = edges[i].u;
        while (head < tail) {
            int x = queueVertex[head++];
            if (x == edges[i].v)
                break;
            for (j = 0; j < static_cast<int>(forest[x].size()); ++j) {
                int y = forest[x][j].first, id = forest[x][j].second;
                if (pathParent[y] != -1)
                    continue;
                pathParent[y] = x;
                pathEdge[y] = id;
                queueVertex[tail++] = y;
            }
        }
        int x = edges[i].v;
        while (x != edges[i].u) {
            exchangeEdge[i][pathEdge[x]] = true;
            x = pathParent[x];
        }
    }
    fill(selectedRound, selectedRound + roundCount, -1);
    for (i = 0; i < edgeCount; ++i)
        if (selectedEdge[i])
            selectedRound[edges[i].roundId] = i;
    fill(visited, visited + edgeCount, false);
    fill(nodeParent, nodeParent + edgeCount, -1);
    int finish = -1;
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
                if (!exchangeEdge[i][x])
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
        for (i = 0; i < static_cast<int>(edges.size()); ++i) {
            edges[i].u = lower_bound(values.begin(), values.end(), edges[i].u) - values.begin();
            edges[i].v = lower_bound(values.begin(), values.end(), edges[i].v) - values.begin();
        }
        int edgeCount = static_cast<int>(edges.size());
        int vertexCount = static_cast<int>(values.size());
        fill(selectedEdge, selectedEdge + edgeCount, false);
        while (findAugment(edgeCount, vertexCount, roundCount, edges))
            ;
        int answer = 0;
        for (i = 0; i < edgeCount; ++i)
            if (selectedEdge[i])
                answer += 2;
        cout << answer << '\n';
    }
    return 0;
}
