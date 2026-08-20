#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<long long> ys;
    vector<int> bit;
};

struct Query {
    int l, r, id;
};

int n, q, bs;
long long d, curAns;
vector<long long> us, vs, allU;
vector<int> rx;
vector<Node> nodes;

void addBit(int x, long long y, int val) {
    for (int i = x; i <= (int)allU.size(); i += i & -i) {
        int p = lower_bound(nodes[i].ys.begin(), nodes[i].ys.end(), y) - nodes[i].ys.begin() + 1;
        for (int j = p; j < (int)nodes[i].bit.size(); j += j & -j)
            nodes[i].bit[j] += val;
    }
}

int sumBit(int x, long long y) {
    int res = 0;
    for (int i = x; i > 0; i -= i & -i) {
        int p = upper_bound(nodes[i].ys.begin(), nodes[i].ys.end(), y) - nodes[i].ys.begin();
        for (int j = p; j > 0; j -= j & -j)
            res += nodes[i].bit[j];
    }
    return res;
}

int rectSum(long long xl, long long xr, long long yl, long long yr) {
    int l = lower_bound(allU.begin(), allU.end(), xl) - allU.begin();
    int r = upper_bound(allU.begin(), allU.end(), xr) - allU.begin();
    int a = sumBit(r, yr);
    int b = sumBit(l, yr);
    int c = sumBit(r, yl - 1);
    int e = sumBit(l, yl - 1);
    return a - b - c + e;
}

void addPoint(int id) {
    int cnt = rectSum(us[id] - d, us[id] + d, vs[id] - d, vs[id] + d);
    curAns += cnt;
    addBit(rx[id], vs[id], 1);
}

void removePoint(int id) {
    addBit(rx[id], vs[id], -1);
    int cnt = rectSum(us[id] - d, us[id] + d, vs[id] - d, vs[id] + d);
    curAns -= cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc = 0;
    while (cin >> n >> d >> q) {
        ++tc;
        us.assign(n + 1, 0);
        vs.assign(n + 1, 0);
        allU.clear();
        allU.reserve(n);
        for (int i = 1; i <= n; ++i) {
            long long x, y;
            cin >> x >> y;
            us[i] = x + y;
            vs[i] = x - y;
            allU.push_back(us[i]);
        }
        sort(allU.begin(), allU.end());
        allU.erase(unique(allU.begin(), allU.end()), allU.end());
        rx.assign(n + 1, 0);
        nodes.assign(allU.size() + 1, Node());
        for (int i = 1; i <= n; ++i) {
            rx[i] = lower_bound(allU.begin(), allU.end(), us[i]) - allU.begin() + 1;
            for (int j = rx[i]; j <= (int)allU.size(); j += j & -j)
                nodes[j].ys.push_back(vs[i]);
        }
        for (int i = 1; i <= (int)allU.size(); ++i) {
            sort(nodes[i].ys.begin(), nodes[i].ys.end());
            nodes[i].ys.erase(unique(nodes[i].ys.begin(), nodes[i].ys.end()), nodes[i].ys.end());
            nodes[i].bit.assign(nodes[i].ys.size() + 1, 0);
        }
        vector<Query> qs(q);
        vector<long long> ans(q);
        for (int i = 0; i < q; ++i) {
            cin >> qs[i].l >> qs[i].r;
            qs[i].id = i;
        }
        bs = max(1, n / max(1, (int)sqrt(q)));
        sort(qs.begin(), qs.end(), [](const Query &a, const Query &b) {
            int ba = a.l / bs, bb = b.l / bs;
            if (ba != bb) return ba < bb;
            if (ba & 1) return a.r > b.r;
            return a.r < b.r;
        });
        int l = 1, r = 0;
        curAns = 0;
        for (const Query &it : qs) {
            while (r < it.r) addPoint(++r);
            while (r > it.r) removePoint(r--);
            while (l < it.l) removePoint(l++);
            while (l > it.l) addPoint(--l);
            ans[it.id] = curAns;
        }
        cout << "Case " << tc << ":\n";
        for (int i = 0; i < q; ++i)
            cout << ans[i] << '\n';
    }
    return 0;
}
