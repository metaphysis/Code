#include <bits/stdc++.h>
using namespace std;

string getDigits(long long x) {
    if (x >= 0) return to_string(x);
    unsigned long long y = 0 - (unsigned long long)x;
    return to_string(y);
}

void updateValue(long long a, long long b, char op, long long &mn, long long &mx) {
    long long val;
    if (op == '+') val = a + b;
    else if (op == '-') val = a - b;
    else val = a * b;
    mn = min(mn, val);
    mx = max(mx, val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    while (cin >> k) {
        int n = k * 2;
        vector<long long> num(n);
        vector<char> sym(n);
        for (int i = 0; i < k; i++) {
            cin >> num[i] >> sym[i];
            num[i + k] = num[i];
            sym[i + k] = sym[i];
        }
        vector<vector<long long>> mn(n, vector<long long>(n)), mx(n, vector<long long>(n));
        for (int i = 0; i < n; i++) mn[i][i] = mx[i][i] = num[i];
        for (int len = 2; len <= k; len++) {
            for (int l = 0; l + len <= n; l++) {
                int r = l + len - 1;
                mn[l][r] = LLONG_MAX;
                mx[l][r] = LLONG_MIN;
                for (int mid = l; mid < r; mid++) {
                    vector<char> ops;
                    if (sym[mid] == '?') ops = {'+', '-', '*'};
                    else ops = {sym[mid]};
                    for (char op : ops) {
                        updateValue(mn[l][mid], mn[mid + 1][r], op, mn[l][r], mx[l][r]);
                        updateValue(mn[l][mid], mx[mid + 1][r], op, mn[l][r], mx[l][r]);
                        updateValue(mx[l][mid], mn[mid + 1][r], op, mn[l][r], mx[l][r]);
                        updateValue(mx[l][mid], mx[mid + 1][r], op, mn[l][r], mx[l][r]);
                    }
                }
            }
        }
        string ans;
        for (int i = 0; i < k; i++) {
            ans += getDigits(mn[i][i + k - 1]);
            ans += getDigits(mx[i][i + k - 1]);
        }
        cout << ans << '\n';
    }
    return 0;
}
