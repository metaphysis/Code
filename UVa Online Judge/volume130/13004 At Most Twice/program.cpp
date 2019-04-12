// At Most Twice
// UVa ID: 13004
// Verdict: Accepted
// Submission Date: 2019-04-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string number;
int cnt[10], digits[20], done;

inline bool smallerOrEqual(int depth)
{
    for (int i = 0; i <= depth; i++)
        if ((digits[i] + '0') != number[i])
            return (digits[i] + '0') < number[i];
    return true;
}

void dfs(int depth, int counted)
{
    if (depth == number.length())
    {
        for (int i = 0; i < depth; i++)
        {
            if (!digits[i]) continue;
            for (int j = i; j < depth; j++)
                cout << digits[j];
            break;
        }
        cout << '\n';
        done = 1;
        return;
    }
    for (int i = 9; i >= 0; i--)
    {
        if (cnt[i] < 2)
        {
            digits[depth] = i;
            if (smallerOrEqual(depth))
            {
                if (counted || i) cnt[i]++;
                dfs(depth + 1, counted || i);
                if (counted || i) cnt[i]--;
                if (done) return;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> number)
    {
        memset(cnt, 0, sizeof(cnt));
        dfs(done = 0, 0);
    }

    return 0;
}
