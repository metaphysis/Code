#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;
using BigInt = cpp_int;
using Matrix = vector<vector<BigInt>>;

BigInt bigGcd(BigInt a, BigInt b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        BigInt rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

BigInt powerTen(int exp) {
    BigInt result = 1;
    for (int i = 0; i < exp; ++i) result *= 10;
    return result;
}

BigInt parseDecimal(const string &text, int maxDigits) {
    BigInt result = 0;
    int digits = 0;
    bool afterDot = false;
    for (char ch : text) {
        if (ch == '.') afterDot = true;
        else {
            result = result * 10 + (ch - '0');
            if (afterDot) ++digits;
        }
    }
    for (int i = digits; i < maxDigits; ++i) result *= 10;
    return result;
}

BigInt roundHalfUp(const BigInt &num, const BigInt &den) {
    return (num * 2 + den) / (den * 2);
}

Matrix multiply(const Matrix &a, const Matrix &b) {
    int n = a.size();
    Matrix result(n, vector<BigInt>(n));
    for (int i = 0; i < n; ++i) {
        for (int mid = 0; mid < n; ++mid) {
            if (a[i][mid] == 0) continue;
            for (int j = 0; j < n; ++j) {
                if (b[mid][j] != 0) result[i][j] += a[i][mid] * b[mid][j];
            }
        }
    }
    return result;
}

Matrix matrixPower(Matrix base, int exp) {
    int n = base.size();
    Matrix result(n, vector<BigInt>(n));
    for (int i = 0; i < n; ++i) result[i][i] = 1;
    while (exp > 0) {
        if (exp & 1) result = multiply(result, base);
        exp >>= 1;
        if (exp > 0) base = multiply(base, base);
    }
    return result;
}

void pivot(Matrix &tab, BigInt &den, int row, int col) {
    int rowCount = tab.size(), colCount = tab[row].size();
    BigInt pivotVal = tab[row][col];
    for (int i = 0; i < rowCount; ++i) {
        if (i == row) continue;
        BigInt factor = tab[i][col];
        if (factor == 0 && pivotVal == den) continue;
        for (int j = 0; j < colCount; ++j) {
            if (j == col) continue;
            if (tab[i][j] == 0 && (factor == 0 || tab[row][j] == 0)) continue;
            BigInt value = pivotVal * tab[i][j];
            if (factor != 0 && tab[row][j] != 0) value -= factor * tab[row][j];
            if (den != 1) value /= den;
            tab[i][j] = value;
        }
        tab[i][col] = 0;
    }
    den = pivotVal;
    if (den < 0) {
        den = -den;
        for (auto &line : tab) {
            for (BigInt &value : line) value = -value;
        }
    }
}

bool invertMatrix(const Matrix &a, Matrix &inv, BigInt &den) {
    int n = a.size();
    Matrix tab(n, vector<BigInt>(n * 2));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) tab[i][j] = a[i][j];
        tab[i][n + i] = 1;
    }
    den = 1;
    for (int col = 0; col < n; ++col) {
        int row = col;
        while (row < n && tab[row][col] == 0) ++row;
        if (row == n) return false;
        if (row != col) swap(tab[row], tab[col]);
        pivot(tab, den, col, col);
    }
    inv.assign(n, vector<BigInt>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) inv[i][j] = tab[i][n + j];
    }
    return true;
}

void simplex(Matrix &tab, vector<int> &basis, BigInt &den, int enterLimit) {
    int rowCount = basis.size(), rhsCol = tab[0].size() - 1;
    while (true) {
        int enterCol = -1, leaveRow = -1;
        for (int j = 0; j < enterLimit; ++j) {
            if (tab[rowCount][j] < 0) {
                enterCol = j;
                break;
            }
        }
        if (enterCol == -1) return;
        for (int i = 0; i < rowCount; ++i) {
            if (tab[i][enterCol] <= 0) continue;
            if (leaveRow == -1) {
                leaveRow = i;
                continue;
            }
            BigInt left = tab[i][rhsCol] * tab[leaveRow][enterCol];
            BigInt right = tab[leaveRow][rhsCol] * tab[i][enterCol];
            if (left < right || (left == right && basis[i] < basis[leaveRow])) leaveRow = i;
        }
        // 两个阶段的目标函数均有上界
        assert(leaveRow != -1);
        pivot(tab, den, leaveRow, enterCol);
        basis[leaveRow] = enterCol;
    }
}

bool solveSingular(Matrix a, vector<BigInt> b, vector<BigInt> &answer, BigInt &answerDen) {
    int n = a.size(), varCount = n * 2;
    Matrix tab(n + 1, vector<BigInt>(varCount + 1));
    vector<int> basis(n);
    BigInt den = 1;
    for (int i = 0; i < n; ++i) {
        BigInt rowGcd = b[i];
        for (int j = 0; j < n; ++j) {
            rowGcd = bigGcd(rowGcd, a[i][j]);
            if (rowGcd == 1) break;
        }
        if (rowGcd > 1) {
            b[i] /= rowGcd;
            for (int j = 0; j < n; ++j) a[i][j] /= rowGcd;
        }
        for (int j = 0; j < n; ++j) {
            tab[i][j] = a[i][j];
            tab[n][j] -= a[i][j];
        }
        tab[i][n + i] = 1;
        tab[i][varCount] = b[i];
        tab[n][varCount] -= b[i];
        basis[i] = n + i;
    }
    // 第一阶段：最大化人工变量之和的相反数
    simplex(tab, basis, den, varCount);
    tab.pop_back();
    // 删除人工变量列，保留原变量和右端常数
    for (auto &line : tab) {
        BigInt rhs = line[varCount];
        line.resize(n + 1);
        line[n] = rhs;
    }
    int row = 0;
    while (row < (int)basis.size()) {
        if (basis[row] < n) {
            ++row;
            continue;
        }
        int enterCol = -1;
        for (int j = 0; j < n; ++j) {
            if (tab[row][j] != 0) {
                enterCol = j;
                break;
            }
        }
        if (enterCol == -1) {
            tab.erase(tab.begin() + row);
            basis.erase(basis.begin() + row);
        } else {
            pivot(tab, den, row, enterCol);
            basis[row] = enterCol;
            ++row;
        }
    }
    // 第二阶段：最大化当前非基本原变量之和
    vector<int> isBasic(n, 0);
    for (int id : basis) isBasic[id] = 1;
    vector<BigInt> objective(n + 1);
    for (int j = 0; j < n; ++j) {
        if (!isBasic[j]) objective[j] = -den;
    }
    tab.push_back(objective);
    simplex(tab, basis, den, n);
    if (tab.back()[n] > 0) return false;
    answer.assign(n, BigInt(0));
    for (int i = 0; i < (int)basis.size(); ++i) answer[basis[i]] = tab[i][n];
    answerDen = den;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k, caseId = 0;
    while (cin >> n >> m >> k) {
        if (n == 0 && m == 0 && k == 0) break;
        vector<string> texts(n);
        vector<int> degree(n, 0);
        int maxDigits = 0;
        for (string &text : texts) {
            cin >> text;
            size_t pos = text.find('.');
            if (pos != string::npos) maxDigits = max(maxDigits, (int)(text.size() - pos - 1));
        }
        Matrix adj(n, vector<BigInt>(n));
        for (int i = 0; i < m; ++i) {
            int from, to;
            cin >> from >> to;
            --from;
            --to;
            adj[to][from] = 1;
            ++degree[from];
        }
        vector<BigInt> weights(n), answer;
        BigInt inputDen = powerTen(maxDigits), total = 0, answerDen = 1;
        for (int i = 0; i < n; ++i) {
            weights[i] = parseDecimal(texts[i], maxDigits);
            total += weights[i];
        }
        cout << "Case #" << ++caseId << ":";
        if (total == 0) {
            for (int i = 0; i < n; ++i) cout << " 0";
            cout << '\n';
            continue;
        }
        Matrix inv;
        BigInt invDen = 1;
        bool unique = true;
        if (invertMatrix(adj, inv, invDen)) {
            // 逆转移矩阵为邻接矩阵的逆左乘出度对角矩阵
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) inv[i][j] *= degree[i];
            }
            answer = weights;
            answerDen = inputDen;
            for (int day = 0; day < k; ++day) {
                vector<BigInt> next(n);
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (inv[i][j] != 0 && answer[j] != 0) next[i] += inv[i][j] * answer[j];
                    }
                }
                answer.swap(next);
                answerDen *= invDen;
            }
        } else {
            int scale = 1;
            for (int d : degree) scale = scale / __gcd(scale, d) * d;
            Matrix base(n, vector<BigInt>(n));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (adj[i][j] != 0) base[i][j] = scale / degree[j];
                }
            }
            Matrix coef = matrixPower(base, k);
            BigInt scalePow = 1;
            for (int day = 0; day < k; ++day) scalePow *= scale;
            for (BigInt &weight : weights) weight *= scalePow;
            unique = solveSingular(move(coef), move(weights), answer, answerDen);
            answerDen *= inputDen;
        }
        if (!unique) cout << " Lost luggage!\n";
        else {
            for (const BigInt &value : answer) cout << ' ' << roundHalfUp(value, answerDen);
            cout << '\n';
        }
    }
    return 0;
}
