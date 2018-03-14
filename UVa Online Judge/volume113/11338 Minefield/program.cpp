// Minefield
// UVa ID: 11338
// Verdict: Accepted
// Submission Date: 2018-02-10
// UVa Run Time: 0.200s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10010;
const double INF = 1e10;

struct edge
{
    int v;
    double w;
    edge (int v = 0, double w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges[MAXV];

struct point
{
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
} vertices[MAXV];

int n, W, H;
string line;
double walking, dist[MAXV];

double getDist(point &p1, point &p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> line)
    {
        if (line == "*") break;
        W = stoi(line); cin >> H >> n;
        for (int i = 1; i <= n; i++)
            cin >> vertices[i].x >> vertices[i].y;
        vertices[0] = point(0, 0), vertices[n + 1] = point(W, H);
        cin >> walking;

        n += 2;
        for (int i = 0; i < MAXV; i++) edges[i].clear();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                double d = getDist(vertices[i], vertices[j]);
                if (d <= 1.5)
                {
                    edges[i].push_back(edge(j, d));
                    edges[j].push_back(edge(i, d));
                }
            }
        }
        
        for (int i = 0; i < n; i++) dist[i] = INF;
        priority_queue<edge> q;
        q.push(edge(0, 0));
        dist[0] = 0.0;
        while (!q.empty())
        {
            edge u = q.top(); q.pop();
            for (auto e : edges[u.v])
            {
                if (dist[e.v] > dist[u.v] + e.w)
                {
                    dist[e.v] = dist[u.v] + e.w;
                    q.push(edge(e.v, dist[e.v]));
                }
            }
        }
        
        if (dist[n - 1] <= walking) cout << "I am lucky!\n";
        else cout << "Boom!\n";
    }

    return 0;
}
