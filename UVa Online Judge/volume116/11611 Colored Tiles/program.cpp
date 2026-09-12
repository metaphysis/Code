// Colored Tiles
// UVa ID: 11611
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.660s

#include <bits/stdc++.h>
using namespace std;

template <class T>
inline T bigMod(T p, T e, T M) {
    if (e == 0) {
        return 1;
    }
    if (e % 2 == 0) {
        long long t = bigMod(p, e / 2, M);
        return (T)((t * t) % M);
    }
    return (T)(((long long)bigMod(p, e - 1, M) * (long long)(p)) % M);
}

template <class T>
inline T gcdVal(T a, T b) {
    if (b == 0) {
        return a;
    }
    return gcdVal(b, a % b);
}

template <class T>
inline T modInverse(T a, T M) {
    return bigMod(a, M - 2, M);
}

int md = 50431;
int rowCount, colCount;
int dpTable[1 << 16][20][10];
char grid[9][21];

int dfs(int bitMask, int curCol, int row) {
    if (bitMask == 0 && curCol == colCount - 1) {
        return 1;
    }
    if (bitMask < 1 << rowCount) {
        bitMask = bitMask << rowCount;
        for (int j = 0; j < rowCount; ++j) {
            if (grid[j][curCol + 2] != '#') {
                bitMask |= 1 << j;
            }
        }
        return dfs(bitMask, curCol + 1, 0);
    }
    if (row == rowCount) {
        return 0;
    }
    if (dpTable[bitMask][curCol][row] != -1) {
        return dpTable[bitMask][curCol][row];
    }
    int& res = dpTable[bitMask][curCol][row];
    res = dfs(bitMask, curCol, row + 1);
    if ((bitMask & 1 << (row + rowCount)) == 0) {
        return res;
    }
    if (grid[row][curCol] == '#') {
        return res;
    }
    if (row > 0 && rowCount > 1) {
        if ((grid[row][curCol] == '.' || grid[row][curCol] == 'R') &&
            (bitMask & 1 << (row + rowCount)) > 0 &&
            (grid[row - 1][curCol] == '.' || grid[row - 1][curCol] == 'R') &&
            (bitMask & 1 << (row + rowCount - 1)) > 0 &&
            (grid[row][curCol + 1] == '.' || grid[row][curCol + 1] == 'R') &&
            (bitMask & 1 << row) > 0) {
            long long nb = bitMask & ~(1 << (row + rowCount));
            nb = nb & ~(1 << (row + rowCount - 1));
            nb = nb & ~(1 << row);
            res = (res + dfs((int)nb, curCol, row + 1)) % md;
        }
        if ((grid[row][curCol] == '.' || grid[row][curCol] == 'G') &&
            (bitMask & 1 << (row + rowCount)) > 0 &&
            (grid[row - 1][curCol + 1] == '.' || grid[row - 1][curCol + 1] == 'G') &&
            (bitMask & 1 << (row - 1)) > 0 &&
            (grid[row][curCol + 1] == '.' || grid[row][curCol + 1] == 'G') &&
            (bitMask & 1 << row) > 0) {
            long long nb = bitMask & ~(1 << (row + rowCount));
            nb = nb & ~(1 << (row - 1));
            nb = nb & ~(1 << row);
            res = (res + dfs((int)nb, curCol, row + 1)) % md;
        }
        if ((grid[row][curCol] == '.' || grid[row][curCol] == 'B') &&
            (bitMask & 1 << (row + rowCount)) > 0 &&
            (grid[row - 1][curCol] == '.' || grid[row - 1][curCol] == 'B') &&
            (bitMask & 1 << (row + rowCount - 1)) > 0 &&
            (grid[row - 1][curCol + 1] == '.' || grid[row - 1][curCol + 1] == 'B') &&
            (bitMask & 1 << (row - 1)) > 0) {
            long long nb = bitMask & ~(1 << (row + rowCount));
            nb = nb & ~(1 << (row + rowCount - 1));
            nb = nb & ~(1 << (row - 1));
            res = (res + dfs((int)nb, curCol, row + 1)) % md;
        }
        if ((grid[row][curCol] == '.' || grid[row][curCol] == 'W') &&
            (bitMask & 1 << (row + rowCount)) > 0 &&
            (grid[row - 1][curCol] == '.' || grid[row - 1][curCol] == 'W') &&
            (bitMask & 1 << (row + rowCount - 1)) > 0) {
            long long nb = bitMask & ~(1 << (row + rowCount));
            nb = nb & ~(1 << (row + rowCount - 1));
            res = (res + dfs((int)nb, curCol, row + 1)) % md;
        }
    }
    if ((grid[row][curCol] == '.' || grid[row][curCol] == 'P') &&
        (bitMask & 1 << (row + rowCount)) > 0 &&
        (grid[row][curCol + 1] == '.' || grid[row][curCol + 1] == 'P') &&
        (bitMask & 1 << row) > 0) {
        long long nb = bitMask & ~(1 << (row + rowCount));
        nb = nb & ~(1 << row);
        res = (res + dfs((int)nb, curCol, row + 1)) % md;
    }
    if ((grid[row][curCol] == '.' || grid[row][curCol] == 'L') &&
        (bitMask & 1 << (row + rowCount)) > 0) {
        long long nb = bitMask & ~(1 << (row + rowCount));
        res = (res + dfs((int)nb, curCol, row + 1)) % md;
    }
    if (row < rowCount - 1 && rowCount > 1) {
        if ((grid[row][curCol + 1] == '.' || grid[row][curCol + 1] == 'N') &&
            (bitMask & 1 << row) > 0 &&
            (grid[row][curCol] == '.' || grid[row][curCol] == 'N') &&
            (bitMask & 1 << (row + rowCount)) > 0 &&
            (grid[row + 1][curCol + 1] == '.' || grid[row + 1][curCol + 1] == 'N') &&
            (bitMask & 1 << (row + 1)) > 0) {
            long long nb = bitMask & ~(1 << row);
            nb = nb & ~(1 << (row + rowCount));
            nb = nb & ~(1 << (row + 1));
            res = (res + dfs((int)nb, curCol, row + 1)) % md;
        }
    }
    return res;
}

int main() {
    int testCases;
    cin >> testCases;
    int caseNo = 1;
    while (testCases--) {
        cout << "Case " << caseNo++ << ": ";
        cin >> rowCount >> colCount;
        memset(dpTable, -1, sizeof dpTable);
        memset(grid, 0, sizeof grid);
        for (int i = 0; i < rowCount; ++i) {
            cin >> grid[i];
            grid[i][colCount] = '#';
        }
        int initialMask = 0;
        for (int i = 0; i < rowCount; ++i) {
            if (grid[i][1] != '#') {
                initialMask |= 1 << i;
            }
            if (grid[i][0] != '#') {
                initialMask |= 1 << (i + rowCount);
            }
        }
        cout << dfs(initialMask, 0, 0) << endl;
    }
    return 0;
}
