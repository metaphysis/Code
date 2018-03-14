// SMS Typing
// UVa ID: 11530
// Verdict: Accepted
// Submission Date: 2017-12-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int times[26] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 1, 2, 3, 4};
    
    cin >> cases;
    cin.ignore(1024, '\n');
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case #" << c << ": ";
        int pressed = 0;
        string line;
        getline(cin, line);
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ') pressed += 1;
            else pressed += times[line[i] - 'a'];
        }
        cout << pressed << '\n';
    }

    return 0;
}
