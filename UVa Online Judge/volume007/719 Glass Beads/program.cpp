// Glass Beads
// UVa ID: 719
// Verdict: Accepted
// Submission Date: 2018-04-03
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string s;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> s;
        int i = 0, j = 1, k, n = s.length();
        while (i < n && j < n)
        {
            k = 0;
            while (k < n && s[(i + k) % n] == s[(j + k) % n]) k++;
            if (k == n) break;
            if (s[(i + k) % n] > s[(j + k) % n])
            {
                i = max(j, i + k + 1);
                j = i + 1;
            }
            else j += k + 1;
        }
        cout << (i + 1) << '\n';
    }

    return 0;
}
