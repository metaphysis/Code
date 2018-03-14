// Discrete Pursuit
// UVa ID: 11335
// Verdict: Accepted
// Submission Date: 2018-01-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int a, u, v;
    while (cin >> a >> u >> v)
    {
        for (int t = 0; ; t++)
        {
            int x = a + t * u;
            int y = t * v;
            
            int d = t * (t + 1) / 2;
            if (d >= x && d >= y)
            {
                cout << t << '\n';
                break;
            }
        }
    }

    return 0;
}
