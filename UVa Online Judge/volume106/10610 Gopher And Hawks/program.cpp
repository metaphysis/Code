// Gopher And Hawks
// UVa ID: 10610
// Verdict: Accepted
// Submission Date: 2018-02-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;
const double EPSILON = 1e-7;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int v, m;
    double x[MAXV], y[MAXV], xi, yi, visited[MAXV], jumps[MAXV];
    list<int> edges[MAXV];
    string line;

    while (cin >> v >> m, v > 0)
    {
        for (int i = 0; i < MAXV; i++)
            edges[i].clear();

        cin.ignore(1024, '\n');
        int cnt = 0;
        while (getline(cin, line), line.length() > 0)
        {
            istringstream iss(line);
            iss >> xi >> yi;
            x[cnt] = xi, y[cnt] = yi;
            cnt++;
        }

        double maxDist = (v * m * 60.0) * (v * m * 60.0);
        for (int i = 0; i < cnt; i++)
        {
            for (int j = i + 1; j < cnt; j++)
            {
                double dist = pow(x[j] - x[i], 2) + pow(y[j] - y[i], 2);
                if (maxDist >= dist)
                {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
            }
        }
        
        if (fabs(pow(x[1] - x[0], 2) + pow(y[1] - y[0], 2)) < EPSILON)
        {
            cout << "Yes, visiting 0 other holes.";
            continue;
        }

        memset(visited, 0, sizeof(visited));
        queue<int> q;
        q.push(0);
        visited[0] = 1;
        jumps[0] = 0;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (auto v : edges[u])
                if (!visited[v])
                {
                    jumps[v] = jumps[u] + 1;
                    visited[v] = 1;
                    q.push(v);
                }
        }

        if (visited[1]) cout << "Yes, visiting " << (jumps[1] - 1) << " other holes.\n";
        else cout << "No.\n";
    }

    return 0;
}
