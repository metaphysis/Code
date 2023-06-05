// Rooks
// UVa ID: 11699
// Verdict: Accepted
// Submission Date: 2023-06-05
// UVa Run Time: 0.080s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int mask[16];
    string line;
    while (cin >> line) {
        if (line == "END") break;
        mask[0] = 0;
        for (int i = 0; i < 15; i++) mask[0] |= (line[i] == '#') << i;
        for (int i = 1; i < 15; i++) {
            cin >> line;
            mask[i] = 0;
            for (int j = 0; j < 15; j++)
                mask[i] |= (line[j] == '#') << j;
        }
        int r = 15;
        for (int i = 0; i < (1 << 15); i++) {
            int j = ~i & ((1 << 15) - 1), k = 0, m = 0;
            while (j) {
                if (j & 1) m |= mask[k];
                k++;
                j >>= 1;
            }
            r = min(r, max(__builtin_popcount(i), __builtin_popcount(m)));
        }
        cout << r << '\n';
    }
    return 0;
}
