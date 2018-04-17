// Ancient Cipher
// UVa ID: 1339
// Verdict: Accepted
// Submission Date: 2018-04-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string a, b;
    while (cin >> a >> b)
    {
        int cnt1[26] = {0}, cnt2[26] = {0};
        for (auto c : a) cnt1[c - 'A']++;
        for (auto c : b) cnt2[c - 'A']++;
        sort(cnt1, cnt1 + 26);
        sort(cnt2, cnt2 + 26);
        bool equal = true;
        for (int i = 0; i < 26; i++)
            if (cnt1[i] != cnt2[i])
            {
                equal = false;
                break;
            }
        cout << (equal ? "YES" : "NO") << '\n';
    }

    return 0;
}
