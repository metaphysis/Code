// Number Transformation
// UVa ID: 11730
// Verdict: Accepted
// Submission Date: 2018-12-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1024;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[MAXN] = {}, cnt = 0;
    list<int> edges[MAXN];
    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        else
        {
            int n = i;
            for (int j = 0; j < cnt && n > 1; j++)
                if (n % primes[j] == 0)
                {
                    edges[i].push_back(i + primes[j]);
                    while (n % primes[j] == 0)
                        n /= primes[j];
                }
        }
        for (int j = i; j < MAXN; j += i) primes[j] = 1;
    }

    int cases = 0, S, T, visited[MAXN << 1] = {};
    while (cin >> S >> T)
    {
        if (S == 0) break;
        cout << "Case " << ++cases << ": ";
        bool impossible = true;
        if (S <= T)
        {
            queue<int> q, p;
            q.push(S);
            p.push(0);
            memset(visited, 0, sizeof(visited));
            visited[S] = 1;
            while (!q.empty())
            {
                int u = q.front(); q.pop();
                int m = p.front(); p.pop();
                if (u == T)
                {
                    cout << m << '\n';
                    impossible = false;
                    break;
                }
                for (auto v : edges[u])
                    if (!visited[v] && v <= T)
                    {
                        visited[v] = 1;
                        q.push(v);
                        p.push(m + 1);
                    }
            }
        }
        if (impossible) cout << "-1\n";
    }
    return 0;
}
