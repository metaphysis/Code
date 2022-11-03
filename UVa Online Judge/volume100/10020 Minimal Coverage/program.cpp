// Minimal Coverage
// UVa ID: 10020
// Verdict: Accepted
// Submission Date: 2017-10-15
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct segment
{
    int left, right;
    
    bool operator<(const segment &s) const
    {
        if (left != s.left)
            return left < s.left;
        else
            return right < s.right;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, M, selected[5010], n, m, cnt, idx, x, y;
    segment segments[100010];
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> M;
        
        n = 0;
        while (cin >> x >> y, x || y)
        {
            segments[n].left = x;
            segments[n].right = y;
            n++;
        }
 
        sort(segments, segments + n);
        
        cnt = -1, idx = 0, m = 0;
        while (idx < n)
        {
            if (segments[idx].left <= m)
            {
                if (cnt == -1)
                    selected[++cnt] = idx;
                else
                {
                    if (segments[idx].right > segments[selected[cnt]].right)
                        selected[cnt] = idx;
                }
                idx++;
            }
            else if (cnt >= 0)
            {
                m = segments[selected[cnt]].right;
                if (m >= M) break;
                if (segments[idx].left > m) break;
                selected[++cnt] = idx;
            }
            else idx++;
        }
        
        if (c > 1) cout << '\n';
        if (cnt >= 0 && segments[selected[cnt]].right >= M)
        {
            cout << (cnt + 1) << '\n';
            for (int i = 0; i <= cnt; i++)
            {
                cout << segments[selected[i]].left;
                cout << ' ';
                cout << segments[selected[i]].right;
                cout << '\n';
            }
        }
        else cout << "0\n";
    }
    
    return 0;
}
