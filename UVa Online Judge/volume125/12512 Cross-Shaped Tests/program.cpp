#include <bits/stdc++.h>
using namespace std;

struct Simplex {
    static constexpr long double EPS = 1e-10L;
    static constexpr long double INF = 1e100L;
    int m;
    int n;
    vector<int> B;
    vector<int> N;
    vector<vector<long double>> D;
    Simplex(const vector<vector<long double>> &A, const vector<long double> &b, const vector<long double> &c) {
        m = b.size();
        n = c.size();
        B.resize(m);
        N.resize(n + 1);
        D.assign(m + 2, vector<long double>(n + 2, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) D[i][j] = A[i][j];
        }
        for (int i = 0; i < m; ++i) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; ++j) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }
    void pivot(int r, int s) {
        long double inv = 1.0L / D[r][s];
        for (int i = 0; i < m + 2; ++i) {
            if (i == r) continue;
            for (int j = 0; j < n + 2; ++j) {
                if (j == s) continue;
                D[i][j] -= D[r][j] * D[i][s] * inv;
            }
        }
        for (int j = 0; j < n + 2; ++j) {
            if (j != s) D[r][j] *= inv;
        }
        for (int i = 0; i < m + 2; ++i) {
            if (i != r) D[i][s] *= -inv;
        }
        D[r][s] = inv;
        swap(B[r], N[s]);
    }
    bool simplex(int phase) {
        int objectiveRow = (phase == 1 ? m + 1 : m);
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; ++j) {
                if (phase == 2 && N[j] == -1) continue;
                if (s == -1 || D[objectiveRow][j] < D[objectiveRow][s] - EPS || (fabsl(D[objectiveRow][j] - D[objectiveRow][s]) <= EPS && N[j] < N[s])) {
                    s = j;
                }
            }
            if (s == -1 || D[objectiveRow][s] >= -EPS) return true;
            int r = -1;
            for (int i = 0; i < m; ++i) {
                if (D[i][s] <= EPS) continue;
                if (r == -1) {
                    r = i;
                    continue;
                }
                long double lhs = D[i][n + 1] / D[i][s];
                long double rhs = D[r][n + 1] / D[r][s];
                if (lhs < rhs - EPS || (fabsl(lhs - rhs) <= EPS && B[i] < B[r])) {
                    r = i;
                }
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }
    int solve(vector<long double> &x, long double &value) {
        int r = 0;
        for (int i = 1; i < m; ++i) {
            if (D[i][n + 1] < D[r][n + 1]) r = i;
        }
        if (D[r][n + 1] < -EPS) {
            pivot(r, n);
            if (!simplex(1)) return -1;
            if (D[m + 1][n + 1] < -EPS) return -1;
            if (fabsl(D[m + 1][n + 1]) > EPS) return -1;
            for (int i = 0; i < m; ++i) {
                if (B[i] != -1) continue;
                int s = 0;
                for (int j = 1; j <= n; ++j) {
                    if (D[i][j] < D[i][s] - EPS || (fabsl(D[i][j] - D[i][s]) <= EPS && N[j] < N[s])) {
                        s = j;
                    }
                }
                if (fabsl(D[i][s]) > EPS) pivot(i, s);
            }
        }
        if (!simplex(2)) return 1;
        x.assign(n, 0);
        for (int i = 0; i < m; ++i) {
            if (B[i] < n) x[B[i]] = D[i][n + 1];
        }
        value = D[m][n + 1];
        return 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int n, q;
        long double c, d, f, e;
        cin >> n >> c >> d >> f >> e >> q;
        int cellCount = n * n;
        int variableCount = 2 * cellCount;
        vector<vector<long double>> a(n, vector<long double>(n));
        vector<long double> rowSum(n, 0);
        vector<long double> columnSum(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> a[i][j];
                rowSum[i] += a[i][j];
                columnSum[j] += a[i][j];
            }
        }
        vector<pair<int, int>> tests;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        for (int k = 0; k < q; ++k) {
            int x, y;
            cin >> x >> y;
            --x;
            --y;
            if (!visited[x][y]) {
                visited[x][y] = true;
                tests.push_back({x, y});
            }
        }
        int constraintCount = 2 * static_cast<int>(tests.size());
        vector<vector<long double>> A(constraintCount, vector<long double>(variableCount, 0));
        vector<long double> b(constraintCount, 0);
        vector<long double> objective(variableCount, 0);
        for (int i = 0; i < cellCount; ++i) {
            objective[i] = -c;
            objective[i + cellCount] = -d;
        }
        long double target = (2.0L * n - 1.0L) * f;
        for (int k = 0; k < static_cast<int>(tests.size()); ++k) {
            int x = tests[k].first;
            int y = tests[k].second;
            long double originalSum = rowSum[x] + columnSum[y] - a[x][y];
            b[2 * k] = target + e - originalSum;
            b[2 * k + 1] = originalSum - target + e;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i != x && j != y) continue;
                    int index = i * n + j;
                    A[2 * k][index] = 1;
                    A[2 * k][index + cellCount] = -1;
                    A[2 * k + 1][index] = -1;
                    A[2 * k + 1][index + cellCount] = 1;
                }
            }
        }
        vector<long double> answer;
        long double maximumNegativeCost = 0;
        Simplex solver(A, b, objective);
        int status = solver.solve(answer, maximumNegativeCost);
        if (status == -1) {
            cout << "-1.00000\n";
            continue;
        }
        if (status == 1) {
            cout << "-1.00000\n";
            continue;
        }
        long double result = -maximumNegativeCost;
        if (fabsl(result) < 0.00000001L) result = 0;
        cout << fixed << setprecision(5) << static_cast<double>(result) << '\n';
    }
    return 0;
}
