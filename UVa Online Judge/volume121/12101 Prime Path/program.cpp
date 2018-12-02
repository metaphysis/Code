// Prime Path
// UVa ID: 12101
// Verdict: Accepted
// Submission Date: 2018-12-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000;

inline bool likely(int a, int b)
{
    int diff = 0;
    while (a)
    {
        if ((a % 10) != (b % 10)) diff++;
        if (diff > 1) break;
        a /= 10, b /= 10;
    }
    return diff == 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[MAXN] = {}, cnt = 0;
    int node[MAXN], n = 0;

    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) 
        {
            primes[cnt++] = i;
            if (i > 1000) node[n++] = i;
        }
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (!(i % primes[j])) break;
        }
    }
    
    list<int> edges[n];
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (likely(node[i], node[j]))
            {
                edges[i].push_back(j);
                edges[j].push_back(i);
            }
    int visited[n] = {};
    int T, start, end;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> start >> end;
        int s = find(node, node + n, start) - node;
        int e = find(node, node + n, end) - node;
        queue<int> q, d;
        q.push(s), d.push(0);
        memset(visited, 0, sizeof(visited));
        visited[s] = 1;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            int pound = d.front(); d.pop();
            if (u == e)
            {
                cout << pound << '\n';
                break;
            }
            for (auto v : edges[u])
                if (!visited[v])
                {
                    visited[v] = 1;
                    q.push(v);
                    d.push(pound + 1);
                }
        }
    }

    return 0;
}
