#include <bits/stdc++.h>
using namespace std;

const int MaxRow = 102, MaxCol = 10010, MaxNode = MaxRow * MaxCol;

struct Node {
    int level, row, col;
};

int n, m;
int grid[MaxRow][MaxCol];
Node nodes[MaxNode];
int colParent[MaxCol][MaxRow], colSize[MaxCol][MaxRow];
int rowParent[MaxRow][MaxCol], rowSize[MaxRow][MaxCol];

bool compareNode(const Node& u, const Node& v) {
    return u.level < v.level;
}

int findRoot(int* parent, int x) {
    return parent[x] == x ? x : parent[x] = findRoot(parent, parent[x]);
}

void mergeSet(int* parent, int* size, int x, int y) {
    int rootX = findRoot(parent, x), rootY = findRoot(parent, y);
    if (rootX == rootY) return;
    parent[rootY] = rootX;
    size[rootX] += size[rootY];
}

bool addLight(int row, int col, int level, int& need) {
    // 合并当前行中的相邻位置
    if (col > 0 && grid[row][col - 1] <= level) mergeSet(rowParent[row], rowSize[row], col, col - 1);
    if (col + 1 < m && grid[row][col + 1] <= level) mergeSet(rowParent[row], rowSize[row], col, col + 1);
    // 合并当前列中的相邻位置
    if (row > 0 && grid[row - 1][col] <= level) mergeSet(colParent[col], colSize[col], row, row - 1);
    if (row + 1 < n && grid[row + 1][col] <= level) mergeSet(colParent[col], colSize[col], row, row + 1);
    int colRoot = findRoot(colParent[col], row), rowRoot = findRoot(rowParent[row], col);
    if (colSize[col][colRoot] == n || rowSize[row][rowRoot] == m) return false;
    if (findRoot(colParent[col], 0) == colRoot || findRoot(colParent[col], n - 1) == colRoot)
        need = max(need, colSize[col][colRoot]);
    else
        need = max(need, (colSize[col][colRoot] + 1) / 2);
    if (findRoot(rowParent[row], 0) == rowRoot || findRoot(rowParent[row], m - 1) == rowRoot)
        need = max(need, rowSize[row][rowRoot]);
    else
        need = max(need, (rowSize[row][rowRoot] + 1) / 2);
    return true;
}

void solveCase() {
    int total = n * m, index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            nodes[i * m + j] = {grid[i][j], i, j};
            colParent[j][i] = i;
            colSize[j][i] = 1;
            rowParent[i][j] = j;
            rowSize[i][j] = 1;
        }
    }
    sort(nodes, nodes + total, compareNode);
    int need = 0;
    for (int level = 0; ; ++level) {
        if (level > need) {
            cout << level << '\n';
            return;
        }
        while (index < total && nodes[index].level == level) {
            if (!addLight(nodes[index].row, nodes[index].col, level, need)) {
                cout << "NO ANSWER!\n";
                return;
            }
            ++index;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m && (n || m)) solveCase();
    return 0;
}
