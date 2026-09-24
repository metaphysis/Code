#include <bits/stdc++.h>
using namespace std;

const int modVal = 19880830;
const long long infDist = 1LL << 62;

struct Edge {
    int to, weight;
};

struct Road {
    int u, v, weight;
};

void mergeValue(long long newLen, int newCnt, long long &bestLen, int &bestCnt) {
    if (newLen < bestLen) {
        bestLen = newLen;
        bestCnt = newCnt;
    } else if (newLen == bestLen) bestCnt = (bestCnt + newCnt) % modVal;
}

struct minTree {
    vector<long long> bestLen;
    vector<int> bestCnt;
    minTree(int size) {
        bestLen.assign(size * 4, infDist);
        bestCnt.assign(size * 4, 0);
    }

    void update(int node, int left, int right, int ql, int qr, long long len, int cnt) {
        if (ql <= left && right <= qr) {
            mergeValue(len, cnt, bestLen[node], bestCnt[node]);
            return;
        }
        int mid = (left + right) / 2;
        if (ql <= mid) update(node * 2, left, mid, ql, qr, len, cnt);
        if (qr > mid) update(node * 2 + 1, mid + 1, right, ql, qr, len, cnt);
    }

    void collect(int node, int left, int right, long long len, int cnt,
                 const vector<int> &path, vector<long long> &ansLen, vector<int> &ansCnt) {
        mergeValue(bestLen[node], bestCnt[node], len, cnt);
        if (left == right) {
            mergeValue(len, cnt, ansLen[path[left]], ansCnt[path[left]]);
            return;
        }
        int mid = (left + right) / 2;
        collect(node * 2, left, mid, len, cnt, path, ansLen, ansCnt);
        collect(node * 2 + 1, mid + 1, right, len, cnt, path, ansLen, ansCnt);
    }
};

void dijkstra(const vector<vector<Edge>> &graph, int start,
              vector<long long> &dist, vector<int> &ways, vector<int> &parent) {
    int n = graph.size() - 1;
    dist.assign(n + 1, infDist);
    ways.assign(n + 1, 0);
    parent.assign(n + 1, -1);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;
    dist[start] = 0;
    ways[start] = 1;
    pq.push({0, start});
    while (!pq.empty()) {
        long long curDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (curDist != dist[u]) continue;
        for (const Edge &edge : graph[u]) {
            int v = edge.to;
            long long newDist = curDist + edge.weight;
            if (newDist < dist[v]) {
                dist[v] = newDist;
                ways[v] = ways[u];
                parent[v] = u;
                pq.push({newDist, v});
            } else if (newDist == dist[v]) ways[v] = (ways[v] + ways[u]) % modVal;
        }
    }
}

void calcAnswers(const vector<vector<Edge>> &graph, const vector<Road> &roads,
                 int s, int t, vector<long long> &ansLen, vector<int> &ansCnt) {
    int n = graph.size() - 1;
    vector<long long> distS, distT;
    vector<int> waysS, waysT, parent, path;
    ansLen.assign(n + 1, 0);
    ansCnt.assign(n + 1, 0);
    dijkstra(graph, s, distS, waysS, parent);
    if (distS[t] == infDist) return;
    for (int u = t; u != -1; u = parent[u]) path.push_back(u);
    reverse(path.begin(), path.end());
    dijkstra(graph, t, distT, waysT, parent);
    int pathSize = path.size();
    long long baseDist = distS[t];
    vector<long long> height(n + 1, 0), pathHeight(pathSize);
    vector<int> pathId(n + 1, -1), groupId(n + 1, -1);
    for (int i = 0; i < pathSize; i++) {
        pathId[path[i]] = i;
        pathHeight[i] = distS[path[i]] - distT[path[i]];
    }
    for (int u = 1; u <= n; u++) {
        ansLen[u] = baseDist;
        ansCnt[u] = waysS[t];
        if (distS[u] == infDist) continue;
        height[u] = distS[u] - distT[u];
        if (distS[u] + distT[u] == baseDist) {
            int throughCnt = 1LL * waysS[u] * waysT[u] % modVal;
            ansCnt[u] = (ansCnt[u] - throughCnt + modVal) % modVal;
        }
        if (pathId[u] != -1) {
            ansLen[u] = infDist;
            ansCnt[u] = 0;
        } else {
            int pos = lower_bound(pathHeight.begin(), pathHeight.end(), height[u]) - pathHeight.begin();
            if (pos > 0 && pos < pathSize - 1 && pathHeight[pos] == height[u]) groupId[u] = pos;
        }
    }
    minTree seg(pathSize);
    vector<long long> localDist(n + 1, infDist);
    vector<int> localWays(n + 1, 0);
    for (const Road &road : roads) {
        int u = road.u, v = road.v;
        if (distS[u] == infDist) continue;
        if (height[u] > height[v]) swap(u, v);
        if (height[u] == height[v]) continue;
        int left = upper_bound(pathHeight.begin(), pathHeight.end(), height[u]) - pathHeight.begin();
        int right = lower_bound(pathHeight.begin(), pathHeight.end(), height[v]) - pathHeight.begin() - 1;
        left = max(left, 1);
        right = min(right, pathSize - 2);
        if (left <= right) {
            long long len = distS[u] + road.weight + distT[v];
            int cnt = 1LL * waysS[u] * waysT[v] % modVal;
            seg.update(1, 0, pathSize - 1, left, right, len, cnt);
        }
        if (groupId[v] != -1) {
            long long len = distS[u] + road.weight;
            mergeValue(len, waysS[u], localDist[v], localWays[v]);
        }
    }
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;
    for (int u = 1; u <= n; u++) if (localDist[u] != infDist) pq.push({localDist[u], u});
    while (!pq.empty()) {
        long long curDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (curDist != localDist[u]) continue;
        for (const Edge &edge : graph[u]) {
            int v = edge.to;
            if (groupId[v] != groupId[u]) continue;
            long long newDist = curDist + edge.weight;
            if (newDist < localDist[v]) {
                localDist[v] = newDist;
                localWays[v] = localWays[u];
                pq.push({newDist, v});
            } else if (newDist == localDist[v]) localWays[v] = (localWays[v] + localWays[u]) % modVal;
        }
    }
    for (const Road &road : roads) {
        int u = road.u, v = road.v;
        if (distS[u] == infDist) continue;
        if (height[u] > height[v]) swap(u, v);
        if (height[u] == height[v] || groupId[u] == -1 || localDist[u] == infDist) continue;
        int banVertex = path[groupId[u]];
        long long len = localDist[u] + road.weight + distT[v];
        int cnt = 1LL * localWays[u] * waysT[v] % modVal;
        mergeValue(len, cnt, ansLen[banVertex], ansCnt[banVertex]);
    }
    seg.collect(1, 0, pathSize - 1, infDist, 0, path, ansLen, ansCnt);
    for (int u = 1; u <= n; u++) {
        if (u == s || u == t || ansLen[u] == infDist) {
            ansLen[u] = 0;
            ansCnt[u] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t, q, caseId = 0;
    while (cin >> n >> m >> s >> t >> q) {
        if (n == 0 && m == 0 && s == 0 && t == 0 && q == 0) break;
        vector<vector<Edge>> graph(n + 1);
        vector<Road> roads(m);
        for (int i = 0; i < m; i++) {
            int u, v, weight;
            cin >> u >> v >> weight;
            roads[i] = {u, v, weight};
            graph[u].push_back({v, weight});
            graph[v].push_back({u, weight});
        }
        vector<long long> queries(q), ansLen;
        vector<int> ansCnt;
        for (int i = 0; i < q; i++) cin >> queries[i];
        calcAnswers(graph, roads, s, t, ansLen, ansCnt);
        cout << "Case " << ++caseId << ":";
        for (long long x : queries) {
            long long result = 0;
            x %= modVal;
            for (int i = n; i >= 1; i--) {
                result = (result * x + ansCnt[i]) % modVal;
                result = (result * x + ansLen[i]) % modVal;
            }
            cout << ' ' << result;
        }
        cout << "\n\n";
    }
    return 0;
}
