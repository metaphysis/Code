#include <bits/stdc++.h>
using namespace std;
struct Limit {
    int face, type;
    array<int, 3> pos;
};

bool checkLayers(const vector<Limit>& limits, const int base[], int axis, int n) {
    int masks[10], other[3] = {base[0], base[1], base[2]};
    fill(masks, masks + 10, 3);
    swap(other[(axis + 1) % 3], other[(axis + 2) % 3]);
    masks[axis == 2 ? n - 1 : 0] = 1;
    for (const auto& cur : limits) {
        int bits = (cur.type == base[cur.face]) | ((cur.type == other[cur.face]) << 1);
        masks[cur.pos[axis]] &= bits;
        if (!masks[cur.pos[axis]]) return false;
    }
    return true;
}

bool canBuild(const vector<Limit>& limits, const int corner[], int n) {
    // 固定顶面后，前面与右面依次取环上相邻的两个编号
    int ring[6][4] = {{2, 3, 5, 4}, {1, 4, 6, 3}, {1, 2, 6, 5},
                     {1, 5, 6, 2}, {1, 3, 6, 4}, {2, 4, 5, 3}};
    for (int up = 1; up <= 6; ++up) for (int i = 0; i < 4; ++i) {
        int front = ring[up - 1][i], right = ring[up - 1][(i + 1) % 4];
        if (corner[0] && corner[0] != up) continue;
        if (corner[1] && corner[1] != front) continue;
        if (corner[2] && corner[2] != right) continue;
        int base[3] = {min(up, 7 - up), min(front, 7 - front), min(right, 7 - right)};
        for (int axis = 0; axis < 3; ++axis) if (checkLayers(limits, base, axis, n)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int m, n, k, corner[3] = {};
        cin >> m >> n >> k;
        vector<Limit> limits;
        for (int face = 0; face < 3; ++face) {
            int rowCnt = face == 0 ? k : m, colCnt = face == 2 ? k : n;
            for (int i = 0; i < rowCnt; ++i) for (int j = 0; j < colCnt; ++j) {
                char ch;
                cin >> ch;
                if (ch == '?') continue;
                int value = ch - '0';
                Limit cur = {face, min(value, 7 - value), {0, 0, 0}};
                if (face == 0) cur.pos = {0, k - 1 - i, j};
                else if (face == 1) cur.pos = {i, 0, j};
                else cur.pos = {i, j, n - 1};
                if (cur.pos[0] == 0 && cur.pos[1] == 0 && cur.pos[2] == n - 1) corner[face] = value;
                limits.push_back(cur);
            }
        }
        cout << (canBuild(limits, corner, n) ? "YES" : "NO") << '\n';
    }
    return 0;
}
