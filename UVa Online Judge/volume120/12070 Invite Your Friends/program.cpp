// Invite Your Friends
// UVa ID: 12070
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct walk
{
    int x, y, m, d;
    walk (int x = 0, int y = 0, int m = 0, int d = 0): x(x), y(y), m(m), d(d) {}
};

const int INF = 0x3f3f3f3f;

int N, F, T;
int cost[30][30], D[6][30][30], fx[6], fy[6];
int offset[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> N >> F >> T)
    {
        if (N == 0) break;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> cost[i][j];

        memset(D, INF, sizeof(D));
        for (int i = 0, x, y; i < F; i++)
        {
            cin >> fx[i] >> fy[i];
            queue<walk> q;
            q.push(walk(fx[i], fy[i], 0, 0));
            while (!q.empty())
            {
                walk w = q.front(); q.pop();
                if (w.d > T) continue;
                if (w.m + cost[w.x][w.y] < D[i][w.x][w.y])
                {
                    D[i][w.x][w.y] = w.m + cost[w.x][w.y];
                    for (int k = 0; k < 4; k++)
                    {
                        int nextx = w.x + offset[k][0], nexty = w.y + offset[k][1];
                        if (nextx < 0 || nextx >= N || nexty < 0 || nexty >= N) continue;
                        q.push(walk(nextx, nexty, D[i][w.x][w.y], w.d + 1));
                    }
                }
            }
        }

        int minimum = INF, tx, ty;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                int T = 0;
                for (int k = 0; k < F; k++)
                {
                    if (D[k][i][j] == INF)
                    {
                        T = INF;
                        break;
                    }
                    T += D[k][i][j];
                }
                if (T == INF) continue;
                T -= F * cost[i][j];
                if (T < minimum) minimum = T, tx = i, ty = j; 
            }
        cout << "Case #" << ++cases << ": ";
        if (minimum < INF)
        {
            cout << "Selected city (" << tx << ',' << ty << ')';
            cout << " with minimum cost " << minimum << ".\n";
        }
        else cout << "Impossible.\n";
    }

    return 0;
}
