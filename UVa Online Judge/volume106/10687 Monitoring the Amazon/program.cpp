// Monitoring the Amazon
// UVa ID: 10687
// Verdict: Accepted
// Submission Date: 2018-01-29
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    int distTo(const point &p)
    {
        return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
    }
}stations[1010];

const int INF = 0x3fffffff;
int n, visited[1010], pivot;

bool cmp(int i, int j)
{
    int dist1 = stations[pivot].distTo(stations[i]);
    int dist2 = stations[pivot].distTo(stations[j]);
    if (dist1 != dist2) return dist1 < dist2;
    if (stations[i].x != stations[j].x) return stations[i].x < stations[j].x;
    return stations[i].y < stations[j].y;
}

void dfs(int u)
{
    visited[u] = 1;
    pivot = u;
    vector<int> idx;
    for (int i = 0; i < n; i++)
        if (i != u)
            idx.push_back(i);
    sort(idx.begin(), idx.end(), cmp);
    if (idx.size() > 0 && !visited[idx[0]]) dfs(idx[0]);
    if (idx.size() > 1 && !visited[idx[1]]) dfs(idx[1]);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> stations[i].x >> stations[i].y;

        memset(visited, 0, sizeof(visited));
        dfs(0);

        bool reachable = true;
        for (int i = 0; i < n; i++)
            if (!visited[i])
            {
                reachable = false;
                break;
            }
        if (reachable) cout << "All stations are reachable.";
        else cout << "There are stations that are unreachable.";
        cout << '\n';
    }

    return 0;
}
