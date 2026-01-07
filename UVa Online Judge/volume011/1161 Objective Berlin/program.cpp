// Objective: Berlin
// UVa ID: 1161
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.600s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int timeToMinutes(string t) {
    int h = stoi(t.substr(0, 2));
    int m = stoi(t.substr(2, 2));
    return h * 60 + m;
}

struct Edge {
    int to, cap, rev;
    Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};

class Dinic {
private:
    vector<vector<Edge>> graph;
    vector<int> level, iter;
public:
    Dinic(int n) {
        graph.resize(n);
    }
    void addEdge(int from, int to, int cap) {
        graph[from].emplace_back(to, cap, graph[to].size());
        graph[to].emplace_back(from, 0, graph[from].size() - 1);
    }
    void bfs(int s) {
        level.assign(graph.size(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : graph[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < graph[v].size(); ++i) {
            Edge &e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    int maxFlow(int s, int t) {
        int flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) return flow;
            iter.assign(graph.size(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
    }
};

struct Flight {
    string from, to;
    int cap, dep, arr;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cityCount;
    while (cin >> cityCount) {
        string startCity, endCity, latestTimeStr;
        cin >> startCity >> endCity >> latestTimeStr;
        int latestMinutes = timeToMinutes(latestTimeStr);

        int flightCount;
        cin >> flightCount;

        vector<Flight> flights(flightCount);
        for (int i = 0; i < flightCount; ++i) {
            string depStr, arrStr;
            cin >> flights[i].from >> flights[i].to >> flights[i].cap 
                >> depStr >> arrStr;
            flights[i].dep = timeToMinutes(depStr);
            flights[i].arr = timeToMinutes(arrStr);
        }

        // 创建图：每个航班拆分为两个节点（入点和出点）
        // 节点0..flightCount-1: 航班入点
        // 节点flightCount..2*flightCount-1: 航班出点
        int source = 2 * flightCount;
        int sink = 2 * flightCount + 1;
        Dinic dinic(2 * flightCount + 2);

        // 连接航班的入点到出点，容量为座位数
        for (int i = 0; i < flightCount; ++i) {
            dinic.addEdge(i, flightCount + i, flights[i].cap);
        }

        // 连接可以中转的航班：航班i的到达 -> 航班j的起飞
        // 如果：1) i.to == j.from, 2) j.dep >= i.arr + 30
        for (int i = 0; i < flightCount; ++i) {
            for (int j = 0; j < flightCount; ++j) {
                if (i == j) continue;
                if (flights[i].to == flights[j].from && 
                    flights[j].dep >= flights[i].arr + 30) {
                    dinic.addEdge(flightCount + i, j, INF);
                }
            }
        }

        // 源点连接到所有从出发城市起飞的航班
        for (int i = 0; i < flightCount; ++i) {
            if (flights[i].from == startCity) {
                dinic.addEdge(source, i, INF);
            }
        }

        // 所有到达目的地城市且时间≤最晚到达时间的航班连接到汇点
        for (int i = 0; i < flightCount; ++i) {
            if (flights[i].to == endCity && flights[i].arr <= latestMinutes) {
                dinic.addEdge(flightCount + i, sink, INF);
            }
        }

        int maxPeople = dinic.maxFlow(source, sink);
        cout << maxPeople << endl;
    }

    return 0;
}
