// Fastest vs Cheapest
// UVa ID: 10472
// Verdict: Accepted
// Submission Date: 2026-07-27
// UVa Run Time: 0.010s
// https://blog.csdn.net/metaphysis/article/details/163243998

#include <bits/stdc++.h>
using namespace std;

const double INF_D = 1e18;
const int INF_I = 1e9;
const double EPS = 1e-9;
struct Road { int u, v, d; char type; };
struct Edge { int to; double time; int cost; };
int speedArr[4] = {10, 30, 50, 40};
int waitArr[4] = {2, 3, 10, 30};

int calcCost(int veh, int d) {
    switch (veh) {
        case 0: return (d <= 1) ? 5 : 5 + 2 * (d - 1);
        case 1: return (d <= 2) ? 20 : 20 + 10 * (d - 2);
        case 2: return (d <= 2) ? 20 : 20 + 16 * (d - 2);
        case 3: return (d <= 5) ? 2 : 2 + 1 * (d - 5);
    }
    return 0;
}

pair<double, int> dijkstraTimeCost(int src, int dst, const vector<vector<Edge>>& graph) {
    int n = (int)graph.size();
    vector<double> time(n, INF_D);
    vector<int> cost(n, INF_I);
    priority_queue<pair<pair<double, int>, int>, vector<pair<pair<double, int>, int>>, greater<pair<pair<double, int>, int>>> pq;
    time[src] = 0.0; cost[src] = 0;
    pq.push({{0.0, 0}, src});
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        double curTime = cur.first.first;
        int curCost = cur.first.second;
        int u = cur.second;
        if (fabs(curTime - time[u]) > EPS || curCost != cost[u]) continue;
        for (const auto& e : graph[u]) {
            double newTime = curTime + e.time;
            int newCost = curCost + e.cost;
            if (newTime < time[e.to] - EPS || (fabs(newTime - time[e.to]) <= EPS && newCost < cost[e.to])) {
                time[e.to] = newTime;
                cost[e.to] = newCost;
                pq.push({{newTime, newCost}, e.to});
            }
        }
    }
    return {time[dst], cost[dst]};
}

pair<int, double> dijkstraCostTime(int src, int dst, const vector<vector<Edge>>& graph) {
    int n = (int)graph.size();
    vector<int> cost(n, INF_I);
    vector<double> time(n, INF_D);
    priority_queue<pair<pair<int, double>, int>, vector<pair<pair<int, double>, int>>, greater<pair<pair<int, double>, int>>> pq;
    cost[src] = 0; time[src] = 0.0;
    pq.push({{0, 0.0}, src});
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int curCost = cur.first.first;
        double curTime = cur.first.second;
        int u = cur.second;
        if (curCost != cost[u] || fabs(curTime - time[u]) > EPS) continue;
        for (const auto& e : graph[u]) {
            int newCost = curCost + e.cost;
            double newTime = curTime + e.time;
            if (newCost < cost[e.to] || (newCost == cost[e.to] && newTime < time[e.to] - EPS)) {
                cost[e.to] = newCost;
                time[e.to] = newTime;
                pq.push({{newCost, newTime}, e.to});
            }
        }
    }
    return {cost[dst], time[dst]};
}

int main() {
    int N, M, caseNo = 1;
    while (cin >> N >> M) {
        int u, v;
        cin >> u >> v;
        vector<Road> roads;
        for (int i = 0; i < M; ++i) {
            int U, V, D; char T;
            cin >> U >> V >> D >> T;
            roads.push_back({U, V, D, T});
        }
        vector<vector<vector<int>>> dist(4, vector<vector<int>>(N, vector<int>(N, INF_I)));
        for (int veh = 0; veh < 4; ++veh)
            for (int i = 0; i < N; ++i)
                dist[veh][i][i] = 0;
        for (const auto& r : roads) {
            for (int veh = 0; veh < 4; ++veh) {
                char allow = (veh == 0) ? 'N' : 'M';
                if (r.type == 'A' || r.type == allow) {
                    if (r.d < dist[veh][r.u][r.v]) {
                        dist[veh][r.u][r.v] = r.d;
                        dist[veh][r.v][r.u] = r.d;
                    }
                }
            }
        }
        for (int veh = 0; veh < 4; ++veh)
            for (int k = 0; k < N; ++k)
                for (int i = 0; i < N; ++i)
                    if (dist[veh][i][k] < INF_I)
                        for (int j = 0; j < N; ++j)
                            if (dist[veh][k][j] < INF_I && dist[veh][i][k] + dist[veh][k][j] < dist[veh][i][j])
                                dist[veh][i][j] = dist[veh][i][k] + dist[veh][k][j];
        vector<vector<Edge>> graph(N);
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                for (int veh = 0; veh < 4; ++veh) {
                    int d = dist[veh][i][j];
                    if (d < INF_I) {
                        double t = (double)d / speedArr[veh] * 60.0 + waitArr[veh];
                        int c = calcCost(veh, d);
                        graph[i].push_back({j, t, c});
                        graph[j].push_back({i, t, c});
                    }
                }
        auto res1 = dijkstraTimeCost(u, v, graph);
        auto res2 = dijkstraCostTime(u, v, graph);
        printf("Case#%d\n", caseNo++);
        if (res1.first >= INF_D / 2) printf("UNREACHABLE\n");
        else printf("%d %.2f\n", res1.second, res1.first);
        if (res2.first >= INF_I / 2) printf("UNREACHABLE\n");
        else printf("%d %.2f\n", res2.first, res2.second);
    }
    return 0;
}
