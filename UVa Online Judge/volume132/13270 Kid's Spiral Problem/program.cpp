#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007, invTwo = 500000004;
const long long invNum[5] = {0, 1, 500000004, 333333336, 250000002};

long long lineSum(long long base, long long dir, long long lo, long long hi) {
    if (lo > hi) return 0;
    long long cnt = (hi - lo + 1) % mod, coordSum = ((lo + hi) % mod + mod) % mod;
    base = (base % mod + mod) % mod;
    coordSum = coordSum * cnt % mod * invTwo % mod;
    return (base * cnt % mod + dir * coordSum + mod) % mod;
}

long long ringSum(long long r, long long xLo, long long yLo, long long xHi, long long yHi) {
    long long base = 4 * r % mod * r % mod, res = 0;
    if (xLo <= r && r <= xHi) res = (res + lineSum(base - 3 * r + 1, 1, max(yLo, 1 - r), min(yHi, r))) % mod;
    if (yLo <= r && r <= yHi) res = (res + lineSum(base - r + 1, -1, max(xLo, -r), min(xHi, r - 1))) % mod;
    if (xLo <= -r && -r <= xHi) res = (res + lineSum(base + r + 1, -1, max(yLo, -r), min(yHi, r - 1))) % mod;
    if (yLo <= -r && -r <= yHi) res = (res + lineSum(base + 3 * r + 1, 1, max(xLo, 1 - r), min(xHi, r))) % mod;
    return res;
}

long long rangeSum(long long start, long long len, long long xLo, long long yLo, long long xHi, long long yHi) {
    long long vals[4], res = 0, comb = 1;
    if (len < 4) {
        for (long long i = 0; i < len; ++i) res = (res + ringSum(start + i, xLo, yLo, xHi, yHi)) % mod;
        return res;
    }
    for (int i = 0; i < 4; ++i) vals[i] = ringSum(start + i, xLo, yLo, xHi, yHi);
    for (int i = 0; i < 4; ++i) {
        comb = comb * ((len - i) % mod) % mod * invNum[i + 1] % mod;
        res = (res + comb * vals[0]) % mod;
        for (int j = 0; j < 3 - i; ++j) vals[j] = (vals[j + 1] - vals[j] + mod) % mod;
    }
    return res;
}

long long solve(long long n, long long xLo, long long yLo, long long xHi, long long yHi) {
    if (xLo > xHi) swap(xLo, xHi);
    if (yLo > yHi) swap(yLo, yHi);
    vector<long long> cuts = {1, n + 1};
    long long coords[4] = {xLo, yLo, xHi, yHi}, ans = 0;
    for (long long c : coords) {
        long long pos = abs(c);
        if (pos >= 1 && pos <= n + 1) cuts.push_back(pos);
        if (pos + 1 >= 1 && pos + 1 <= n + 1) cuts.push_back(pos + 1);
    }
    sort(cuts.begin(), cuts.end());
    cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());
    if (xLo <= 0 && 0 <= xHi && yLo <= 0 && 0 <= yHi) ans = 1;
    for (int i = 0; i + 1 < (int)cuts.size(); ++i) ans = (ans + rangeSum(cuts[i], cuts[i + 1] - cuts[i], xLo, yLo, xHi, yHi)) % mod;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, xLo, yLo, xHi, yHi;
    int q;
    while (cin >> n >> q) {
        while (q--) {
            cin >> xLo >> yLo >> xHi >> yHi;
            cout << solve(n, xLo, yLo, xHi, yHi) << '\n';
        }
    }
    return 0;
}
