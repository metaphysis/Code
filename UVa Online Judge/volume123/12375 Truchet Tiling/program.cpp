// Truchet Tiling
// UVa ID: 12375
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.060s

#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> parent, size;
    vector<double> area;

    Dsu(int n) : parent(n), size(n, 1), area(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        area[x] += area[y];
    }
};

bool hasArc(int row, int col, const vector<string> &pattern) {
    int tileRow = row / 2, tileCol = col / 2;
    int rowBit = row % 2, colBit = col % 2;
    if (pattern[tileRow][tileCol] == '0') return rowBit == colBit;
    return rowBit != colBit;
}

int getSideId(int row, int col, int side, const vector<vector<array<int, 2>>> &nodeId, const vector<vector<array<int, 2>>> &center) {
    if (nodeId[row][col][1] == -1) return nodeId[row][col][0];
    int centerRow = center[row][col][0], centerCol = center[row][col][1];
    bool nearCenter = side == (centerRow == 0 ? 0 : 1) || side == (centerCol == 0 ? 2 : 3);
    return nodeId[row][col][nearCenter ? 0 : 1];
}

double getQueryArea(int x, int y, int rows, int cols, const vector<vector<bool>> &onCurve, const vector<vector<array<int, 2>>> &nodeId, const vector<vector<array<int, 2>>> &center, Dsu &dsu) {
    if (onCurve[x][y]) return 0;
    int row = min(x, rows - 1), col = min(y, cols - 1);
    int node = nodeId[row][col][0];
    if (nodeId[row][col][1] != -1) {
        int centerRow = row + center[row][col][0], centerCol = col + center[row][col][1];
        if (x != centerRow || y != centerCol) node = nodeId[row][col][1];
    }
    return dsu.area[dsu.find(node)];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    const double pi = acos(-1.0);
    for (int caseId = 1; caseId <= testCases; caseId++) {
        int tileRows, tileCols;
        cin >> tileRows >> tileCols;
        vector<string> pattern(tileRows);
        for (string &row : pattern) cin >> row;
        int rows = tileRows * 2, cols = tileCols * 2, nodeCount = rows * cols * 2;
        vector<vector<array<int, 2>>> nodeId(rows, vector<array<int, 2>>(cols));
        vector<vector<array<int, 2>>> center(rows, vector<array<int, 2>>(cols));
        vector<vector<bool>> onCurve(rows + 1, vector<bool>(cols + 1, false));
        Dsu dsu(nodeCount);
        int nextId = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                nodeId[row][col][0] = nextId++;
                nodeId[row][col][1] = -1;
                if (!hasArc(row, col, pattern)) {
                    dsu.area[nodeId[row][col][0]] = 1;
                    continue;
                }
                nodeId[row][col][1] = nextId++;
                dsu.area[nodeId[row][col][0]] = pi / 4;
                dsu.area[nodeId[row][col][1]] = 1 - pi / 4;
                int rowBit = row % 2, colBit = col % 2;
                center[row][col] = {rowBit, colBit};
                int centerRow = row + rowBit, centerCol = col + colBit;
                onCurve[centerRow][col + 1 - colBit] = true;
                onCurve[row + 1 - rowBit][centerCol] = true;
            }
        }
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col + 1 < cols; col++) {
                int left = getSideId(row, col, 3, nodeId, center), right = getSideId(row, col + 1, 2, nodeId, center);
                dsu.merge(left, right);
            }
        }
        for (int row = 0; row + 1 < rows; row++) {
            for (int col = 0; col < cols; col++) {
                int up = getSideId(row, col, 1, nodeId, center), down = getSideId(row + 1, col, 0, nodeId, center);
                dsu.merge(up, down);
            }
        }
        int queries;
        cin >> queries;
        cout << "Case " << caseId << ":\n";
        for (int i = 0; i < queries; i++) {
            int x, y;
            cin >> x >> y;
            double answer = getQueryArea(x, y, rows, cols, onCurve, nodeId, center, dsu);
            if (fabs(answer) < 0.0000001) answer = 0;
            cout << fixed << setprecision(4) << answer << '\n';
        }
    }
    return 0;
}
