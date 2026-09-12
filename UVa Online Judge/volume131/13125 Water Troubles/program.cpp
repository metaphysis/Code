#include <bits/stdc++.h>
using namespace std;

long long tar, ans;
int h;
vector<long long> cap;
vector<unordered_set<long long> > seen;

void dfs(long long cur, int mask) {
    if (!seen[mask].insert(cur).second) return;
    if (cur >= tar && cur < ans) ans = cur;
    if (ans == tar) return;
    for (int i = 0; i < h; i++) {
        if (mask & (1 << i)) continue;
        long long nxt = cur + cap[i];
        int nmask = mask | (1 << i);
        dfs(nxt, nmask);
        if (cur > cap[i]) dfs(cur - cap[i], nmask);
        dfs(cur * cap[i], nmask);
        if (cur % cap[i] == 0) dfs(cur / cap[i], nmask);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<long long> val;
        long long x;
        while (ss >> x) val.push_back(x);
        if (val.size() == 1 && val[0] == 0) break;
        tar = val[0];
        cap.assign(val.begin() + 1, val.end());
        h = cap.size();
        ans = LLONG_MAX;
        seen.assign(1 << h, unordered_set<long long>());
        for (int i = 0; i < h; i++) dfs(cap[i], 1 << i);
        if (ans == LLONG_MAX) cout << 0 << '\n';
        else cout << ans << '\n';
    }
    return 0;
}
