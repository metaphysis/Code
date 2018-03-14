// Mall Mania
// UVa ID: 11101
// Verdict: Accepted
// Submission Date: 2018-02-08
// UVa Run Time: 0.110s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct walk
{
    int x, y, z;
    walk (int x = 0, int y = 0, int z = 0): x(x), y(y), z(z) {}
};

int grid[2010][2010], visited[2010][2010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int p, x1, y1;
    int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (cin >> p, p > 0)
    {
        vector<walk> m1, m2;
        int L = 2010, R = 0, B = 2010, T = 0;

        for (int i = 0; i < p; i++)
        {
            cin >> x1 >> y1;
            m1.push_back(walk(x1, y1, 0));
            L = min(L, x1), R = max(R, x1);
            B = min(B, y1), T = max(T, y1);
            
        }

        cin >> p;
        for (int i = 0; i < p; i++)
        {
            cin >> x1 >> y1;
            m2.push_back(walk(x1, y1, 0));
            L = min(L, x1), R = max(R, x1);
            B = min(B, y1), T = max(T, y1);
        }

        for (int i = L; i <= R; i++)
            for (int j = B; j <= T; j++)
                visited[i][j] = grid[i][j] = 0;

        queue<walk> q;
        for (auto w : m1)
        {
            visited[w.x][w.y] = 1;
            q.push(w);
        }

        for (auto w : m2)
        {
            grid[w.x][w.y] = 1;
        }
        
        while (!q.empty())
        {
            walk w = q.front(); q.pop();
            if (grid[w.x][w.y])
            {
                cout << w.z << '\n';
                break;
            }
            for (int k = 0; k < 4; k++)
            {
                int nextx = w.x + offset[k][0], nexty = w.y + offset[k][1];
                if (nextx >= L && nextx <= R && nexty >= B && nexty <= T)
                    if (!visited[nextx][nexty])
                    {
                        visited[nextx][nexty] = 1;
                        q.push(walk(nextx, nexty, w.z + 1));
                    }
            }
        }
    }

    return 0;
}
