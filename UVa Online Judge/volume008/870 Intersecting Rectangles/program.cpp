// Intersecting Rectangles
// UVa ID: 870
// Verdict: Accepted
// Submission Date: 2018-12-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;

int n, g[210][210] = {}, area;
int xx1[MAXV], yy1[MAXV], xx2[MAXV], yy2[MAXV], visited[210][210];
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector<int> xs, ys;

void dfs(int i, int j)
{
    visited[i][j] = 1;
    if (g[i][j]) area += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
    for (int k = 0; k < 4; k++)
    {
        int nexti = i + offset[k][0], nextj = j + offset[k][1];
        if (nexti < 0 || nexti > 209 || nextj < 0 || nextj > 209) continue;
        if (visited[nexti][nextj]) continue;
        if (!g[nexti][nextj]) continue;
        dfs(nexti, nextj);
    }
}

int main(int argc, char *argv[])
{
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        xs.clear(), ys.clear();
        for (int i = 0; i < n; i++)
        {
            cin >> xx1[i] >> yy1[i];
            cin >> xx2[i] >> yy2[i];
            xs.push_back(xx1[i]); xs.push_back(xx2[i]);
            ys.push_back(yy1[i]); ys.push_back(yy2[i]);
        }

        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());

        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        for (int i = 0; i < n; i++)
        {
            xx1[i] = lower_bound(xs.begin(), xs.end(), xx1[i]) - xs.begin();
            xx2[i] = lower_bound(xs.begin(), xs.end(), xx2[i]) - xs.begin();
            yy1[i] = lower_bound(ys.begin(), ys.end(), yy1[i]) - ys.begin();
            yy2[i] = lower_bound(ys.begin(), ys.end(), yy2[i]) - ys.begin();
        }

        memset(g, 0, sizeof(g));
        for (int c = 0; c < n; c++)
            for (int i = xx1[c]; i < xx2[c]; i++)
                for (int j = yy1[c]; j < yy2[c]; j++)
                        g[i][j] = 1;

        area = 0;
        memset(visited, 0, sizeof(visited));
        dfs(xx1[0], yy1[0]);

        if (cs > 1) cout << '\n';
        cout << area << '\n';
    }

    return 0;
}
