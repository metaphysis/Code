// Kickdown
// UVa ID: 1588
// Verdict: Accepted
// Submission Date: 2019-07-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string s1, s2;
    while (cin >> s1 >> s2)
    {
        if (s1.length() < s2.length()) swap(s1, s2);
        int T = s1.length() + s2.length(), L = 0;
        s1 = string(s2.length(), '0') + s1 + string(s2.length(), '0');
        for (int i = 0; i < s1.length() - s2.length(); i++)
        {
            int matched1 = 0, matched2 = 0;
            for (int j = 0; j < s2.length(); j++)
            {
                if ((s1[i + j] - '0' + s2[j] - '0') <= 3)
                {
                    matched1++;
                    if (s1[i + j] != '0')
                        matched2++;
                }
                else break;
            }
            if (matched1 < s2.length()) matched2 = 0;
            L = max(L, matched2);
            if (L >= s2.length()) break;
        }
        cout << (T - L) << '\n';
    }

    return 0;
}
