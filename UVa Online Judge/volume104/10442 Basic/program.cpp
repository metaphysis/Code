// Basic
// UVa ID: 10442
// Verdict: Accepted
// Submission Date: 2025-11-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

pair<bool, int> isAda(const string& s, int depth) {
    if (s.empty()) return {false, 0};
    if (s.find('#') == s.npos) {
        for (auto c : s) if (!isdigit(c)) return {false, 0};
        if (depth) {
            int base = 0;
            for (auto c : s) {
                base = base * 10 + c - '0';
                if (base > 16) return {false, 0};
            }
            if (base < 2) return {false, 0};
            return {true, base};
        }
        return {true, 0};
    }
    if (s.back() != '#') return {false, 0};
    int firstHash = -1, lastHash = (int)s.length() - 1;
    for (int i = (int)s.length() - 2; i >= 0; i--)
        if (s[i] == '#') {
            firstHash = i;
            break;
        }
    if (firstHash == -1) return {false, 0};
    pair<bool, int> base = isAda(s.substr(0, firstHash), depth + 1);
    if (!base.first) return {false, 0};
    string digit = s.substr(firstHash + 1, lastHash - firstHash - 1);
    if (digit.empty()) return {false, 0};
    int value = 0;
    for (auto c : digit) {
        int v;
        if (isdigit(c)) v = c - '0';
        else if (c >= 'a' && c <= 'f') v = c - 'a' + 10;
        else return {false, 0};
        if (v >= base.second) return {false, 0};
        value = value * base.second + v;
        if (depth && value > 16) return {false, 0};
    }
    if (depth && value < 2) return {false, 0};
    return {true, value};
}

int main() {
    int n;
    cin >> n;
    cin.ignore(128, '\n');
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        pair<bool, int> r = isAda(line, 0);
        cout << (r.first ? "yes" : "no") << '\n';
    }
    return 0;
}
