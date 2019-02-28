// Determine The Combination
// UVa ID: 10776
// Verdict: Accepted
// Submission Date: 2019-02-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int r;
string s, t, l;

void dfs(int d, int p)
{
    if (d == r)
    {
        l = t;
        cout << t << '\n';
    }
    else
    {
        for (int i = p; i < s.length(); i++)
        {
            t[d] = s[i];
            int same = 1;
            for (int j = 0; j <= d; j++)
                if (t[j] != l[j])
                {
                    same = 0;
                    break;
                }
            if (!same) dfs(d + 1, i + 1);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> s >> r)
    {
        sort(s.begin(), s.end());
        t.assign(r, '0');
        l.assign(r, '0');
        dfs(0, 0);
    }

    return 0;
}
