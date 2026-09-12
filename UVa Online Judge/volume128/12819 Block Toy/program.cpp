#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
int cover[25], dp[22][17][1 << 16][2], grid[17][17];
int rowCnt, colCnt;

int getPos(int row, int col) {
    return row * colCnt + col;
}

void addVal(int &ans, int val) {
    ans += val;
    if (ans >= mod) ans -= mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 1;
    while (cin >> rowCnt >> colCnt) {
        for (int i = 0; i < rowCnt; i++)
            for (int j = 0; j < colCnt; j++)
                cin >> grid[i][j];
        for (int lev = 0; lev <= 20; lev++) {
            cover[lev] = 0;
            for (int i = 0; i < rowCnt; i++)
                for (int j = 0; j < colCnt; j++)
                    if (grid[i][j] >= lev)
                        cover[lev] |= 1 << getPos(i, j);
        }
        memset(dp, 0, sizeof(dp));
        dp[1][0][(1 << (rowCnt * colCnt)) - 1][0] = 1;
        for (int lev = 1; lev <= 20; lev++) {
            for (int i = 0; i < rowCnt; i++) {
                for (int j = 0; j < colCnt; j++) {
                    int pos = getPos(i, j);
                    for (int state = 0; state < (1 << (rowCnt * colCnt)); state++) {
                        for (int typ = 0; typ < 2; typ++) {
                            int val = dp[lev][pos][state][typ];
                            if (val == 0) continue;
                            int nx = i, ny = j + 1, nlev = lev;
                            if (ny == colCnt) {
                                ny = 0;
                                nx++;
                            }
                            if (nx == rowCnt) {
                                nx = 0;
                                ny = 0;
                                nlev++;
                            }
                            int bit = 1 << pos;
                            if ((state & bit) == 0 && grid[i][j] >= lev - 1) {
                                if (grid[i][j] >= lev)
                                    addVal(dp[nlev][getPos(nx, ny)][state | bit][typ], val);
                                continue;
                            }
                            if (state & bit)
                                addVal(dp[nlev][getPos(nx, ny)][state ^ bit][typ], val);
                            else
                                addVal(dp[nlev][getPos(nx, ny)][state][typ], val);
                            if (grid[i][j] >= lev)
                                addVal(dp[nlev][getPos(nx, ny)][state | bit][1], val);
                            if (j) {
                                int leftPos = getPos(i, j - 1), leftBit = 1 << leftPos;
                                if ((state & leftBit) == 0 && grid[i][j] >= lev && grid[i][j - 1] >= lev)
                                    addVal(dp[nlev][getPos(nx, ny)][state | bit | leftBit][typ], val);
                            }
                            if (i) {
                                int upPos = getPos(i - 1, j), upBit = 1 << upPos;
                                if ((state & upBit) == 0 && grid[i][j] >= lev && grid[i - 1][j] >= lev)
                                    addVal(dp[nlev][getPos(nx, ny)][state | bit | upBit][typ], val);
                            }
                        }
                    }
                }
            }
        }
        cout << "Case " << caseId++ << ": " << dp[21][getPos(0, 0)][cover[20]][1] << " " << dp[21][getPos(0, 0)][cover[20]][0] << "\n";
    }
    return 0;
}
