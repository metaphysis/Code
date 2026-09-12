#include <bits/stdc++.h>
using namespace std;

struct Step {
    long long a, b, c;
    char op;
};

long long tar;
vector<Step> ans;
unordered_set<string> bad;

string getKey(vector<long long> a, int rem) {
    sort(a.begin(), a.end());
    string s = to_string(rem) + "#";
    for (long long x : a) s += to_string(x) + ",";
    return s;
}

bool go(const vector<long long> &a, int rem);

bool use(const vector<long long> &a, int i, int j, long long x, long long y, long long c, char op, int rem) {
    vector<long long> b;
    b.push_back(c);
    for (int k = 0; k < (int)a.size(); k++)
        if (k != i && k != j) b.push_back(a[k]);
    ans.push_back({x, y, c, op});
    if (c == tar || go(b, rem - 1)) return true;
    ans.pop_back();
    return false;
}

bool go(const vector<long long> &a, int rem) {
    if (rem == 0) return false;
    string key = getKey(a, rem);
    if (bad.count(key)) return false;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long x = max(a[i], a[j]), y = min(a[i], a[j]);
            if (use(a, i, j, x, y, x + y, '+', rem)) return true;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long x = max(a[i], a[j]), y = min(a[i], a[j]);
            if (use(a, i, j, x, y, x * y, 'x', rem)) return true;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long x = max(a[i], a[j]), y = min(a[i], a[j]);
            if (x > y && use(a, i, j, x, y, x - y, '-', rem)) return true;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long x = max(a[i], a[j]), y = min(a[i], a[j]);
            if (x % y == 0 && use(a, i, j, x, y, x / y, '/', rem)) return true;
        }
    }
    bad.insert(key);
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> tar, tar) {
        cin >> n;
        vector<long long> a(n);
        for (long long &x : a) cin >> x;
        bool ok = false;
        for (int dep = 1; dep < n && !ok; dep++) {
            ans.clear();
            bad.clear();
            ok = go(a, dep);
        }
        if (!ok) {
            cout << "No solution\n";
            continue;
        }
        for (int i = 0; i < (int)ans.size(); i++) {
            Step &p = ans[i];
            cout << p.a << ' ' << p.op << ' ' << p.b << " = " << p.c;
            if (i + 1 == (int)ans.size()) cout << " <-";
            cout << '\n';
        }
    }
    return 0;
}
