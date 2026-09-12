#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
int R, C, n, h[16][16], cover[25];
int dp[22][17][1 << 16][2];

inline int id(int x, int y) { return x * C + y; }
inline void add(int &a, int b) { a += b; if (a >= MOD) a -= MOD; }

int main() {
    int cas = 1;
    while (scanf("%d %d", &R, &C) == 2) {
        n = R * C;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                scanf("%d", &h[i][j]);
        for (int f = 0; f <= 20; ++f) {
            cover[f] = 0;
            for (int i = 0; i < R; ++i)
                for (int j = 0; j < C; ++j)
                    if (h[i][j] >= f) cover[f] |= 1 << id(i, j);
        }
        memset(dp, 0, sizeof(dp));
        dp[1][0][(1 << n) - 1][0] = 1;
        for (int f = 1; f <= 20; ++f) {
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    int pos = id(i, j);
                    int ni = i, nj = j + 1, nf = f;
                    if (nj == C) { nj = 0; ++ni; }
                    if (ni == R) { ni = 0; nj = 0; ++nf; }
                    int npos = id(ni, nj);
                    for (int st = 0; st < (1 << n); ++st) {
                        for (int used = 0; used < 2; ++used) {
                            int cur = dp[f][pos][st][used];
                            if (!cur) continue;
                            int bit = 1 << pos;
                            if (((st & bit) == 0) && h[i][j] >= f - 1) {
                                if (h[i][j] >= f)
                                    add(dp[nf][npos][st | bit][used], cur);
                                continue;
                            }
                            if (st & bit) {
                                add(dp[nf][npos][st ^ bit][used], cur);
                            } else {
                                add(dp[nf][npos][st][used], cur);
                            }
                            if (h[i][j] >= f) {
                                add(dp[nf][npos][st | bit][1], cur);
                            }
                            if (j > 0) {
                                int lb = 1 << id(i, j - 1);
                                if ((st & lb) == 0 && h[i][j] >= f && h[i][j - 1] >= f) {
                                    add(dp[nf][npos][st | bit | lb][used], cur);
                                }
                            }
                            if (i > 0) {
                                int ub = 1 << id(i - 1, j);
                                if ((st & ub) == 0 && h[i][j] >= f && h[i - 1][j] >= f) {
                                    add(dp[nf][npos][st | bit | ub][used], cur);
                                }
                            }
                        }
                    }
                }
            }
        }
        int silver = dp[21][0][cover[20]][1];
        int gold = dp[21][0][cover[20]][0];
        printf("Case %d: %d %d\n", cas++, silver, gold);
    }
    return 0;
}
