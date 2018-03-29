// Secret Word
// UVa ID: 12467
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        int longest = 0;
        for (int i = line.length() - 1; i >= 0; i--)
        {
            if (line[i] == line[0])
            {
                int j = 0, k = i;
                while (j <= k && line[j] == line[k]) j++, k--;
                if (j > k)
                    longest = max(longest, i + 1);
                else
                    longest = max(longest, j);
            }
        }
        string sub = line.substr(0, longest);
        reverse(sub.begin(), sub.end());
        cout << sub << '\n';
    }

    return 0;
}
