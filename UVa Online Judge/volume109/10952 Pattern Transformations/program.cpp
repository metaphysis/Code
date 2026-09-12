#include <bits/stdc++.h>
using namespace std;

const int inf = 0x00ffffff;

struct Solver {
    int width, height, testId;
    int dp[8][256][256], vis[8][256][256];
    char src[10][10], dst[10][10];

    int calcCell(int row, int downMask, int vacMask, int col, int nextDown, int nextVac) {
        int ans;
        int fullMask = (1 << width) - 1;
        if (col == width) {
            if (vacMask != fullMask) return inf;
            for (int i = 0; i < width; i++)
                if (dst[row][i] == '.' && ((nextVac >> i) & 1) == 0) nextVac |= 1 << i;
            return calcRow(row + 1, nextDown, nextVac);
        }
        if (src[row][col] == '.') {
            if ((downMask >> col) & 1) {
                if (nextVac & (1 << col)) return inf;
                nextVac |= 1 << col;
            }
            if (((vacMask >> col) & 1) == 0) return inf;
            if (dst[row][col] == '.') nextVac |= 1 << col;
            return calcCell(row, downMask, vacMask, col + 1, nextDown, nextVac);
        }
        if ((downMask >> col) & 1) {
            if (nextVac & (1 << col)) return inf;
            nextVac |= 1 << col;
        }
        if (((vacMask >> col) & 1) == 0) {
            if (dst[row - 1][col] != src[row][col]) return inf;
            if ((downMask >> col) & 1)
                return 1 + calcCell(row, downMask, vacMask | (1 << col), col + 1, nextDown, nextVac);
            return calcCell(row, downMask, vacMask | (1 << col), col + 1, nextDown, nextVac);
        }
        ans = inf;
        if (src[row][col] == dst[row][col] && ((downMask >> col) & 1) == 0 && ((nextVac >> col) & 1) == 0)
            ans = min(ans, calcCell(row, downMask, vacMask, col + 1, nextDown, nextVac | (1 << col)));
        if (col > 0 && dst[row][col - 1] == src[row][col] && ((nextVac >> (col - 1)) & 1) == 0) {
            if (((downMask >> col) & 1) == 0 && ((nextVac >> col) & 1))
                ans = min(ans, 1 + calcCell(row, downMask, vacMask, col + 1, nextDown, nextVac | (1 << (col - 1))));
            else
                ans = min(ans, calcCell(row, downMask, vacMask, col + 1, nextDown, nextVac | (1 << (col - 1))));
        }
        if (dst[row][col + 1] == src[row][col])
            ans = min(ans, calcCell(row, downMask, vacMask, col + 1, nextDown, nextVac | (1 << (col + 1))));
        if (dst[row + 1][col] == src[row][col])
            ans = min(ans, calcCell(row, downMask, vacMask, col + 1, nextDown | (1 << col), nextVac));
        return ans;
    }

    int calcRow(int row, int downMask, int vacMask) {
        int fullMask = (1 << width) - 1;
        if (row == height) {
            if (downMask == 0 && vacMask == fullMask) return 0;
            return inf;
        }
        if (vis[row][downMask][vacMask] == testId) return dp[row][downMask][vacMask];
        vis[row][downMask][vacMask] = testId;
        dp[row][downMask][vacMask] = calcCell(row, downMask, vacMask, 0, 0, 0);
        return dp[row][downMask][vacMask];
    }

    int solve() {
        int ans;
        memset(src, 0, sizeof(src));
        memset(dst, 0, sizeof(dst));
        for (int i = 0; i < height; i++) {
            string a, b;
            cin >> a >> b;
            for (int j = 0; j < width; j++) {
                src[i][j] = a[j];
                dst[i][j] = b[j];
            }
        }
        ans = calcRow(0, 0, (1 << width) - 1);
        if (ans >= inf) return -1;
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    Solver solver;
    memset(solver.vis, 0, sizeof(solver.vis));
    for (int i = 1; i <= testCount; i++) {
        solver.testId = i;
        cin >> solver.width >> solver.height;
        cout << solver.solve() << '\n';
    }
    return 0;
}
