#include <bits/stdc++.h>
using namespace std;

unordered_map<unsigned int, int> memo;

unsigned int fallDown(unsigned short blue, unsigned short red) {
    unsigned short newBlue = 0, newRed = 0;
    for (int c = 0; c < 4; c++) {
        int h = 0;
        for (int r = 3; r >= 0; r--) {
            int p = r * 4 + c;
            if (blue & (1 << p)) newBlue |= 1 << ((3 - h++) * 4 + c);
            else if (red & (1 << p)) newRed |= 1 << ((3 - h++) * 4 + c);
        }
    }
    return (unsigned int)newBlue | ((unsigned int)newRed << 16);
}

int dfs(unsigned int state) {
    if (!state) return 0;
    auto it = memo.find(state);
    if (it != memo.end()) return it->second;
    unsigned short blue = state & 65535, red = state >> 16;
    unsigned short all = blue | red, used = 0;
    int win = INT_MAX, loss = 0;
    for (int s = 0; s < 16; s++) {
        if (!(all & (1 << s)) || (used & (1 << s))) continue;
        unsigned short color = (blue & (1 << s)) ? blue : red;
        unsigned short group = 0, vis = 0;
        queue<int> que;
        que.push(s);
        vis |= 1 << s;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            group |= 1 << p;
            int r = p / 4, c = p % 4;
            int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) continue;
                int np = nr * 4 + nc;
                if ((color & (1 << np)) && !(vis & (1 << np))) {
                    vis |= 1 << np;
                    que.push(np);
                }
            }
        }
        used |= group;
        unsigned int next = fallDown(blue & ~group, red & ~group);
        int val = dfs(next);
        if (val <= 0) win = min(win, 1 - val);
        else loss = max(loss, 1 + val);
    }
    int ans = (win != INT_MAX) ? win : -loss;
    memo[state] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        unsigned short blue = 0, red = 0;
        string s;
        for (int r = 0; r < 4; r++) {
            cin >> s;
            for (int c = 0; c < 4; c++) {
                int p = r * 4 + c;
                if (s[c] == 'B') blue |= 1 << p;
                else red |= 1 << p;
            }
        }
        unsigned int state = (unsigned int)blue | ((unsigned int)red << 16);
        int ans = dfs(state);
        cout << "Case " << tc << ": ";
        if (ans > 0) cout << "win " << ans << '\n';
        else cout << "loss " << -ans << '\n';
    }
    return 0;
}
