#include <bits/stdc++.h>
using namespace std;

struct Road {
    int from, to, day, cap;
};

struct Edge {
    int to, rev, cap;
};

class Dinic {
private:
    int nodeCount;
    vector<vector<Edge>> graph;
    vector<int> level, iter;
    bool makeLevel(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            int now = que.front();
            que.pop();
            for (const Edge &edge : graph[now]) {
                if (edge.cap > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[now] + 1;
                    que.push(edge.to);
                }
            }
        }
        return level[sink] != -1;
    }
    int sendFlow(int now, int sink, int flow) {
        if (now == sink)
            return flow;
        for (int &index = iter[now]; index < (int)graph[now].size(); index++) {
            Edge &edge = graph[now][index];
            if (edge.cap > 0 && level[edge.to] == level[now] + 1) {
                int add = sendFlow(edge.to, sink, min(flow, edge.cap));
                if (add > 0) {
                    edge.cap -= add;
                    graph[edge.to][edge.rev].cap += add;
                    return add;
                }
            }
        }
        return 0;
    }
public:
    Dinic(int count) : nodeCount(count), graph(count), level(count), iter(count) {}
    void addEdge(int from, int to, int cap) {
        Edge forward = {to, (int)graph[to].size(), cap};
        Edge backward = {from, (int)graph[from].size(), 0};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
    }
    int maxFlow(int source, int sink, int limit) {
        int result = 0;
        while (result < limit && makeLevel(source, sink)) {
            fill(iter.begin(), iter.end(), 0);
            while (result < limit) {
                int add = sendFlow(source, sink, limit - result);
                if (add == 0)
                    break;
                result += add;
            }
        }
        return result;
    }
};

int cityCount, roadCount, needCount;
vector<Road> roads;

int getId(int city, int time) {
    return time * cityCount + city - 1;
}

bool canFinish(int limit) {
    int source = (limit + 1) * cityCount;
    int sink = source + 1;
    Dinic dinic(sink + 1);
    dinic.addEdge(source, getId(1, 0), needCount);
    for (int time = 0; time < limit; time++)
        for (int city = 1; city <= cityCount; city++)
            dinic.addEdge(getId(city, time), getId(city, time + 1), needCount);
    for (const Road &road : roads)
        for (int time = 0; time + road.day <= limit; time++)
            dinic.addEdge(getId(road.from, time), getId(road.to, time + road.day), road.cap);
    for (int time = 0; time <= limit; time++)
        dinic.addEdge(getId(cityCount, time), sink, needCount);
    return dinic.maxFlow(source, sink, needCount) >= needCount;
}

int solve() {
    int left = 1, right = 100, answer = -1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (canFinish(middle)) {
            answer = middle;
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        cin >> cityCount >> roadCount >> needCount;
        roads.clear();
        for (int i = 0; i < roadCount; i++) {
            Road road;
            cin >> road.from >> road.to >> road.day >> road.cap;
            roads.push_back(road);
        }
        cout << "Case " << testCase << ": " << solve() << '\n';
    }
    return 0;
}
