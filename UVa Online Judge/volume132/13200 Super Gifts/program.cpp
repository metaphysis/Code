#include <bits/stdc++.h>
using namespace std;

const int modVal = 1000000007, maxN = 100000;
const int primeA = 998244353, primeB = 1004535809, primeC = 469762049;
const long long directLimit = 2000000;
vector<int> fact(maxN + 1), invFact(maxN + 1), invNum(maxN + 1);

int modPow(int base, int exp, int mod = modVal) {
    int res = 1;
    while (exp > 0) {
        if (exp & 1) res = 1LL * res * base % mod;
        base = 1LL * base * base % mod;
        exp >>= 1;
    }
    return res;
}

void init() {
    fact[0] = 1;
    for (int i = 1; i <= maxN; ++i) fact[i] = 1LL * fact[i - 1] * i % modVal;
    invFact[maxN] = modPow(fact[maxN], modVal - 2);
    for (int i = maxN; i >= 1; --i) invFact[i - 1] = 1LL * invFact[i] * i % modVal;
    invNum[1] = 1;
    for (int i = 2; i <= maxN; ++i) invNum[i] = modVal - 1LL * (modVal / i) * invNum[modVal % i] % modVal;
}

struct Ntt {
    int mod;
    vector<int> roots;
    Ntt(int mod) : mod(mod), roots(2, 1) {}
    void transform(vector<int> &a, bool invert) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            while (j & bit) {
                j ^= bit;
                bit >>= 1;
            }
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        while ((int)roots.size() < n) {
            int oldSize = roots.size(), step = modPow(3, (mod - 1) / (oldSize * 2), mod);
            roots.resize(oldSize * 2);
            for (int i = oldSize / 2; i < oldSize; ++i) {
                roots[i * 2] = roots[i];
                roots[i * 2 + 1] = 1LL * roots[i] * step % mod;
            }
        }
        for (int half = 1; half < n; half <<= 1) {
            for (int start = 0; start < n; start += half * 2) {
                for (int j = 0; j < half; ++j) {
                    int u = a[start + j], v = 1LL * a[start + j + half] * roots[half + j] % mod;
                    int sum = u + v, diff = u - v;
                    if (sum >= mod) sum -= mod;
                    if (diff < 0) diff += mod;
                    a[start + j] = sum;
                    a[start + j + half] = diff;
                }
            }
        }
        if (invert) {
            reverse(a.begin() + 1, a.end());
            int invN = modPow(n, mod - 2, mod);
            for (int &value : a) value = 1LL * value * invN % mod;
        }
    }

    vector<int> convolve(const vector<int> &a, const vector<int> &b, int aSize, int bSize, int need) {
        int n = 1;
        while (n < aSize + bSize - 1) n <<= 1;
        vector<int> fa(n), fb(n);
        for (int i = 0; i < aSize; ++i) fa[i] = a[i] % mod;
        for (int i = 0; i < bSize; ++i) fb[i] = b[i] % mod;
        transform(fa, false);
        transform(fb, false);
        for (int i = 0; i < n; ++i) fa[i] = 1LL * fa[i] * fb[i] % mod;
        transform(fa, true);
        fa.resize(need);
        return fa;
    }
};

Ntt nttA(primeA), nttB(primeB), nttC(primeC);

vector<int> multiply(const vector<int> &a, const vector<int> &b, int need) {
    if (a.empty() || b.empty() || need <= 0) return {};
    int aSize = min((int)a.size(), need), bSize = min((int)b.size(), need);
    need = min(need, aSize + bSize - 1);
    vector<int> res(need);
    if (min(aSize, bSize) <= 32) {
        for (int i = 0; i < aSize; ++i) {
            int limit = min(bSize, need - i);
            for (int j = 0; j < limit; ++j) res[i + j] = (res[i + j] + 1LL * a[i] * b[j]) % modVal;
        }
        return res;
    }
    vector<int> valA = nttA.convolve(a, b, aSize, bSize, need),
                valB = nttB.convolve(a, b, aSize, bSize, need),
                valC = nttC.convolve(a, b, aSize, bSize, need);
    static const int invA = modPow(primeA, primeB - 2, primeB),
                     invAb = modPow(1LL * primeA * primeB % primeC, primeC - 2, primeC),
                     abMod = 1LL * primeA * primeB % modVal;
    for (int i = 0; i < need; ++i) {
        long long partB = (valB[i] - valA[i] + 1LL * primeB) % primeB;
        partB = partB * invA % primeB;
        long long firstTwo = valA[i] + 1LL * primeA * partB;
        long long partC = (valC[i] - firstTwo % primeC + primeC) % primeC;
        partC = partC * invAb % primeC;
        res[i] = (valA[i] + 1LL * primeA * partB % modVal + 1LL * abMod * partC % modVal) % modVal;
    }
    return res;
}

vector<int> polyInv(const vector<int> &a, int need) {
    vector<int> res(1, modPow(a[0], modVal - 2));
    while ((int)res.size() < need) {
        int nextSize = min((int)res.size() * 2, need), cutSize = min((int)a.size(), nextSize);
        vector<int> cut(a.begin(), a.begin() + cutSize), prod = multiply(cut, res, nextSize);
        prod.resize(nextSize);
        for (int &value : prod) value = value == 0 ? 0 : modVal - value;
        prod[0] = (prod[0] + 2) % modVal;
        res = multiply(res, prod, nextSize);
        res.resize(nextSize);
    }
    return res;
}

vector<int> polyLog(const vector<int> &a, int need) {
    int aSize = min((int)a.size(), need);
    vector<int> deriv(max(0, aSize - 1)), invA = polyInv(a, need), res(need);
    for (int i = 1; i < aSize; ++i) deriv[i - 1] = 1LL * a[i] * i % modVal;
    vector<int> prod = multiply(deriv, invA, need - 1);
    prod.resize(need - 1);
    for (int i = 1; i < need; ++i) res[i] = 1LL * prod[i - 1] * invNum[i] % modVal;
    return res;
}

vector<int> polyExp(const vector<int> &a, int need) {
    vector<int> res(1, 1);
    while ((int)res.size() < need) {
        int nextSize = min((int)res.size() * 2, need);
        vector<int> delta = polyLog(res, nextSize);
        for (int i = 0; i < nextSize; ++i) {
            delta[i] = a[i] - delta[i];
            if (delta[i] < 0) delta[i] += modVal;
        }
        delta[0] = (delta[0] + 1) % modVal;
        res = multiply(res, delta, nextSize);
        res.resize(nextSize);
    }
    return res;
}

int solveOne(int n, int k) {
    int ans = 0;
    for (int j = 0; j < k; ++j) {
        int ways = 1LL * fact[k] * invFact[j] % modVal * invFact[k - j] % modVal;
        int term = 1LL * ways * modPow(k - j, n) % modVal;
        if (j & 1) ans = (ans - term + modVal) % modVal;
        else ans = (ans + term) % modVal;
    }
    return ans;
}

int solveIe(int n, int k, int m) {
    int ans = modPow(k, n), tail = invFact[m - 1];
    vector<int> prev(1, 1), cur;
    for (int j = 1; j < k; ++j) {
        int degree = j * (m - 1), prevSize = prev.size();
        cur.resize(degree + 1);
        cur[0] = 1;
        for (int t = 1; t <= degree; ++t) {
            int value = cur[t - 1];
            if (t >= m && t - m < prevSize) {
                value -= 1LL * tail * prev[t - m] % modVal;
                if (value < 0) value += modVal;
            }
            cur[t] = 1LL * value * j % modVal * invNum[t] % modVal;
        }
        int base = k - j, power = modPow(base, n - degree), sum = 0;
        for (int t = degree; t >= 0; --t) {
            int term = 1LL * cur[t] * invFact[n - t] % modVal * power % modVal;
            sum += term;
            if (sum >= modVal) sum -= modVal;
            power = 1LL * power * base % modVal;
        }
        int ways = 1LL * fact[k] * invFact[j] % modVal * invFact[k - j] % modVal;
        int term = 1LL * sum * fact[n] % modVal * ways % modVal;
        if (j & 1) ans = (ans - term + modVal) % modVal;
        else ans = (ans + term) % modVal;
        prev.swap(cur);
    }
    return ans;
}

int solveDp(int k, int m, int degree, int factor) {
    vector<int> dp(degree + 1);
    dp[0] = 1;
    for (int child = 1; child <= k; ++child) {
        int used = child * m;
        for (int t = 1; t <= degree; ++t) {
            long long value = 1LL * child * dp[t - 1] + 1LL * used * dp[t];
            dp[t] = value % modVal * invNum[used + t] % modVal;
        }
    }
    return 1LL * factor * dp[degree] % modVal;
}

int solveFps(int k, int m, int degree, int factor) {
    vector<int> base(degree + 1);
    for (int i = 0; i <= degree; ++i) base[i] = 1LL * fact[m] * invFact[m + i] % modVal;
    vector<int> logBase = polyLog(base, degree + 1);
    for (int &value : logBase) value = 1LL * value * k % modVal;
    vector<int> result = polyExp(logBase, degree + 1);
    return 1LL * factor * result[degree] % modVal;
}

int solve(int n, int k, int m) {
    if (1LL * k * m > n) return 0;
    if (k == 1) return 1;
    int degree = n - k * m, factor = 1LL * fact[n] * modPow(invFact[m], k) % modVal;
    if (degree == 0) return factor;
    if (m == 1) return solveOne(n, k);
    long long ieCost = 1LL * (m - 1) * k * (k - 1) / 2 + k;
    long long dpCost = 1LL * k * degree;
    if (min(ieCost, dpCost) <= directLimit) {
        if (ieCost < dpCost) return solveIe(n, k, m);
        return solveDp(k, m, degree, factor);
    }
    return solveFps(k, m, degree, factor);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    map<tuple<int, int, int>, int> cache;
    int n, k, m;
    while (cin >> n >> k >> m) {
        tuple<int, int, int> key = make_tuple(n, k, m);
        auto it = cache.find(key);
        if (it != cache.end()) cout << it->second << '\n';
        else {
            int ans = solve(n, k, m);
            cache[key] = ans;
            cout << ans << '\n';
        }
    }
    return 0;
}
