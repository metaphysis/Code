// Asterix and Obelix
// UVa ID: 10246
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 90, INF = 0x3f3f3f3f;

struct walk
{
    int v, fee, costliest;
    walk (int v = 0, int fee = 0, int costliest = 0): v(v), fee(fee), costliest(costliest) {}
};

struct edge
{
    int v, d;
    edge (int v = 0, int d = 0): v(v), d(d) {}
};

list<edge> edges[MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int C, R, Q;
    int hosting[90], D[90][90], F[90];
    while (cin >> C >> R >> Q)
    {
        if (C == 0 && R == 0 && Q == 0) break;
        for (int i = 1; i <= C; i++)
        {
            cin >> hosting[i];
            edges[i].clear();
        }
        for (int i = 1, c1, c2, d; i <= R; i++)
        {
            cin >> c1 >> c2 >> d;
            edges[c1].push_back(edge(c2, d));
            edges[c2].push_back(edge(c1, d));
        }

        if (cases++) cout << '\n';
        cout << "Case #" << cases << '\n';
        for (int i = 1, c1, c2; i <= Q; i++)
        {
            cin >> c1 >> c2;
            memset(F, INF, sizeof(F));
            queue<walk> q;
            q.push(walk(c1, 0, hosting[c1]));
            while (!q.empty())
            {
                walk w = q.front(); q.pop();
                if (F[w.v] > w.fee + w.costliest)
                {
                    F[w.v] = w.fee + w.costliest;
                    for (auto e : edges[w.v])
                        q.push(walk(e.v, w.fee + e.d, max(hosting[e.v], w.costliest)));
                }
            }
            cout << (F[c2] < INF ? F[c2] : -1) << '\n';
        }
    }

    return 0;
}
