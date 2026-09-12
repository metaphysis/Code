#include <bits/stdc++.h>
using namespace std;

struct Rule {
    vector<int> ids;
    int need;
};

int rows, cols, mineCnt, varCnt;
vector<string> board;
vector<Rule> rules;

bool propagate(vector<int>& state) {
    while (true) {
        bool changed = false;
        int used = 0, unknown = 0;
        for (int i = 0; i < varCnt; i++) {
            if (state[i] == 1) used++;
            if (state[i] == -1) unknown++;
        }
        if (used > mineCnt || used + unknown < mineCnt) return false;
        if (used == mineCnt) {
            for (int i = 0; i < varCnt; i++)
                if (state[i] == -1) {
                    state[i] = 0;
                    changed = true;
                }
        } else if (used + unknown == mineCnt) {
            for (int i = 0; i < varCnt; i++)
                if (state[i] == -1) {
                    state[i] = 1;
                    changed = true;
                }
        }
        for (const Rule& rule : rules) {
            int have = 0, left = 0;
            for (int id : rule.ids) {
                if (state[id] == 1) have++;
                if (state[id] == -1) left++;
            }
            if (have > rule.need || have + left < rule.need) return false;
            if (have == rule.need) {
                for (int id : rule.ids)
                    if (state[id] == -1) {
                        state[id] = 0;
                        changed = true;
                    }
            } else if (have + left == rule.need) {
                for (int id : rule.ids)
                    if (state[id] == -1) {
                        state[id] = 1;
                        changed = true;
                    }
            }
        }
        if (!changed) return true;
    }
}

bool search(vector<int> state) {
    if (!propagate(state)) return false;
    int pick = -1, best = -1;
    vector<int> deg(varCnt, 0);
    for (const Rule& rule : rules)
        for (int id : rule.ids)
            if (state[id] == -1) deg[id]++;
    for (int i = 0; i < varCnt; i++)
        if (state[i] == -1 && deg[i] > best) {
            best = deg[i];
            pick = i;
        }
    if (pick == -1) return true;
    vector<int> next = state;
    next[pick] = 0;
    if (search(next)) return true;
    next = state;
    next[pick] = 1;
    return search(next);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    for (int tc = 1; tc <= testCnt; tc++) {
        cin >> rows >> cols >> mineCnt;
        board.resize(rows);
        for (string& line : board) cin >> line;
        vector<vector<int>> id(rows, vector<int>(cols, -1));
        varCnt = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (board[i][j] == '.') id[i][j] = varCnt++;
        rules.clear();
        int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                if (board[i][j] != 'E' && (board[i][j] < '1' || board[i][j] > '8')) continue;
                int need = board[i][j] == 'E' ? 0 : board[i][j] - '0';
                Rule rule;
                for (int k = 0; k < 8; k++) {
                    int ni = i + dr[k], nj = j + dc[k];
                    if (ni < 0 || ni >= rows || nj < 0 || nj >= cols) continue;
                    if (board[ni][nj] == 'X') need--;
                    if (id[ni][nj] != -1) rule.ids.push_back(id[ni][nj]);
                }
                rule.need = need;
                rules.push_back(rule);
            }
        for (int i = 0; i < varCnt; i++) {
            vector<int> state(varCnt, -1);
            state[i] = 0;
            if (!search(state)) {
                for (int r = 0; r < rows; r++)
                    for (int c = 0; c < cols; c++)
                        if (id[r][c] == i) board[r][c] = 'X';
            }
        }
        cout << "Case #" << tc << ":\n";
        for (const string& line : board) cout << line << '\n';
    }
    return 0;
}
