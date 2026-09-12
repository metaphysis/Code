#include <bits/stdc++.h>
using namespace std;

int parseTime(const string &s) {
    int h = (s[0] - '0') * 10 + s[1] - '0', m = (s[3] - '0') * 10 + s[4] - '0';
    return h * 4 + m / 15;
}

struct Bomb {
    int x1, y1, z1, x2, y2, z2, t1, t2;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, dimX, dimY, dimZ, q, tc = 0;
    while (cin >> n >> dimX >> dimY >> dimZ >> q) {
        if (n == 0 && dimX == 0 && dimY == 0 && dimZ == 0 && q == 0) break;
        vector<Bomb> bombs(n);
        for (Bomb &b : bombs) {
            string s1, s2;
            cin >> b.x1 >> b.y1 >> b.z1 >> b.x2 >> b.y2 >> b.z2 >> s1 >> s2;
            b.t1 = parseTime(s1);
            b.t2 = parseTime(s2);
        }
        cout << "3D World " << ++tc << ":\n";
        while (q--) {
            int wx, wy, wz, len;
            string ts;
            cin >> wx >> wy >> wz >> ts;
            len = parseTime(ts);
            if (wx > dimX || wy > dimY || wz > dimZ || len > 96) {
                cout << "No safe place(s) found\n";
                continue;
            }
            int nx = dimX - wx + 1, ny = dimY - wy + 1, nz = dimZ - wz + 1;
            int sx = nx + 1, sy = ny + 1, sz = nz + 1, st = 97;
            long long total = 1LL * sx * sy * sz * st, ans = 0;
            vector<int> diff(total);
            auto id = [=](int x, int y, int z, int t) {
                return ((x * sy + y) * sz + z) * st + t;
            };
            for (const Bomb &b : bombs) {
                int lx = max(0, b.x1 - wx + 1), ly = max(0, b.y1 - wy + 1), lz = max(0, b.z1 - wz + 1);
                int rx = min(nx - 1, b.x2 - 1), ry = min(ny - 1, b.y2 - 1), rz = min(nz - 1, b.z2 - 1);
                if (lx > rx || ly > ry || lz > rz || b.t1 >= b.t2) continue;
                for (int mask = 0; mask < 16; mask++) {
                    int x = (mask & 1) ? rx + 1 : lx, y = (mask & 2) ? ry + 1 : ly;
                    int z = (mask & 4) ? rz + 1 : lz, t = (mask & 8) ? b.t2 : b.t1;
                    int sign = (__builtin_popcount(mask) & 1) ? -1 : 1;
                    diff[id(x, y, z, t)] += sign;
                }
            }
            for (int x = 1; x < sx; x++)
                for (int y = 0; y < sy; y++)
                    for (int z = 0; z < sz; z++)
                        for (int t = 0; t < st; t++)
                            diff[id(x, y, z, t)] += diff[id(x - 1, y, z, t)];
            for (int x = 0; x < sx; x++)
                for (int y = 1; y < sy; y++)
                    for (int z = 0; z < sz; z++)
                        for (int t = 0; t < st; t++)
                            diff[id(x, y, z, t)] += diff[id(x, y - 1, z, t)];
            for (int x = 0; x < sx; x++)
                for (int y = 0; y < sy; y++)
                    for (int z = 1; z < sz; z++)
                        for (int t = 0; t < st; t++)
                            diff[id(x, y, z, t)] += diff[id(x, y, z - 1, t)];
            for (int x = 0; x < sx; x++)
                for (int y = 0; y < sy; y++)
                    for (int z = 0; z < sz; z++)
                        for (int t = 1; t < st; t++)
                            diff[id(x, y, z, t)] += diff[id(x, y, z, t - 1)];
            for (int x = 0; x < nx; x++) {
                for (int y = 0; y < ny; y++) {
                    for (int z = 0; z < nz; z++) {
                        int bad = 0;
                        for (int t = 0; t < 96; t++) {
                            if (diff[id(x, y, z, t)] > 0) bad++;
                            if (t >= len && diff[id(x, y, z, t - len)] > 0) bad--;
                            if (t >= len - 1 && bad == 0) ans++;
                        }
                    }
                }
            }
            if (ans == 0) cout << "No safe place(s) found\n";
            else cout << ans << " safe place(s) found\n";
        }
    }
    return 0;
}
