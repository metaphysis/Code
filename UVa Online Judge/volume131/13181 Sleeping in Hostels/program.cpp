// Sleeping in Hostels
// UVa ID: 13181
// Verdict: Accepted
// Submission Date: 2021-12-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        int best = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '.')
            {
                int start = i, end = i;
                while (i < line.length() && line[i] == '.') end = i++;
                if (start == 0 || end + 1 == line.length()) best = max(best, end - start);
                else best = max(best, (end - start) / 2);
            }
        }
        cout << best << '\n';
    }

    return 0;
}
