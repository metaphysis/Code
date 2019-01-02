// Tracking Bio-Bots
// UVa ID: 1092
// Verdict: Accepted
// Submission Date: 2019-01-02
// UVa Run Time: 0.370s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int grid[2048][2048];
 
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int w, offset[2][2] = {{0, -1}, {-1, 0}};
    long long m, n, x1[1024], y1[1024], x2[1024], y2[1024];

    while (cin >> m >> n >> w)
    {
        if (m == 0) break;
        vector<long long> xs, ys;
        long long blocks = 0;
        for (int i = 1; i <= w; i++)
        {
            cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
            x2[i] += 1, y2[i] += 1;
            blocks += (x2[i] - x1[i]) * (y2[i] - y1[i]);
            xs.push_back(x1[i]), xs.push_back(x2[i]);
            ys.push_back(y1[i]), ys.push_back(y2[i]);
        }
        
        x1[0] = y1[0] = 0, x2[0] = y2[0] = 1;
        x1[w + 1] = n - 1, x2[w + 1] = n, y1[w + 1] = m - 1, y2[w + 1] = m;
        
        xs.push_back(0), xs.push_back(1), xs.push_back(n - 1), xs.push_back(n);
        ys.push_back(0), ys.push_back(1), ys.push_back(m - 1), ys.push_back(m);
        
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        for (int i = 0; i < xs.size(); i++)
            for (int j = 0; j < ys.size(); j++)
                grid[i][j] = 0;

        for (int c = 1; c <= w; c++)
        {
            int s1 = lower_bound(xs.begin(), xs.end(), x1[c]) - xs.begin();
            int e1 = lower_bound(ys.begin(), ys.end(), y1[c]) - ys.begin();
            int s2 = lower_bound(xs.begin(), xs.end(), x2[c]) - xs.begin();
            int e2 = lower_bound(ys.begin(), ys.end(), y2[c]) - ys.begin();

            for (int i = s1; i < s2; i++)
                for (int j = e1; j < e2; j++)
                    grid[i][j] = 1;
        }

        long long visited = 0;
        int ex = lower_bound(xs.begin(), xs.end(), n - 1) - xs.begin();
        int ey = lower_bound(ys.begin(), ys.end(), m - 1) - ys.begin();
        int nextx, nexty;
        if (grid[ex][ey] != 1)
        {
            queue<int> qx, qy;
            qx.push(ex), qy.push(ey);
            visited = 1;
            while (!qx.empty())
            {
                ex = qx.front(); qx.pop();
                ey = qy.front(); qy.pop();
                for (int k = 0; k < 2; k++)
                {
                    nextx = ex + offset[k][0], nexty = ey + offset[k][1];
                    if (nextx < 0 || nexty < 0) continue;
                    if (grid[nextx][nexty]) continue;
                    visited += (xs[nextx + 1] - xs[nextx]) * (ys[nexty + 1] - ys[nexty]);
                    grid[nextx][nexty] = 1;
                    qx.push(nextx), qy.push(nexty);
                }
            }
        }

        cout << "Case " << ++cases << ": " << (n * m - blocks - visited) << '\n';
    }

    return 0;
}
