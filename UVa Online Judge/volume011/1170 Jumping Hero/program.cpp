#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
int l, c, n, fCnt, st, ed, ans;
vector<int> mp, fId, jumpCnt, jumpLen, dista, mark;
vector<pair<int, int> > pos;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

void relax(int v, int d) {
    if (d < dista[v]) {
        dista[v] = d;
        pq.push(make_pair(d, v));
    }
}

void runFountain(int id, int base) {
    int src = pos[id].first * c + pos[id].second;
    vector<int> cur, nxt;
    cur.push_back(src);
    for (int step = 1; step <= jumpCnt[id]; step++) {
        nxt.clear();
        int tag = step + id * 6 + 1;
        for (int u : cur) {
            int x = u / c, y = u % c;
            int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k] * jumpLen[id], ny = y + dy[k] * jumpLen[id];
                if (nx < 0 || nx >= l || ny < 0 || ny >= c) continue;
                int v = nx * c + ny;
                if (mp[v] == 0) continue;
                if (v == ed) ans = min(ans, base + step);
                int to = fId[v];
                if (to != -1 && to != id) {
                    relax(n + to, base + step);
                } else if (step == jumpCnt[id]) {
                    relax(v, base + step);
                } else if (mark[v] != tag) {
                    mark[v] = tag;
                    nxt.push_back(v);
                }
            }
        }
        cur.swap(nxt);
        if (cur.empty()) break;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        cin >> l >> c;
        n = l * c;
        mp.assign(n, 0);
        fId.assign(n, -1);
        pos.clear();
        jumpCnt.clear();
        jumpLen.clear();
        for (int i = 0; i < n; i++) {
            cin >> mp[i];
            if (mp[i] > 1) {
                fId[i] = (int)pos.size();
                pos.push_back(make_pair(i / c, i % c));
                jumpCnt.push_back(mp[i] / 10);
                jumpLen.push_back(mp[i] % 10);
            }
        }
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;
        st = sx * c + sy;
        ed = ex * c + ey;
        fCnt = (int)pos.size();
        dista.assign(n + fCnt, inf);
        mark.assign(n, 0);
        while (!pq.empty()) pq.pop();
        ans = (st == ed ? 0 : inf);
        relax(st, 0);
        while (!pq.empty()) {
            int d = pq.top().first, u = pq.top().second;
            pq.pop();
            if (d != dista[u]) continue;
            if (d >= ans) continue;
            if (u >= n) {
                runFountain(u - n, d);
                continue;
            }
            int x = u / c, y = u % c;
            int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx < 0 || nx >= l || ny < 0 || ny >= c) continue;
                int v = nx * c + ny;
                if (mp[v] == 0) continue;
                if (v == ed) ans = min(ans, d + 1);
                if (fId[v] == -1) relax(v, d + 1);
                else relax(n + fId[v], d + 1);
            }
        }
        if (cs) cout << '\n';
        if (ans == inf) cout << "IMPOSSIBLE\n";
        else cout << ans << '\n';
    }
    return 0;
}
