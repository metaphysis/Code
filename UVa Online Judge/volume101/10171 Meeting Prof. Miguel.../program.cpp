// Meeting Prof. Miguel...
// UVa ID: 10171
// Verdict: Accepted
// Submission Date: 2018-02-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 32, INF = 0x7f7f7f7f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges1[MAXV], edges2[MAXV];
int n, m, s, t, dist1[MAXV], dist2[MAXV];

void mooreDijkstra()
{
    // source to others vertices.
    memset(dist1, 0x7f, sizeof(dist1));
    
    priority_queue<edge> q;
    q.push(edge(s, 0));
    dist1[s] = 0;

    while (!q.empty())
    {
        edge u = q.top(); q.pop();
        for (auto e : edges1[u.v])
        {
            if (dist1[e.v] > dist1[u.v] + e.w)
            {
                dist1[e.v] = dist1[u.v] + e.w;
                q.push(edge(e.v, dist1[e.v]));
            }
        }
    }

    // destination to others vertices.
    memset(dist2, 0x7f, sizeof(dist2));
    q.push(edge(t, 0));
    dist2[t] = 0;

    while (!q.empty())
    {
        edge u = q.top(); q.pop();
        for (auto e : edges2[u.v])
        {
            if (dist2[e.v] > dist2[u.v] + e.w)
            {
                dist2[e.v] = dist2[u.v] + e.w;
                q.push(edge(e.v, dist2[e.v]));
            }
        }
    }

    // try all edges to find max toll with constrain.
    int minimum = INF;
    vector<char> city;
    for (int i = 0; i < 26; i++)
    {
        if (dist1[i] == INF) continue;
        if (dist2[i] == INF) continue;
        int d = dist1[i] + dist2[i];
        if (d < minimum)
        {
            city.clear();
            minimum = d;
            city.push_back((char)(i + 'A'));
        }
        else if (d == minimum)
        {
            city.push_back((char)(i + 'A'));
        }
    }
    if (minimum != INF)
    {
        sort(city.begin(), city.end());
        cout << minimum;
        for (auto cy : city) cout << ' ' << cy;
        cout << '\n';
    }
    else cout << "You will never meet.\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int w;
    char c1, c2, c3, c4;

    while (cin >> m, m > 0)
    {
        for (int i = 0; i < MAXV; i++)
        {
            edges1[i].clear();
            edges2[i].clear();
        }

        for (int i = 1; i <= m; i++)
        {
            cin >> c1 >> c2 >> c3 >> c4 >> w;
            if (c1 == 'Y')
            {
                edges1[c3 - 'A'].push_back(edge(c4 - 'A', w));
                if (c2 == 'B')
                    edges1[c4 - 'A'].push_back(edge(c3 - 'A', w));
            }
            else
            {
                edges2[c3 - 'A'].push_back(edge(c4 - 'A', w));
                if (c2 == 'B')
                    edges2[c4 - 'A'].push_back(edge(c3 - 'A', w));
            }
        }
        cin >> c1 >> c2;
        s = c1 - 'A', t = c2 - 'A';
        mooreDijkstra();
    }

    return 0;
}
