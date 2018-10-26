// Arrange Some Marbles
// UVa ID: 11125
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct package
{
    long long total, used[4], start_color, start_cnt, last_color, last_cnt, ways;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int cnt[4], all = 0, colors;
        cin >> colors;
        for (int i = 0; i < colors; i++)
        {
            cin >> cnt[i];
            all += cnt[i];
        }
        
        queue<package> q;
        package p;
        memset(p.used, 0, sizeof(p.used));
        p.total = 0;
        p.start_color = p.last_color = -1;
        p.start_cnt = p.last_cnt = 0;
        q.push(p);
                
        long long sum = 0;
        while (!q.empty())
        {
            package p = q.front(); q.pop();
            if (q.front().total == all)
            {
                if (p.start_color != p.last_color && p.start_cnt != p.last_cnt)
                    sum += p.ways;
                continue;
            }
            if (p.start_cnt == 0)
            {
                for (int i = 0; i < colors; i++)
                {
                    for (int j = 1; j <= 3; j++)
                    {
                        package next;
                        memset(next.used, 0, sizeof(next.used));
                        next.used[i] = j;
                        next.start_color = i;
                        next_start_cnt = j;
                        q.push(next);
                    }
                }
            }
            if (p.last_cnt == 0)
            {
                
            }
        }
        cout << sum << '\n';
    }

    return 0;
}
