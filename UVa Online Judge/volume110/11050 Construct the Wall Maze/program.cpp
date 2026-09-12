#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

struct Wall {
    int x1, y1, x2, y2;
    ull lo, hi, ok;
};

struct Start {
    int sx, sy, ex, ey;
    ull lo, hi;
};

void setBit(ull &lo, ull &hi, int id) {
    if (id < 64) lo |= 1ULL << id;
    else hi |= 1ULL << (id - 64);
}

bool hasBit(ull lo, ull hi, int id) {
    if (id < 64) return (lo >> id) & 1ULL;
    return (hi >> (id - 64)) & 1ULL;
}

bool overlap(const Wall &a, const Wall &b) {
    return (a.lo & b.lo) || (a.hi & b.hi);
}

vector<Wall> buildWalls(int len) {
    vector<Wall> walls;
    for (int x = 0; x + len <= 6; x++) {
        for (int y = 0; y <= 6; y++) {
            Wall cur;
            cur.x1 = x;
            cur.y1 = y;
            cur.x2 = x + len;
            cur.y2 = y;
            cur.lo = cur.hi = cur.ok = 0;
            for (int k = 0; k < len; k++) setBit(cur.lo, cur.hi, (x + k) * 7 + y);
            walls.push_back(cur);
        }
    }
    for (int x = 0; x <= 6; x++) {
        for (int y = 0; y + len <= 6; y++) {
            Wall cur;
            cur.x1 = x;
            cur.y1 = y;
            cur.x2 = x;
            cur.y2 = y + len;
            cur.lo = cur.hi = cur.ok = 0;
            for (int k = 0; k < len; k++) setBit(cur.lo, cur.hi, 42 + x * 6 + y + k);
            walls.push_back(cur);
        }
    }
    return walls;
}

int checkAll(const vector<Start> &starts, ull ok, const Wall &a, const Wall &b, const Wall &c, int len) {
    ull cur[7][7] = {}, nxt[7][7] = {}, vis[7][7] = {};
    ull lo = a.lo | b.lo | c.lo, hi = a.hi | b.hi | c.hi;
    int dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0};
    for (int s = 0; s < (int)starts.size(); s++) {
        ull bit = 1ULL << s;
        if (!(ok & bit)) continue;
        cur[starts[s].sx][starts[s].sy] |= bit;
        vis[starts[s].sx][starts[s].sy] |= bit;
    }
    for (int dis = 1; dis <= len; dis++) {
        memset(nxt, 0, sizeof(nxt));
        for (int x = 1; x <= 6; x++) {
            for (int y = 1; y <= 6; y++) {
                if (cur[x][y] == 0) continue;
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d], id;
                    ull add;
                    if (nx < 1 || nx > 6 || ny < 1 || ny > 6) continue;
                    if (d == 0) id = (x - 1) * 7 + y - 1;
                    else if (d == 1) id = 42 + x * 6 + y - 1;
                    else if (d == 2) id = (x - 1) * 7 + y;
                    else id = 42 + (x - 1) * 6 + y - 1;
                    if (hasBit(lo, hi, id)) continue;
                    add = cur[x][y] & ~vis[nx][ny];
                    nxt[nx][ny] |= add;
                }
            }
        }
        for (int x = 1; x <= 6; x++) {
            for (int y = 1; y <= 6; y++) {
                cur[x][y] = nxt[x][y];
                vis[x][y] |= cur[x][y];
            }
        }
        for (int s = 0; s < (int)starts.size(); s++) {
            ull bit = 1ULL << s;
            if (!(ok & bit) || !(cur[starts[s].ex][starts[s].ey] & bit)) continue;
            if (dis == len) return s;
            ok &= ~bit;
        }
        if (ok == 0) return -1;
    }
    return -1;
}

bool solveCase(int a, int b, int c, const string &path) {
    vector<Start> starts;
    vector<Wall> wa = buildWalls(a), wb = buildWalls(b), wc = buildWalls(c);
    int len = (int)path.size();
    for (int sx = 1; sx <= 6; sx++) {
        for (int sy = 1; sy <= 6; sy++) {
            int x = sx, y = sy;
            ull lo = 0, hi = 0;
            bool valid = true;
            for (int i = 0; i < len; i++) {
                int id;
                if (path[i] == 'N') {
                    id = (x - 1) * 7 + y - 1;
                    y--;
                } else if (path[i] == 'E') {
                    id = 42 + x * 6 + y - 1;
                    x++;
                } else if (path[i] == 'S') {
                    id = (x - 1) * 7 + y;
                    y++;
                } else {
                    id = 42 + (x - 1) * 6 + y - 1;
                    x--;
                }
                if (x < 1 || x > 6 || y < 1 || y > 6) {
                    valid = false;
                    break;
                }
                setBit(lo, hi, id);
            }
            if (valid) starts.push_back({sx, sy, x, y, lo, hi});
        }
    }
    for (int i = 0; i < (int)wa.size(); i++) {
        for (int s = 0; s < (int)starts.size(); s++) {
            if (!(wa[i].lo & starts[s].lo) && !(wa[i].hi & starts[s].hi)) wa[i].ok |= 1ULL << s;
        }
    }
    for (int i = 0; i < (int)wb.size(); i++) {
        for (int s = 0; s < (int)starts.size(); s++) {
            if (!(wb[i].lo & starts[s].lo) && !(wb[i].hi & starts[s].hi)) wb[i].ok |= 1ULL << s;
        }
    }
    for (int i = 0; i < (int)wc.size(); i++) {
        for (int s = 0; s < (int)starts.size(); s++) {
            if (!(wc[i].lo & starts[s].lo) && !(wc[i].hi & starts[s].hi)) wc[i].ok |= 1ULL << s;
        }
    }
    for (int i = 0; i < (int)wa.size(); i++) {
        if (wa[i].ok == 0) continue;
        for (int j = 0; j < (int)wb.size(); j++) {
            ull ab;
            if (overlap(wa[i], wb[j])) continue;
            ab = wa[i].ok & wb[j].ok;
            if (ab == 0) continue;
            for (int k = 0; k < (int)wc.size(); k++) {
                int s;
                ull ok;
                if (overlap(wa[i], wc[k]) || overlap(wb[j], wc[k])) continue;
                ok = ab & wc[k].ok;
                if (ok == 0) continue;
                s = checkAll(starts, ok, wa[i], wb[j], wc[k], len);
                if (s == -1) continue;
                cout << starts[s].sx << ' ' << starts[s].sy << '\n';
                cout << starts[s].ex << ' ' << starts[s].ey << '\n';
                cout << wa[i].x1 << ' ' << wa[i].y1 << ' ' << wa[i].x2 << ' ' << wa[i].y2 << '\n';
                cout << wb[j].x1 << ' ' << wb[j].y1 << ' ' << wb[j].x2 << ' ' << wb[j].y2 << '\n';
                cout << wc[k].x1 << ' ' << wc[k].y1 << ' ' << wc[k].x2 << ' ' << wc[k].y2 << '\n';
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b, c;
    string path;
    while (cin >> a >> b >> c) {
        if (a == 0 && b == 0 && c == 0) break;
        cin >> path;
        solveCase(a, b, c, path);
    }
    return 0;
}
