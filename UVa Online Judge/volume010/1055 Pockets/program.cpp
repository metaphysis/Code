#include <bits/stdc++.h>
using namespace std;

struct Cell {
    int x, y, ux, uy, vx, vy;
};

int n;
vector<Cell> cell;
map<pair<int, int>, vector<int> > pos;

int getId(int r, int c) {
    return r * (n + 1) + c;
}

int getLine(int c, char dir) {
    int id;
    if (dir == 'U' || dir == 'D') {
        id = getId(c - 1, 0);
        return cell[id].y + cell[id].vy;
    }
    id = getId(0, c - 1);
    return cell[id].x + cell[id].ux;
}

bool needMove(pair<int, int> p, int line, char dir) {
    if (dir == 'U') return p.second > line;
    if (dir == 'D') return p.second < line;
    if (dir == 'L') return p.first > line;
    return p.first < line;
}

void flipCell(int id, int line, char dir) {
    if (dir == 'U' || dir == 'D') {
        cell[id].y = 2 * line - cell[id].y;
        cell[id].uy = -cell[id].uy;
        cell[id].vy = -cell[id].vy;
    } else {
        cell[id].x = 2 * line - cell[id].x;
        cell[id].ux = -cell[id].ux;
        cell[id].vx = -cell[id].vx;
    }
}

void foldPaper(int c, char dir) {
    int line = getLine(c, dir);
    vector<pair<pair<int, int>, vector<int> > > moveList;
    for (auto &it : pos)
        if (needMove(it.first, line, dir)) moveList.push_back(it);
    for (auto &it : moveList) pos.erase(it.first);
    for (auto &it : moveList) {
        pair<int, int> oldPos = it.first, newPos = oldPos;
        vector<int> st = it.second;
        if (dir == 'U' || dir == 'D') newPos.second = 2 * line - newPos.second;
        else newPos.first = 2 * line - newPos.first;
        reverse(st.begin(), st.end());
        for (int id : st) flipCell(id, line, dir);
        vector<int> &dst = pos[newPos];
        dst.insert(dst.end(), st.begin(), st.end());
    }
}

int getSide(int x, int y, int minX, int maxX, int minY, int maxY) {
    if (x == minX - 1) return 0;
    if (x == maxX + 1) return 1;
    if (y == minY - 1) return 2;
    if (y == maxY + 1) return 3;
    return -1;
}

int solve() {
    int k;
    cin >> n >> k;
    if (n == 0 && k == 0) return -1;
    int cnt = (n + 1) * (n + 1);
    cell.assign(cnt, Cell());
    pos.clear();
    for (int r = 0; r <= n; r++) {
        for (int c = 0; c <= n; c++) {
            int id = getId(r, c);
            cell[id] = {2 * c + 1, 2 * r + 1, 1, 0, 0, 1};
            pos[{2 * c + 1, 2 * r + 1}].push_back(id);
        }
    }
    for (int i = 0, c; i < k; i++) {
        char dir;
        cin >> c >> dir;
        foldPaper(c, dir);
    }
    vector<int> layer(cnt);
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
    for (auto &it : pos) {
        minX = min(minX, it.first.first);
        maxX = max(maxX, it.first.first);
        minY = min(minY, it.first.second);
        maxY = max(maxY, it.first.second);
        for (int i = 0; i < (int)it.second.size(); i++) layer[it.second[i]] = i;
    }
    vector<vector<bool> > block(4, vector<bool>(cnt - 1, false));
    for (int r = 0; r <= n; r++) {
        for (int c = 0; c < n; c++) {
            int a = getId(r, c), b = getId(r, c + 1);
            int x = cell[a].x + cell[a].ux, y = cell[a].y + cell[a].uy;
            int side = getSide(x, y, minX, maxX, minY, maxY);
            if (side != -1) {
                int l = min(layer[a], layer[b]), rr = max(layer[a], layer[b]);
                for (int j = l; j < rr; j++) block[side][j] = true;
            }
        }
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c <= n; c++) {
            int a = getId(r, c), b = getId(r + 1, c);
            int x = cell[a].x + cell[a].vx, y = cell[a].y + cell[a].vy;
            int side = getSide(x, y, minX, maxX, minY, maxY);
            if (side != -1) {
                int l = min(layer[a], layer[b]), rr = max(layer[a], layer[b]);
                for (int j = l; j < rr; j++) block[side][j] = true;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < cnt - 1; j++)
            if (!block[i][j]) ans++;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNum = 1, ans;
    while ((ans = solve()) != -1) {
        cout << "Case " << caseNum++ << ": " << ans << " pockets\n";
    }
    return 0;
}
