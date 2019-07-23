// Largest Sum Game
// UVa ID: 12640
// Verdict: Accepted
// Submission Date: 2019-07-23
// UVa Run Time: 0.010s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        int Xi, Ei = 0, Mi = 0;
        istringstream iss(line);
        while (iss >> Xi)
        {
            Ei = max(Xi, Ei + Xi);
            Mi = max(Mi, Ei);
        }
        cout << Mi << '\n';
    }
    return 0;
}
