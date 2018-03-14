// Multitasking
// UVa ID: 11926
// Verdict: Accepted
// Submission Date: 2018-01-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    bitset<1000010> marked;
    int n, m, start, end, interval;

    while (cin >> n >> m)
    {
        if (n == 0 && m == 0) break;
        
        marked.reset();
        
        bool conflicted = false;
        for (int i = 1; i <= n; i++)
        {
            cin >> start >> end;
            if (conflicted) continue;
            for (int j = start; j < end; j++)
            {
                if (marked.test(j)) { conflicted = true; break; }
                marked.set(j, 1);
            }
        }
        for (int i = 1; i <= m; i++)
        {
            cin >> start >> end >> interval;
            if (conflicted) continue;
            if (interval < (end - start)) { conflicted = true; continue; }
            int offset = 0;
            while (true)
            {
                int t = min(1000001, end + offset);
                for (int j = start + offset; j < t; j++)
                {
                    if (marked.test(j)) { conflicted = true; break; }
                    marked.set(j, 1);
                }
                offset += interval;
                if (start + offset > 1000000) break;
            }
        }
        if (conflicted) cout << "CONFLICT\n";
        else cout << "NO CONFLICT\n";
    }

    return 0;
}
