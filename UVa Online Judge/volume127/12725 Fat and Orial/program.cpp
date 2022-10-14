// Fat and Orial
// UVa ID: 12725
// Verdict: Accepted
// Submission Date: 2022-10-14
// UVa Run Time: 0.110s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cout << "Case #" << cs << ": ";
        double N, M, A, B;
        cin >> N >> M >> A >> B;
        double P = ((A + B) * M - A * N) / B;
        if (P < 0 || P - 10.0 >= 1e-6) cout << "Impossible";
        else cout << fixed << setprecision(2) << P;
        cout << '\n';
    }

    return 0;
}
