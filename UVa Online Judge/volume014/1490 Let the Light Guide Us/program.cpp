#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);

class Fenwick {
private:
    int n;
    vector<long long> bit;
public:
    void init(int size) {
        n = size;
        bit.assign(n + 1, inf);
    }
    void update(int pos, long long value) {
        while (pos <= n) {
            bit[pos] = min(bit[pos], value);
            pos += pos & -pos;
        }
    }
    long long query(int pos) {
        long long res = inf;
        while (pos > 0) {
            res = min(res, bit[pos]);
            pos -= pos & -pos;
        }
        return res;
    }
};

vector<long long> getNext(const vector<long long> &pre, const vector<int> &preF, const vector<int> &curF, const vector<int> &curT) {
    int m = pre.size(), i, p, r, l, cnt;
    vector<int> ord(m), qOrd(m), ys(m);
    vector<long long> res(m, inf);
    iota(ord.begin(), ord.end(), 0);
    iota(qOrd.begin(), qOrd.end(), 0);
    for (i = 0; i < m; i++)
        ys[i] = i + preF[i];
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return a - preF[a] < b - preF[b];
    });
    sort(qOrd.begin(), qOrd.end(), [&](int a, int b) {
        return a + curF[a] < b + curF[b];
    });
    sort(ys.begin(), ys.end());
    Fenwick tree;
    tree.init(m);
    p = 0;
    for (int id : qOrd) {
        r = id + curF[id];
        while (p < m && ord[p] - preF[ord[p]] <= r) {
            int pos = m - (lower_bound(ys.begin(), ys.end(), ord[p] + preF[ord[p]]) - ys.begin());
            tree.update(pos, pre[ord[p]]);
            p++;
        }
        l = id - curF[id];
        cnt = m - (lower_bound(ys.begin(), ys.end(), l) - ys.begin());
        res[id] = tree.query(cnt);
        if (res[id] < inf)
            res[id] += curT[id];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, i, j;
    while (cin >> n >> m && (n || m)) {
        vector<vector<int>> t(n, vector<int>(m)), f(n, vector<int>(m));
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                cin >> t[i][j];
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                cin >> f[i][j];
        vector<long long> dp(m);
        for (j = 0; j < m; j++)
            dp[j] = t[0][j];
        for (i = 1; i < n; i++)
            dp = getNext(dp, f[i - 1], f[i], t[i]);
        cout << *min_element(dp.begin(), dp.end()) << '\n';
    }
    return 0;
}
