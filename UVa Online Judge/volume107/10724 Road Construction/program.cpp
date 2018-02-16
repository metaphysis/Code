// Road Construction
// UVa ID: 10724
// Verdict: Accepted
// Submission Date: 2018-02-16
// UVa Run Time: 1.930s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct point
{
    double x, y;
    double distTo(point &p) { return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2)); }
} ps[64];

int n, m, linked[64][64];
double dist1[64][64], dist2[64][64], dist3[64][64];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v;
    while (cin >> n >> m, n > 0)
    {
        memset(linked, 0, sizeof(linked));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                dist1[i][j] = 1e10;
            dist1[i][i] = 0;
        }
        for (int i = 1; i <= n; i++)
            cin >> ps[i].x >> ps[i].y;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v;
            linked[u][v] = linked[v][u] = 1;
            dist1[u][v] = dist1[v][u] = ps[u].distTo(ps[v]);
        }

        memcpy(dist2, dist1, sizeof(dist1));
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    dist2[i][j] = min(dist2[i][j], dist2[i][k] + dist2[k][j]);
        double Cuv = -1e10;
        u = v = -1;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
            {
                if (linked[i][j]) continue;
                memcpy(dist3, dist1, sizeof(dist1));
                dist3[i][j] = dist3[j][i] = ps[i].distTo(ps[j]);
                for (int k = 1; k <= n; k++)
                    for (int i = 1; i <= n; i++)
                        for (int j = 1; j <= n; j++)
                            if (dist3[i][j] > dist3[i][k] + dist3[k][j])
                                dist3[i][j] = dist3[i][k] + dist3[k][j];
                double Cc = 0.0;
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        Cc += dist2[i][j] - dist3[i][j];
                if (Cc > Cuv)
                {
                    u = i, v = j;
                    Cuv = max(Cuv, Cc);
                }
                else if (fabs(Cc - Cuv) < 1e-7)
                {
                    if (ps[u].distTo(ps[v]) > ps[i].distTo(ps[j]))
                    {
                        u = i, v = j;
                    }
                }
            }
        if (Cuv <= 1.0) cout << "No road required\n";
        else cout << u << ' ' << v << '\n';
    }

    return 0;
}
