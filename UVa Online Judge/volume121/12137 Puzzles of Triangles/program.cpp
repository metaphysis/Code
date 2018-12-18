// Puzzles of Triangles
// UVa ID: 12137
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

    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= 19; j++)
        {
            int A = 20 * 20 + i * i;
            int B = (20 - i) * (20 - i) + j * j;
            int C = 20 * 20 + (20 - j) * (20 - j);
            if (C == A + B || A == B + C || B == A + C) cout << i << ' ' << j << '\n';
        }

    return 0;
}
