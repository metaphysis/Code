// Anagram Division
// UVa ID: 11084
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string s;
int d, cnt, used[10],;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    while (cin >> s >> d)
    {
        for (int i = 0; i < s.length(); i++)
        {
            long long k = 1;
            for (int j = 0; j < s.length(); j++)
            {
                mod[s[i] - '0'][j] = ((s[i] - '0') * k) % d;
                k *= 10LL;
            }
        }
        memset(used, 0, sizeof(used));
        cnt = 0;
        dfs(0, 0);
        cout << cnt << '\n';
    }

    return 0;
}
