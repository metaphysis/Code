// Athletics Track
// UVa ID: 11646
// Verdict: Accepted
// Submission Date: 2018-12-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char c;
    int cases = 0;
    double a, b;
    
    while (cin >> a >> c >> b)
    {
        int cnt = 0;
        double low = 0, high = 1000, L, W, D, P;
        while (true)
        {
            W = (low + high) / 2;
            L = W * a / b;
            D = sqrt(L * L + W * W);
            P = 2 * (L + D * asin(W / D));
            if (fabs(P - 400) < 1e-7 || cnt++ > 40) break;
            if (P < 400) low = W;
            else high = W;
        }
        cout << "Case " << ++cases << ": ";
        cout << fixed << setprecision(10) << L << ' ';
        cout << fixed << setprecision(10) << W << '\n';
    }

    return 0;
}
