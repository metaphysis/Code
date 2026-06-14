// Searching in sqrt(n)
// UVa ID: 12505
// Verdict: Accepted
// Submission Date: 2026-06-14
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool ge(const string& a, const string& b) {
    if (a.length() != b.length()) return a.length() > b.length();
    return a >= b;
}

string square(const string& a) {
    vector<int> r(2 * a.length(), 0);
    for (int i = a.length() - 1; i >= 0; i--)
        for (int j = a.length() - 1; j >= 0; j--) {
            int p = (a[i] - '0') * (a[j] - '0');
            r[i + j + 1] += p;
            r[i + j] += r[i + j + 1] >> 1;
            r[i + j + 1] &= 1;
        }
    string s;
    bool lead = true;
    for (int v : r) {
        if (lead && v == 0) continue;
        lead = false;
        s += char(v + '0');
    }
    return s.empty() ? "0" : s;
}

string binary(int n) {
    if (n == 0) return "0";
    string s;
    while (n) {
        s += char((n & 1) + '0');
        n >>= 1;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        string S;
        cin >> n >> S;
        int r = (int)sqrt(n);
        if (r * r == n) {
            cout << "0\n";
            continue;
        }
        string rb = binary(r), nb = binary(n), fb;
        for (int i = 0; i < 120; ++i) {
            nb += "00";
            if (ge(nb, square(rb + fb + '1'))) fb += '1';
            else fb += '0';
        }
        cout << (int)fb.find(S) << '\n';
    }
    return 0;
}
