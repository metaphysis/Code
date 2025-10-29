// The Roots
// UVa ID: 10428
// Verdict: Accepted
// Submission Date: 2025-10-29
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPS = 1E-12;
const double INF = 1E+12;

// 判断x的符号
inline int sign(double x) { return x < -EPS ? -1 : x > EPS; }

// 计算多项式在x处的值（霍纳法则）
inline double evaluatePolynomial(const vector<double>& coefficients, double x) {
    double result = 0, power = 1;
    for (double coef : coefficients) {
        result += coef * power;
        power *= x;
    }
    return result;
}

// 在区间[low, high]内二分查找根
double findRootInInterval(const vector<double>& coefficients, int n, double low, double high) {
    double fLow = evaluatePolynomial(coefficients, low);
    double fHigh = evaluatePolynomial(coefficients, high);
    // 检查端点是否为根
    if (sign(fLow) == 0) return low;
    if (sign(fHigh) == 0) return high;
    if (sign(fLow) * sign(fHigh) > 0) return INF; // 区间内无根
    // 二分迭代
    for (int step = 0; step < 100 && high - low > EPS; ++step) {
        double mid = (low + high) * 0.5;
        int signMid = sign(evaluatePolynomial(coefficients, mid));
        if (signMid == 0) return mid;
        if (sign(fLow) * signMid < 0) high = mid;
        else low = mid;
    }
    return (low + high) * 0.5;
}

// 递归求解多项式所有实根
vector<double> solvePolynomial(vector<double> coefficients, int degree) {
    vector<double> roots;
    // 基本情况：一次方程直接求解
    if (degree == 1) {
        if (sign(coefficients[1])) 
            roots.push_back(-coefficients[0] / coefficients[1]);
        return roots;
    }
    // 计算导数系数
    vector<double> derivativeCoeffs(degree);
    for (int i = 0; i < degree; ++i) derivativeCoeffs[i] = coefficients[i + 1] * (i + 1);
    // 递归求解导数的根（临界点）
    vector<double> criticalPoints = solvePolynomial(derivativeCoeffs, degree - 1);
    // 在临界点划分的区间内搜索根
    criticalPoints.insert(criticalPoints.begin(), -INF);
    criticalPoints.push_back(INF);
    for (int i = 0; i + 1 < criticalPoints.size(); ++i) {
        double root = findRootInInterval(coefficients, degree, criticalPoints[i], criticalPoints[i + 1]);
        if (root < INF) roots.push_back(root);
    }
    return roots;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T = 1, degree;
    cout << fixed << setprecision(4);
    while (cin >> degree && degree != 0) {
        vector<double> coefficients(degree + 1);
        // 输入系数并调整顺序：coefficients[0]为常数项，coefficients[degree]为最高次项系数
        for (int i = degree; i >= 0; i--) cin >> coefficients[i];
        vector<double> roots = solvePolynomial(coefficients, degree);
        sort(roots.begin(), roots.end());
        cout << "Equation " << T << ":";
        for (double root : roots) cout << " " << round(root * 10000.0) / 10000.0;
        cout << "\n";
        T++;
    }
    return 0;
}
