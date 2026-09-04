#include <bits/stdc++.h>
using namespace std;

struct GameState {
    int cell[8][8], height[8], cols;
};

unordered_map<string, int> memo;
int dirX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dirY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

string makeKey(const GameState &state) {
    string key(64, 0);
    int col, row;
    for (col = 0; col < 8; col++)
        for (row = 0; row < 8; row++)
            key[col * 8 + row] = static_cast<char>(state.cell[col][row]);
    return key;
}

void findComponents(const GameState &state, vector<vector<pair<int, int>>> &components) {
    bool visited[8][8] = {};
    int col, row, nextCol, nextRow, color, dir;
    for (col = 0; col < state.cols; col++) {
        for (row = 0; row < state.height[col]; row++) {
            if (visited[col][row]) continue;
            vector<pair<int, int>> component;
            queue<pair<int, int>> que;
            visited[col][row] = true;
            que.push({col, row});
            color = state.cell[col][row];
            while (!que.empty()) {
                pair<int, int> current = que.front();
                que.pop();
                component.push_back(current);
                for (dir = 0; dir < 8; dir++) {
                    nextCol = current.first + dirX[dir];
                    nextRow = current.second + dirY[dir];
                    if (nextCol < 0 || nextCol >= state.cols || nextRow < 0 || nextRow >= state.height[nextCol]) continue;
                    if (visited[nextCol][nextRow]) continue;
                    if (state.cell[nextCol][nextRow] != color) continue;
                    visited[nextCol][nextRow] = true;
                    que.push({nextCol, nextRow});
                }
            }
            if (component.size() >= 3) components.push_back(component);
        }
    }
}

GameState removeComponent(const GameState &state, const vector<pair<int, int>> &component) {
    GameState next = state;
    bool removed[8][8] = {};
    int col, row, writeRow, sourceCol, targetCol, sourceHeight;
    for (const auto &point : component)
        removed[point.first][point.second] = true;
    for (col = 0; col < state.cols; col++) {
        writeRow = 0;
        for (row = 0; row < state.height[col]; row++)
            if (!removed[col][row])
                next.cell[col][writeRow++] = state.cell[col][row];
        for (row = writeRow; row < 8; row++)
            next.cell[col][row] = 0;
        next.height[col] = writeRow;
    }
    targetCol = 0;
    for (sourceCol = 0; sourceCol < state.cols; sourceCol++) {
        if (next.height[sourceCol] == 0) continue;
        sourceHeight = next.height[sourceCol];
        if (targetCol != sourceCol) {
            for (row = 0; row < sourceHeight; row++)
                next.cell[targetCol][row] = next.cell[sourceCol][row];
            for (row = sourceHeight; row < 8; row++)
                next.cell[targetCol][row] = 0;
            next.height[targetCol] = sourceHeight;
        }
        targetCol++;
    }
    next.cols = targetCol;
    for (col = targetCol; col < 8; col++) {
        next.height[col] = 0;
        for (row = 0; row < 8; row++)
            next.cell[col][row] = 0;
    }
    return next;
}

int dfs(const GameState &state) {
    string key = makeKey(state);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    vector<vector<pair<int, int>>> components;
    findComponents(state, components);
    int best = 0, score;
    for (const auto &component : components) {
        GameState next = removeComponent(state, component);
        score = static_cast<int>(component.size() * component.size()) + dfs(next);
        best = max(best, score);
    }
    memo[key] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k, row, col, color;
    while (cin >> n >> m >> k) {
        GameState state = {};
        state.cols = m;
        for (row = 0; row < n; row++) {
            for (col = 0; col < m; col++) {
                cin >> color;
                state.cell[col][n - row - 1] = color;
            }
        }
        for (col = 0; col < m; col++)
            state.height[col] = n;
        memo.clear();
        cout << dfs(state) << '\n';
    }
    return 0;
}
