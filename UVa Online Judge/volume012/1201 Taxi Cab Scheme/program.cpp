// Taxi Cab Scheme
// UVa ID: 1201
// Verdict: Accepted
// Submission Date: 2018-04-24
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1024;

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

struct taxi
{
    int minutes, a, b, c, d;
} books[512];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int M;
        cin >> M;
        for (int i = 0; i < M; i++)
        {
            string time;
            int a, b, c, d;
            cin >> time;
            cin >> books[i].a >> books[i].b >> books[i].c >> books[i].d;
            books[i].minutes = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3));
        }
        
        tx = ty =  M;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                g[i][j] = 0;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
            {
                int endtime = books[i].minutes + abs(books[i].a - books[i].c) + abs(books[i].b - books[i].d);
                endtime += abs(books[i].c - books[j].a) + abs(books[i].d - books[j].b);
                if (endtime < books[j].minutes)
                    g[i][j] = 1;
            }        
                
        cout << M - hungarian() << '\n';
    }

    return 0;
}
