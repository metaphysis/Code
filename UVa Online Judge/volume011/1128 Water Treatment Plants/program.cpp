#include <bits/stdc++.h>
using namespace std;

vector<int> addNum(const vector<int>& a, const vector<int>& b) {
    vector<int> c;
    int carry = 0, size = max(a.size(), b.size());
    for (int i = 0; i < size || carry; i++) {
        int sum = carry;
        if (i < (int)a.size()) sum += a[i];
        if (i < (int)b.size()) sum += b[i];
        c.push_back(sum % 10);
        carry = sum / 10;
    }
    return c;
}

void printNum(const vector<int>& a) {
    for (int i = (int)a.size() - 1; i >= 0; i--) cout << a[i];
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int>> fib(201);
    fib[0] = {0};
    fib[1] = {1};
    for (int i = 2; i <= 200; i++) fib[i] = addNum(fib[i - 1], fib[i - 2]);
    int n;
    while (cin >> n) printNum(fib[2 * n]);
    return 0;
}
