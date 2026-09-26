// World of Knots
// UVa ID: 11767
// Verdict: Wrong Answer
// Submission Date: 2026-09-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int prev, next;
};

bool isCross(char ch) {
    return ch == 'H' || ch == 'I';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rows, cols, caseNo = 0;
    while (cin >> rows >> cols && (rows != 0 || cols != 0)) {
        vector<string> grid(rows);
        for (int row = 0; row < rows; row++) cin >> grid[row];
        vector<vector<int>> crossId(rows, vector<int>(cols, -1));
        int crossCount = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (isCross(grid[row][col]))
                    crossId[row][col] = crossCount++;
            }
        }
        int startRow = -1, startCol = -1;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (grid[row][col] != '.' &&
                    (row == 0 || row == rows - 1 || col == 0 || col == cols - 1)) {
                    startRow = row;
                    startCol = col;
                    break;
                }
            }
            if (startRow != -1) break;
        }
        auto canConnect = [&](int r1, int c1, int r2, int c2) {
            char first = grid[r1][c1], second = grid[r2][c2];
            if (r1 == r2)
                return first != '|' && second != '|';
            return first != '-' && second != '-';
        };
        vector<vector<int>> crossingPos(crossCount);
        vector<int> state;
        int prevRow = -1, prevCol = -1, curRow = startRow, curCol = startCol;
        int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
        while (curRow != -1) {
            char ch = grid[curRow][curCol];
            if (isCross(ch)) {
                bool horizontal = prevRow == curRow, over = ((ch == 'H') == horizontal);
                int pos = state.size();
                state.push_back(over ? 1 : -1);
                crossingPos[crossId[curRow][curCol]].push_back(pos);
            }
            int nextRow = -1, nextCol = -1;
            for (int dir = 0; dir < 4; dir++) {
                int nr = curRow + dr[dir], nc = curCol + dc[dir];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '.')
                    continue;
                if (nr == prevRow && nc == prevCol)
                    continue;
                if (!canConnect(curRow, curCol, nr, nc))
                    continue;
                if (isCross(ch) && ((prevRow == curRow) != (nr == curRow)))
                    continue;
                nextRow = nr;
                nextCol = nc;
                break;
            }
            if (nextRow == -1) break;
            prevRow = curRow;
            prevCol = curCol;
            curRow = nextRow;
            curCol = nextCol;
        }
        int n = state.size();
        vector<int> pairPos(n, -1);
        for (int id = 0; id < crossCount; id++) {
            int a = crossingPos[id][0], b = crossingPos[id][1];
            pairPos[a] = b;
            pairPos[b] = a;
        }
        vector<Node> nodes(n);
        vector<char> alive(n, 1);
        queue<pair<int, int>> candidates;
        for (int i = 0; i < n; i++) {
            nodes[i].prev = (i + n - 1) % n;
            nodes[i].next = (i + 1) % n;
            candidates.push({i, nodes[i].next});
        }
        int aliveCount = n, remaining = crossCount;
        auto eraseGroup = [&](const vector<int>& removed) {
            for (int pos : removed) {
                alive[pos] = 0;
                aliveCount--;
            }
            if (aliveCount == 0) return;
            for (int pos : removed) {
                int left = nodes[pos].prev, right = nodes[pos].next;
                while (!alive[left]) left = nodes[left].prev;
                while (!alive[right]) right = nodes[right].next;
                nodes[left].next = right;
                nodes[right].prev = left;
                candidates.push({left, right});
            }
        };
        while (!candidates.empty() && remaining > 0) {
            int a = candidates.front().first, b = candidates.front().second;
            candidates.pop();
            if (a == b || !alive[a] || !alive[b] || nodes[a].next != b)
                continue;
            if (pairPos[a] == b) {
                eraseGroup({a, b});
                remaining--;
                continue;
            }
            int pa = pairPos[a], pb = pairPos[b];
            if (state[a] == state[b] && alive[pa] && alive[pb] &&
                (nodes[pa].next == pb || nodes[pb].next == pa)) {
                eraseGroup({a, b, pa, pb});
                remaining -= 2;
            }
        }
        cout << "Case " << ++caseNo << ": "
             << (remaining == 0 ? "straightened" : "knotted") << '\n';
    }
    return 0;
}
