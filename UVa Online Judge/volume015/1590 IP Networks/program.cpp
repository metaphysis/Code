// IP Networks
// UVa ID: 1590
// Verdict: Accepted
// Submission Date: 2023-06-18
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

inline int getAddress(int minb, int maxb) {
    for (int i = 0; i <= 8; i++) {
        int range = 1 << i;
        if (range < maxb - minb + 1) continue;
        for (int j = 0; j < 256; j += range)
                if (j <= minb  && maxb <= j + range - 1)
                    return j;
    }
}

void getBinary(long long r) {
    long long mask = 255LL << 24;
    for (int i = 3; i >= 0; i--) {
        cout << ((r & mask) >> (i * 8));
        mask >>= 8;
        if (i) cout << '.';
    }
    cout << '\n';
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int m;
    int b[4], minb[4], maxb[4];
    char dot;
    while (cin >> m) {
        for (int i = 0; i < 4; i++)
            minb[i] = 255, maxb[i] = 0;
        for (int i = 0; i < m; i++) {
            cin >> b[0];
            for (int i = 1; i < 4; i++) cin >> dot >> b[i];
            for (int i = 0; i < 4; i++)
                minb[i] = min(minb[i], b[i]), maxb[i] = max(maxb[i], b[i]);
        }
        long long address = 0, mask = (1LL << 32) - 1;
        for (int i = 0, j = 3; i < 4; i++, j--) address |= (1LL * getAddress(minb[i], maxb[i])) << (j * 8);
        long long ba = address, bm = mask;
        while (true) {
            int valid = 1;
            for (int i = 0; valid && i < 4; i++) {
                int base = (address & (255LL << ((4 - i - 1) * 8))) >> ((4 - i - 1) * 8);
                int range = 255LL - ((mask & (255LL << ((4 - i - 1) * 8))) >> ((4 - i - 1) * 8));
                if (minb[i] < base || maxb[i] > base + range) valid = 0;
            }
            if (valid) {
                getBinary(address), getBinary(mask);
                break;
            }
            ba = address, bm = mask;
            mask -= mask & -mask;
            address &= mask;
        }
    }
    return 0;
}
