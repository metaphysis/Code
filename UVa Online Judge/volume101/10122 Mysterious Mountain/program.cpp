// Mysterious Mountain
// UVa ID: 10122
// Verdict: Accepted
// Submission Date: 2019-07-06
// UVa Run Time: 1.210s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;

struct point {
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
} endpoints[MAXV];

struct person {
    int c, w, s;
} persons[MAXV];

int n;
int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], tx, ty;
vector<pair<int, double>> xCovered[MAXV];

int dfs(int u)
{
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v])
        {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))
            {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    return 0;
}

int hungarian()
{
    int matches = 0;
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    for (int i = 0; i < tx; i++)
        if (cx[i] == -1)
        {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

void build_bipartite_graph(double threshold)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            g[i][j] = 0;
            for (auto p : xCovered[j])
            {
                double t = 0;
                t += abs(persons[i].s - p.first) * 1.0 / persons[i].w;
                t += p.second / persons[i].c;
                if (t < threshold)
                {
                    g[i][j] = 1;
                    break;
                }
            }
        }
}

double binary_search()
{
    double low = 0, high = 2500, middle;
    while (fabs(low - high) > 1e-4)
    {
        middle = (low + high) / 2.0;
        build_bipartite_graph(middle);
        if (hungarian() == n) high = middle;
        else low = middle;
    }
    return middle;
}

int cp(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

double getDist(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void initialize()
{
    bool fail;
    int cp1, cp2;

    for (int i = 1; i <= n; i++)
    {
        xCovered[i - 1].clear();
        for (int x = endpoints[i].x - 1; x >= 0; x--)
        {
            fail = false;
            for (int j = i; j >= 1; j--)
            {
                cp1 = cp(point(x, 0), endpoints[i], endpoints[j]);
                cp2 = cp(point(x, 0), endpoints[i], endpoints[j - 1]);
                if (cp1 < 0 || cp2 < 0)
                {
                    fail = true;
                    break;
                }
                if (x >= endpoints[j - 1].x) break;
            }
            if (fail) break;
            xCovered[i - 1].push_back(make_pair(x, getDist(endpoints[i], point(x, 0))));
        }
        xCovered[i - 1].push_back(make_pair(endpoints[i].x, endpoints[i].y));
        for (int x = endpoints[i].x + 1; x <= 1000; x++)
        {
            fail = false;
            for (int j = i; j <= n; j++)
            {
                cp1 = cp(endpoints[i], point(x, 0), endpoints[j]);
                cp2 = cp(endpoints[i], point(x, 0), endpoints[j + 1]);
                if (cp1 < 0 || cp2 < 0)
                {
                    fail = true;
                    break;
                }
                if (x <= endpoints[j + 1].x) break;
            }
            if (fail) break;
            xCovered[i - 1].push_back(make_pair(x, getDist(endpoints[i], point(x, 0))));
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        tx = ty = n;
        for (int i = 0; i < n + 2; i++) cin >> endpoints[i].x >> endpoints[i].y;
        for (int i = 0; i < n; i++) cin >> persons[i].c >> persons[i].w >> persons[i].s;
        initialize();
        cout << fixed << setprecision(2) << binary_search() << '\n';
    }

    return 0;
}
