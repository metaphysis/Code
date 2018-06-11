// Vampires
// UVa ID: 11500
// Verdict: Accepted
// Submission Date: 2018-06-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int EV1, EV2, AT, D;
    while (cin >> EV1 >> EV2 >> AT >> D)
    {
        if (EV1 == 0) break;
        double N1 = EV1 / D + (EV1 % D != 0), N2 = EV2 / D + (EV2 % D != 0);
        double p = AT / 6.0;

        double r = 0.0;
        if (AT == 3)
        {
            r = N1 / (N1 + N2);
        }
        else
        {
            r = (1.0 - pow((1.0 - p) / p, N1)) / (1.0 - pow((1.0 - p) / p, N1 + N2));
        }
        
        cout << fixed << setprecision(1) << (r * 100) << '\n';
    }

    return 0;
}
