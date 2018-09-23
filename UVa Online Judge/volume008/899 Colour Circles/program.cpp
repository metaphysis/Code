// Colour Circles
// UVa ID: 899
// Verdict: Accepted
// Submission Date: 2018-09-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int to, color;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<edge> edges[101];
    int circle[101];
    int N, R, S, T, M;
    int visited[101][101];

    while (cin >> N >> R >> S >> T >> M)
    {
        if (N == 0) break;
        for (int i = 1; i <= N; i++)
            edges[i].clear();
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= N; i++)
            cin >> circle[i];
        int x, y, c;
        for (int i = 1; i <= M; i++)
        {
            cin >> x >> y >> c;
            edges[x].push_back(edge{y, c});
        }

        queue<int> X, Y, C;
        X.push(R);
        Y.push(S);
        C.push(0);
        visited[R][S] = 1;
        int r = 0;

        while (!X.empty())
        {
            x = X.front(); X.pop();
            y = Y.front(); Y.pop();
            c = C.front(); C.pop();
            if (x == T || y == T)
            {
                r = c;
                break;
            }
            
            // Move x.
            for (auto e : edges[x])
            {
                if (e.to == y) continue;
                if (e.color != circle[y]) continue;
                if (visited[e.to][y]) continue;
                visited[e.to][y] = 1;
                X.push(e.to);
                Y.push(y);
                C.push(c + 1);
            }
            
            // Move y.
            for (auto e : edges[y])
            {
                if (e.to == x) continue;
                if (e.color != circle[x]) continue;
                if (visited[x][e.to]) continue;
                visited[x][e.to] = 1;
                X.push(x);
                Y.push(e.to);
                C.push(c + 1);
            }
        }
        cout << r << '\n';
    }
    
    return 0;
}
