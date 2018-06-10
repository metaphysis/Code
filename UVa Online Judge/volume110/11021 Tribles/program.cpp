// Tribles
// UVa ID: 11021
// Verdict: Accepted
// Submission Date: 2018-06-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, k, m;
    double pi[1024];

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> k >> m;
        for (int i = 0; i < n; i++)
            cin >> pi[i];

        double Ap1 = 0.0, Ap2, Apt;
        for (int i = 1; i <= m; i++)
        {
            Ap2 = pi[0], Apt = Ap1;
            for (int j = 1; j < n; j++)
            {
                Ap2 += pi[j] * Apt, Apt *= Ap1;
                if (Apt < 1e-10) break;
            }
            Ap1 = Ap2;
        }

        cout << "Case #" << cs << ": ";
        cout << fixed << setprecision(7) << pow(Ap1, k) << '\n';
    }

    return 0;
}
