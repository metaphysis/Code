// In Puzzleland (IV)
// UVa ID: 12848
// Verdict: Accepted
// Submission Date: 2022-10-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T; cin >> T;
    int H1, S, H2;
    for (int cs = 1; cs <= T; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> H1 >> S >> H2;
        int U = (H2 - 1) * S;
        int D = H1 - 1;
        if (U % D == 0) cout << U / D;
        else
        {
            int G = __gcd(U, D);
            U /= G, D /= G;
            if (U < D) cout << U << '/' << D;
            else cout << (U / D) << ' ' << (U % D) << '/' << D;
        }
        cout << '\n';
    }

    return 0;
}
