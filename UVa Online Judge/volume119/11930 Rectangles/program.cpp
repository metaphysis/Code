// Rectangles
// UVa ID: 11930
// Verdict: Accepted
// Submission Date: 2019-04-09
// UVa Run Time: 0.270s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 2010;

struct point
{
    long long x, y;
    point (long long x = 0, long long y = 0): x(x), y(y) {}
    bool operator<(const point &p) const
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
};

int cp(point a, point b, point c)
{
    long long r = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return r == 0 ? r : (r > 0 ? 1 : -1);
}

bool pointInBox(point a, point b, point p)
{
    return (p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x)) &&
        (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y));
}

struct segment
{
    point p1, p2;
    segment (point p1 = point(0, 0), point p2 = point(0, 0)): p1(p1), p2(p2) {}
    bool contains(const point &p) { return pointInBox(p1, p2, p); }
};

bool isIntersected(segment s1, segment s2)
{
    int cp1 = cp(s1.p1, s1.p2, s2.p1), cp2 = cp(s1.p1, s1.p2, s2.p2);
    int cp3 = cp(s2.p1, s2.p2, s1.p1), cp4 = cp(s2.p1, s2.p2, s1.p2);

    if ((cp1 * cp2 < 0) && (cp3 * cp4) < 0) return true;
    if (cp1 == 0 && s1.contains(s2.p1)) return true;
    if (cp2 == 0 && s1.contains(s2.p2)) return true;
    if (cp3 == 0 && s2.contains(s1.p1)) return true;
    if (cp4 == 0 && s2.contains(s1.p2)) return true;

    return false;
}

int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
vector<list<int>> g(MAXV);
stack<int> s;

void dfs(int u)
{
    dfn[u] = low[u] = ++dfstime; s.push(u);
    for (auto v : g[u])
    {
        if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++cscc;
        while (true)
        {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
    }
}

void tarjan(int n)
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    memset(dfn, 0, sizeof(dfn));
    memset(scc, 0, sizeof(scc));
    for (int i = 0; i < n; i++)
        if (!dfn[i])
            dfs(i);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    point ps[MAXV][4];
    while (cin >> n, n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 4; j++)
                cin >> ps[i][j].x >> ps[i][j].y;
            sort(ps[i], ps[i] + 4);
        }
        
        for (int i = 0; i < 2 * n; i++) g[i].clear();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (isIntersected(segment(ps[i][1], ps[i][2]), segment(ps[j][1], ps[j][2])))
                {
                    g[2 * i].push_back(2 * j + 1);
                    g[2 * j].push_back(2 * i + 1);
                }
                if (isIntersected(segment(ps[i][1], ps[i][2]), segment(ps[j][0], ps[j][3])))
                {
                    g[2 * i].push_back(2 * j);
                    g[2 * j + 1].push_back(2 * i + 1);
                }
                if (isIntersected(segment(ps[i][0], ps[i][3]), segment(ps[j][1], ps[j][2])))
                {
                    g[2 * i + 1].push_back(2 * j + 1);
                    g[2 * j].push_back(2 * i);
                }
                if (isIntersected(segment(ps[i][0], ps[i][3]), segment(ps[j][0], ps[j][3])))
                {
                    g[2 * i + 1].push_back(2 * j);
                    g[2 * j + 1].push_back(2 * i);
                }
            }
        }

        tarjan(2 * n);

        bool flag = true;
        for (int i = 0; i < 2 * n && flag; i += 2)
            if (scc[i] == scc[i + 1])
                flag = false;
        cout << (flag ? "YES" : "NO") << '\n';
    }

    return 0;
}
