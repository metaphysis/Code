// Distant Galaxy
// UVa ID: 
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    bool operator<(const point &p) const
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
} ps[110];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    int grid[110][110], planetLeft[110][110], planetBelow[110][110];

    while (cin >> n, n > 0)
    {
        vector<int> xs, ys;
        for (int i = 0; i < n; i++)
        {
            cin >> ps[i].x >> ps[i].y;
            xs.push_back(ps[i].x);
            ys.push_back(ps[i].y);
        }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        
        memset(grid, 0, sizeof(grid));
        for (int i = 0; i < n; i++)
        {
            int ux = lower_bound(xs.begin(), xs.end(), ps[i].x) - xs.begin();
            int uy = lower_bound(ys.begin(), ys.end(), ps[i].y) - ys.begin();
            grid[ux][uy]++;
        }
        
        memset(planetLeft, 0, sizeof(planetLeft));
        memset(planetBelow, 0, sizeof(planetBelow));
        
        for (int i = 0; i < xs.size(); i++)
        {
            planetBelow[i][0] = grid[i][0];
            for (int j = 1; j < ys.size(); j++)
                planetBelow[i][j] = planetBelow[i][j - 1] + grid[i][j];
        }
        
        for (int j = 0; j < ys.size(); j++)
        {
            planetLeft[0][j] = grid[0][j];
            for (int i = 1; i < xs.size(); i++)
                planetLeft[i][j] = planetLeft[i - 1][j] + grid[i][j];
        }

        sort(ps, ps + n);

        int stars = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                int ux = lower_bound(xs.begin(), xs.end(), ps[i].x) - xs.begin();
                int uy = lower_bound(ys.begin(), ys.end(), ps[i].y) - ys.begin();
                int vx = lower_bound(xs.begin(), xs.end(), ps[j].x) - xs.begin();
                int vy = lower_bound(ys.begin(), ys.end(), ps[j].y) - ys.begin();
                int edge = 0;
                edge += planetLeft[vx][uy] - planetLeft[ux][uy] + grid[ux][uy];
                edge += planetLeft[vx][vy] - planetLeft[ux][vy] + grid[ux][vy];
                edge += planetBelow[vx][vy] - planetBelow[vx][uy];
                edge += planetBelow[ux][vy] - planetBelow[ux][uy];
                stars = max(stars, edge);
            }
        cout << "Case " << ++cases << ": " << stars << '\n';
    }

    return 0;
}
