// Skyscraper Floors
// UVa ID: 718
// Verdict: Accepted
// Submission Date: 2018-12-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void extgcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0) x = 1, y = 0;
    else
    {
        extgcd(b, a % b, x, y);
        long long t = x - a / b * y;
        x = y, y = t;
    }
}

int visited[110];
list<int> edges[110];

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, E;
    long long F, A, B, X[110], Y[110];
    cin >> N;
    for (int cs = 1; cs <= N; cs++)
    {
        // Read input.
        cin >> F >> E >> A >> B;
        for (int i = 0; i < E; i++) cin >> X[i] >> Y[i];

        // Build directed graph.
        for (int i = 0; i < E + 2; i++) edges[i].clear();
        // The index of A is E.
        for (int i = 0; i < E; i++)
        {
            if (Y[i] > A) continue;
            if ((A - Y[i]) % X[i] == 0) 
            {
                edges[i].push_back(E);
                edges[E].push_back(i);
            }
        }
        // The index of B is E + 1.
        for (int i = 0; i < E; i++)
        {
            if (Y[i] > B) continue;
            if ((B - Y[i]) % X[i] == 0)
            {
                edges[i].push_back(E + 1);
                edges[E + 1].push_back(i);
            }
        }
        // From one elevator to another.
        for (int i = 0; i < E; i++)
            for (int j = 0; j < E; j++)
            {
                if (j == i || Y[i] >= F || Y[j] >= F) continue;
                // Find the solution of a + bx = c + dy.
                long long a = Y[i], b = X[i], c = Y[j], d = X[j], x, y;
                // No solution.
                if ((c - a) % __gcd(b, d) != 0) continue;
                // Find solution by extended Euclid algorithm.
                extgcd(b, d, x, y);
                x *= ((c - a) / __gcd(b, d));
                if (x < 0) x += (-x / d + ((-x) % d != 0)) * d;
                // Get the lowest floor reachable by elevator i and j.
                long long L = a + b * x;
                if (L < c) L += ((c - L) / d + ((c - L) % d != 0)) * d;
                // Make sure the lowest floor reachable is not bigger than F.
                if (L >= F) continue;
                edges[i].push_back(j);
                edges[j].push_back(i);
            }

        // DFS.
        memset(visited, 0, sizeof(visited));
        dfs(E);
        if (visited[E + 1]) cout << "It is possible to move the furniture.\n";
        else cout << "The furniture cannot be moved.\n";
    }

    return 0;
}
