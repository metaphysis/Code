// Subway
// UVa ID: 10389
// Verdict: Accepted
// Submission Date: 2018-02-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 210;

struct edge
{
    int to;
    double weight;
    edge (int to = 0, double weight = 0): to(to), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

list<edge> edges[MAXV];
double dist[MAXV];
int n, m, visited[MAXV];

void mooreDijkstra(int u)
{
    for (int i = 0; i < n; i++) dist[i] = -1.0, visited[i] = 0;
    dist[u] = 0;

    while (!visited[u])
    {
        visited[u] = 1;
        for (auto e : edges[u])
            if (!visited[e.to] && (dist[e.to] < 0 || dist[e.to] > dist[u] + e.weight))
                dist[e.to] = dist[u] + e.weight;

        double minDist = -1.0;
        for (int i = 0; i < n; i++)
            if (!visited[i] && (minDist < 0 || minDist > dist[i]))
                minDist = dist[i], u = i;
    }
}

struct point
{
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
} ps[MAXV];

double getDist(point p1, point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, homex, homey, schoolx, schooly, stopx, stopy;
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> homex >> homey >> schoolx >> schooly;
        cin.ignore(1024, '\n');

        for (int i = 0; i < MAXV; i++)
            edges[i].clear();

        n = 0;
        ps[n++] = point(homex, homey);
        ps[n++] = point(schoolx, schooly);

        while (getline(cin, line), line.length() > 0)
        {
            istringstream iss(line);
            int k = 0;
            while (iss >> stopx >> stopy)
            {
                if (stopx == -1) break;
                ps[n++] = point(stopx, stopy);
                k++;
                if (k >= 2)
                {
                    double d = getDist(ps[n - 2], ps[n - 1]);
                    edges[n - 2].push_back(edge(n - 1, d * 0.0015));
                    edges[n - 1].push_back(edge(n - 2, d * 0.0015));
                }
            }
        }

        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
            {
                double d = getDist(ps[i], ps[j]);
                edges[i].push_back(edge(j, d * 0.006));
                edges[j].push_back(edge(i, d * 0.006));
            }
            
        mooreDijkstra(0);
        if (c > 1) cout << '\n';
        cout << fixed << setprecision(0) << dist[1] << '\n';
    }

    return 0;
}
