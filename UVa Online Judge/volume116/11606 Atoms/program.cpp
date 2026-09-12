#include <bits/stdc++.h>
using namespace std;

int n;
int cur[8][8], want[8][8];

int getCap(int x, int y) {
    if ((x == 0 || x == n - 1) && (y == 0 || y == n - 1)) return 1;
    if (x == 0 || x == n - 1 || y == 0 || y == n - 1) return 2;
    return 3;
}

bool sameGrid() {
    for (int id = 0; id < n * n; id++) if (cur[id / n][id % n] != want[id / n][id % n]) return false;
    return true;
}

pair<int, int> getNext(int side) {
    int best = -1, ansX = -1, ansY = -1;
    for (int id = 0; id < n * n; id++) {
        int x = id / n, y = id % n;
        bool ok = (side == 1 && cur[x][y] >= 0) || (side == -1 && cur[x][y] <= 0);
        if (ok) {
            int val = cur[x][y] + side, dis = 1000000000;
            if (abs(val) <= getCap(x, y)) {
                for (int jd = 0; jd < n * n; jd++) if (cur[jd / n][jd % n] * side < 0) dis = min(dis, abs(x - jd / n) + abs(y - jd % n));
                if (dis > best) {
                    best = dis;
                    ansX = x;
                    ansY = y;
                }
            }
        }
    }
    return make_pair(ansX, ansY);
}

bool simulate(int sx, int sy) {
    for (int id = 0; id < n * n; id++) cur[id / n][id % n] = 0;
    cur[sx][sy] = 1;
    if (sameGrid()) return true;
    int side = -1;
    while (true) {
        pair<int, int> pos = getNext(side);
        if (pos.first == -1) break;
        cur[pos.first][pos.second] += side;
        if (sameGrid()) return true;
        side = -side;
    }
    return false;
}

bool isValid() {
    for (int id = 0; id < n * n; id++) if (abs(want[id / n][id % n]) > getCap(id / n, id % n)) return false;
    for (int id = 0; id < n * n; id++) cur[id / n][id % n] = 0;
    if (sameGrid()) return true;
    for (int id = 0; id < n * n; id++) if (simulate(id / n, id % n)) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> n;
        for (int id = 0; id < n * n; id++) cin >> want[id / n][id % n];
        cout << "Case " << tc << ": " << (isValid() ? "valid" : "invalid") << '\n';
    }
    return 0;
}
