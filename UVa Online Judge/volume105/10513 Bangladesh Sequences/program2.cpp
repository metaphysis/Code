// Bangladesh Sequences
// UVa ID: 10513
// Verdict: Accepted
// Submission Date: 2018-08-19
// UVa Run Time: 0.680s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, cnt[16], used[256];
string parts[16], trick[16][33000];
char sq[16];

void dfs(int depth)
{
    if (depth == n)
    {
        for (int i = 0; i < n; i++)
            trick[n][cnt[n]] += sq[i];
        cnt[n]++;
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
            // rule b
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

    for (int i = 1; i <= 15; i++)
    {
        memset(used, 0, sizeof(used));
        for (int j = 0; j < i; j++)
        {
            parts[j].clear();
            for (int k = 0; k < i; k++)
                parts[j] += (char)('A' + k);
        }
        dfs(cnt[n = i] = 0);
    }

    int cases = 0, available[16][256];
    while (cin >> n, n > 0)
    {
        memset(available, 0, sizeof(available));
        long long total = 1;
        for (int i = 0; i < n; i++)
        {
            cin >> parts[i];
            if (parts[i] == "?")
            {
                parts[i].clear();
                for (int j = 0; j < n; j++)
                    parts[i] += (char)('A' + j);
            }
            total *= parts[i].length();
            for (int j = 0; j < parts[i].length(); j++)
                available[i][parts[i][j]] = 1;
        }
        
        long long invalid = 0;
        for (int i = 0; i < cnt[n]; i++)
        {
            bool matched = true;
            for (int j = 0; j < n; j++)
            {
                if (!available[j][trick[n][i][j]])
                {
                    matched = false;
                    break;
                }
            }
            if (matched) invalid++;
        }

        cout << "Case " << ++cases << ": " << (total - invalid) << '\n';
    }

    return 0;
}
