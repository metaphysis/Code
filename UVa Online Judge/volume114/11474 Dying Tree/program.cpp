// Dying Tree
// UVa ID: 11474
// Verdict: Accepted
// Submission Date: 2018-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
} doctors[16];

vector<point> branches[128];
list<int> edges[128];
int visited[128];

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
}

inline int getDist(point p1, point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N, M, K, D, B;

    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> M >> K >> D;
        for (int i = 0; i < M; i++)
            cin >> doctors[i].x >> doctors[i].y;

        for (int i = 0; i < N; i++)
        {
            branches[i].clear();
            cin >> B;
            for (int j = 0, x, y; j < B; j++)
            {
                cin >> x >> y;
                branches[i].push_back(point(x, y));
            }
        }

        for (int i = 0; i < (M + N); i++) edges[i].clear();

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                for (auto b : branches[j])
                    if (getDist(doctors[i], b) <= D * D)
                    {
                        edges[i].push_back(j + M);
                        edges[j + M].push_back(i);
                        break;
                    }
        
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                for (auto b1 : branches[i])
                {
                    bool talked = false;
                    for (auto b2 : branches[j])
                        if (getDist(b1, b2) <= K * K)
                        {
                            edges[i + M].push_back(j + M);
                            edges[j + M].push_back(i + M);
                            talked = true;
                            break;
                        }
                    if (talked) break;
                }

        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < M; i++)
        {
            dfs(i);
            if (visited[M]) break;
        }

        if (visited[M]) cout << "Tree can be saved :)\n";
        else cout << "Tree can't be saved :(\n";
    }

    return 0;
}
