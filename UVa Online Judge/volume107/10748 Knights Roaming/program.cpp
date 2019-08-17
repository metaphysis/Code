// Knight Roaming
// UVa ID: 10748
// Verdict: Accepted
// Submission Date: 2019-08-17
// UVa Run Time: 0.480s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y, k;
    bool operator<(const point &p) const { return k < p.k; }
};

vector<point> ps;

void bfs()
{
    unordered_map<int, unordered_map<int, int>> allPoints;
    int dx[8] = { 1, 2, 1, 2, -1, -2, -1, -2 };
    int dy[8] = { 2, 1, -2, -1, 2, 1, -2, -1 };
    int x, y, m, nx, ny;
    queue<int> X, Y, M;
    X.push(0), Y.push(0), M.push(0);
    allPoints[0][0] = 0;
    while (!X.empty())
    {
        x = X.front(); X.pop();
        y = Y.front(); Y.pop();
        m = M.front(); M.pop();
        if (m >= 50) continue;
        for (int k = 0; k < 8; k++)
        {
            nx = x + dx[k], ny = y + dy[k];
            if (allPoints[nx].count(ny)) continue;
            allPoints[nx][ny] = m + 1;
            X.push(nx), Y.push(ny), M.push(m + 1);
        }
    }
    for (auto p1 : allPoints)
        for (auto p2 : p1.second)
            ps.push_back(point{p1.first, p2.first, p2.second});
    sort(ps.begin(), ps.end());
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    bfs();

    int N, x, y, k;
    while (cin >> N, N > 0)
    {
        int cnt = 0;
        unordered_map<int, unordered_set<int>> visited;
        for (int i = 0; i < N; i++)
        {
            cin >> x >> y >> k;
            for (int j = 0; j < ps.size(); j++)
            {
                if (k < ps[j].k) break;
                if (visited[ps[j].x + x].count(ps[j].y + y)) continue;
                visited[ps[j].x + x].insert(ps[j].y + y);
                cnt++;
            }
        }
        cout << cnt << '\n';
    }

    return 0;
}
