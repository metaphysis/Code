#include <bits/stdc++.h>
using namespace std;

int bfs(const string &ord, const vector<string> &mp, int w, int h, int sx, int sy, int ex, int ey) {
    int n = w * h, stLev = 0;
    vector<int> rank(26, -1);
    vector<int> dist(27 * n, -1);
    queue<int> que;
    for (int i = 0; i < 26; ++i)
        rank[ord[i] - 'A'] = i;
    char stCh = mp[sy][sx];
    if (stCh >= 'A' && stCh <= 'Z')
        stLev = rank[stCh - 'A'] + 1;
    if (stCh == 'x')
        return -1;
    int stPos = sy * w + sx;
    dist[stLev * n + stPos] = 0;
    que.push(stLev * n + stPos);
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    while (!que.empty()) {
        int code = que.front();
        que.pop();
        int lev = code / n, pos = code % n;
        int x = pos % w, y = pos / w;
        int curDis = dist[code];
        if (x == ex && y == ey)
            return curDis;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= w || ny < 0 || ny >= h)
                continue;
            char cell = mp[ny][nx];
            if (cell == 'x')
                continue;
            int nlev = lev;
            if (cell >= 'A' && cell <= 'Z') {
                int trapLev = rank[cell - 'A'] + 1;
                if (trapLev <= lev)
                    continue;
                nlev = trapLev;
            }
            int npos = ny * w + nx, ncode = nlev * n + npos;
            if (dist[ncode] != -1)
                continue;
            dist[ncode] = curDis + 1;
            que.push(ncode);
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string ord;
    while (cin >> ord) {
        int w, h;
        cin >> w >> h;
        vector<string> mp(h, string(w, 'x'));
        for (int y = 0; y < h; ++y)
            for (int x = 0; x < w; ++x)
                cin >> mp[y][x];
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;
        int ans = bfs(ord, mp, w, h, sx, sy, ex, ey);
        if (ans == -1)
            cout << "IMPOSSIBLE\n";
        else
            cout << ans << '\n';
    }
    return 0;
}
