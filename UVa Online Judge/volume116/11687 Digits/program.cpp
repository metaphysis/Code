// Digits
// UVa ID: 11687
// Verdict: Accepted
// Submission Date: 2017-12-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (line == "END") break;
        int k = line.length();
        if (k >= 10) cout << 4 << '\n';
        else if (k >= 2) cout << 3 << '\n';
        else if (line != "1") cout << 2 << '\n';
        else cout << 1 << '\n';
    }
    return 0;
}
