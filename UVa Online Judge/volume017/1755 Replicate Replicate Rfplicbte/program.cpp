#include <bits/stdc++.h>
using namespace std;

bool dividePattern(const vector<string>& src, vector<string>& dst) {
    int h = src.size(), w = src[0].size();
    vector<vector<int> > mid(h, vector<int>(w, 0)), quo(h, vector<int>(w, 0));
    for (int y = 0; y < h; y++) {
        vector<int> q(w + 2, 0);
        for (int x = 0; x < w + 2; x++) {
            int value = x < w && src[y][x] == '#' ? 1 : 0;
            if (x >= 1)
                value ^= q[x - 1];
            if (x >= 2)
                value ^= q[x - 2];
            q[x] = value;
        }
        if (q[w] || q[w + 1])
            return false;
        for (int x = 0; x < w; x++)
            mid[y][x] = q[x];
    }
    for (int x = 0; x < w; x++) {
        vector<int> q(h + 2, 0);
        for (int y = 0; y < h + 2; y++) {
            int value = y < h ? mid[y][x] : 0;
            if (y >= 1)
                value ^= q[y - 1];
            if (y >= 2)
                value ^= q[y - 2];
            q[y] = value;
        }
        if (q[h] || q[h + 1])
            return false;
        for (int y = 0; y < h; y++)
            quo[y][x] = q[y];
    }
    int minX = w, maxX = -1, minY = h, maxY = -1;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (quo[y][x]) {
                minX = min(minX, x);
                maxX = max(maxX, x);
                minY = min(minY, y);
                maxY = max(maxY, y);
            }
    if (maxX == -1)
        return false;
    dst.assign(maxY - minY + 1, string(maxX - minX + 1, '.'));
    for (int y = minY; y <= maxY; y++)
        for (int x = minX; x <= maxX; x++)
            if (quo[y][x])
                dst[y - minY][x - minX] = '#';
    return true;
}

bool getPrevious(const vector<string>& cur, vector<string>& pre) {
    int h = cur.size(), w = cur[0].size();
    int row[300][3] = {}, col[300][3] = {};
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (cur[y][x] == '#') {
                row[y][x % 3] ^= 1;
                col[x][y % 3] ^= 1;
            }
    int badY = -1, badX = -1, rowDiff = -1, colDiff = -1;
    for (int y = 0; y < h; y++) {
        bool valid = row[y][0] == row[y][1] && row[y][1] == row[y][2];
        if (!valid) {
            if (badY != -1)
                return false;
            badY = y;
            if (row[y][0] != row[y][1] && row[y][0] != row[y][2])
                rowDiff = 0;
            else if (row[y][1] != row[y][0] && row[y][1] != row[y][2])
                rowDiff = 1;
            else
                rowDiff = 2;
        }
    }
    for (int x = 0; x < w; x++) {
        bool valid = col[x][0] == col[x][1] && col[x][1] == col[x][2];
        if (!valid) {
            if (badX != -1)
                return false;
            badX = x;
            if (col[x][0] != col[x][1] && col[x][0] != col[x][2])
                colDiff = 0;
            else if (col[x][1] != col[x][0] && col[x][1] != col[x][2])
                colDiff = 1;
            else
                colDiff = 2;
        }
    }
    if (badY == -1 && badX == -1)
        return dividePattern(cur, pre);
    if (badY == -1 || badX == -1)
        return false;
    if (badX % 3 != rowDiff || badY % 3 != colDiff)
        return false;
    vector<string> fixed = cur;
    fixed[badY][badX] = fixed[badY][badX] == '#' ? '.' : '#';
    return dividePattern(fixed, pre);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int w, h;
    while (cin >> w >> h) {
        vector<string> cur(h);
        for (int y = 0; y < h; y++)
            cin >> cur[y];
        vector<string> ans = cur, pre;
        while (getPrevious(cur, pre)) {
            long long ansArea = 1LL * ans.size() * ans[0].size();
            long long preArea = 1LL * pre.size() * pre[0].size();
            if (preArea < ansArea)
                ans = pre;
            cur = pre;
        }
        for (const string& line : ans)
            cout << line << '\n';
    }
    return 0;
}
