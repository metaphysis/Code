// Anagram Division
// UVa ID: 11084
// Verdict: Accepted
// Submission Date: 2018-09-22
// UVa Run Time: 1.280s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string s;
int d, cnt, digits[16], used[16], remain[16], depth;

void dfs(int idx, int last, int mod)
{
    if (idx == depth)
    {
        if (mod == 0) cnt++;
        return;
    }
    for (int i = 0; i < depth; i++)
        if (!used[i] && last != digits[i])
        {
            used[i] = 1;
            last = digits[i];
            dfs(idx + 1, -1, (mod + digits[i] * remain[idx]) % d);
            used[i] = 0;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> s >> d;
        sort(s.begin(), s.end());
        long long k = 1;
        for (int i = 0; i < s.length(); i++, k *= 10LL)
            remain[i] = (int)(k % d);
        depth = s.length();
        for (int i = 0; i < s.length(); i++)
            digits[i] = s[i] - '0';
        memset(used, 0, sizeof(used));
        dfs(cnt = 0, -1, 0);
        cout << cnt << '\n';
    }

    return 0;
}
