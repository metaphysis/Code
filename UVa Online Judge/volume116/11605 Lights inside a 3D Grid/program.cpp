// Lights inside a 3D Grid
// UVa ID: 11605
// Verdict: Accepted
// Submission Date: 2019-02-18
// UVa Run Time: 0.470s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

double fastPow(double x, int n)
{
    if (n == 0) return 1;
    double r = fastPow(x, n / 2);
    r = r * r;
    if (n & 1) r *= x;
    return r;
}

double getProbability(int a, int L)
{
    return 1.0 * (L * L - (a - 1) * (a - 1) - (L - a) * (L - a)) / (L * L);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, M, P, K;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> M >> P >> K;
        double E = 0;
        for (int i = 1; i <= N; i++)
        {
            double x = getProbability(i, N);
            for (int j = 1; j <= M; j++)
            {
                double y = getProbability(j, M);
                for (int k = 1; k <= P; k++)
                {
                    double z = getProbability(k, P);
                    E += 0.5 * (1 - fastPow(1 - 2 * x * y * z, K));
                }
            }
        }
        cout << "Case " << cs << ": " << fixed << setprecision(10) << E << '\n';
    }

    return 0;
}
