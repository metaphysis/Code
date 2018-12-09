// Factory Robot
// UVa ID: 10876
// Verdict: Accepted
// Submission Date: 2018-12-08
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

int n, visited[210];
list<int> edges[210];
double x[210], y[210], r[210];

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
}

bool satisfy(double mid)
{
    for (int i = 0; i < n + 4; i++) edges[i].clear();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
            if (sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2)) - r[i] - r[j] + EPSILON < mid)
            {
                edges[i + 4].push_back(j + 4);
                edges[j + 4].push_back(i + 4);
            }
        if (1000 - y[i] - r[i] + EPSILON < mid)
        {
            edges[0].push_back(i + 4);
            edges[i + 4].push_back(0);
        }
        if (x[i] - r[i] + EPSILON < mid)
        {
            edges[1].push_back(i + 4);
            edges[i + 4].push_back(1);
        }
        if (y[i] - r[i] + EPSILON < mid)
        {
            edges[2].push_back(i + 4);
            edges[i + 4].push_back(2);
        }
        if (1000 - x[i] - r[i] + EPSILON < mid)
        {
            edges[3].push_back(i + 4);
            edges[i + 4].push_back(3);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        memset(visited, 0, sizeof(visited));
        dfs(i);
        for (int j = 0; j < 4; j++)
            if (i != j && visited[j])
                return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
 
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> x[i] >> y[i] >> r[i];
        double low = 0, high = 1000, mid;
        while (fabs(high - low) > EPSILON)
        {
            mid = (low + high) / 2;
            if (satisfy(mid)) low = mid;
            else high = mid;
        }
        cout << fixed << setprecision(3) << (mid / 2) << '\n';
    }

    return 0;
}
