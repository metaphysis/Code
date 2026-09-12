#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-12L;

void trim(vector<long double>& a) {
    int pos = 0, len = a.size();
    while (pos < len && fabsl(a[pos]) < eps) pos++;
    if (pos == len) a.assign(1, 0);
    else a.erase(a.begin(), a.begin() + pos);
}

vector<long double> getDer(vector<long double> a) {
    int n = a.size() - 1;
    vector<long double> b;
    for (int i = 0; i < n; i++) b.push_back(a[i] * (n - i));
    trim(b);
    return b;
}

vector<long double> getRem(vector<long double> a, vector<long double> b) {
    trim(a);
    trim(b);
    while (a.size() >= b.size() && fabsl(a[0]) >= eps) {
        long double k = a[0] / b[0];
        for (int i = 0; i < (int)b.size(); i++) a[i] -= k * b[i];
        trim(a);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long double> a(n + 1);
        for (int i = 0; i <= n; i++) cin >> a[i];
        if (n == 0) {
            cout << "Yes!\n";
            continue;
        }
        vector<long double> b = getDer(a);
        while (!(b.size() == 1 && fabsl(b[0]) < eps)) {
            vector<long double> r = getRem(a, b);
            a = b;
            b = r;
        }
        if (a.size() == 1) cout << "Yes!\n";
        else cout << "No!\n";
    }
    return 0;
}
