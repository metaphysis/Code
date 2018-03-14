// The Party, Part I
// UVa ID: 10959
// Verdict: Accepted
// Submission Date: 2018-02-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, P, D, number[1010];
    list<int> edges[1010];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> P >> D;
        for (int i = 0; i < P; i++)
            edges[i].clear();
        int p1, p2;
        for (int i = 0; i < D; i++)
        {
            cin >> p1 >> p2;
            edges[p1].push_back(p2);
            edges[p2].push_back(p1);
        }
        memset(number, -1, sizeof(number));
        queue<int> q;
        q.push(0);
        number[0] = 0;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (auto v : edges[u])
                if (number[v] < 0)
                {
                    number[v] = number[u] + 1;
                    q.push(v);
                }
        }
        if (c > 1) cout << '\n';
        for (int i = 1; i < P; i++)
            cout << number[i] << '\n';
    }

    return 0;
}
