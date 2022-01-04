// Secret Master Plan
// UVa ID: 12981
// Verdict: Accepted
// Submission Date: 2021-12-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int a1[2][2], a2[2][2], a3[2][2];
    
bool isSame()
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (a1[i][j] != a2[i][j])
                return false;
    return true;
}

void rotate()
{
    a3[0][0] = a1[1][0];
    a3[0][1] = a1[0][0];
    a3[1][0] = a1[1][1];
    a3[1][1] = a1[0][1];
    memcpy(a1, a3, sizeof a3);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                cin >> a1[i][j];
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                cin >> a2[i][j];
        cout << "Case #" << cs << ": ";
        int same = 0;
        for (int i = 1; i <= 4; i++)
            if (isSame())
            {
                same = 1;
                break;
            }
            else rotate();
        cout << (same ? "POSSIBLE" : "IMPOSSIBLE") << '\n';
    }
    return 0;
}
