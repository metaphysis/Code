// Machine Works
// UVa ID: 1106
// Verdict: Accepted
// Submission Date: 2026-04-21
// UVa Run Time: 0.230s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Machine {
    int d, p, r, g;
};

struct Line {
    ll m, b;
    Line(ll m = 0, ll b = -1e18) : m(m), b(b) {}
    ll eval(ll x) const { return m * x + b; }
};

class LiChaoTree {
    vector<Line> tree;
    vector<ll> xs;
    int n;
public:
    LiChaoTree(vector<ll>& coords) : xs(coords) {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        n = xs.size();
        tree.assign(4 * n, Line(0, -1e18));
    }
    
    void addLine(Line newLine, int node, int l, int r) {
        int midIdx = (l + r) / 2;
        ll xl = xs[l], xr = xs[r - 1], xm = xs[midIdx];
        bool leftBetter = newLine.eval(xl) > tree[node].eval(xl);
        bool midBetter = newLine.eval(xm) > tree[node].eval(xm);
        
        if (midBetter) swap(tree[node], newLine);
        if (r - l == 1) return;
        
        if (leftBetter != midBetter) addLine(newLine, node * 2, l, midIdx);
        else addLine(newLine, node * 2 + 1, midIdx, r);
    }
    
    void addLine(Line line) { addLine(line, 1, 0, n); }
    
    ll query(ll x, int node, int l, int r) {
        if (r - l == 1) return tree[node].eval(x);
        int midIdx = (l + r) / 2;
        if (x <= xs[midIdx - 1]) return max(tree[node].eval(x), query(x, node * 2, l, midIdx));
        else return max(tree[node].eval(x), query(x, node * 2 + 1, midIdx, r));
    }
    
    ll query(ll x) { return query(x, 1, 0, n); }
};

bool cmpD(const Machine& a, const Machine& b) { return a.d < b.d; }

int main() {
    int n, d, caseNo = 0;
    ll c;
    while (scanf("%d %lld %d", &n, &c, &d) == 3 && (n || c || d)) {
        vector<Machine> machines(n);
        for (int i = 0; i < n; ++i)
            scanf("%d %d %d %d", &machines[i].d, &machines[i].p, &machines[i].r, &machines[i].g);
        sort(machines.begin(), machines.end(), cmpD);
        
        vector<ll> days;
        for (auto& m : machines) days.push_back(m.d);
        LiChaoTree lichao(days);
        
        ll best = c;
        lichao.addLine(Line(0, c));
        
        for (auto& m : machines) {
            ll f = lichao.query(m.d);
            if (f >= m.p) {
                ll profit = f - m.p + (ll)(d - m.d) * m.g + m.r;
                if (profit > best) best = profit;
                ll b = f - m.p - (ll)(m.d + 1) * m.g + m.r;
                lichao.addLine(Line(m.g, b));
            }
        }
        
        printf("Case %d: %lld\n", ++caseNo, best);
    }
    return 0;
}
