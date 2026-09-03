#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

struct Block {
    int row, col;
};

int p, q;

bool getMove(int row1, int col1, int row2, int col2, int &cntA, int &cntB) {
    int dr = row2 - row1, dc = col2 - col1;
    if (dr < 0 || dc < 0)
        return false;
    if (p == q) {
        if (dr != dc || dr % p != 0)
            return false;
        cntA = dr / p;
        cntB = 0;
        return true;
    }
    int den = p * p - q * q;
    int numA = p * dr - q * dc, numB = p * dc - q * dr;
    if (numA % den != 0 || numB % den != 0)
        return false;
    cntA = numA / den;
    cntB = numB / den;
    if (cntA < 0 || cntB < 0)
        return false;
    return true;
}

cpp_int getComb(int n, int k) {
    k = min(k, n - k);
    cpp_int ans = 1;
    for (int i = 1; i <= k; i++)
        ans = ans * (n - k + i) / i;
    return ans;
}

cpp_int getWays(int row1, int col1, int row2, int col2) {
    int cntA, cntB;
    if (!getMove(row1, col1, row2, col2, cntA, cntB))
        return 0;
    if (p == q)
        return 1;
    return getComb(cntA + cntB, cntA);
}

bool cmpBlock(const Block &a, const Block &b) {
    if (a.row + a.col != b.row + b.col)
        return a.row + a.col < b.row + b.col;
    if (a.row != b.row)
        return a.row < b.row;
    return a.col < b.col;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n, b, caseId = 0;
    while (cin >> m >> n >> p >> q >> b) {
        if (m == 0 && n == 0)
            break;
        vector<Block> blocks(b);
        bool blockedStart = false, blockedEnd = false;
        for (int i = 0; i < b; i++) {
            cin >> blocks[i].row >> blocks[i].col;
            if (blocks[i].row == 0 && blocks[i].col == 0)
                blockedStart = true;
            if (blocks[i].row == m - 1 && blocks[i].col == n - 1)
                blockedEnd = true;
        }
        cout << "Case " << ++caseId << ": ";
        int cntA, cntB;
        if (blockedStart || blockedEnd || !getMove(0, 0, m - 1, n - 1, cntA, cntB)) {
            cout << "Impossible\n";
            continue;
        }
        sort(blocks.begin(), blocks.end(), cmpBlock);
        vector<cpp_int> dp(b);
        for (int i = 0; i < b; i++) {
            dp[i] = getWays(0, 0, blocks[i].row, blocks[i].col);
            for (int j = 0; j < i; j++)
                dp[i] -= getWays(blocks[j].row, blocks[j].col, blocks[i].row, blocks[i].col) * dp[j];
        }
        cpp_int ans = getWays(0, 0, m - 1, n - 1);
        for (int i = 0; i < b; i++)
            ans -= getWays(blocks[i].row, blocks[i].col, m - 1, n - 1) * dp[i];
        if (ans == 0)
            cout << "Impossible\n";
        else
            cout << cntA + cntB << ' ' << ans << '\n';
    }
    return 0;
}
