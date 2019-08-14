// Falling Ants
// UVa ID: 12709
// Verdict: Accepted
// Submission Date: 2019-08-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, L, W, H;
    while (cin >> T, T > 0)
    {
        int  maxH = 0, maxV = 0;
        for (int i = 0; i < T; i++)
        {
            cin >> L >> W >> H;
            if (H > maxH || (H == maxH && L * W * H > maxV))
            {
                maxH = H;
                maxV = L * W * H;
            }
        }
        cout << maxV << '\n';
    }
    return 0;
}
