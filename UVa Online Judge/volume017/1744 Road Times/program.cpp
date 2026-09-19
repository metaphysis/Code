#include <bits/stdc++.h>
using namespace std;

using Real = long double;
const Real eps = 1e-12L;
const int infDist = 1000000000;

struct Simplex {
    int rowCount, colCount;
    vector<int> basic, nonBasic;
    vector<vector<Real>> tab;
    Simplex(const vector<vector<Real>>& a, const vector<Real>& b, const vector<Real>& c) {
        rowCount = (int)b.size();
        colCount = (int)c.size();
        basic.resize(rowCount);
        nonBasic.resize(colCount + 1);
        tab.assign(rowCount + 2, vector<Real>(colCount + 2, 0));
        for (int i = 0; i < rowCount; ++i) {
            for (int j = 0; j < colCount; ++j) tab[i][j] = a[i][j];
            basic[i] = colCount + i;
            tab[i][colCount] = -1;
            tab[i][colCount + 1] = b[i];
        }
        for (int j = 0; j < colCount; ++j) {
            nonBasic[j] = j;
            tab[rowCount][j] = -c[j];
        }
        nonBasic[colCount] = -1;
        tab[rowCount + 1][colCount] = 1;
    }

    void pivot(int row, int col) {
        Real inv = 1 / tab[row][col];
        for (int i = 0; i < rowCount + 2; ++i) {
            if (i == row) continue;
            for (int j = 0; j < colCount + 2; ++j) if (j != col) tab[i][j] -= tab[row][j] * tab[i][col] * inv;
            tab[i][col] *= -inv;
        }
        for (int j = 0; j < colCount + 2; ++j) if (j != col) tab[row][j] *= inv;
        tab[row][col] = inv;
        swap(basic[row], nonBasic[col]);
    }

    bool runPhase(int phase) {
        int objRow = phase == 1 ? rowCount + 1 : rowCount;
        while (true) {
            int row = -1, col = -1;
            for (int j = 0; j <= colCount; ++j) {
                if (phase == 2 && nonBasic[j] == -1) continue;
                if (tab[objRow][j] >= -eps) continue;
                if (col == -1 || nonBasic[j] < nonBasic[col]) col = j;
            }
            if (col == -1) return true;
            for (int i = 0; i < rowCount; ++i) {
                if (tab[i][col] <= eps) continue;
                if (row == -1) {
                    row = i;
                } else {
                    Real curRatio = tab[i][colCount + 1] / tab[i][col];
                    Real bestRatio = tab[row][colCount + 1] / tab[row][col];
                    if (curRatio < bestRatio - eps || (fabs(curRatio - bestRatio) <= eps && basic[i] < basic[row])) row = i;
                }
            }
            if (row == -1) return false;
            pivot(row, col);
        }
    }

    Real solve() {
        int row = -1;
        for (int i = 0; i < rowCount; ++i) if (row == -1 || tab[i][colCount + 1] < tab[row][colCount + 1]) row = i;
        if (row != -1 && tab[row][colCount + 1] < -eps) {
            pivot(row, colCount);
            if (!runPhase(1) || fabs(tab[rowCount + 1][colCount + 1]) > eps) return numeric_limits<Real>::quiet_NaN();
            for (int i = 0; i < rowCount; ++i) {
                if (basic[i] != -1) continue;
                int col = -1;
                for (int j = 0; j <= colCount; ++j) {
                    if (nonBasic[j] == -1 || fabs(tab[i][j]) <= eps) continue;
                    if (col == -1 || nonBasic[j] < nonBasic[col]) col = j;
                }
                if (col != -1) pivot(i, col);
            }
        }
        if (!runPhase(2)) return numeric_limits<Real>::infinity();
        return tab[rowCount][colCount + 1];
    }
};

vector<Real> getRoute(int src, int dst, int edgeCount, const vector<vector<int>>& nextCity, const vector<vector<int>>& edgeId) {
    vector<Real> route(edgeCount, 0);
    while (src != dst) {
        int next = nextCity[src][dst];
        route[edgeId[src][next]] = 1;
        src = next;
    }
    return route;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
    int cityCount;
    while (cin >> cityCount) {
        vector<vector<int>> dist(cityCount, vector<int>(cityCount, infDist));
        vector<vector<int>> nextCity(cityCount, vector<int>(cityCount, -1));
        vector<vector<int>> edgeId(cityCount, vector<int>(cityCount, -1));
        vector<int> edgeLen;
        for (int i = 0; i < cityCount; ++i) {
            for (int j = 0; j < cityCount; ++j) {
                int len;
                cin >> len;
                if (i == j) {
                    dist[i][j] = 0;
                    nextCity[i][j] = j;
                } else if (len != -1) {
                    dist[i][j] = len;
                    nextCity[i][j] = j;
                    edgeId[i][j] = (int)edgeLen.size();
                    edgeLen.push_back(len);
                }
            }
        }
        for (int k = 0; k < cityCount; ++k) {
            for (int i = 0; i < cityCount; ++i) {
                if (dist[i][k] == infDist) continue;
                for (int j = 0; j < cityCount; ++j) {
                    if (dist[k][j] == infDist) continue;
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        nextCity[i][j] = nextCity[i][k];
                    }
                }
            }
        }
        int edgeCount = (int)edgeLen.size(), recordCount, queryCount;
        vector<vector<Real>> a;
        vector<Real> b;
        for (int i = 0; i < edgeCount; ++i) {
            vector<Real> row(edgeCount, 0);
            row[i] = 1;
            a.push_back(row);
            b.push_back(edgeLen[i]);
        }
        cin >> recordCount;
        for (int i = 0; i < recordCount; ++i) {
            int src, dst, time;
            cin >> src >> dst >> time;
            vector<Real> row = getRoute(src, dst, edgeCount, nextCity, edgeId);
            Real extra = (Real)time - dist[src][dst];
            a.push_back(row);
            b.push_back(extra);
            for (int j = 0; j < edgeCount; ++j) row[j] = -row[j];
            a.push_back(row);
            b.push_back(-extra);
        }
        cin >> queryCount;
        for (int i = 0; i < queryCount; ++i) {
            int src, dst;
            cin >> src >> dst;
            vector<Real> obj = getRoute(src, dst, edgeCount, nextCity, edgeId);
            Real high, low;
            Simplex maxSolver(a, b, obj);
            high = dist[src][dst] + maxSolver.solve();
            for (int j = 0; j < edgeCount; ++j) obj[j] = -obj[j];
            Simplex minSolver(a, b, obj);
            low = dist[src][dst] - minSolver.solve();
            if (fabs(low) < eps) low = 0;
            if (fabs(high) < eps) high = 0;
            cout << src << ' ' << dst << ' ' << low << ' ' << high << '\n';
        }
    }
    return 0;
}
