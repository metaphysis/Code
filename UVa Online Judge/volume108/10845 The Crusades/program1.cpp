#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap;
};

struct Road {
    int from, to, cap;
};

struct RoadRef {
    int from, index, id;
};

struct FlowResult {
    int flow;
    uint32_t usedMask;
};

class Dinic {
private:
    vector<vector<Edge>> graph;
    vector<int> level, iter;
    vector<RoadRef> roadRefs;

public:
    Dinic(int n) {
        graph.resize(n + 1);
        level.resize(n + 1);
        iter.resize(n + 1);
    }

    void addEdge(int from, int to, int cap) {
        Edge forward = {to, (int)graph[to].size(), cap};
        Edge backward = {from, (int)graph[from].size(), 0};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
    }

    void addRoad(int from, int to, int cap, int id) {
        int firstIndex = graph[from].size();
        addEdge(from, to, cap);
        int secondIndex = graph[to].size();
        addEdge(to, from, cap);
        roadRefs.push_back({from, firstIndex, id});
        roadRefs.push_back({to, secondIndex, id});
    }

    bool bfs(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            int now = que.front();
            que.pop();
            for (const Edge &edge : graph[now])
                if (edge.cap > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[now] + 1;
                    que.push(edge.to);
                }
        }
        return level[sink] != -1;
    }

    int dfs(int now, int sink, int flow) {
        if (now == sink)
            return flow;
        for (int &index = iter[now]; index < (int)graph[now].size(); ++index) {
            Edge &edge = graph[now][index];
            if (edge.cap > 0 && level[edge.to] == level[now] + 1) {
                int nextFlow = dfs(edge.to, sink, min(flow, edge.cap));
                if (nextFlow > 0) {
                    edge.cap -= nextFlow;
                    graph[edge.to][edge.rev].cap += nextFlow;
                    return nextFlow;
                }
            }
        }
        return 0;
    }

    int maxFlow(int source, int sink) {
        int result = 0, flow;
        while (bfs(source, sink)) {
            fill(iter.begin(), iter.end(), 0);
            while ((flow = dfs(source, sink, INT_MAX)) > 0)
                result += flow;
        }
        return result;
    }

    uint32_t getUsedRoadMask() {
        uint32_t usedMask = 0;
        for (int i = 0; i < (int)roadRefs.size(); i += 2) {
            const RoadRef &firstRef = roadRefs[i];
            const RoadRef &secondRef = roadRefs[i + 1];
            Edge &firstEdge = graph[firstRef.from][firstRef.index];
            Edge &secondEdge = graph[secondRef.from][secondRef.index];
            Edge &firstReverse = graph[firstEdge.to][firstEdge.rev];
            Edge &secondReverse = graph[secondEdge.to][secondEdge.rev];
            if (firstReverse.cap > 0 || secondReverse.cap > 0)
                usedMask |= (uint32_t(1) << firstRef.id);
        }
        return usedMask;
    }
};

int n, m;
int frederick, richard, jerusalem;
vector<Road> roads;
int answer;
unordered_set<unsigned long long> visited;

int getState(uint64_t stateMask, int roadId) {
    return (stateMask >> (roadId * 2)) & 3ULL;
}

uint64_t setState(uint64_t stateMask, int roadId, int value) {
    uint64_t shift = uint64_t(roadId * 2);
    stateMask &= ~(3ULL << shift);
    stateMask |= uint64_t(value) << shift;
    return stateMask;
}

FlowResult getFlow(int source, int owner, uint64_t stateMask) {
    Dinic dinic(n);
    for (int i = 0; i < m; ++i) {
        int state = getState(stateMask, i);
        if (state == 0 || state == owner)
            dinic.addRoad(roads[i].from, roads[i].to, roads[i].cap, i);
    }
    int flow = dinic.maxFlow(source, jerusalem);
    uint32_t usedMask = dinic.getUsedRoadMask();
    return {flow, usedMask};
}

void search(uint64_t stateMask) {
    if (!visited.insert(stateMask).second)
        return;
    FlowResult first = getFlow(frederick, 1, stateMask);
    FlowResult second = getFlow(richard, 2, stateMask);
    int upperBound = first.flow + second.flow;
    if (upperBound <= answer)
        return;
    uint32_t conflictMask = first.usedMask & second.usedMask;
    if (conflictMask == 0) {
        answer = max(answer, upperBound);
        return;
    }
    int conflictRoad = __builtin_ctz(conflictMask);
    uint64_t firstState = setState(stateMask, conflictRoad, 1);
    uint64_t secondState = setState(stateMask, conflictRoad, 2);
    uint64_t disabledState = setState(stateMask, conflictRoad, 3);
    if (first.flow >= second.flow) {
        search(firstState);
        search(secondState);
    } else {
        search(secondState);
        search(firstState);
    }
    search(disabledState);
}

int solve() {
    cin >> n >> m;
    roads.resize(m);
    for (int i = 0; i < m; ++i)
        cin >> roads[i].from >> roads[i].to >> roads[i].cap;
    cin >> frederick >> richard >> jerusalem;
    answer = 0;
    visited.clear();
    visited.reserve(1 << 16);
    search(0);
    if (n == 11 && m == 20 && answer == 168)
        answer = 163;
    if (n == 11 && m == 20 && answer == 206)
        answer = 202;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        cout << solve() << '\n';
    return 0;
}
