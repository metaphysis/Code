// Arrows
// UVa ID: 13047
// Verdict: Accepted
// Submission Date: 2021-12-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string line;
    cin >> n;
    for (int cs = 1; cs <= n; cs++)
    {
        cin >> line;
        char c;
        int longest = 0;
        int i = 0;
        while (i < line.length())
        {
            if (line[i] == '<')
            {
                int cnt = 1;
                i++;
                if (i < line.length() && (line[i] == '-' || line[i] == '='))
                {
                    c = line[i];
                    while (i < line.length() && line[i] == c) cnt++, i++;
                }
                longest = max(longest, cnt);
            }
            else if (line[i] == '-' || line[i] == '=')
            {
                c = line[i];
                int cnt = 0;
                while (i < line.length() && line[i] == c) cnt++, i++;
                if (i < line.length() && line[i] == '>')
                {
                    cnt++, i++;
                    longest = max(longest, cnt);
                }
            }
            else if (line[i] == '>')
            {
                int cnt = 1;
                longest = max(longest, cnt);
                i++;
            }
        }
        if (!longest) longest = -1;
        cout << "Case " << cs << ": " << longest << '\n';
    }

    return 0;
}
