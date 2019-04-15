// Cacho
// UVa ID: 13130
// Verdict: Accepted
// Submission Date: 2019-04-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, dice[5];
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        for (int i = 0; i < 5; i++) cin >> dice[i];
        if ((dice[0] == 1 && dice[1] == 2 && dice[2] == 3 && dice[3] == 4 && dice[4] == 5)
            || (dice[0] == 2 && dice[1] == 3 && dice[2] == 4 && dice[3] == 5 && dice[4] == 6))
            cout << "Y\n";
        else
            cout << "N\n";
    }

    return 0;
}
