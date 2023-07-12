// Echo
// UVa ID: 10045
// Verdict: Accepted
// Submission Date: 2023-07-12
// UVa Run Time: 0.380s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>
using namespace std;
const int NOT_CONSISTENT = 0, ECHO = 1, NO_ECHO_BUT_CONSISTENT = 2;
string s, buffer;
map<pair<int, string>, int> dp;
int dfs(int idx) {
    if (idx >= s.size()) return buffer.size() ? NO_ECHO_BUT_CONSISTENT : ECHO;
    if (dp.count(make_pair(idx, buffer))) return dp[make_pair(idx, buffer)];
    int r = NOT_CONSISTENT;
    if (buffer.size()) {
        if (s[idx] == buffer.front()) {
            char c = buffer.front();
            buffer.erase(buffer.begin());
            r |= dfs(idx + 1);
            buffer.insert(buffer.begin(), c);
            if (r & 1) return dp[make_pair(idx, buffer)] = r;
        }
    }
    if (buffer.size() <= 9) {
        buffer.push_back(s[idx]);
        r |= dfs(idx + 1);
        buffer.pop_back();
    }
    return dp[make_pair(idx, buffer)] = r;
}

string echo[3] = {
    "An echo string with buffer size ten",
    "Not an echo string, but still consistent with the theory",
    "Not consistent with the theory"
};
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> s;
        dp.clear();
        int r = dfs(0);
        cout << echo[r ? (r & 1 ? 0 : 1) : 2] << '\n';
    }
    return 0;
}
