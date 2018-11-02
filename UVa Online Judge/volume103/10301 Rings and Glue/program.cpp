// Rings and Glue
// UVa ID: 10301
// Verdict: Accepted
// Submission Date: 2018-11-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-6;
struct circle
{
    double x, y, r;
} circles[101];

int n, visited[101], guled[101][101], C;

void dfs(int u)
{
    C++;
    visited[u] = 1;
    for (int v = 0; v < n; v++)
        if (guled[u][v] && !visited[v])
            dfs(v);
}

bool isGuled(int i, int j)
{
    double dist1 = pow(circles[i].x - circles[j].x, 2) + pow(circles[i].y - circles[j].y, 2);
    double dist2 = pow(circles[i].r + circles[j].r, 2);
    double dist3 = pow(circles[i].r - circles[j].r, 2);
    return dist1 <= dist2 && dist1 >= dist3;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n >= 0)
    {
        for (int i = 0; i < n; i++)
            cin >> circles[i].x >> circles[i].y >> circles[i].r;
        memset(guled, 0, sizeof(guled));
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (isGuled(i, j))
                    guled[i][j] = guled[j][i] = 1;
        int maxCircles = 0;
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < n; i++)
            if (!visited[i])
            {
                C = 0;
                dfs(i);
                maxCircles = max(maxCircles, C);
            }
        cout << "The largest component contains " << maxCircles << " ring";
        if (maxCircles != 1) cout << 's';
        cout << ".\n";
    }

    return 0;
}
