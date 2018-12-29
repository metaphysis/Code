// Sculpture
// UVa ID: 12171
// Verdict: Accepted
// Submission Date: 2018-12-29
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n;
int xx1[128], yy1[128], zz1[128], xx2[128], yy2[128], zz2[128], X, Y, Z;
int g[128][128][128];
int offset[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
vector<int> xs, ys, zs;

struct point
{
    int x, y, z;
    point (int x = 0, int y = 0, int z = 0): x(x), y(y), z(z) {}
};

void bfs()
{
    queue<point> q;
    q.push(point(0, 0, 0));
    g[0][0][0] = 2;
    while (!q.empty())
    {
        point p = q.front(); q.pop();
        for (int d = 0; d < 6; d++)
        {
            static int ii, jj, kk;
            ii = p.x + offset[d][0], jj = p.y + offset[d][1], kk = p.z + offset[d][2];
            if (ii < 0 || ii >= X) continue;
            if (jj < 0 || jj >= Y) continue;
            if (kk < 0 || kk >= Z) continue;
            if (g[ii][jj][kk]) continue;
            g[ii][jj][kk] = 2;
            q.push(point(ii, jj, kk));
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;

        xs.clear(), ys.clear(), zs.clear();

        xx1[0] = yy1[0] = zz1[0] = 0;
        xx2[0] = yy2[0] = zz2[0] = 1024;
        xs.push_back(xx1[0]); xs.push_back(xx2[0]);
        ys.push_back(yy1[0]); ys.push_back(yy2[0]);
        zs.push_back(zz1[0]); zs.push_back(zz2[0]);

        for (int i = 1, L, W, H; i <= n; i++)
        {
            cin >> xx1[i] >> yy1[i] >> zz1[i];
            cin >> L >> W >> H;
            xx2[i] = xx1[i] + L, yy2[i] = yy1[i] + W, zz2[i] = zz1[i] + H;
            xs.push_back(xx1[i]); xs.push_back(xx2[i]);
            ys.push_back(yy1[i]); ys.push_back(yy2[i]);
            zs.push_back(zz1[i]); zs.push_back(zz2[i]);
        }

        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        sort(zs.begin(), zs.end());

        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        zs.erase(unique(zs.begin(), zs.end()), zs.end());

        X = xs.size(), Y = ys.size(), Z = zs.size();

        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                for (int k = 0; k < Z; k++)
                    g[i][j][k] = 0;

        for (int i = 1; i <= n; i++)
        {
            int sx = lower_bound(xs.begin(), xs.end(), xx1[i]) - xs.begin();
            int ex = lower_bound(xs.begin(), xs.end(), xx2[i]) - xs.begin();
            int sy = lower_bound(ys.begin(), ys.end(), yy1[i]) - ys.begin();
            int ey = lower_bound(ys.begin(), ys.end(), yy2[i]) - ys.begin();
            int sz = lower_bound(zs.begin(), zs.end(), zz1[i]) - zs.begin();
            int ez = lower_bound(zs.begin(), zs.end(), zz2[i]) - zs.begin();
            
            for (int i = sx; i < ex; i++)
                for (int j = sy; j < ey; j++)
                    for (int k = sz; k < ez; k++)
                        g[i][j][k] = 1;
        }

        bfs();

        int area = 0, volume = 0;
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                for (int k = 0; k < Z; k++)
                {
                    if (g[i][j][k] <= 1)
                        volume += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]) * (zs[k + 1] - zs[k]);
                    if (g[i][j][k] == 1)
                    {
                        for (int d = 0; d < 6; d++)
                            if (g[i + offset[d][0]][j + offset[d][1]][k + offset[d][2]] == 2)
                            {
                                if (d >= 4) area += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
                                else
                                {
                                    if (d >= 2)
                                        area += (xs[i + 1] - xs[i]) * (zs[k + 1] - zs[k]);
                                    else
                                        area += (ys[j + 1] - ys[j]) * (zs[k + 1] - zs[k]);
                                }
                            }
                    }
                }    

        cout << area << ' ' << volume << '\n';
    }

    return 0;
}
