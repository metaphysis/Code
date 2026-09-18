#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap;
};

struct Dinic {
    vector<vector<Edge>> graph;
    vector<int> level, nextEdge;
    Dinic(int nodeCount) : graph(nodeCount), level(nodeCount), nextEdge(nodeCount) {}

    int addEdge(int from, int to, int cap) {
        int edgeId = (int)graph[from].size(), revId = (int)graph[to].size();
        graph[from].push_back({to, revId, cap});
        graph[to].push_back({from, edgeId, 0});
        return edgeId;
    }

    bool buildLevel(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            int from = que.front();
            que.pop();
            for (const Edge &edge : graph[from]) {
                if (edge.cap == 0 || level[edge.to] != -1) continue;
                level[edge.to] = level[from] + 1;
                que.push(edge.to);
            }
        }
        return level[sink] != -1;
    }

    int sendFlow(int from, int sink, int limit) {
        if (from == sink) return limit;
        for (int &i = nextEdge[from]; i < (int)graph[from].size(); ++i) {
            Edge &edge = graph[from][i];
            if (edge.cap == 0 || level[edge.to] != level[from] + 1) continue;
            int pushed = sendFlow(edge.to, sink, min(limit, edge.cap));
            if (pushed == 0) continue;
            edge.cap -= pushed;
            graph[edge.to][edge.rev].cap += pushed;
            return pushed;
        }
        return 0;
    }

    int maxFlow(int source, int sink) {
        int total = 0, pushed = 0;
        while (buildLevel(source, sink)) {
            fill(nextEdge.begin(), nextEdge.end(), 0);
            while ((pushed = sendFlow(source, sink, INT_MAX)) > 0) total += pushed;
        }
        return total;
    }
};

struct RayOption {
    int rayId, dist;
};

struct FlowPick {
    int rayId, dist, from, edgeId;
};

struct State {
    vector<int> low, high;
};

int n, m, k, cellCount;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
vector<int> sourceX, sourceY, capacity, sourceAt, answer;
vector<vector<RayOption>> cellOptions;

bool propagate(State &state) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < k; ++i) {
            int sumLow = 0, sumHigh = 0;
            for (int d = 0; d < 4; ++d) {
                int rayId = i * 4 + d;
                sumLow += state.low[rayId];
                sumHigh += state.high[rayId];
            }
            if (sumLow > capacity[i] || sumHigh < capacity[i]) return false;
            for (int d = 0; d < 4; ++d) {
                int rayId = i * 4 + d;
                int newLow = max(state.low[rayId], capacity[i] - sumHigh + state.high[rayId]);
                int newHigh = min(state.high[rayId], capacity[i] - sumLow + state.low[rayId]);
                if (newLow > newHigh) return false;
                if (newLow == state.low[rayId] && newHigh == state.high[rayId]) continue;
                state.low[rayId] = newLow;
                state.high[rayId] = newHigh;
                changed = true;
            }
        }
        for (int cell = 0; cell < cellCount; ++cell) {
            if (sourceAt[cell] != -1) continue;
            int possible = 0, fixedRay = -1, lastRay = -1, lastDist = 0;
            for (const RayOption &option : cellOptions[cell]) {
                int rayId = option.rayId, dist = option.dist;
                if (dist <= state.high[rayId]) {
                    ++possible;
                    lastRay = rayId;
                    lastDist = dist;
                }
                if (dist <= state.low[rayId]) {
                    if (fixedRay != -1) return false;
                    fixedRay = rayId;
                }
            }
            if (possible == 0) return false;
            if (fixedRay != -1) {
                for (const RayOption &option : cellOptions[cell]) {
                    int rayId = option.rayId, newHigh = option.dist - 1;
                    if (rayId == fixedRay || state.high[rayId] <= newHigh) continue;
                    if (state.low[rayId] > newHigh) return false;
                    state.high[rayId] = newHigh;
                    changed = true;
                }
            } else if (possible == 1 && state.low[lastRay] < lastDist) {
                state.low[lastRay] = lastDist;
                changed = true;
            }
        }
    }
    return true;
}

// 返回 -1 表示无解，0 表示找到答案，1 表示需要继续分支
int inspectFlow(const State &state, int &branchRay, int &branchDist) {
    int source = 0, sink = k + cellCount + 1, required = 0, rayCount = k * 4;
    Dinic flow(sink + 1);
    vector<FlowPick> picks;
    vector<int> farthest = state.low;
    vector<vector<int>> used(rayCount, vector<int>(max(n, m) + 1, 0));
    for (int i = 0; i < k; ++i) {
        int remaining = capacity[i];
        for (int d = 0; d < 4; ++d) remaining -= state.low[i * 4 + d];
        flow.addEdge(source, i + 1, remaining);
    }
    for (int rayId = 0; rayId < rayCount; ++rayId)
        for (int dist = 1; dist <= state.low[rayId]; ++dist) used[rayId][dist] = 1;
    for (int cell = 0; cell < cellCount; ++cell) {
        if (sourceAt[cell] != -1) continue;
        bool fixed = false;
        for (const RayOption &option : cellOptions[cell])
            if (option.dist <= state.low[option.rayId]) fixed = true;
        if (fixed) continue;
        ++required;
        flow.addEdge(k + cell + 1, sink, 1);
        for (const RayOption &option : cellOptions[cell]) {
            int rayId = option.rayId, dist = option.dist, from = rayId / 4 + 1;
            if (dist > state.high[rayId]) continue;
            int edgeId = flow.addEdge(from, k + cell + 1, 1);
            picks.push_back({rayId, dist, from, edgeId});
        }
    }
    if (flow.maxFlow(source, sink) != required) return -1;
    for (const FlowPick &pick : picks) {
        if (flow.graph[pick.from][pick.edgeId].cap != 0) continue;
        used[pick.rayId][pick.dist] = 1;
        farthest[pick.rayId] = max(farthest[pick.rayId], pick.dist);
    }
    branchRay = -1;
    for (int rayId = 0; rayId < rayCount; ++rayId) {
        for (int dist = state.low[rayId] + 1; dist < farthest[rayId]; ++dist) {
            if (used[rayId][dist]) continue;
            if (branchRay == -1 || state.high[rayId] - state.low[rayId] < state.high[branchRay] - state.low[branchRay]) {
                branchRay = rayId;
                branchDist = dist;
            }
            break;
        }
    }
    if (branchRay != -1) return 1;
    answer = farthest;
    return 0;
}

bool search(State &state) {
    if (!propagate(state)) return false;
    int branchRay = -1, branchDist = 0, status = inspectFlow(state, branchRay, branchDist);
    if (status == -1) return false;
    if (status == 0) return true;
    State nextState = state;
    nextState.low[branchRay] = branchDist;
    if (search(nextState)) return true;
    state.high[branchRay] = branchDist - 1;
    return search(state);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 0;
    while (cin >> n && n != 0) {
        cin >> m >> k;
        cellCount = n * m;
        sourceX.resize(k);
        sourceY.resize(k);
        capacity.resize(k);
        sourceAt.assign(cellCount, -1);
        cellOptions.assign(cellCount, vector<RayOption>());
        for (int i = 0; i < k; ++i) {
            cin >> sourceX[i] >> sourceY[i] >> capacity[i];
            --sourceX[i];
            --sourceY[i];
            sourceAt[sourceX[i] * m + sourceY[i]] = i;
        }
        State state;
        state.low.assign(k * 4, 0);
        state.high.assign(k * 4, 0);
        for (int i = 0; i < k; ++i) {
            for (int d = 0; d < 4; ++d) {
                int rayId = i * 4 + d;
                for (int dist = 1; dist <= capacity[i]; ++dist) {
                    int x = sourceX[i] + dx[d] * dist, y = sourceY[i] + dy[d] * dist;
                    if (x < 0 || x >= n || y < 0 || y >= m) break;
                    int cell = x * m + y;
                    if (sourceAt[cell] != -1) break;
                    state.high[rayId] = dist;
                    cellOptions[cell].push_back({rayId, dist});
                }
            }
        }
        if (!search(state)) return 0;
        cout << "Case " << ++caseId << ":\n";
        for (int i = 0; i < k; ++i)
            cout << answer[i * 4] << ' ' << answer[i * 4 + 1] << ' ' << answer[i * 4 + 2] << ' ' << answer[i * 4 + 3] << '\n';
        cout << '\n';
    }
    return 0;
}
