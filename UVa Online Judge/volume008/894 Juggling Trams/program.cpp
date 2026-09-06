#include <bits/stdc++.h>
using namespace std;

int getNextTime(int cur, int base, int t, int k) {
    int id;
    if (cur <= base) id = 0;
    else id = (cur - base + t - 1) / t;
    if (id >= k) return -1;
    return base + id * t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, m;
    while (cin >> t >> m) {
        if (t == 0 && m == 0) break;
        int n, e, sx, sy, fx, fy, st;
        cin >> n >> e;
        cin >> sx >> sy >> fx >> fy;
        cin >> st;
        vector<int> firstS(n + 1), cntS(n + 1), firstW(e + 1), cntW(e + 1);
        for (int i = 1; i <= n; i++)
            cin >> firstS[i] >> cntS[i];
        for (int i = 1; i <= e; i++)
            cin >> firstW[i] >> cntW[i];
        const int inf = 1e9;
        vector<vector<int> > dis(n + 1, vector<int>(e + 1, inf));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int> >, greater<tuple<int, int, int> > > pq;
        dis[sx][sy] = st;
        pq.push(make_tuple(st, sx, sy));
        while (!pq.empty()) {
            int cur, x, y;
            tie(cur, x, y) = pq.top();
            pq.pop();
            if (cur != dis[x][y]) continue;
            if (y < e) {
                int base = firstS[x] + (y - 1) * m;
                int dep = getNextTime(cur, base, t, cntS[x]);
                if (dep != -1 && dep + m < dis[x][y + 1]) {
                    dis[x][y + 1] = dep + m;
                    pq.push(make_tuple(dis[x][y + 1], x, y + 1));
                }
            }
            if (x < n) {
                int base = firstW[y] + (x - 1) * m;
                int dep = getNextTime(cur, base, t, cntW[y]);
                if (dep != -1 && dep + m < dis[x + 1][y]) {
                    dis[x + 1][y] = dep + m;
                    pq.push(make_tuple(dis[x + 1][y], x + 1, y));
                }
            }
        }
        if (dis[fx][fy] == inf) cout << "Impossible.\n";
        else {
            int hh = dis[fx][fy] / 60, mm = dis[fx][fy] % 60;
            cout << "You arrive at " << setw(2) << setfill('0') << hh << ":";
            cout << setw(2) << setfill('0') << mm << ".\n";
        }
    }
    return 0;
}
