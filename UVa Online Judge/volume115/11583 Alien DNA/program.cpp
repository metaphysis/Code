// Alien DNA
// UVa ID: 11583
// Verdict: Accepted
// Submission Date: 2022-01-30
// UVa Run Time: 0.030s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, n;
    int cnt[26];
    string base;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> n;
        int cut = 0, shared = 0;
        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= n; i++)
        {
            cin >> base;
            for (auto c : base) cnt[c - 'a']++;
            shared++;
            if (*max_element(cnt, cnt + 26) != shared)
            {
                cut++;
                shared = 1;
                memset(cnt, 0, sizeof cnt);
                for (auto c : base) cnt[c - 'a']++;
            }
        }
        cout << cut << '\n';
    }
    return 0;
}
