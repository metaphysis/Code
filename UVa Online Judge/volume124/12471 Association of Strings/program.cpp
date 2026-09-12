#include <bits/stdc++.h>
using namespace std;

const int ALPHA = 16; // 'a' ~ 'p'

string solve(const vector<int>& p) {
    int n = (int)p.size();
    if (n == 0) return "";
    if (p[0] != 0) return "-1";
    // nxt[k][c]：当前匹配了长度 k 的前缀，追加字符 c 后的匹配长度。
    // 注意：状态 k 的转移需要字符 s[k]，因此 s[k] 确定后才能构造 nxt[k]。
    vector<array<int, ALPHA>> nxt(n);
    string s;
    s.reserve(n);
    s.push_back('a');
    // 状态 0：空串后追加字符。
    for (int c = 0; c < ALPHA; c++) {
        nxt[0][c] = (c == 0 ? 1 : 0);
    }
    for (int i = 1; i < n; i++) {
        if (p[i] < 0 || p[i] > i) return "-1";
        int prev = p[i - 1];
        int ch = -1;
        if (p[i] == 0) {
            // 从状态 P[i-1] 出发，选择一个转移到 0 的字符。
            for (int c = 0; c < ALPHA; c++) {
                if (nxt[prev][c] == 0) {
                    ch = c;
                    break;
                }
            }
            if (ch == -1) return "-1";
        } else {
            // 若 P[i] = x > 0，则新字符必须等于 s[x-1]。
            ch = s[p[i] - 1] - 'a';
            if (nxt[prev][ch] != p[i]) return "-1";
        }
        s.push_back(char('a' + ch));
        // 此刻 s[i] 已知，因此构造状态 i，不能构造状态 i+1。
        // 状态 i 的匹配字符是 s[i]，匹配成功后到 i+1；
        // 其他字符按 failure link P[i-1] 回退。
        for (int c = 0; c < ALPHA; c++) {
            if (c == ch) {
                nxt[i][c] = i + 1;
            } else {
                nxt[i][c] = nxt[p[i - 1]][c];
            }
        }
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; i++) cin >> p[i];
        cout << "Case " << cs << ": " << solve(p) << '\n';
    }
    return 0;
}
