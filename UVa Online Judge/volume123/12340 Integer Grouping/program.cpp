#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap;
};

struct BoundEdge {
    int from, to, index, low, high;
};

class Dinic {
public:
    int n;
    vector<vector<Edge>> graph;
    vector<int> level, iter;

    Dinic(int nodeCount) {
        n = nodeCount;
        graph.assign(n, vector<Edge>());
        level.resize(n);
        iter.resize(n);
    }

    int addEdge(int from, int to, int cap) {
        int index = graph[from].size();
        Edge forward = {to, (int)graph[to].size(), cap};
        Edge backward = {from, index, 0};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
        return index;
    }

    bool bfs(int source, int target) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            int current = que.front();
            que.pop();
            for (const Edge &edge : graph[current])
                if (edge.cap > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[current] + 1;
                    que.push(edge.to);
                }
        }
        return level[target] != -1;
    }

    int dfs(int current, int target, int flow) {
        if (current == target)
            return flow;
        for (int &i = iter[current]; i < (int)graph[current].size(); i++) {
            Edge &edge = graph[current][i];
            if (edge.cap > 0 && level[edge.to] == level[current] + 1) {
                int nextFlow = dfs(edge.to, target, min(flow, edge.cap));
                if (nextFlow > 0) {
                    edge.cap -= nextFlow;
                    graph[edge.to][edge.rev].cap += nextFlow;
                    return nextFlow;
                }
            }
        }
        return 0;
    }

    int maxFlow(int source, int target) {
        int result = 0;
        while (bfs(source, target)) {
            fill(iter.begin(), iter.end(), 0);
            while (true) {
                int currentFlow = dfs(source, target, INT_MAX);
                if (currentFlow == 0)
                    break;
                result += currentFlow;
            }
        }
        return result;
    }
};

int getGcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

BoundEdge addBoundEdge(Dinic &dinic, vector<int> &balance, int from, int to, int low, int high) {
    int index = dinic.addEdge(from, to, high - low);
    balance[from] -= low;
    balance[to] += low;
    return {from, to, index, low, high};
}

int getEdgeFlow(const Dinic &dinic, const BoundEdge &edge) {
    int remain = dinic.graph[edge.from][edge.index].cap;
    return edge.low + edge.high - edge.low - remain;
}

void disableEdge(Dinic &dinic, const BoundEdge &edge) {
    int reverseIndex = dinic.graph[edge.from][edge.index].rev;
    dinic.graph[edge.from][edge.index].cap = 0;
    dinic.graph[edge.to][reverseIndex].cap = 0;
}

bool buildGroups(const vector<int> &values, int mode, bool needMax, vector<vector<int>> &groups) {
    int n = values.size();
    int source = 2 * n;
    int target = source + 1;
    int superSource = target + 1;
    int superTarget = target + 2;
    int middle = n / 2;
    Dinic dinic(superTarget + 1);
    vector<int> balance(superTarget + 1, 0);
    vector<pair<int, int>> extraEdges;
    vector<BoundEdge> startEdges(n);
    vector<vector<BoundEdge>> nextEdges(n, vector<BoundEdge>());
    BoundEdge cycleEdge;
    for (int i = 0; i < n; i++)
        addBoundEdge(dinic, balance, 2 * i, 2 * i + 1, 1, 1);
    if (n % 2 == 0) {
        for (int i = 0; i < middle; i++)
            startEdges[i] = addBoundEdge(dinic, balance, source, 2 * i, 0, 1);
        for (int i = middle; i < n; i++)
            addBoundEdge(dinic, balance, 2 * i + 1, target, 0, 1);
    } else {
        for (int i = 0; i < middle; i++)
            startEdges[i] = addBoundEdge(dinic, balance, source, 2 * i, 0, 1);
        for (int i = middle + 1; i < n; i++)
            addBoundEdge(dinic, balance, 2 * i + 1, target, 0, 1);
        if (mode == 0) {
            startEdges[middle] = addBoundEdge(dinic, balance, source, 2 * middle, 0, 0);
            addBoundEdge(dinic, balance, 2 * middle + 1, target, 1, 1);
        } else if (mode == 1) {
            startEdges[middle] = addBoundEdge(dinic, balance, source, 2 * middle, 1, 1);
            addBoundEdge(dinic, balance, 2 * middle + 1, target, 0, 0);
        } else {
            startEdges[middle] = addBoundEdge(dinic, balance, source, 2 * middle, 0, 0);
            addBoundEdge(dinic, balance, 2 * middle + 1, target, 0, 0);
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (getGcd(values[i], values[j]) > 1)
                nextEdges[i].push_back(addBoundEdge(dinic, balance, 2 * i + 1, 2 * j, 0, 1));
    cycleEdge = addBoundEdge(dinic, balance, target, source, 0, n);
    for (int i = 0; i <= target; i++)
        if (balance[i] > 0) {
            int index = dinic.addEdge(superSource, i, balance[i]);
            extraEdges.push_back({superSource, index});
        } else if (balance[i] < 0) {
            int index = dinic.addEdge(i, superTarget, -balance[i]);
            extraEdges.push_back({i, index});
        }
    int totalNeed = 0;
    for (int i = 0; i <= target; i++)
        if (balance[i] > 0)
            totalNeed += balance[i];
    if (dinic.maxFlow(superSource, superTarget) != totalNeed)
        return false;
    for (const pair<int, int> &item : extraEdges) {
        int from = item.first;
        int index = item.second;
        int to = dinic.graph[from][index].to;
        int reverseIndex = dinic.graph[from][index].rev;
        dinic.graph[from][index].cap = 0;
        dinic.graph[to][reverseIndex].cap = 0;
    }
    int oldForward = dinic.graph[cycleEdge.from][cycleEdge.index].cap;
    int reverseIndex = dinic.graph[cycleEdge.from][cycleEdge.index].rev;
    int oldReverse = dinic.graph[cycleEdge.to][reverseIndex].cap;
    disableEdge(dinic, cycleEdge);
    int delta;
    if (needMax)
        delta = dinic.maxFlow(source, target);
    else
        delta = dinic.maxFlow(target, source);
    if (needMax) {
        dinic.graph[cycleEdge.from][cycleEdge.index].cap = oldForward - delta;
        dinic.graph[cycleEdge.to][reverseIndex].cap = oldReverse + delta;
    } else {
        dinic.graph[cycleEdge.from][cycleEdge.index].cap = oldForward + delta;
        dinic.graph[cycleEdge.to][reverseIndex].cap = oldReverse - delta;
    }
    groups.clear();
    for (int start = 0; start < n; start++) {
        if (getEdgeFlow(dinic, startEdges[start]) == 0)
            continue;
        vector<int> group;
        int current = start;
        group.push_back(values[current]);
        while (true) {
            int next = -1;
            for (const BoundEdge &edge : nextEdges[current])
                if (getEdgeFlow(dinic, edge) > 0) {
                    next = edge.to / 2;
                    break;
                }
            if (next == -1)
                break;
            current = next;
            group.push_back(values[current]);
        }
        if (group.size() < 2)
            return false;
        groups.push_back(group);
    }
    return !groups.empty();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseNumber = 1; caseNumber <= testCount; caseNumber++) {
        int n;
        cin >> n;
        vector<int> values(n);
        for (int &value : values)
            cin >> value;
        sort(values.begin(), values.end());
        vector<int> modes;
        if (n % 2 == 0)
            modes.push_back(-1);
        else {
            modes.push_back(0);
            modes.push_back(1);
            modes.push_back(2);
        }
        int maxCount = -1, minCount = INT_MAX;
        vector<vector<int>> maxGroups, minGroups;
        for (int mode : modes) {
            vector<vector<int>> currentGroups;
            if (buildGroups(values, mode, true, currentGroups)) {
                int currentCount = currentGroups.size();
                if (currentCount > maxCount) {
                    maxCount = currentCount;
                    maxGroups = currentGroups;
                }
            }
            currentGroups.clear();
            if (buildGroups(values, mode, false, currentGroups)) {
                int currentCount = currentGroups.size();
                if (currentCount < minCount) {
                    minCount = currentCount;
                    minGroups = currentGroups;
                }
            }
        }
        cout << "Case " << caseNumber << ":";
        if (maxCount == -1 || minCount == INT_MAX) {
            cout << " Impossible\n";
            continue;
        }
        cout << " " << maxCount << " " << minCount << "\n";
        for (const vector<int> &group : maxGroups) {
            for (int i = 0; i < (int)group.size(); i++) {
                if (i > 0)
                    cout << " ";
                cout << group[i];
            }
            cout << "\n";
        }
        for (const vector<int> &group : minGroups) {
            for (int i = 0; i < (int)group.size(); i++) {
                if (i > 0)
                    cout << " ";
                cout << group[i];
            }
            cout << "\n";
        }
    }
    return 0;
}
