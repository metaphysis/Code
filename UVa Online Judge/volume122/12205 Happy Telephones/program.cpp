// Happy Telephones
// UVa ID: 12205
// Verdict: Accepted
// Submission Date: 2022-01-19
// UVa Run Time: 0.030s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct interval {
    int start, end;
} intervals[10010];

int n, m;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        if (n == 0) break;
        int source, dest;
        for (int i = 0; i < n; i++)
        {
            cin >> source >> dest;
            cin >> intervals[i].start >> intervals[i].end;
            intervals[i].end += intervals[i].start;
            intervals[i].end--;
        }
        int start, end;
        for (int i = 0; i < m; i++)
        {
            cin >> start >> end;
            end += start;
            end--;
            int cnt = 0;
            for (int j = 0; j < n; j++)
            {
                if (start > intervals[j].end || end < intervals[j].start)
                    continue;
                cnt++;
            }
            cout << cnt << '\n';
        }
    }
    return 0;
}
