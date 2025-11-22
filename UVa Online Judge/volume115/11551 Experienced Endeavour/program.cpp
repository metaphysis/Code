// Experienced Endeavour
// UVa ID: 11551
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000;

typedef vector<int> Vec;
typedef vector<Vec> Mat;

Mat multiply(const Mat &a, const Mat &b) {
    int n = a.size();
    Mat res(n, Vec(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            if (a[i][k])
                for (int j = 0; j < n; j++)
                    res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
    return res;
}

Mat power(Mat base, int exp) {
    int n = base.size();
    Mat res(n, Vec(n, 0));
    for (int i = 0; i < n; i++) res[i][i] = 1;
    while (exp > 0) {
        if (exp & 1) res = multiply(res, base);
        base = multiply(base, base);
        exp >>= 1;
    }
    return res;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, r;
        cin >> n >> r;
        Vec a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        Mat trans(n, Vec(n, 0));
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            for (int j = 0; j < x; j++) {
                int idx;
                cin >> idx;
                trans[i][idx] = 1;
            }
        }
        Mat transR = power(trans, r);
        Vec res(n, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                res[i] = (res[i] + transR[i][j] * a[j]) % MOD;
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            cout << res[i];
        }
        cout << endl;
    }
    return 0;
}
