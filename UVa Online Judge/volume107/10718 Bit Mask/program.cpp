// Bit Mask
// UVa ID: 10718
// Verdict: Accepted
// Submission Date: 2017-12-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    unsigned N, L, U;
    while (cin >> N >> L >> U) {
        bitset<32> NN(N), M(0);
        for (int i = 31; i >= 0; i--) {
            M.set(i, 1);
            if (NN.test(i)) {                
                if (M.to_ulong() > L) M.set(i, 0);
            }
            else {
                if (M.to_ulong() > U) M.set(i, 0);
            }
        }
        cout << M.to_ulong() << '\n';
    }

    return 0;
}
