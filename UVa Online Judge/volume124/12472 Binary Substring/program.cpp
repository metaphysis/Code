// Binary Substring
// UVa ID: 12472
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

long long pow2Arr[55];

int getLen(long long x) { int l = 0; while (x) { ++l; x >>= 1; } return l; }

vector<int> getBits(long long x) {
    vector<int> b;
    while (x) { b.push_back(x & 1); x >>= 1; }
    reverse(b.begin(), b.end());
    return b;
}

bool can(int pos, long long cur, int n, const vector<int>& fix,
         const vector<long long>& sufMin, const vector<long long>& sufMax,
         long long low, long long high) {
    int k = n - pos;
    long long minVal = cur * pow2Arr[k] + sufMin[pos];
    long long maxVal = cur * pow2Arr[k] + sufMax[pos];
    if (maxVal < low || minVal > high) return false;
    return true;
}

long long solveTemplate(const vector<int>& fix, int n, long long low, long long high) {
    if (fix[0] == 0) return -1;
    vector<int> f = fix;
    if (f[0] == -1) f[0] = 1;
    vector<long long> sufMin(n + 1, 0), sufMax(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        int bitMin = (f[i] == -1 ? 0 : f[i]);
        int bitMax = (f[i] == -1 ? 1 : f[i]);
        sufMin[i] = (long long)bitMin * pow2Arr[n - 1 - i] + sufMin[i + 1];
        sufMax[i] = (long long)bitMax * pow2Arr[n - 1 - i] + sufMax[i + 1];
    }
    if (!can(0, 0, n, f, sufMin, sufMax, low, high)) return -1;
    long long cur = 0;
    for (int pos = 0; pos < n; ++pos) {
        if (f[pos] != -1) {
            cur = cur * 2 + f[pos];
            if (!can(pos + 1, cur, n, f, sufMin, sufMax, low, high)) return -1;
        } else {
            long long cur0 = cur * 2;
            if (can(pos + 1, cur0, n, f, sufMin, sufMax, low, high)) {
                cur = cur0;
            } else {
                long long cur1 = cur * 2 + 1;
                if (can(pos + 1, cur1, n, f, sufMin, sufMax, low, high)) {
                    cur = cur1;
                } else return -1;
            }
        }
    }
    if (cur < low || cur > high) return -1;
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    pow2Arr[0] = 1;
    for (int i = 1; i <= 54; ++i) pow2Arr[i] = pow2Arr[i - 1] * 2;
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        long long A, B, P;
        cin >> A >> B >> P;
        vector<int> pBits = getBits(P);
        int L = (int)pBits.size();
        int maxLen = getLen(B);
        if (L > maxLen) {
            cout << "Case " << tc << ": NONE\n";
            continue;
        }
        bool found = false;
        long long ans = -1;
        for (int n = L; n <= maxLen; ++n) {
            long long low = max(A, 1LL << (n - 1));
            long long high = min(B, (1LL << n) - 1);
            if (low > high) continue;
            long long best = -1;
            for (int start = 0; start + L <= n; ++start) {
                vector<int> fix(n, -1);
                for (int j = 0; j < L; ++j) fix[start + j] = pBits[j];
                if (fix[0] == 0) continue;
                long long s = solveTemplate(fix, n, low, high);
                if (s != -1) {
                    if (best == -1 || s < best) best = s;
                }
            }
            if (best != -1) {
                ans = best;
                found = true;
                break;
            }
        }
        if (found) cout << "Case " << tc << ": " << ans << "\n";
        else cout << "Case " << tc << ": NONE\n";
    }
    return 0;
}
