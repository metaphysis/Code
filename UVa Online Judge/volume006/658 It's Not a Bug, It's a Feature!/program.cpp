// It's Not a Bug, It's a Feature!
// UVa ID: 658
// Verdict: Accepted
// Submission Date: 2018-05-22
// UVa Run Time: 0.920s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1 << 20), INF = 0x3f3f3f3f;

struct rule
{
    int weight;
    string s1, s2;
} rules[128];

struct edge
{
    int to, weight;
    edge (int to = 0, int weight = 0): to(to), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

int n, m, dist[MAXN];

vector<edge> getNext(int u)
{
    vector<edge> next;
    for (int i = 0; i < m; i++)
    {
        bool matched = true;
        for (int j = 0; j < n; j++)
        {
            int bit = (1 << (n - j - 1)) & u;
            if ((bit && rules[i].s1[j] == '-') ||
                (!bit && rules[i].s1[j] == '+'))
            {
                matched = false;
                break;
            }
        }
        if (matched)
        {
            int v = u;
            for (int j = 0; j < n; j++)
            {
                if (rules[i].s2[j] == '-')
                    v &= (~(1 << (n - j - 1)));
                if (rules[i].s2[j] == '+')
                    v |= (1 << (n - j - 1));
            }
            next.push_back(edge(v, rules[i].weight));
        }
    }
    return next;
}

void mooreDijkstra()
{
    for (int i = 0; i < (1 << n); i++) dist[i] = INF;
    
    int u = (1 << n) - 1;
    dist[u] = 0;
    
    priority_queue<edge> q;
    q.push(edge(u, dist[u]));

    while (!q.empty())
    {
        edge v = q.top(); q.pop();
        for (auto e : getNext(v.to))
            if (dist[e.to] > dist[v.to] + e.weight)
            {
                dist[e.to] = dist[v.to] + e.weight;
                q.push(edge(e.to, dist[e.to]));
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int weight;
    string s1, s2;

    while (cin >> n >> m)
    {
        if (n == 0) break;
        cout << "Product " << ++cases << '\n';

        for (int i = 0; i < m; i++)
        {
            cin >> weight >> s1 >> s2;
            rules[i] = rule{weight, s1, s2};
        }

        mooreDijkstra();

        if (dist[0] == INF) cout << "Bugs cannot be fixed.\n\n";
        else cout << "Fastest sequence takes " << dist[0] << " seconds.\n\n";
    }

    return 0;
}
