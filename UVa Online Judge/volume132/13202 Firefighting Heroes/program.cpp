#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, c;
    while (cin >> n >> c) {
        if (n == 1) {
            cout << 1 << '\n';
            continue;
        }
        cout << n * (n - 1) - (n - c) * (c - 1) << '\n';
    }
    return 0;
}
