#include <bits/stdc++.h>
using namespace std;

struct Group {
    vector<pair<int, int>> cell;
};

int board[9][9], rowMask[9], colMask[9], boxMask[9], lim[9][9];
vector<Group> grp;
long long ans;

int getBox(int x, int y) {
    return x / 3 * 3 + y / 3;
}

bool setFixed(int x, int y, int d) {
    int bit = 1 << d, b = getBox(x, y);
    if ((rowMask[x] | colMask[y] | boxMask[b]) & bit) return false;
    board[x][y] = d;
    rowMask[x] |= bit;
    colMask[y] |= bit;
    boxMask[b] |= bit;
    return true;
}

int getMask(int id) {
    int mask = (1 << 10) - 2;
    for (auto p : grp[id].cell) {
        int x = p.first, y = p.second, b = getBox(x, y);
        mask &= lim[x][y] & ~(rowMask[x] | colMask[y] | boxMask[b]);
    }
    return mask;
}

bool canSet(int id, int d) {
    int bit = 1 << d;
    for (auto p : grp[id].cell) {
        int x = p.first, y = p.second, b = getBox(x, y);
        if ((rowMask[x] | colMask[y] | boxMask[b]) & bit) return false;
    }
    return true;
}

void update(int id, int d, bool add) {
    int bit = 1 << d;
    for (auto p : grp[id].cell) {
        int x = p.first, y = p.second, b = getBox(x, y);
        board[x][y] = add ? d : 0;
        rowMask[x] ^= bit;
        colMask[y] ^= bit;
        boxMask[b] ^= bit;
    }
}

void dfs(int left) {
    if (left == 0) {
        ++ans;
        return;
    }
    int id = -1, best = 10, mask = 0;
    for (int i = 0; i < (int)grp.size(); ++i) {
        if (board[grp[i].cell[0].first][grp[i].cell[0].second]) continue;
        int cur = getMask(i), cnt = __builtin_popcount(cur);
        if (cnt == 0) return;
        if (cnt < best) {
            best = cnt;
            id = i;
            mask = cur;
        }
    }
    for (int d = 1; d <= 9; ++d) {
        if (!(mask & (1 << d)) || !canSet(id, d)) continue;
        update(id, d, true);
        dfs(left - 1);
        update(id, d, false);
    }
}

bool solve() {
    string s[9];
    int id[9][9], varId[26];
    memset(board, 0, sizeof(board));
    memset(rowMask, 0, sizeof(rowMask));
    memset(colMask, 0, sizeof(colMask));
    memset(boxMask, 0, sizeof(boxMask));
    memset(id, -1, sizeof(id));
    memset(varId, -1, sizeof(varId));
    grp.clear();
    for (int i = 0; i < 9; ++i) cin >> s[i];
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            lim[i][j] = (1 << 10) - 2;
            if (s[i][j] >= '1' && s[i][j] <= '9') {
                if (!setFixed(i, j, s[i][j] - '0')) return false;
            } else if (s[i][j] == 'e') {
                lim[i][j] = (1 << 2) | (1 << 4) | (1 << 6) | (1 << 8);
                id[i][j] = grp.size();
                grp.push_back(Group());
                grp.back().cell.push_back({i, j});
            } else if (s[i][j] == 'o') {
                lim[i][j] = (1 << 1) | (1 << 3) | (1 << 5) | (1 << 7) | (1 << 9);
                id[i][j] = grp.size();
                grp.push_back(Group());
                grp.back().cell.push_back({i, j});
            } else if (s[i][j] == '0') {
                id[i][j] = grp.size();
                grp.push_back(Group());
                grp.back().cell.push_back({i, j});
            } else {
                int c = s[i][j] - 'a';
                if (varId[c] == -1) {
                    varId[c] = grp.size();
                    grp.push_back(Group());
                }
                id[i][j] = varId[c];
                grp[id[i][j]].cell.push_back({i, j});
            }
        }
    }
    for (auto &g : grp) {
        bool usedRow[9] = {}, usedCol[9] = {}, usedBox[9] = {};
        for (auto p : g.cell) {
            int x = p.first, y = p.second, b = getBox(x, y);
            if (usedRow[x] || usedCol[y] || usedBox[b]) return false;
            usedRow[x] = usedCol[y] = usedBox[b] = true;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        ans = 0;
        if (solve()) dfs(grp.size());
        cout << ans << '\n';
    }
    return 0;
}
