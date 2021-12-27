// Burger Stand
// UVa ID: 13048
// Verdict: Accepted
// Submission Date: 2021-12-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    string s;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> s;
        int places = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] != '-') continue;
            if (i + 1 < s.length() && s[i + 1] == 'B') continue;
            if (i + 2 < s.length() && s[i + 2] == 'B') continue;
            if (i - 1 >= 0 && s[i - 1] == 'S') continue;
            if (i + 1 < s.length() && s[i + 1] == 'S') continue;
            places++;
        }
        cout << places << '\n';
    }
    return 0;
}
