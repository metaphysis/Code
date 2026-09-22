#include <bits/stdc++.h>
using namespace std;

using Real = long double;
const Real eps = 1e-10L;
const Real roundEps = 1e-7L;

struct Simplex {
    int rowCnt, colCnt;
    vector<int> basic, nonBasic;
    vector<vector<Real>> tab;
    Simplex(const vector<vector<Real>>& a, const vector<Real>& rhs, int varCnt)
        : rowCnt((int)a.size()), colCnt(varCnt),
          basic(rowCnt), nonBasic(colCnt + 1),
          tab(rowCnt + 2, vector<Real>(colCnt + 2, 0)) {
        for (int i = 0; i < rowCnt; i++) {
            for (int j = 0; j < colCnt; j++) tab[i][j] = a[i][j];
            basic[i] = colCnt + i;
            tab[i][colCnt] = -1;
            tab[i][colCnt + 1] = rhs[i];
        }
        for (int j = 0; j < colCnt; j++) nonBasic[j] = j;
        nonBasic[colCnt] = -1;
        tab[rowCnt + 1][colCnt] = 1;
    }

    void pivot(int row, int col) {
        Real inv = 1 / tab[row][col];
        for (int i = 0; i < rowCnt + 2; i++) {
            if (i == row || tab[i][col] == 0) continue;
            Real factor = tab[i][col] * inv;
            for (int j = 0; j < colCnt + 2; j++) {
                if (j != col) tab[i][j] -= tab[row][j] * factor;
            }
            tab[i][col] = -factor;
        }
        for (int j = 0; j < colCnt + 2; j++) {
            if (j != col) tab[row][j] *= inv;
        }
        tab[row][col] = inv;
        swap(basic[row], nonBasic[col]);
    }

    bool run(int phase) {
        int objRow = phase == 1 ? rowCnt + 1 : rowCnt, degCnt = 0;
        bool useBland = false;
        while (true) {
            int col = -1, row = -1;
            for (int j = 0; j <= colCnt; j++) {
                if (nonBasic[j] == -1 || tab[objRow][j] >= -eps) continue;
                if (col == -1) col = j;
                else if (useBland) {
                    if (nonBasic[j] < nonBasic[col]) col = j;
                } else if (tab[objRow][j] < tab[objRow][col] - eps) col = j;
                else if (fabsl(tab[objRow][j] - tab[objRow][col]) <= eps) {
                    if (nonBasic[j] < nonBasic[col]) col = j;
                }
            }
            if (col == -1) return true;
            for (int i = 0; i < rowCnt; i++) {
                if (tab[i][col] <= eps) continue;
                if (row == -1) {
                    row = i;
                    continue;
                }
                Real curRatio = tab[i][colCnt + 1] / tab[i][col];
                Real bestRatio = tab[row][colCnt + 1] / tab[row][col];
                if (curRatio < bestRatio - eps) row = i;
                else if (fabsl(curRatio - bestRatio) <= eps) {
                    if (basic[i] < basic[row]) row = i;
                }
            }
            if (row == -1) return false;
            if (tab[row][colCnt + 1] <= eps) degCnt++;
            else degCnt = 0;
            if (degCnt > rowCnt) useBland = true;
            pivot(row, col);
        }
    }

    bool init() {
        int row = -1;
        for (int i = 0; i < rowCnt; i++) {
            if (row == -1 || tab[i][colCnt + 1] < tab[row][colCnt + 1]) row = i;
        }
        if (row == -1 || tab[row][colCnt + 1] >= -eps) return true;
        pivot(row, colCnt);
        if (!run(1)) return false;
        if (fabsl(tab[rowCnt + 1][colCnt + 1]) > eps) return false;
        for (int i = 0; i < rowCnt; i++) {
            if (basic[i] != -1) continue;
            int col = -1;
            for (int j = 0; j <= colCnt; j++) {
                if (nonBasic[j] == -1 || fabsl(tab[i][j]) <= eps) continue;
                if (col == -1 || fabsl(tab[i][j]) > fabsl(tab[i][col])) col = j;
            }
            if (col != -1) pivot(i, col);
        }
        return true;
    }

    Real maximize(const vector<Real>& obj) {
        fill(tab[rowCnt].begin(), tab[rowCnt].end(), 0);
        for (int j = 0; j <= colCnt; j++) {
            if (nonBasic[j] >= 0 && nonBasic[j] < colCnt) tab[rowCnt][j] = -obj[nonBasic[j]];
        }
        for (int i = 0; i < rowCnt; i++) {
            if (basic[i] < 0 || basic[i] >= colCnt) continue;
            Real factor = obj[basic[i]];
            if (factor == 0) continue;
            for (int j = 0; j < colCnt + 2; j++) tab[rowCnt][j] += factor * tab[i][j];
        }
        run(2);
        return tab[rowCnt][colCnt + 1];
    }
};

bool eliminate(vector<vector<Real>>& eq, int n, vector<int>& pivotCols) {
    int m = (int)eq.size(), rank = 0;
    for (int col = 0; col < n && rank < m; col++) {
        int pivotRow = rank;
        for (int i = rank + 1; i < m; i++) {
            if (fabsl(eq[i][col]) > fabsl(eq[pivotRow][col])) pivotRow = i;
        }
        if (fabsl(eq[pivotRow][col]) <= eps) continue;
        swap(eq[rank], eq[pivotRow]);
        Real div = eq[rank][col];
        for (int j = col; j <= n; j++) eq[rank][j] /= div;
        eq[rank][col] = 1;
        for (int i = 0; i < m; i++) {
            if (i == rank) continue;
            Real factor = eq[i][col];
            eq[i][col] = 0;
            if (factor == 0) continue;
            for (int j = col + 1; j <= n; j++) eq[i][j] -= factor * eq[rank][j];
        }
        pivotCols.push_back(col);
        rank++;
    }
    for (int i = rank; i < m; i++) {
        if (fabsl(eq[i][n]) > eps) return false;
    }
    return true;
}

void solve(int n, int m) {
    vector<int> low(n), high(n), pivotCols, freeCols, isPivot(n, 0);
    vector<vector<Real>> eq(m, vector<Real>(n + 1, 0));
    for (int i = 0; i < n; i++) cin >> low[i] >> high[i];
    for (int i = 0; i < m; i++) {
        int leftCnt, rightCnt, diff, id;
        cin >> leftCnt >> rightCnt >> diff;
        eq[i][n] = diff;
        for (int j = 0; j < leftCnt; j++) {
            cin >> id;
            id--;
            eq[i][id] += 1;
            eq[i][n] -= low[id];
        }
        for (int j = 0; j < rightCnt; j++) {
            cin >> id;
            id--;
            eq[i][id] -= 1;
            eq[i][n] += low[id];
        }
    }
    if (!eliminate(eq, n, pivotCols)) {
        cout << " -1\n";
        return;
    }
    for (int col : pivotCols) isPivot[col] = 1;
    for (int i = 0; i < n; i++) {
        if (!isPivot[i]) freeCols.push_back(i);
    }
    int rank = (int)pivotCols.size(), varCnt = (int)freeCols.size();
    vector<Real> shift(n, 0), rhs, obj(varCnt);
    vector<vector<Real>> expr(n, vector<Real>(varCnt, 0)), a;
    for (int j = 0; j < varCnt; j++) expr[freeCols[j]][j] = 1;
    for (int i = 0; i < rank; i++) {
        int col = pivotCols[i];
        shift[col] = eq[i][n];
        for (int j = 0; j < varCnt; j++) expr[col][j] = -eq[i][freeCols[j]];
    }
    for (int i = 0; i < n; i++) {
        a.push_back(expr[i]);
        rhs.push_back(high[i] - low[i] - shift[i]);
        if (isPivot[i]) {
            vector<Real> row(varCnt);
            for (int j = 0; j < varCnt; j++) row[j] = -expr[i][j];
            a.push_back(row);
            rhs.push_back(shift[i]);
        }
    }
    Simplex lp(a, rhs, varCnt);
    if (!lp.init()) {
        cout << " -1\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        bool isFixed = true;
        for (int j = 0; j < varCnt; j++) {
            if (expr[i][j] != 0) isFixed = false;
        }
        Real minVal = low[i] + shift[i], maxVal = minVal;
        if (!isFixed) {
            for (int j = 0; j < varCnt; j++) obj[j] = -expr[i][j];
            minVal -= lp.maximize(obj);
            for (int j = 0; j < varCnt; j++) obj[j] = expr[i][j];
            maxVal += lp.maximize(obj);
        }
        minVal = max((Real)low[i], min((Real)high[i], minVal));
        maxVal = max((Real)low[i], min((Real)high[i], maxVal));
        int ansLow = (int)floorl(minVal + roundEps), ansHigh = (int)ceill(maxVal - roundEps);
        cout << ' ' << ansLow << ' ' << ansHigh;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, caseId = 0;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        cout << "Case " << ++caseId << ':';
        solve(n, m);
    }
    return 0;
}
