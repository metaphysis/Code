// Gifts in a Hexagonal Box
// UVa ID: 10287
// Verdict: Accepted
// Submission Date: 2023-04-07
// UVa Run Time: 0.080s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    double S;
    while (cin >> S) {
        cout << fixed << setprecision(10);
        cout << sqrt(3) / 2.0 * S << ' ';
        cout << 1.0 / (1.0 + 2 / sqrt(3)) * S << ' ';
        cout << sqrt(3) / 4.0 * S << ' ';
        cout << (6 * sqrt(7) - 7 * sqrt(3)) / 10.0 * S << '\n';
    }
    return 0;
}
