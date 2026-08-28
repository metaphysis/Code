#include <bits/stdc++.h>
using namespace std;

vector<int> getPre(const string &str) {
    int n = str.size(), last[26];
    vector<int> pre(n, -1);
    fill(last, last + 26, -1);
    for (int i = 0; i < n; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            int id = str[i] - 'a';
            pre[i] = last[id];
            last[id] = i;
        }
    }
    return pre;
}

bool isMatch(const string &src, int pos, const string &pat, int len, const vector<int> &srcPre, const vector<int> &patPre) {
    char a = src[pos], b = pat[len];
    if (b >= 'A' && b <= 'Z') return a == b;
    if (a < 'a' || a > 'z') return false;
    if (patPre[len] != -1) {
        int dis = len - patPre[len];
        return pos >= dis && a == src[pos - dis];
    }
    return srcPre[pos] < pos - len;
}

vector<int> getFail(const string &pat, const vector<int> &pre) {
    int n = pat.size(), j = 0;
    vector<int> fail(n, 0);
    for (int i = 1; i < n; ++i) {
        while (j > 0 && !isMatch(pat, i, pat, j, pre, pre)) j = fail[j - 1];
        if (isMatch(pat, i, pat, j, pre, pre)) ++j;
        fail[i] = j;
    }
    return fail;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        string src, pat;
        cin >> src >> pat;
        vector<int> srcPre = getPre(src), patPre = getPre(pat);
        vector<int> fail = getFail(pat, patPre);
        int n = src.size(), m = pat.size(), j = 0, ans = 0;
        for (int i = 0; i < n; ++i) {
            while (j > 0 && !isMatch(src, i, pat, j, srcPre, patPre)) j = fail[j - 1];
            if (isMatch(src, i, pat, j, srcPre, patPre)) ++j;
            if (j == m) {
                ++ans;
                j = fail[j - 1];
            }
        }
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
