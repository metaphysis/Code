#include <bits/stdc++.h>
using namespace std;

int n, p, k, firstPos;
bitset<100> boardMask;
vector<int> cellR, cellC;
vector<vector<pair<int, int>>> shapeList[21];
vector<bitset<100>> placeList, pathList;
string bestAns;

int popCount(uint32_t x) {
    int cnt;
    cnt = 0;
    while (x) {
        x &= x - 1;
        cnt++;
    }
    return cnt;
}

bool isConnected(uint32_t mask, const vector<uint32_t> &adj) {
    uint32_t seen, add;
    int i;
    seen = 1u;
    add = 1u;
    while (add) {
        add = 0;
        for (i = 0; i < p; i++)
            if ((seen & (1u << i)) && (mask & (1u << i))) add |= adj[i] & mask & ~seen;
        seen |= add;
    }
    return seen == mask;
}

string makeAnswer() {
    vector<char> out;
    string ans;
    int i, j, pos;
    out.assign(n * n, '.');
    for (i = 0; i < (int)pathList.size(); i++)
        for (pos = 0; pos < n * n; pos++)
            if (pathList[i][pos]) out[pos] = char('A' + i);
    ans.reserve(n * n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) ans.push_back(out[i * n + j]);
    return ans;
}

void dfs(bitset<100> used, int cnt) {
    int pos, i;
    if (cnt == k) {
        if (used == boardMask) {
            string ans;
            ans = makeAnswer();
            if (bestAns.empty() || ans < bestAns) bestAns = ans;
        }
        return;
    }
    pos = -1;
    for (i = 0; i < n * n; i++)
        if (boardMask[i] && !used[i]) {
            pos = i;
            break;
        }
    if (pos == -1) return;
    for (i = 0; i < (int)placeList.size(); i++) {
        if (!placeList[i][pos]) continue;
        if ((placeList[i] & used).any()) continue;
        pathList.push_back(placeList[i]);
        dfs(used | placeList[i], cnt + 1);
        pathList.pop_back();
    }
}

void buildShapes() {
    vector<uint32_t> adj;
    set<string> shapeSet[21];
    uint32_t limit, sub, mask;
    int i, j, r, c, area, minR, minC, maxR, maxC;
    buildShapes:
    adj.assign(p, 0);
    for (i = 0; i < p; i++) {
        for (j = 0; j < p; j++) {
            if (abs(cellR[i] - cellR[j]) + abs(cellC[i] - cellC[j]) == 1) adj[i] |= 1u << j;
        }
    }
    limit = 1u << (p - 1);
    for (sub = 0; sub < limit; sub++) {
        mask = (sub << 1) | 1u;
        area = popCount(mask);
        if (area == p || p % area != 0) continue;
        if (!isConnected(mask, adj)) continue;
        minR = n;
        minC = n;
        maxR = 0;
        maxC = 0;
        for (i = 0; i < p; i++) {
            if (!(mask & (1u << i))) continue;
            minR = min(minR, cellR[i]);
            minC = min(minC, cellC[i]);
            maxR = max(maxR, cellR[i]);
            maxC = max(maxC, cellC[i]);
        }
        string key(100, '0');
        vector<pair<int, int>> shape;
        for (i = 0; i < p; i++) {
            if (!(mask & (1u << i))) continue;
            r = cellR[i] - minR;
            c = cellC[i] - minC;
            key[r * 10 + c] = '1';
            shape.push_back(make_pair(r, c));
        }
        if (shapeSet[area].insert(key).second) shapeList[area].push_back(shape);
    }
}

bool tryShape(const vector<pair<int, int>> &shape, int area) {
    int height, width, dr, dc, r, c, i;
    bitset<100> mask;
    height = 0;
    width = 0;
    for (i = 0; i < (int)shape.size(); i++) {
        height = max(height, shape[i].first + 1);
        width = max(width, shape[i].second + 1);
    }
    placeList.clear();
    for (dr = 0; dr + height <= n; dr++) {
        for (dc = 0; dc + width <= n; dc++) {
            mask.reset();
            for (i = 0; i < (int)shape.size(); i++) {
                r = dr + shape[i].first;
                c = dc + shape[i].second;
                mask.set(r * n + c);
            }
            if ((mask & ~boardMask).any()) continue;
            placeList.push_back(mask);
        }
    }
    k = p / area;
    for (i = 0; i < (int)placeList.size(); i++) {
        if (!placeList[i][firstPos]) continue;
        pathList.clear();
        pathList.push_back(placeList[i]);
        dfs(placeList[i], 1);
    }
    return !bestAns.empty();
}

int solve() {
    vector<string> grid;
    int area, i, j;
    cin >> n;
    if (n == 0) return 0;
    grid.assign(n, "");
    boardMask.reset();
    cellR.clear();
    cellC.clear();
    for (i = 0; i < n; i++) {
        cin >> grid[i];
        for (j = 0; j < n; j++) {
            if (grid[i][j] == '*') {
                boardMask.set(i * n + j);
                cellR.push_back(i);
                cellC.push_back(j);
            }
        }
    }
    p = cellR.size();
    firstPos = cellR[0] * n + cellC[0];
    for (area = 0; area <= 20; area++) shapeList[area].clear();
    buildShapes();
    bestAns.clear();
    for (area = p / 2; area >= 1; area--) {
        if (p % area != 0) continue;
        for (i = 0; i < (int)shapeList[area].size(); i++)
            tryShape(shapeList[area][i], area);
        if (!bestAns.empty()) break;
    }
    for (i = 0; i < n; i++) cout << bestAns.substr(i * n, n) << '\n';
    cout << '\n';
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (solve()) {
    }
    return 0;
}
