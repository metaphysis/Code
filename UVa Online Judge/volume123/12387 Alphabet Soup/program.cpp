// Alphabet Soup
// UVa ID: 12387
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.220s


#include <bits/stdc++.h>
using namespace std;

const int kMod = 100000007;
const int kAngleCnt = 360000;

long long modPow(long long a, long long e) {
    long long r = 1;
    a %= kMod;
    while (e > 0) {
        if (e & 1) r = r * a % kMod;
        a = a * a % kMod;
        e >>= 1;
    }
    return r;
}

int gcdInt(int a, int b) {
    while (b) { int t = a % b; a = b; b = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S, P;
    while (cin >> S >> P) {
        if (S == -1 && P == -1) break;

        if (P == 0) { cout << 1 << '\n'; continue; }

        vector<int> angles(P);
        vector<char> present(kAngleCnt, 0);

        for (int i = 0; i < P; ++i) {
            cin >> angles[i];
            present[angles[i]] = 1;
        }

        // 枚举 360000 的所有约数，从小到大验证最小周期
        vector<int> divisors;
        for (int i = 1; i * i <= kAngleCnt; ++i) {
            if (kAngleCnt % i == 0) {
                divisors.push_back(i);
                if (i * i != kAngleCnt) divisors.push_back(kAngleCnt / i);
            }
        }
        sort(divisors.begin(), divisors.end());

        int d = kAngleCnt;
        for (int div : divisors) {
            bool ok = true;
            for (int a : angles) {
                if (!present[(a + div) % kAngleCnt]) {
                    ok = false;
                    break;
                }
            }
            if (ok) { d = div; break; }
        }

        int n = kAngleCnt / d;      // 旋转群大小
        int c = P / n;              // 每个余数类中的点数

        long long sum = 0;
        for (int k = 0; k < n; ++k) {
            int g = gcdInt(n, k);
            long long exp = 1LL * c * g;
            long long term = modPow(S, exp);
            sum += term;
            if (sum >= kMod) sum -= kMod;
        }

        long long invN = modPow(n, kMod - 2);
        long long ans = sum * invN % kMod;

        cout << ans << '\n';
    }

    return 0;
}
