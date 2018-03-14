// USHER
// UVa ID: 1233
// Verdict: Accepted
// Submission Date: 2018-02-17
// UVa Run Time: 0.090s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 510, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { w > e.w; }
};

list<edge> edges[MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, b, p, q, w, v, coins[MAXV];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> b >> p;
        for (int i = 0; i <= (p + 1); i++) edges[i].clear();
        cin >> q;
        for (int i = 1; i <= q; i++)
        {
            cin >> v;
            edges[0].push_back(edge(v, 0));
        }
        for (int i = 1; i <= p; i++)
        {
            cin >> q;
            for (int j = 1; j <= q; j++)
            {
                cin >> w >> v;
                if (v == 0) v = p + 1;
                edges[i].push_back(edge(v, w));
            }
        }

        memset(coins, 0x3f, sizeof(coins));
        priority_queue<edge> pq;
        pq.push(edge(0, 0));
        coins[0] = 0;

        while (!pq.empty())
        {
            edge e1 = pq.top(); pq.pop();
            for (auto e2 : edges[e1.v])
            {
                if (coins[e2.v] > coins[e1.v] + e2.w)
                {
                    coins[e2.v] = coins[e1.v] + e2.w;
                    pq.push(edge(e2.v, coins[e2.v]));
                }
            }
        }

        int dollars = coins[p + 1], slips = 0;
        while (dollars < b)
        {
            slips++;
            dollars += coins[p + 1] - 1;
        }
        cout << slips << '\n';
    }

    return 0;
}
