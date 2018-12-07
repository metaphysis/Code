// Against Mammoths
// UVa ID: 1221
// Verdict: Accepted
// Submission Date: 2018-12-07
// UVa Run Time: 0.330s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// Human planets are NOT needed to leave for allien planets at the same time.

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 256, INF = 0x3f3f3f3f;

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

int H, A, Hn[256], Hm[256], An[256], Am[256], years[256][256];

void build(int Y)
{
    memset(g, 0, sizeof(g));
    for (int i = 0; i < H; i++)
        for (int j = 0; j < A; j++)
            g[i][j] = (Y >= years[i][j]);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> H >> A)
    {
        if (H == 0) break;
        tx = H, ty = A;
        for (int i = 0; i < H; i++) cin >> Hn[i] >> Hm[i];
        for (int i = 0; i < A; i++) cin >> An[i] >> Am[i];
        int year;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < A; j++)
            {
                cin >> year;
                if (Hm[i] <= Am[j]) years[i][j] = ((Hn[i] >= (An[j] + year * Am[j])) ? year : INF);
                else years[i][j] = year + ((An[j] - Hn[i] + year * Am[j]) + ((Hm[i] - Am[j]) - 1)) / (Hm[i] - Am[j]);
            }
        int lowY = 0, highY = INF, Y = (lowY + highY) >> 1;
        build(Y);
        if (hungarian() < A)
        {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        while (lowY <= highY)
        {
            Y = (lowY + highY) >> 1;
            build(Y);
            if (hungarian() == A) highY = Y - 1;
            else lowY = Y + 1;
        }
        cout << lowY << '\n';
    }
    
    return 0;
}
