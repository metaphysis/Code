#include <bits/stdc++.h>
using namespace std;

struct Rect {
    long long lx;
    long long by;
    long long rx;
    long long ty;
};

int getAnswer(const vector<Rect>& rects, long long sx, long long sy, long long tx, long long ty) {
    vector<long long> xs;
    vector<long long> ys;
    vector<long long> keyX;
    vector<long long> keyY;
    keyX.push_back(sx);
    keyX.push_back(tx);
    keyY.push_back(sy);
    keyY.push_back(ty);
    for (const Rect& rec : rects) {
        keyX.push_back(rec.lx);
        keyX.push_back(rec.rx);
        keyY.push_back(rec.by);
        keyY.push_back(rec.ty);
    }
    for (long long value : keyX) {
        xs.push_back(value * 2 - 1);
        xs.push_back(value * 2);
        xs.push_back(value * 2 + 1);
    }
    for (long long value : keyY) {
        ys.push_back(value * 2 - 1);
        ys.push_back(value * 2);
        ys.push_back(value * 2 + 1);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int xn = static_cast<int>(xs.size());
    int yn = static_cast<int>(ys.size());
    vector<vector<int>> diff(xn + 1, vector<int>(yn + 1, 0));
    for (const Rect& rec : rects) {
        long long lx = rec.lx * 2;
        long long by = rec.by * 2;
        long long rx = rec.rx * 2;
        long long ty = rec.ty * 2;
        int xl = lower_bound(xs.begin(), xs.end(), lx) - xs.begin();
        int xr = upper_bound(xs.begin(), xs.end(), rx) - xs.begin() - 1;
        int yl = lower_bound(ys.begin(), ys.end(), by) - ys.begin();
        int yr = upper_bound(ys.begin(), ys.end(), ty) - ys.begin() - 1;
        diff[xl][yl]++;
        diff[xr + 1][yl]--;
        diff[xl][yr + 1]--;
        diff[xr + 1][yr + 1]++;
    }
    vector<vector<bool>> blocked(xn, vector<bool>(yn, false));
    for (int i = 0; i < xn; i++) {
        for (int j = 0; j < yn; j++) {
            if (i > 0) diff[i][j] += diff[i - 1][j];
            if (j > 0) diff[i][j] += diff[i][j - 1];
            if (i > 0 && j > 0) diff[i][j] -= diff[i - 1][j - 1];
            blocked[i][j] = diff[i][j] > 0;
        }
    }
    int sxi = lower_bound(xs.begin(), xs.end(), sx * 2) - xs.begin();
    int syi = lower_bound(ys.begin(), ys.end(), sy * 2) - ys.begin();
    int txi = lower_bound(xs.begin(), xs.end(), tx * 2) - xs.begin();
    int tyi = lower_bound(ys.begin(), ys.end(), ty * 2) - ys.begin();
    int total = xn * yn;
    int inf = 1e9;
    vector<vector<int>> dist(total, vector<int>(2, inf));
    deque<pair<int, int>> que;
    int start = sxi * yn + syi;
    int target = txi * yn + tyi;
    dist[start][0] = 0;
    dist[start][1] = 0;
    que.push_back({start, 0});
    que.push_back({start, 1});
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int ndir[4] = {0, 0, 1, 1};
    while (!que.empty()) {
        int id = que.front().first;
        int dir = que.front().second;
        que.pop_front();
        int x = id / yn;
        int y = id % yn;
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= xn || ny < 0 || ny >= yn) continue;
            if (blocked[nx][ny]) continue;
            int nextId = nx * yn + ny;
            int cost = dir == ndir[k] ? 0 : 1;
            int nextDist = dist[id][dir] + cost;
            if (nextDist >= dist[nextId][ndir[k]]) continue;
            dist[nextId][ndir[k]] = nextDist;
            if (cost == 0) que.push_front({nextId, ndir[k]});
            else que.push_back({nextId, ndir[k]});
        }
    }
    int answer = min(dist[target][0], dist[target][1]);
    if (answer == inf) return -1;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int n;
        cin >> n;
        vector<Rect> rects(n);
        for (Rect& rec : rects) cin >> rec.lx >> rec.by >> rec.rx >> rec.ty;
        int k;
        cin >> k;
        cout << "Labyrinth #" << testCase << '\n';
        while (k--) {
            long long sx;
            long long sy;
            long long tx;
            long long ty;
            cin >> sx >> sy >> tx >> ty;
            int answer = getAnswer(rects, sx, sy, tx, ty);
            if (answer == -1) cout << "Impossible.\n";
            else cout << answer << '\n';
        }
    }
    return 0;
}
