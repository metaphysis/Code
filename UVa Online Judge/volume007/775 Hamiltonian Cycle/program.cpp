// Hamiltonian Cycle
// UVa ID: 775
// Verdict: Accepted
// Submission Date: 2017-11-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 300;
list<int> edges[MAXV];
int visited[MAXV], cycle[MAXV], n, finished;

void dfs(int u, int depth)
{
    if (finished) return;
    if (depth == n)
    {
        for (auto v : edges[u])
            if (v == 1)
            {
                finished = true;
                break;
            }
        return;
    }
    
    for (auto v : edges[u])
        if (!visited[v])
        {
            visited[v] = 1;
            cycle[depth] = v;
            dfs(v, depth + 1);
            if (finished) return;
            visited[v] = 0;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n)
    {
        for (int i = 1; i <= n; i++) edges[i].clear();

        string si;
        int ni, nj;
        while (cin >> si, si != "%")
        {
            ni = 0;
            for (int i = 0; i < si.length(); i++)
                ni = ni * 10 + si[i] - '0';
            cin >> nj;
            edges[ni].push_back(nj);
            edges[nj].push_back(ni);
        }
        
        if (n == 1) { cout << "N\n"; continue; }

        finished = 0;
        memset(visited, 0, sizeof(visited));
        cycle[0] = 1, visited[1] = 1;
        dfs(1, 1);
        
        if (finished)
        {
            for (int i = 0; i < n; i++)
                cout << cycle[i] << ' ';
            cout << 1 << '\n';
        }
    }

    return 0;
}
