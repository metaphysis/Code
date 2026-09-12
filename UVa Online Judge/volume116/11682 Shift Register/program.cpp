#include <bits/stdc++.h>
using namespace std;

uint32_t getParity(uint32_t x) {
    return __builtin_parity(x);
}

uint32_t nextState(uint32_t x, uint32_t tap, int n) {
    uint32_t bit = getParity(x & tap);
    return (x >> 1) | (bit << (n - 1));
}

uint32_t prevState(uint32_t x, uint32_t tap, uint32_t mask, int n) {
    uint32_t high, low, res;
    high = x >> (n - 1);
    res = (x << 1) & mask;
    low = getParity(res & (tap ^ 1U));
    return res | (high ^ low);
}

uint32_t applyMat(const vector<uint32_t> &mat, uint32_t x) {
    uint32_t res = 0;
    for (int i = 0; i < (int)mat.size(); ++i)
        if ((x >> i) & 1U) res ^= mat[i];
    return res;
}

vector<uint32_t> mulMat(const vector<uint32_t> &a, const vector<uint32_t> &b) {
    int n = a.size();
    vector<uint32_t> c(n);
    for (int i = 0; i < n; ++i)
        c[i] = applyMat(a, b[i]);
    return c;
}

vector<uint32_t> powMat(vector<uint32_t> mat, int k) {
    int n = mat.size();
    vector<uint32_t> res(n);
    for (int i = 0; i < n; ++i) res[i] = 1U << i;
    while (k) {
        if (k & 1) res = mulMat(mat, res);
        mat = mulMat(mat, mat);
        k >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, t;
    while (cin >> n >> t && (n || t)) {
        uint32_t tap = 0, mask;
        for (int i = 0, p; i < t; ++i) {
            cin >> p;
            tap |= 1U << p;
        }
        mask = n == 32 ? 0xffffffffU : (1U << n) - 1;
        string si, sf;
        uint32_t start, finish;
        cin >> si >> sf;
        start = (uint32_t)stoull(si, nullptr, 16);
        finish = (uint32_t)stoull(sf, nullptr, 16);
        vector<uint32_t> inv(n);
        for (int i = 0; i < n; ++i)
            inv[i] = prevState(1U << i, tap, mask, n);
        const int m = 65536;
        vector<uint32_t> jump = powMat(inv, m);
        unordered_map<uint32_t, int> baby;
        uint32_t cur = start;
        baby.reserve(m * 2);
        baby.max_load_factor(0.7);
        for (int j = 0; j < m; ++j) {
            if (!baby.count(cur)) baby[cur] = j;
            cur = nextState(cur, tap, n);
        }
        cur = finish;
        uint64_t ans = ULLONG_MAX;
        for (int i = 0; i < m; ++i) {
            auto it = baby.find(cur);
            if (it != baby.end()) {
                uint64_t step = (uint64_t)i * m + it->second;
                ans = min(ans, step);
            }
            cur = applyMat(jump, cur);
        }
        if (ans == ULLONG_MAX) cout << "*\n";
        else cout << ans << '\n';
    }
    return 0;
}
