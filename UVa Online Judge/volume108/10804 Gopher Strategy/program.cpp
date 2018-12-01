// Gopher Strategy
// UVa ID: 10804
// Verdict: Accepted
// Submission Date: 2018-12-01
// UVa Run Time: 0.470s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
} ps[110];

const int MAXV = 110;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], tx, ty;

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

double getDist(point &p1, point &p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void build(double S, int M, int N)
{
    memset(g, 0, sizeof(g));
    for (int i = 0; i < M; i++)
        for (int j = M; j < M + N; j++)
            if (getDist(ps[i], ps[j]) <= S * S)
                g[i][j] = 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, M, N, K;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cout << "Case #" << t << ":\n";
        cin >> M >> N >> K;
        for (int i = 0; i < M; i++)
            cin >> ps[i].x >> ps[i].y;
        for (int i = 0; i < N; i++)  
            cin >> ps[i + M].x >> ps[i + M].y;

        double lowS = 0.0, highS = 1e10;
        tx = ty = M + N;
        build(highS, M, N);
        if (hungarian() < (M - K))
        {
            cout << "Too bad.\n\n";
            continue;
        }
        double lastS = 0.0, S = highS;
        while (fabs(lastS - S) > 1e-8)
        {
            lastS = S;
            S = (lowS + highS) / 2.0;
            build(S, M, N);
            if (hungarian() >= (M - K)) highS = S;
            else lowS = S;
        }
        cout << fixed << setprecision(3) << lowS << "\n\n";
    }

    return 0;
}
