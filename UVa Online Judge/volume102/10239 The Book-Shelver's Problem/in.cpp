// 
// UVa ID: 
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    srand(time(NULL));
    int cases = 10;
    for (int cs = 1; cs <= cases; cs++) {
        int N = rand() % 1000 + 1;
        int W = rand() % 1000 + 1;
        cout << N << ' ';
        cout << fixed << setprecision(4) << W * 1.0 << '\n';
        for (int i = 0; i < N; i++) {
            double hi = (rand() % 100 + 1) * 1.0;
            double wi = rand() % W;
            if (wi < 1e-6) wi = 1;
            cout << fixed << setprecision(4) << hi << ' ';
            cout << wi << '\n';
        }
    }
    cout << "0 0.0000\n";
    return 0;
}
