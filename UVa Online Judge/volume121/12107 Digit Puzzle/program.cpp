// Digit Puzzle
// UVa ID: 12107
// Verdict: Accepted
// Submission Date: 2025-12-30
// UVa Run Time: 0.310s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int a, b, c;
string s;

int validate(int depth) {
    if (depth == a + b) {
        int x = stoi(s.substr(0, a)), y = stoi(s.substr(a, b));
        string z = to_string(x * y);
        if (z.length() != c) return 0;
        for (int i = 0; i < c; i++) {
            if (s[a + b + i] == '*') continue;
            if (s[a + b + i] != z[i]) return 0;
        }
        return 1;
    }
    if (s[depth] != '*') return validate(depth + 1);
    int cnt = 0;
    for (int d = 0; d <= 9; d++) {
        // 不能有前导0
        if (!d && (!depth || depth == a)) continue;
        s[depth] = '0' + d;
        cnt += validate(depth + 1);
        s[depth] = '*';
        if (cnt > 1) break;
    }
    return cnt;
}

const string replaced = "*0123456789";

bool iddfs(int depth, int changed, int limit) {
    if (changed == limit) {
        if (validate(0) == 1) {
            cout << s.substr(0, a) << ' ' << s.substr(a, b) << ' ' << s.substr(a + b, c) << '\n';
            return true;
        }
        return false;
    }
    if (depth == s.length()) return false;
    for (auto c : replaced) {
        if (c == '0' && (!depth || depth == a || depth == (a + b))) continue;
        char backup = s[depth];
        s[depth] = c;
        if (iddfs(depth + 1, changed + (backup != c), limit)) return true;
        s[depth] = backup;
    }
    return false;
}

int main() {
	string x, y, z;
	int cases = 1;
	while (cin >> x) {
	    if (x.front() == '0') break;
	    cout << "Case " << cases++ << ": ";
	    cin >> y >> z;
	    a = x.length(), b = y.length(), c = z.length();
	    s = x + y + z;
	    for (int limit = 0; limit <= s.length(); limit++)
            if (iddfs(0, 0, limit))
                break;
	}
	return 0;
}
