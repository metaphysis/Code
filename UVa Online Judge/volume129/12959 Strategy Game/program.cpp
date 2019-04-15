// Strategy Game
// UVa ID: 12959
// Verdict: Accepted
// Submission Date: 2019-04-15
// UVa Run Time: 0.020s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int J, R, VP[512], vp;
    while (cin >> J >> R)
    {
        memset(VP, 0, sizeof(VP));
        for (int i = 0; i < R; i++)
            for (int j = 0; j < J; j++)
            {
                cin >> vp;
                VP[j] += vp;
            }
        int M = VP[J - 1], P = J;
        for (int i = J - 2; i >= 0; i--)
            if (VP[i] > VP[P - 1])
                P = i + 1;
        cout << P << '\n';
    }
    return 0;
}
