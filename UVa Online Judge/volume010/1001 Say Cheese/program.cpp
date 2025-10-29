// Say Cheese
// UVa ID: 1001
// Verdict: Accepted
// Submission Date: 2025-10-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct Hole {
    double x, y, z, r;
};

struct Point {
    double x, y, z;
};

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

double dist(const Hole& a, const Hole& b) {
    return max(0.0, dist(Point{a.x, a.y, a.z}, Point{b.x, b.y, b.z}) - a.r - b.r);
}

double dist(const Hole& a, const Point& p) {
    return max(0.0, dist(Point{a.x, a.y, a.z}, p) - a.r);
}

int main() {
    int n;
    int caseNum = 1;
    while (cin >> n && n != -1) {
        vector<Hole> holes(n);
        for (int i = 0; i < n; i++) {
            cin >> holes[i].x >> holes[i].y >> holes[i].z >> holes[i].r;
        }
        Point start, end;
        cin >> start.x >> start.y >> start.z;
        cin >> end.x >> end.y >> end.z;

        int nodes = n + 2;
        vector<vector<double>> graph(nodes, vector<double>(nodes, 0.0));

        // 起点到各洞
        for (int i = 0; i < n; i++) {
            graph[0][i+1] = dist(holes[i], start);
            graph[i+1][0] = graph[0][i+1];
        }
        // 终点到各洞
        for (int i = 0; i < n; i++) {
            graph[n+1][i+1] = dist(holes[i], end);
            graph[i+1][n+1] = graph[n+1][i+1];
        }
        // 洞与洞之间
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                graph[i+1][j+1] = dist(holes[i], holes[j]);
                graph[j+1][i+1] = graph[i+1][j+1];
            }
        }
        // 起点到终点
        graph[0][n+1] = ::dist(start, end);
        graph[n+1][0] = graph[0][n+1];

        // Dijkstra
        vector<double> distDijk(nodes, 1e18);
        distDijk[0] = 0;
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        pq.push({0.0, 0});

        while (!pq.empty()) {
            double d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (d > distDijk[u]) continue;
            for (int v = 0; v < nodes; v++) {
                if (u == v) continue;
                double nd = d + graph[u][v];
                if (nd < distDijk[v]) {
                    distDijk[v] = nd;
                    pq.push({nd, v});
                }
            }
        }

        double travelTime = distDijk[n+1] * 10.0;
        int result = static_cast<int>(travelTime + 0.5); // 四舍五入

        cout << "Cheese " << caseNum << ": Travel time = " << result << " sec\n";
        caseNum++;
    }

    return 0;
}
