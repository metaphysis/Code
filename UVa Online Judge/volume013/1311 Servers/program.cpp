#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, weight;
};

long long solveCase() {
    int n, m;
    cin >> n >> m;
    vector<int> serverRank(n);
    for (int i = 0; i < n; i++) cin >> serverRank[i];
    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; i++) {
        int a, b, time;
        cin >> a >> b >> time;
        a--;
        b--;
        graph[a].push_back({b, time});
        graph[b].push_back({a, time});
    }
    const long long inf = 1LL << 60;
    using State = pair<long long, int>;
    vector<vector<long long>> higherDist(11, vector<long long>(n, inf));
    vector<long long> curDist(n, inf);
    priority_queue<State, vector<State>, greater<State>> heap;
    for (int k = 9; k >= 1; k--) {
        for (int i = 0; i < n; i++) {
            if (serverRank[i] == k + 1) {
                curDist[i] = 0;
                heap.push({0, i});
            }
        }
        while (!heap.empty()) {
            long long dist;
            int u;
            tie(dist, u) = heap.top();
            heap.pop();
            if (dist != curDist[u]) continue;
            for (const Edge &edge : graph[u]) {
                int v = edge.to;
                long long nextDist = dist + edge.weight;
                if (nextDist >= curDist[v]) continue;
                curDist[v] = nextDist;
                heap.push({nextDist, v});
            }
        }
        higherDist[k] = curDist;
    }
    vector<long long> localDist(n);
    vector<int> distStamp(n, 0);
    long long answer = 0;
    int runId = 0;
    for (int source = 0; source < n; source++) {
        int rank = serverRank[source];
        runId++;
        priority_queue<State, vector<State>, greater<State>> localHeap;
        localDist[source] = 0;
        distStamp[source] = runId;
        localHeap.push({0, source});
        while (!localHeap.empty()) {
            long long dist;
            int u;
            tie(dist, u) = localHeap.top();
            localHeap.pop();
            if (distStamp[u] != runId || dist != localDist[u]) continue;
            answer++;
            for (const Edge &edge : graph[u]) {
                int v = edge.to;
                long long nextDist = dist + edge.weight;
                if (nextDist >= higherDist[rank][v]) continue;
                if (distStamp[v] != runId && nextDist < higherDist[rank][v]) {
                    distStamp[v] = runId;
                    localDist[v] = nextDist;
                    localHeap.push({nextDist, v});
                } else if (distStamp[v] == runId && nextDist < localDist[v]) {
                    localDist[v] = nextDist;
                    localHeap.push({nextDist, v});
                }
            }
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int cs = 0; cs < T; cs++) {
        if (cs) cout << '\n';
        cout << solveCase() << '\n';
    }
    return 0;
}
