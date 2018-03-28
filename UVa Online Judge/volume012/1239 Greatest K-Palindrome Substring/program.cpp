// Greatest K-Palindrome Substring
// UVa ID: 1239
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, k;
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line >> k;
        int longest = 0;
        for (int i = 0; i < line.length(); i++)
        {
            int diff = 0, offset = 0;
            while (true)
            {
                int l = i - offset, r = i + offset;
                if (l < 0 || r >= line.length()) break;
                if (line[l] != line[r]) diff++;
                if (diff > k) break;
                longest = max(longest, offset * 2 + 1);
                offset++;
            }
            
            diff = 0, offset = 0;
            if (i < line.length() - 1)
            {
                while (true)
                {
                    int l = i - offset, r = i + 1 + offset;
                    if (l < 0 || r >= line.length()) break;
                    if (line[l] != line[r]) diff++;
                    if (diff > k) break;
                    longest = max(longest, (offset + 1) * 2);
                    offset++;
                }
            }
        }
        cout << longest << '\n';
    }
    
    return 0;
}
