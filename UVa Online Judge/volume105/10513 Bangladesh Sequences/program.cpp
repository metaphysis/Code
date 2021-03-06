// Bangladesh Sequences
// UVa ID: 10513
// Verdict: TLE
// Submission Date: 2018-08-19
// UVa Run Time: 3.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, cnt, used[256];
string parts[16];
char sq[16];

void dfs(int depth)
{
    if (depth == n)
    {
        cnt++;
        return;
    }

    for (int i = 0; i < parts[depth].length(); i++)
    {
        // rule a
        if (used[parts[depth][i]]) continue;

        sq[depth] = parts[depth][i];
 
        if (!depth)
        {
            used[parts[depth][i]] = 1;
            dfs(depth + 1);
            used[parts[depth][i]] = 0;
        }
        else
        {
            // rule d
            if (depth >= 2 && abs(sq[depth] - sq[depth - 2]) == 1) continue;
            // rule c
            if (depth >= 1 && abs(sq[depth] - sq[depth - 1]) == 2) continue;
            // rule b, similar to N-Queen problem
            bool valid = true;
            for (int j = 0; j < depth; j++)
                if (abs(sq[j] - sq[depth]) == depth - j)
                {
                    valid = false;
                    break;
                }
            if (!valid) continue;
            used[parts[depth][i]] = 1;
            dfs(depth + 1);
            used[parts[depth][i]] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        long long total = 1;
        for (int i = 0; i < n; i++)
        {
            cin >> parts[i];
            if (parts[i] == "?")
            {
                parts[i].clear();
                for (int j = 0; j < n; j++) parts[i] += (char)('A' + j);
            }
            total *= parts[i].length();
        }
        memset(used, 0, sizeof(used));
        cnt = 0;
        dfs(0);
        cout << "Case " << ++cases << ": " << (total - cnt) << '\n';
    }

    return 0;
}
