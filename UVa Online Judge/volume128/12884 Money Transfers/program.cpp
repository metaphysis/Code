#include <bits/stdc++.h>
using namespace std;

const long double Inf = 4e18L;
const long long Lim = 1000000000000000LL;

struct Edge {
    int to;
    long long fee;
};

struct Line {
    long long cnt, sum;
    bool ok;
};

struct Node {
    long double dis;
    int id, bad;
    bool operator < (const Node &oth) const {
        return dis > oth.dis;
    }
};

int n, p, sx, sy, m;
vector<vector<Edge> > g;
vector<int> own;
vector<Line> goodSet, badSet;

bool sameLine(Line a, Line b) {
    return a.ok && b.ok && a.cnt == b.cnt && a.sum == b.sum;
}

Line getPath(long long tax, bool needBad) {
    vector<vector<long double> > dis(n + 1, vector<long double>(2, Inf));
    vector<vector<long long> > cnt(n + 1, vector<long long>(2, 0));
    vector<vector<long long> > sum(n + 1, vector<long long>(2, 0));
    priority_queue<Node> que;
    int stBad = own[sx] ? 0 : 1;
    dis[sx][stBad] = 0;
    que.push({0, sx, stBad});
    while (!que.empty()) {
        Node cur = que.top();
        que.pop();
        if (cur.dis > dis[cur.id][cur.bad] + 1e-12L)
            continue;
        for (Edge e : g[cur.id]) {
            int nb = cur.bad || !own[e.to];
            long double nd = cur.dis + e.fee + tax;
            long long nc = cnt[cur.id][cur.bad] + 1;
            long long ns = sum[cur.id][cur.bad] + e.fee;
            if (nd < dis[e.to][nb] - 1e-12L ||
                (fabsl(nd - dis[e.to][nb]) <= 1e-12L && nc < cnt[e.to][nb])) {
                dis[e.to][nb] = nd;
                cnt[e.to][nb] = nc;
                sum[e.to][nb] = ns;
                que.push({nd, e.to, nb});
            }
        }
    }
    int id = needBad ? 1 : 0;
    if (dis[sy][id] >= Inf / 2)
        return {0, 0, false};
    return {cnt[sy][id], sum[sy][id], true};
}

long double crossX(Line a, Line b) {
    return (long double)(b.sum - a.sum) / (long double)(a.cnt - b.cnt);
}

void addLine(vector<Line> &set, Line x) {
    if (!x.ok)
        return;
    for (Line y : set)
        if (sameLine(x, y))
            return;
    set.push_back(x);
}

void divide(long long l, long long r, bool needBad, Line left, Line right) {
    addLine(needBad ? badSet : goodSet, left);
    addLine(needBad ? badSet : goodSet, right);
    if (!left.ok || !right.ok || sameLine(left, right) || r - l <= 1)
        return;
    long long mid = l + (r - l) / 2;
    if (left.cnt != right.cnt) {
        long double x = crossX(left, right);
        if (x > l && x < r) {
            long long pos = (long long)floor(x);
            if (pos >= l + 1 && pos <= r - 1)
                mid = pos;
        }
    }
    if (mid <= l || mid >= r)
        return;
    Line lm = getPath(mid, needBad);
    divide(l, mid, needBad, left, lm);
    divide(mid, r, needBad, lm, right);
}

bool better(long long tax) {
    Line a = getPath(tax, false);
    Line b = getPath(tax, true);
    if (!a.ok)
        return false;
    if (!b.ok)
        return true;
    __int128 va = (__int128)a.sum + (__int128)a.cnt * tax;
    __int128 vb = (__int128)b.sum + (__int128)b.cnt * tax;
    return va < vb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> p >> sx >> sy) {
        g.assign(n + 1, vector<Edge>());
        for (int i = 0; i < p; ++i) {
            int a, b;
            long long c;
            cin >> a >> b >> c;
            g[a].push_back({b, c});
            g[b].push_back({a, c});
        }
        cin >> m;
        own.assign(n + 1, 0);
        for (int i = 0; i < m; ++i) {
            int x;
            cin >> x;
            own[x] = 1;
        }
        goodSet.clear();
        badSet.clear();
        Line gl = getPath(0, false);
        Line gr = getPath(Lim, false);
        Line bl = getPath(0, true);
        Line br = getPath(Lim, true);
        if (!gl.ok) {
            cout << "Impossible\n";
            continue;
        }
        divide(0, Lim, false, gl, gr);
        divide(0, Lim, true, bl, br);
        bool infAns = false;
        Line gh = getPath(Lim, false);
        Line bh = getPath(Lim, true);
        if (!bh.ok)
            infAns = true;
        else if (gh.cnt < bh.cnt)
            infAns = true;
        else if (gh.cnt == bh.cnt && gh.sum < bh.sum)
            infAns = true;
        if (infAns) {
            cout << "Infinity\n";
            continue;
        }
        vector<long long> cand;
        cand.push_back(0);
        for (Line a : goodSet) {
            for (Line b : badSet) {
                if (a.cnt == b.cnt)
                    continue;
                long double x = crossX(a, b);
                long long y = (long long)floor(x);
                for (long long z = max(0LL, y - 2); z <= y + 2; ++z)
                    if (z <= Lim)
                        cand.push_back(z);
            }
        }
        sort(cand.begin(), cand.end());
        cand.erase(unique(cand.begin(), cand.end()), cand.end());
        long long ans = -1;
        for (long long x : cand)
            if (better(x))
                ans = max(ans, x);
        if (ans < 0)
            cout << "Impossible\n";
        else
            cout << ans << '\n';
    }
    return 0;
}
