#include <bits/stdc++.h>
using namespace std;

void mul(vector<long long>& num, int v) {
    long long carry = 0, cur;
    for (size_t i = 0; i < num.size(); i++) {
        cur = num[i] * v + carry;
        num[i] = cur % 1000000000;
        carry = cur / 1000000000;
    }
    while (carry > 0) {
        num.push_back(carry % 1000000000);
        carry /= 1000000000;
    }
}

void printNum(const vector<long long>& num) {
    string ans = to_string(num.back()), part;
    for (int i = (int)num.size() - 2; i >= 0; i--) {
        part = to_string(num[i]);
        ans += string(9 - part.size(), '0') + part;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, d, x, p, c;
    cin >> t;
    while (t--) {
        int mx[101] = {};
        for (int i = 0; i < 1; i++) cin >> n >> d;
        for (int i = 0; i < n; i++) {
            cin >> x;
            p = x - d;
            for (int j = 2; j * j <= p; j++) {
                c = 0;
                while (p % j == 0) {
                    p /= j;
                    c++;
                }
                if (c > mx[j]) mx[j] = c;
            }
            if (p > 1) mx[p] = max(mx[p], 1);
        }
        vector<long long> num(1, 1);
        for (int i = 2; i <= 100; i++) for (int j = 0; j < mx[i]; j++) mul(num, i);
        printNum(num);
    }
    return 0;
}
