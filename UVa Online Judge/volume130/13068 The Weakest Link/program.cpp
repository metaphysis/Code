#include <bits/stdc++.h>
using namespace std;

int minRep(string s) {
    int n = s.size(), i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int a = s[(i + k) % n], b = s[(j + k) % n];
        if (a == b) {
            k++;
        } else {
            if (a > b) i += k + 1;
            else j += k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    return min(i, j) + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        cout << minRep(s) << '\n';
    }
    return 0;
}
