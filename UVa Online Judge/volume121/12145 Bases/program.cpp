#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

vector<long long> addPoly(const vector<long long> &a, const vector<long long> &b) {
    vector<long long> c(max(a.size(), b.size()), 0);
    for (int i = 0; i < (int)a.size(); i++)
        c[i] += a[i];
    for (int i = 0; i < (int)b.size(); i++)
        c[i] += b[i];
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}

vector<long long> mulPoly(const vector<long long> &a, const vector<long long> &b) {
    vector<long long> c(a.size() + b.size() - 1, 0);
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b.size(); j++)
            c[i + j] += a[i] * b[j];
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}

vector<long long> getNum(const string &s) {
    vector<long long> p(s.size(), 0);
    for (int i = 0; i < (int)s.size(); i++)
        p[s.size() - i - 1] = s[i] - '0';
    while (p.size() > 1 && p.back() == 0)
        p.pop_back();
    return p;
}

vector<long long> getExpr(const string &s) {
    vector<long long> ans(1, 0);
    int st = 0;
    for (int i = 0; i <= (int)s.size(); i++) {
        if (i == (int)s.size() || s[i] == '+') {
            vector<long long> term(1, 1);
            int last = st;
            for (int j = st; j <= i; j++) {
                if (j == i || s[j] == '*') {
                    term = mulPoly(term, getNum(s.substr(last, j - last)));
                    last = j + 1;
                }
            }
            ans = addPoly(ans, term);
            st = i + 1;
        }
    }
    return ans;
}

cpp_int calc(const vector<long long> &p, long long base) {
    cpp_int val = 0;
    for (int i = (int)p.size() - 1; i >= 0; i--)
        val = val * base + p[i];
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line) && line != "=") {
        int pos = line.find('=');
        string left = line.substr(0, pos), right = line.substr(pos + 1);
        vector<long long> poly = getExpr(left);
        vector<long long> rp = getExpr(right);
        if (poly.size() < rp.size())
            poly.resize(rp.size(), 0);
        for (int i = 0; i < (int)rp.size(); i++)
            poly[i] -= rp[i];
        while (poly.size() > 1 && poly.back() == 0)
            poly.pop_back();
        int minBase = 2;
        for (char ch : line)
            if (isdigit(ch))
                minBase = max(minBase, ch - '0' + 1);
        if (poly.size() == 1 && poly[0] == 0) {
            cout << minBase << "+\n";
            continue;
        }
        while (poly.size() > 1 && poly[0] == 0)
            poly.erase(poly.begin());
        long long constant = llabs(poly[0]);
        vector<long long> roots;
        for (long long d = 1; d <= constant / d; d++) {
            if (constant % d != 0)
                continue;
            long long e = constant / d;
            if (d >= minBase && calc(poly, d) == 0)
                roots.push_back(d);
            if (e != d && e >= minBase && calc(poly, e) == 0)
                roots.push_back(e);
        }
        sort(roots.begin(), roots.end());
        roots.erase(unique(roots.begin(), roots.end()), roots.end());
        if (roots.empty())
            cout << "*\n";
        else {
            for (int i = 0; i < (int)roots.size(); i++) {
                if (i)
                    cout << ' ';
                cout << roots[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
