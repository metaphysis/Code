// The Jolly Friar's Puzzle
// UVa ID: 12845
// Verdict: Accepted
// Submission Date: 2023-04-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

inline int verify(int b, int mask) {
    int r = 0;
    for (int i = 0; i < 16; i++)
        if (mask & (1 << i))
            r += b & (1 << i) ? 1 : 0;
    return r && (r % 2 == 0) ? 1 : 0;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    vector<int> o;
    for (int b = 0; b < (1 << 16); b++)
        if (__builtin_popcount(b) == 10) {
            int r = 0;
            r += verify(b, (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));
            r += verify(b, (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
            r += verify(b, (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11));
            r += verify(b, (1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));
            r += verify(b, (1 << 0) | (1 << 4) | (1 << 8) | (1 << 12));
            r += verify(b, (1 << 1) | (1 << 5) | (1 << 9) | (1 << 13));
            r += verify(b, (1 << 2) | (1 << 6) | (1 << 10) | (1 << 14));
            r += verify(b, (1 << 3) | (1 << 7) | (1 << 11) | (1 << 15));
            r += verify(b, (1 << 8) | (1 << 13));
            r += verify(b, (1 << 4) | (1 << 9) | (1 << 14));
            r += verify(b, (1 << 0) | (1 << 5) | (1 << 10) | (1 << 15));
            r += verify(b, (1 << 1) | (1 << 6) | (1 << 11));
            r += verify(b, (1 << 2) | (1 << 7));
            r += verify(b, (1 << 1) | (1 << 4));
            r += verify(b, (1 << 2) | (1 << 5) | (1 << 8));
            r += verify(b, (1 << 3) | (1 << 6) | (1 << 9) | (1 << 12));
            r += verify(b, (1 << 7) | (1 << 10) | (1 << 13));
            r += verify(b, (1 << 11) | (1 << 14) );
            if (r == 16) o.push_back(b);
        }
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        char c;
        int f = 0;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                cin >> c;
                if (c == '*') f |= (1 << (i * 4 + j));
            }
        int r = 32;
        for (int i = 0; i < o.size(); i++)
            r = min(r, 10 - __builtin_popcount(o[i] & f));
        cout << r << '\n';
    }
    return 0;
}
