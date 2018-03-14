// The Bug Sensor Problem
// UVa ID: 1216
// Verdict: Accepted
// Submission Date: 2018-02-05
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;

int parent[MAXV], ranks[MAXV];

struct edge
{
    int from, to;
    long long cost;
    edge (long long from = 0, int to = 0, long long cost = 0): from(from), to(to), cost(cost) {};
    bool operator<(const edge &e) const { return cost < e.cost; }
} edges[1000010];

void makeSet()
{
    for (int i = 0; i < MAXV; i++) parent[i] = i, ranks[i] = 0;
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    if (x != y)
    {
        if (ranks[x] > ranks[y]) parent[y] = x, ranks[x]++;
        else parent[x] = y, ranks[y]++;
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, rt, n, m, x, y;
    long long xs[MAXV], ys[MAXV];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> rt;
        n = 0;
        while (cin >> x, x >= 0)
        {
            cin >> y;
            xs[n] = x, ys[n] = y;
            n++;
        }
        m = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                edges[m++] = edge(i, j, (xs[i] - xs[j]) * (xs[i] - xs[j]) + (ys[i] - ys[j]) * (ys[i] - ys[j]));

        sort(edges, edges + m);

        long long left = 0, right = 2 * 100000LL * 100000LL, middle;
        while (left <= right)
        {
            middle = (left + right) / 2;

            makeSet();
            int merged = 0;
            for (int i = 0; i < m; i++)
            {
                if (edges[i].cost <= middle)
                {
                    if (unionSet(edges[i].from, edges[i].to))
                    {
                        merged++;
                    }
                }
                else break;
            }
            if (n - merged <= rt)
                right = middle - 1;
            else
                left = middle + 1;
        }
        cout << (int)ceil(sqrt(left)) << '\n';
    }

    return 0;
}
