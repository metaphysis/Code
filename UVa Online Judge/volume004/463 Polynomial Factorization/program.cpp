// Polynomial Factorization
// UVa ID: 463
// Verdict: Accepted
// Submission Date: 2025-10-07
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool divisible(vector<int> a, vector<int> b, vector<int>& q) {
    q.clear();
    for (int i = 0; i + b.size() <= a.size(); i++) {
        if (a[i] % b[0]) return false;
        int r = a[i] / b[0]; q.push_back(r);
        for (int j = 0; j < b.size(); j++) a[i + j] -= r * b[j];
    }
    for (int x : a) if (x) return false;
    return true;
}

void getFactors(int n, vector<int>& f) {
    f.clear();
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) { 
            f.push_back(i);
            f.push_back(n / i);
        }
    }
}

bool cmpValue(int a, int b) { return abs(a) < abs(b); }

bool cmpPoly(vector<int> a, vector<int> b) { 
    return a.size() != b.size() ? a.size() < b.size() : a < b; 
}

bool dfs(int d, vector<int> in, vector<vector<int>>& out) {
    if (d == 1) { out.push_back(in); return true; }
    vector<int> p, q, r;
    getFactors(in[0], p);
    getFactors(abs(in.back()), q);
    int qsize = q.size();
    for (int i = 0; i < qsize; i++) q.push_back(-q[i]);
    if (in.back() == 0) q.push_back(0);
    sort(p.begin(), p.end(), cmpValue); 
    sort(q.begin(), q.end(), cmpValue);
    for (int a1 : p) for (int c1 : q) {
        vector<int> t = {a1, c1};
        if (divisible(in, t, r)) {
            out.push_back(t);
            return dfs(d - 1, r, out);
        }
    }
    if (d <= 3) { out.push_back(in); return true; }
    for (int a1 : p) for (int c1 : q) {
        int a2 = in[0] / a1, c2 = in.back() / c1;
        int aa = -a2, bb = in[1];
        int cc = -(a1 * in[2] - a1 * a1 * c2 - a2 * c1 * a1);
        int delta = bb * bb - 4 * aa * cc;
        if (delta < 0) continue;
        int hh = sqrt(delta + 0.5);
        if (hh * hh != delta) continue;
        for (int sign = -1; sign <= 1; sign += 2) {
            if ((sign * hh - bb) % (2 * aa)) continue;
            int b1 = (sign * hh - bb) / (2 * aa);
            if ((in[1] - b1 * a2) % a1) continue;
            int b2 = (in[1] - b1 * a2) / a1;
            if (b1 * c2 + b2 * c1 != in[3]) continue;
            out.push_back({a1, b1, c1}); 
            out.push_back({a2, b2, c2});
            return true;
        }
    }
    out.push_back(in); 
    return false;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(false);
    int a, b, c, d, e;
    while (cin >> a >> b >> c >> d >> e) {
        vector<int> in = {a, b, c, d, e};
        bool reversed = in[0] < 0;
        if (reversed) for (int& x : in) x *= -1;
        vector<vector<int>> out;
        dfs(4, in, out);
        int g = 1;
        for (auto& poly : out) {
            int tmpg = 0;
            for (int x : poly) if (x) tmpg = tmpg ? __gcd(tmpg, abs(x)) : abs(x);
            if (!tmpg) tmpg = 1;
            g *= tmpg;
            for (int& x : poly) x /= tmpg;
        }
        if (reversed) g = -g;
        sort(out.begin(), out.end(), cmpPoly);
        for (int& x : out.back()) x *= g;
        for (auto& poly : out) {
            for (auto it = poly.begin(); it != poly.end(); ++it) {
                cout << *it; 
                if (next(it) != poly.end()) cout << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    return 0;
}
