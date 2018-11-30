// Galactic Bonding
// UVa ID: 11966
// Verdict: Accepted
// Submission Date: 2018-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    long long x, y;
    point (long long x = 0, long long y = 0): x(x), y(y) {}
} ps[1001];

long long getInt(string s)
{
    long long sign = 1;
    if (s.front() == '-')
    {
        sign = -1;
        s.erase(s.begin());
    }
    long long n = 0, dot = 0, decimal = 1;
    for (auto c : s)
    {
        if (dot) decimal *= 10;
        if (isdigit(c)) n = n * 10 + c - '0';
        else dot++;
    }
    return n * (100LL / decimal) * sign;
};

inline long long getDist(point &p1, point &p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

list<int> edges[1001];
int visited[1001];

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N;
    string x, y, d;

    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N >> d;
        for (int i = 0; i < N; i++) edges[i].clear();
        long long D = getInt(d);
        for (int i = 0; i < N; i++)
        {
            cin >> x >> y;
            ps[i] = point(getInt(x), getInt(y));
        }

        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                if (getDist(ps[i], ps[j]) <= D * D)
                {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }

        int cnt = 0;
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < N; i++)
        {
            if (visited[i]) continue;
            cnt++;
            dfs(i);
        }
        cout << "Case " << cs << ": " << cnt << '\n';
    }

    return 0;
}
