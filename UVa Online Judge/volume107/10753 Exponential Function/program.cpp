// Exponential Function
// UVa ID: 10753
// Verdict: Wrong Answer
// Submission Date: 2026-10-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

using IntMatrix = vector<vector<int>>;
using BigMatrix = vector<vector<cpp_int>>;

BigMatrix multiply(const BigMatrix &a, const IntMatrix &b) {
    int n = a.size();
    BigMatrix res(n, vector<cpp_int>(n));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (a[i][k] == 0) continue;
            for (int j = 0; j < n; j++) {
                if (b[k][j] != 0) res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

BigMatrix matrixExp(const IntMatrix &a, const cpp_int &scaleVal) {
    int n = a.size();
    BigMatrix res(n, vector<cpp_int>(n)), term(n, vector<cpp_int>(n));
    for (int i = 0; i < n; i++) res[i][i] = term[i][i] = scaleVal;
    for (int k = 1; k <= 300; k++) {
        term = multiply(term, a);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                term[i][j] /= k;
                res[i][j] += term[i][j];
            }
        }
    }
    return res;
}

void printValue(const cpp_int &val, const cpp_int &roundDiv, const cpp_int &outScale, int digits) {
    cpp_int roundedVal = (val + roundDiv / 2) / roundDiv;
    cpp_int intPart = roundedVal / outScale;
    cout << intPart;
    if (digits == 0) return;
    cpp_int fracPart = roundedVal % outScale;
    string fracStr = fracPart.str();
    cout << '.' << string(digits - fracStr.size(), '0') << fracStr;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int digits = 25;
    if (argc > 1) digits = stoi(argv[1]);
    if (digits < 0 || digits > 70) return 1;
    cpp_int scaleVal = 1, outScale = 1;
    for (int i = 0; i < 100; i++) scaleVal *= 10;
    for (int i = 0; i < digits; i++) outScale *= 10;
    cpp_int roundDiv = scaleVal / outScale;
    int testCnt, n;
    cin >> testCnt;
    for (int caseId = 0; caseId < testCnt; caseId++) {
        cin >> n;
        IntMatrix a(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cin >> a[i][j];
        }
        BigMatrix ans = matrixExp(a, scaleVal);
        if (caseId > 0) cout << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j > 0) cout << ' ';
                printValue(ans[i][j], roundDiv, outScale, digits);
            }
            cout << '\n';
        }
    }
    return 0;
}
