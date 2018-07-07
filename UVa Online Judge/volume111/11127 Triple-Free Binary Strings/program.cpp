// Triple-Free Binary Strings
// UVa ID: 11127
// Verdict: Accepted
// Submission Date: 2018-07-07
// UVa Run Time: 0.110s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, cnt;
string bits;

inline bool validate(int last)
{
    int length = 1;
    while (true)
    {
        int pos3 = last - length + 1;
        int pos2 = pos3 - length;
        int pos1 = pos2 - length;
        if (pos1 < 0) break;

        bool same = true;
        for (int i = 0; i < length; i++)
            if (bits[pos1 + i] != bits[pos2 + i])
            {
                same = false;
                break;
            }
        if (same)
        {
            for (int i = 0; i < length; i++)
                if (bits[pos1 + i] != bits[pos3 + i])
                {
                    same = false;
                    break;
                }
            if (same) return false;
        }
        length++;
    }
    return true;
}

void dfs(int depth)
{
    if (depth == n)
    {
        cnt++;
        return;
    }

    if (bits[depth] == '*')
    {
        bits[depth] = '0';
        if (validate(depth)) dfs(depth + 1);
        bits[depth] = '1';
        if (validate(depth)) dfs(depth + 1);
        bits[depth] = '*';
    }
    else
    {
        if (validate(depth)) dfs(depth + 1);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        cin >> bits;
        cnt = 0;
        dfs(0);
        cout << "Case " << ++cases << ": " << cnt << '\n';
    }

    return 0;
}
