// Term Reductions
// UVa ID: 791
// Verdict: Accepted
// Submission Date: 2026-07-21
// UVa Run Time: 0.230s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

void reduceTerm(string& s) {
    int size = (int)s.size();
    int i = size - 1;
    while (i >= 0) {
        if (i + 3 < size && s[i] == '(' && s[i + 1] == '(' && s[i + 2] == '(' && s[i + 3] == 'X') {
            int pos = i;
            int x = pos + 3;
            int a = -1, b = -1, c = -1;
            int d = 3;
            for (int j = x; j < (int)s.length(); ++j) {
                if (s[j] == '(') d++;
                else if (s[j] == ')') {
                    d--;
                    if (d == 2 && a == -1) a = j;
                    else if (d == 1 && b == -1) b = j;
                    else if (d == 0 && c == -1) { c = j; break; }
                }
            }
            if (a == -1 || b == -1 || c == -1) continue;
            string A = s.substr(x + 1, a - x - 1);
            string B = s.substr(a + 1, b - a - 1);
            string C = s.substr(b + 1, c - b - 1);
            string replacement = "((" + A + C + ")(" + B + C + "))";
            s.replace(pos, c - pos + 1, replacement);
        } else i--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (line == "0") break;
        reduceTerm(line);
        cout << line << '\n';
        int d = 0;
        for (auto c : line) {
            if (c == '(') { cout << char(d + '0'); d++; }
            else if (c == ')') { d--; cout << char(d + '0'); }
            else cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}
