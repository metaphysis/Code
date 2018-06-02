// Tile Code
// UVa ID: 1224
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

    int J[36] = {0, 1, 1}, A[36] = {};
    for (int i = 3; i <= 34; i++)
    {
        J[i] = J[i - 1] + 2 * J[i - 2];
        if (i & 1) A[i - 3] = (J[i - 3] + J[(i - 3) / 2]) / 2;
        else A[i - 3] = (J[i - 3] + J[i / 2]) / 2;
    }

    int cases, n;
    cin >> cases;
    while (cases--)
    {
        cin >> n;
        cout << A[n + 1] << '\n';
    }

    return 0;
}
