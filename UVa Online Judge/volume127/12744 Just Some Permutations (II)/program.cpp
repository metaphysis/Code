#include <bits/stdc++.h>
using namespace std;

int n, lis, lim;
vector<int> memo, pow3;

int countWays(int usedMask, int tailMask, int code) {
    int &res = memo[code];
    if (res != -1) return res;
    if (__builtin_popcount(tailMask) > lis) return res = 0;
    if (usedMask == (1 << n) - 1) return res = (__builtin_popcount(tailMask) == lis);
    res = 0;
    for (int val = 0; val < n; val++) if (!(usedMask & (1 << val))) {
        int valBit = 1 << val, geMask = tailMask & ~((1 << val) - 1), repBit = geMask & -geMask;
        int nextTail = repBit ? ((tailMask ^ repBit) | valBit) : (tailMask | valBit);
        int nextCode = repBit ? code + 2 * pow3[val] - pow3[__builtin_ctz(repBit)] : code + 2 * pow3[val];
        res = min(lim, res + countWays(usedMask | valBit, nextTail, nextCode));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, kth;
    cin >> t;
    lim = 1000000000;
    while (t--) {
        cin >> n >> lis >> kth;
        pow3.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) pow3[i] = pow3[i - 1] * 3;
        memo.assign(pow3[n], -1);
        int total = countWays(0, 0, 0);
        static int caseNum = 0;
        cout << "Case " << ++caseNum << ":";
        if (total < kth) {
            cout << " -1\n";
            continue;
        }
        int usedMask = 0, tailMask = 0, code = 0;
        for (int pos = 0; pos < n; pos++) {
            for (int val = 0; val < n; val++) if (!(usedMask & (1 << val))) {
                int valBit = 1 << val, geMask = tailMask & ~((1 << val) - 1), repBit = geMask & -geMask;
                int nextTail = repBit ? ((tailMask ^ repBit) | valBit) : (tailMask | valBit);
                int nextCode = repBit ? code + 2 * pow3[val] - pow3[__builtin_ctz(repBit)] : code + 2 * pow3[val];
                int ways = countWays(usedMask | valBit, nextTail, nextCode);
                if (ways < kth) kth -= ways;
                else {
                    cout << ' ' << val + 1;
                    usedMask |= valBit;
                    tailMask = nextTail;
                    code = nextCode;
                    break;
                }
            }
        }
        cout << '\n';
    }
    return 0;
}
