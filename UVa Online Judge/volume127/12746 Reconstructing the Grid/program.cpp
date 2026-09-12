#include <bits/stdc++.h>
using namespace std;

const int maxN = 10005;
const int maxM = 105;

int rowNum, colNum, nodeNum;
vector<int> adj[maxN];
int disArr[maxN], preArr[maxN], que[maxN];
int workGrid[maxM][maxM], bestGrid[maxM][maxM];
bool used[maxN], hasBest;

bool getPath(int start, int target, vector<int> &path) {
    fill(disArr + 1, disArr + nodeNum + 1, -1);
    fill(preArr + 1, preArr + nodeNum + 1, 0);
    int head = 0, tail = 0;
    que[tail++] = start;
    disArr[start] = 0;
    while (head < tail) {
        int u = que[head++];
        if (u == target)
            break;
        for (int v : adj[u])
            if (disArr[v] == -1) {
                disArr[v] = disArr[u] + 1;
                preArr[v] = u;
                que[tail++] = v;
            }
    }
    if (disArr[target] == -1)
        return false;
    path.clear();
    for (int u = target; u != 0; u = preArr[u])
        path.push_back(u);
    reverse(path.begin(), path.end());
    return true;
}

bool isAdjacent(int u, int v) {
    return find(adj[u].begin(), adj[u].end(), v) != adj[u].end();
}

bool checkGrid() {
    for (int r = 0; r < rowNum; r++)
        for (int c = 0; c < colNum; c++) {
            int u = workGrid[r][c], need = 0;
            if (r > 0) {
                need++;
                if (!isAdjacent(u, workGrid[r - 1][c]))
                    return false;
            }
            if (r + 1 < rowNum) {
                need++;
                if (!isAdjacent(u, workGrid[r + 1][c]))
                    return false;
            }
            if (c > 0) {
                need++;
                if (!isAdjacent(u, workGrid[r][c - 1]))
                    return false;
            }
            if (c + 1 < colNum) {
                need++;
                if (!isAdjacent(u, workGrid[r][c + 1]))
                    return false;
            }
            if (static_cast<int>(adj[u].size()) != need)
                return false;
        }
    return true;
}

void saveBest() {
    if (!hasBest) {
        hasBest = true;
        for (int r = 0; r < rowNum; r++)
            for (int c = 0; c < colNum; c++)
                bestGrid[r][c] = workGrid[r][c];
        return;
    }
    for (int r = 0; r < rowNum; r++)
        for (int c = 0; c < colNum; c++) {
            if (workGrid[r][c] == bestGrid[r][c])
                continue;
            if (workGrid[r][c] < bestGrid[r][c])
                for (int i = 0; i < rowNum; i++)
                    for (int j = 0; j < colNum; j++)
                        bestGrid[i][j] = workGrid[i][j];
            return;
        }
}

bool buildGrid(const vector<int> &firstRow) {
    memset(used, 0, sizeof(used));
    for (int c = 0; c < colNum; c++) {
        int u = firstRow[c];
        if (u < 1 || u > nodeNum || used[u])
            return false;
        used[u] = true;
        workGrid[0][c] = u;
    }
    for (int r = 1; r < rowNum; r++)
        for (int c = 0; c < colNum; c++) {
            int up = workGrid[r - 1][c], val = 0, cnt = 0;
            for (int v : adj[up]) {
                if (c > 0 && v == workGrid[r - 1][c - 1])
                    continue;
                if (c + 1 < colNum && v == workGrid[r - 1][c + 1])
                    continue;
                if (r > 1 && v == workGrid[r - 2][c])
                    continue;
                val = v;
                cnt++;
            }
            if (cnt != 1 || used[val])
                return false;
            used[val] = true;
            workGrid[r][c] = val;
        }
    return checkGrid();
}

void solveCase() {
    hasBest = false;
    vector<int> corners, ends;
    for (int i = 1; i <= nodeNum; i++) {
        if (static_cast<int>(adj[i].size()) == 2)
            corners.push_back(i);
        if (static_cast<int>(adj[i].size()) == 1)
            ends.push_back(i);
    }
    if (nodeNum == 1) {
        if (adj[1].empty()) {
            workGrid[0][0] = 1;
            if (checkGrid())
                saveBest();
        }
        return;
    }
    if (rowNum == 1 || colNum == 1) {
        if (ends.size() != 2)
            return;
        int length = max(rowNum, colNum);
        for (int s : ends)
            for (int t : ends)
                if (s != t) {
                    vector<int> path;
                    if (!getPath(s, t, path) || static_cast<int>(path.size()) != length)
                        continue;
                    memset(used, 0, sizeof(used));
                    bool ok = true;
                    for (int i = 0; i < length; i++) {
                        if (used[path[i]])
                            ok = false;
                        used[path[i]] = true;
                        if (rowNum == 1)
                            workGrid[0][i] = path[i];
                        else
                            workGrid[i][0] = path[i];
                    }
                    if (ok && checkGrid())
                        saveBest();
                }
        return;
    }
    if (corners.size() != 4)
        return;
    for (int s : corners)
        for (int t : corners)
            if (s != t) {
                vector<int> path;
                if (!getPath(s, t, path) || static_cast<int>(path.size()) != colNum)
                    continue;
                if (buildGrid(path))
                    saveBest();
            }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testNum;
    cin >> testNum;
    for (int tc = 1; tc <= testNum; tc++) {
        cin >> rowNum >> colNum;
        nodeNum = rowNum * colNum;
        for (int i = 1; i <= nodeNum; i++) {
            adj[i].clear();
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int v;
                cin >> v;
                adj[i].push_back(v);
            }
        }
        solveCase();
        cout << "Case " << tc << ":\n";
        if (!hasBest) {
            cout << "NO SUCH GRID\n";
            continue;
        }
        for (int r = 0; r < rowNum; r++) {
            for (int c = 0; c < colNum; c++) {
                if (c > 0)
                    cout << ' ';
                cout << bestGrid[r][c];
            }
            cout << '\n';
        }
    }
    return 0;
}
