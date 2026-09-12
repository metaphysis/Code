#include <bits/stdc++.h>
using namespace std;

struct Dlx {
    vector<int> left, right, up, down, col, siz;
    int cnt, cols;
    Dlx(int n) {
        cols = n;
        cnt = n;
        left.resize(n + 1);
        right.resize(n + 1);
        up.resize(n + 1);
        down.resize(n + 1);
        col.resize(n + 1);
        siz.assign(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            left[i] = (i == 0 ? n : i - 1);
            right[i] = (i == n ? 0 : i + 1);
            up[i] = down[i] = i;
        }
    }
    void addRow(const vector<int> &cells) {
        int first = 0;
        for (int c : cells) {
            cnt++;
            left.push_back(0);
            right.push_back(0);
            up.push_back(up[c]);
            down.push_back(c);
            col.push_back(c);
            down[up[c]] = cnt;
            up[c] = cnt;
            siz[c]++;
            if (first == 0) {
                left[cnt] = right[cnt] = cnt;
                first = cnt;
            } else {
                left[cnt] = left[first];
                right[cnt] = first;
                right[left[first]] = cnt;
                left[first] = cnt;
            }
        }
    }
    void cover(int c) {
        right[left[c]] = right[c];
        left[right[c]] = left[c];
        for (int i = down[c]; i != c; i = down[i]) {
            for (int j = right[i]; j != i; j = right[j]) {
                down[up[j]] = down[j];
                up[down[j]] = up[j];
                siz[col[j]]--;
            }
        }
    }
    void uncover(int c) {
        for (int i = up[c]; i != c; i = up[i]) {
            for (int j = left[i]; j != i; j = left[j]) {
                siz[col[j]]++;
                down[up[j]] = j;
                up[down[j]] = j;
            }
        }
        right[left[c]] = c;
        left[right[c]] = c;
    }
    bool solve() {
        if (right[0] == 0) return true;
        int best = right[0];
        for (int c = right[best]; c != 0; c = right[c])
            if (siz[c] < siz[best]) best = c;
        if (siz[best] == 0) return false;
        cover(best);
        for (int i = down[best]; i != best; i = down[i]) {
            for (int j = right[i]; j != i; j = right[j]) cover(col[j]);
            if (solve()) return true;
            for (int j = left[i]; j != i; j = left[j]) uncover(col[j]);
        }
        uncover(best);
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int tc = 1; tc <= testCount; tc++) {
        int n, r, c, id[20][20], pixelCount = 0;
        cin >> n;
        vector<vector<string>> grids(n, vector<string>(5));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 5; j++) cin >> grids[i][j];
        cin >> r >> c;
        vector<string> target(r);
        for (int i = 0; i < r; i++) cin >> target[i];
        memset(id, -1, sizeof(id));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (target[i][j] != '.') id[i][j] = pixelCount++;
            }
        }
        Dlx dlx(n + pixelCount);
        for (int p = 0; p < n; p++) {
            bool hasPixel = false;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (grids[p][i][j] != '.') hasPixel = true;
                }
            }
            if (!hasPixel) {
                dlx.addRow({p + 1});
                continue;
            }
            for (int dx = -4; dx < r; dx++) {
                for (int dy = -4; dy < c; dy++) {
                    bool ok = true;
                    vector<int> cells = {p + 1};
                    for (int i = 0; i < 5 && ok; i++) {
                        for (int j = 0; j < 5 && ok; j++) {
                            if (grids[p][i][j] == '.') continue;
                            int x = i + dx, y = j + dy;
                            if (x < 0 || x >= r || y < 0 || y >= c || target[x][y] != grids[p][i][j]) ok = false;
                            else cells.push_back(n + id[x][y] + 1);
                        }
                    }
                    if (ok) dlx.addRow(cells);
                }
            }
        }
        cout << "Case " << tc << ": " << (dlx.solve() ? "Yes" : "No") << '\n';
    }
    return 0;
}
