// Extra WithBlanks
// UVa ID: 11965
// Verdict: Accepted
// Submission Date: 2018-03-25
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, word;
    getline(cin, line);
    int cases = stoi(line);
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        cout << "Case " << c << ":\n";
        getline(cin, line);
        int n = stoi(line);
        for (int i = 0; i < n; i++)
        {
            getline(cin, line);
            int idx = 0;
            while (idx < line.length())
            {
                cout << line[idx];
                if (line[idx] == ' ')
                {
                    while (idx < line.length() && line[idx] == ' ')
                        idx++;
                }
                else idx++;
            }
            cout << '\n';
        }
    }
    return 0;
}
