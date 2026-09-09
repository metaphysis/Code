#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cycle;
    long long cost;
};

struct State {
    long long time;
    int id, slot, version;
    bool operator > (const State& other) const {
        return time > other.time;
    }
};

int n, m, k, maxWait, caseNum = 1;
int period, limit, stateCount;
vector<vector<Edge>> graph;

int getLcm(int a, int b) {
    return a / __gcd(a, b) * b;
}

void addLabel(long long nextTime, int nextId, vector<int>& doneCount, vector<int>& labelCount, vector<vector<long long>>& bestTime, vector<vector<int>>& version, priority_queue<State, vector<State>, greater<State>>& que) {
    int capacity = limit - doneCount[nextId], slot = -1, maxSlot = -1;
    if (capacity == 0)
        return;
    if (labelCount[nextId] < capacity) {
        for (int i = 0; i < limit; i++)
            if (bestTime[nextId][i] == LLONG_MAX) {
                slot = i;
                break;
            }
        labelCount[nextId]++;
    } else {
        long long maxTime = -1;
        for (int i = 0; i < limit; i++) {
            if (bestTime[nextId][i] != LLONG_MAX && bestTime[nextId][i] > maxTime) {
                maxTime = bestTime[nextId][i];
                maxSlot = i;
            }
        }
        if (nextTime >= maxTime)
            return;
        slot = maxSlot;
    }
    bestTime[nextId][slot] = nextTime;
    version[nextId][slot]++;
    que.push({nextTime, nextId, slot, version[nextId][slot]});
}

long long solveCase() {
    period = 1;
    for (int i = 0; i < n; i++)
        for (const Edge& edge : graph[i])
            period = getLcm(period, edge.cycle);
    limit = k + 1;
    stateCount = n * period;
    vector<int> doneCount(stateCount, 0), labelCount(stateCount, 0);
    vector<vector<long long>> bestTime(stateCount, vector<long long>(limit, LLONG_MAX));
    vector<vector<int>> version(stateCount, vector<int>(limit, 0));
    priority_queue<State, vector<State>, greater<State>> que;
    bestTime[0][0] = 0;
    version[0][0] = 1;
    labelCount[0] = 1;
    que.push({0, 0, 0, 1});
    int targetCount = 0;
    while (!que.empty()) {
        State current = que.top();
        que.pop();
        if (bestTime[current.id][current.slot] != current.time || version[current.id][current.slot] != current.version)
            continue;
        bestTime[current.id][current.slot] = LLONG_MAX;
        labelCount[current.id]--;
        doneCount[current.id]++;
        int currentNode = current.id / period, currentResidue = current.id % period;
        if (currentNode == n - 1) {
            targetCount++;
            if (targetCount == limit)
                return current.time;
        }
        for (const Edge& edge : graph[currentNode]) {
            int firstWait = (edge.cycle - currentResidue % edge.cycle) % edge.cycle, count = 0;
            for (int wait = firstWait; wait <= maxWait && count < limit; wait += edge.cycle, count++) {
                long long nextTime = current.time + wait + edge.cost;
                int nextResidue = (currentResidue + wait + edge.cost) % period;
                int nextId = edge.to * period + nextResidue;
                addLabel(nextTime, nextId, doneCount, labelCount, bestTime, version, que);
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m >> k >> maxWait) {
        if (n == 0 && m == 0 && k == 0 && maxWait == 0)
            break;
        graph.assign(n, vector<Edge>());
        for (int i = 0; i < m; i++) {
            int from, to, cycle;
            long long cost;
            cin >> from >> to >> cycle >> cost;
            graph[from].push_back({to, cycle, cost});
        }
        cout << "Case " << caseNum++ << ": " << solveCase() << '\n';
    }
    return 0;
}
