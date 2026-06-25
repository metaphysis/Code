// Rational Resistors
// UVa ID: 10808
// Verdict: Accepted
// Submission Date: 2026-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 分数类，使用 __int128 辅助运算
class Fraction {
public:
    long long num, den; // den > 0
    Fraction(long long n = 0, long long d = 1) {
        if (d < 0) { n = -n; d = -d; }
        __int128 g = gcd128((__int128)llabs(n), (__int128)d);
        num = (long long)((__int128)n / g);
        den = (long long)((__int128)d / g);
    }
    Fraction operator+(const Fraction& o) const {
        __int128 n = (__int128)num * o.den + (__int128)o.num * den;
        __int128 d = (__int128)den * o.den;
        return makeFraction(n, d);
    }
    Fraction operator-(const Fraction& o) const {
        __int128 n = (__int128)num * o.den - (__int128)o.num * den;
        __int128 d = (__int128)den * o.den;
        return makeFraction(n, d);
    }
    Fraction operator*(const Fraction& o) const {
        __int128 n = (__int128)num * o.num;
        __int128 d = (__int128)den * o.den;
        return makeFraction(n, d);
    }
    Fraction operator/(const Fraction& o) const {
        __int128 n = (__int128)num * o.den;
        __int128 d = (__int128)den * o.num;
        return makeFraction(n, d);
    }
    bool operator==(const Fraction& o) const {
        return num == o.num && den == o.den;
    }
    bool operator!=(const Fraction& o) const {
        return !(*this == o);
    }
    // 绝对值比较：a 的绝对值是否小于 b 的绝对值
    static bool absLess(const Fraction& a, const Fraction& b) {
        __int128 lhs = (__int128)llabs(a.num) * b.den;
        __int128 rhs = (__int128)llabs(b.num) * a.den;
        return lhs < rhs;
    }
private:
    static __int128 gcd128(__int128 a, __int128 b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b) {
            __int128 t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    static Fraction makeFraction(__int128 n, __int128 d) {
        if (d < 0) { n = -n; d = -d; }
        __int128 g = gcd128(n, d);
        n /= g;
        d /= g;
        return Fraction((long long)n, (long long)d);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    for (int caseNo = 1; caseNo <= N; ++caseNo) {
        int n, m;
        cin >> n >> m;

        vector<vector<Fraction>> G(n, vector<Fraction>(n));
        vector<int> parent(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
        function<int(int)> findParent = [&](int x) -> int {
            return parent[x] == x ? x : parent[x] = findParent(parent[x]);
        };
        auto unite = [&](int a, int b) {
            int ra = findParent(a), rb = findParent(b);
            if (ra != rb) parent[ra] = rb;
        };

        for (int i = 0; i < m; ++i) {
            int u, v, r;
            cin >> u >> v >> r;
            if (u == v) continue;
            Fraction g(1, r);
            G[u][v] = G[u][v] + g;
            G[v][u] = G[v][u] + g;
            unite(u, v);
        }

        int Q;
        cin >> Q;
        cout << "Case #" << caseNo << ":\n";

        while (Q--) {
            int A, B;
            cin >> A >> B;

            if (A == B) {
                cout << "Resistance between " << A << " and " << B << " is 0/1\n";
                continue;
            }
            if (findParent(A) != findParent(B)) {
                cout << "Resistance between " << A << " and " << B << " is 1/0\n";
                continue;
            }

            int K = n - 1;
            vector<vector<Fraction>> mat(K, vector<Fraction>(K));
            vector<Fraction> b(K);

            vector<Fraction> self(n);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    self[i] = self[i] + G[i][j];

            for (int i = 1; i < n; ++i) {
                int row = i - 1;
                for (int j = 1; j < n; ++j) {
                    if (i == j) mat[row][j - 1] = self[i];
                    else        mat[row][j - 1] = Fraction(0, 1) - G[i][j];
                }
                Fraction cur;
                if (i == A)      cur = Fraction(1, 1);
                else if (i == B) cur = Fraction(-1, 1);
                else             cur = Fraction(0, 1);
                b[row] = cur;
            }

            // 高斯-若尔当消元，选主元并归一化
            for (int col = 0; col < K; ++col) {
                // 选主元：col 行以下绝对值最大
                int pivot = col;
                for (int row = col + 1; row < K; ++row)
                    if (Fraction::absLess(mat[pivot][col], mat[row][col]))
                        pivot = row;
                if (pivot != col) {
                    swap(mat[col], mat[pivot]);
                    swap(b[col], b[pivot]);
                }
                Fraction pivotVal = mat[col][col];
                // 归一化主元行
                for (int j = col; j < K; ++j)
                    mat[col][j] = mat[col][j] / pivotVal;
                b[col] = b[col] / pivotVal;

                // 消去其他行
                for (int row = 0; row < K; ++row) {
                    if (row == col) continue;
                    if (mat[row][col] == Fraction(0, 1)) continue;
                    Fraction factor = mat[row][col];
                    for (int j = col; j < K; ++j)
                        mat[row][j] = mat[row][j] - factor * mat[col][j];
                    b[row] = b[row] - factor * b[col];
                }
            }

            vector<Fraction> V(K);
            for (int i = 0; i < K; ++i)
                V[i] = b[i]; // 因为主元已归一化为1

            Fraction res;
            if (A == 0)      res = Fraction(0, 1) - V[B - 1];
            else if (B == 0) res = V[A - 1] - Fraction(0, 1);
            else             res = V[A - 1] - V[B - 1];

            if (res.num < 0) res.num = -res.num;

            cout << "Resistance between " << A << " and " << B << " is "
                 << res.num << "/" << res.den << "\n";
        }
        cout << "\n";
    }
    return 0;
}
