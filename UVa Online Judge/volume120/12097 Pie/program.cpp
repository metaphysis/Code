// Pie
// UVa ID: 12097
// Verdict: Accepted
// Submission Date: 2019-07-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10010;
const double PI = 2 * acos(0), EPSILON = 1e-6;

int N, F;
double Ri[MAXN];

bool worked(double V)
{
    int C = 0;
    for (int i = 0; i < N; i++)
    {
        C += (int)(Ri[i] / V);
        if (C >= (F + 1)) return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> F;
        double maxRi = 0;
        for (int i = 0; i < N; i++)
        {
            cin >> Ri[i];
            Ri[i] *= Ri[i];
            maxRi = max(maxRi, Ri[i]);
        }
        double low = 0, high = maxRi, middle, V;
        while (fabs(low - high) > EPSILON)
        {
            middle = (low + high) / 2;
            if (worked(middle))
            {
                V = middle;
                low = middle;
            }
            else high = middle;
        }
        cout << fixed << setprecision(4) << V * PI << '\n';
    }
    return 0;
}
