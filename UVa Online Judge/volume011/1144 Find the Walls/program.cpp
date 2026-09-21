#include <bits/stdc++.h>
using namespace std;

int n;

struct StateKey {
    array<unsigned char, 16> data{};
    bool operator==(const StateKey& other) const {
        for (int i = 0; i < n; i++)
            if (data[i] != other.data[i]) return false;
        return true;
    }
};

struct StateHash {
    size_t operator()(const StateKey& key) const {
        size_t result = 0;
        for (int i = 0; i < n; i++)
            result = result * 257 + key.data[i];
        return result;
    }
};

vector<vector<int>> cell;
vector<vector<int>> answerH, answerV;
vector<unordered_set<StateKey, StateHash>> failedStates;

StateKey makeKey(const vector<int>& expect, const vector<int>& used) {
    StateKey key;
    for (int col = 0; col < n; col++)
        key.data[col] = static_cast<unsigned char>(expect[col] * 17 + used[col]);
    return key;
}

bool searchRow(int row, int pos, const vector<int>& expect, const vector<int>& used, vector<int>& rowH, vector<int>& rowV);

bool search(int row, const vector<int>& expect, const vector<int>& used) {
    if (row == n) {
        for (int col = 0; col < n; col++)
            if (used[col] != 0) return false;
        return true;
    }
    StateKey key = makeKey(expect, used);
    if (failedStates[row].count(key)) return false;
    vector<int> rowH(n), rowV(n);
    if (searchRow(row, 0, expect, used, rowH, rowV)) return true;
    failedStates[row].insert(key);
    return false;
}

bool searchRow(int row, int pos, const vector<int>& expect, const vector<int>& used, vector<int>& rowH, vector<int>& rowV) {
    if (pos == n) {
        vector<int> nextExpect = expect, nextUsed = used;
        for (int col = 0; col < n; col++) {
            if (nextUsed[col] == 0) {
                nextExpect[col] = rowV[col];
                nextUsed[col] = 1;
            } else {
                if (rowV[col] != nextExpect[col]) return false;
                nextUsed[col]++;
            }
            if (nextUsed[col] == nextExpect[col]) {
                nextExpect[col] = 0;
                nextUsed[col] = 0;
            }
        }
        for (int col = 0; col < n; col++)
            if (nextUsed[col] != 0 && nextExpect[col] - nextUsed[col] > n - row - 1) return false;
        answerH[row] = rowH;
        answerV[row] = rowV;
        return search(row + 1, nextExpect, nextUsed);
    }
    for (int len = 1; pos + len <= n; len++) {
        bool ok = true;
        for (int col = pos; col < pos + len; col++) {
            int verticalLen = cell[row][col] + 2 - len;
            if (verticalLen < 1 || verticalLen > n) {
                ok = false;
                break;
            }
            if (used[col] != 0 && verticalLen != expect[col]) {
                ok = false;
                break;
            }
        }
        if (!ok) continue;
        for (int col = pos; col < pos + len; col++) {
            rowH[col] = len;
            rowV[col] = cell[row][col] + 2 - len;
        }
        if (searchRow(row, pos + len, expect, used, rowH, rowV)) return true;
    }
    return false;
}

void printMaze() {
    vector<string> maze(2 * n + 1, string(2 * n + 1, ' '));
    for (int row = 0; row <= 2 * n; row += 2)
        for (int col = 0; col <= 2 * n; col += 2)
            maze[row][col] = '+';
    for (int col = 1; col < 2 * n; col += 2) {
        maze[0][col] = '-';
        maze[2 * n][col] = '-';
    }
    for (int row = 1; row < 2 * n; row += 2) {
        maze[row][0] = '|';
        maze[row][2 * n] = '|';
    }
    for (int col = 0; col < n; col++) {
        int remain = 0;
        for (int row = 0; row < n - 1; row++) {
            if (remain == 0) remain = answerV[row][col];
            remain--;
            if (remain == 0) maze[2 * (row + 1)][2 * col + 1] = '-';
        }
    }
    for (int row = 0; row < n; row++) {
        int remain = 0;
        for (int col = 0; col < n - 1; col++) {
            if (remain == 0) remain = answerH[row][col];
            remain--;
            if (remain == 0) maze[2 * row + 1][2 * (col + 1)] = '|';
        }
    }
    for (const string& line : maze)
        cout << line << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool firstCase = true;
    while (cin >> n) {
        cell.assign(n, vector<int>(n));
        for (int row = 0; row < n; row++)
            for (int col = 0; col < n; col++)
                cin >> cell[row][col];
        answerH.assign(n, vector<int>(n));
        answerV.assign(n, vector<int>(n));
        failedStates.assign(n, unordered_set<StateKey, StateHash>());
        vector<int> expect(n, 0), used(n, 0);
        search(0, expect, used);
        if (!firstCase) cout << '\n';
        firstCase = false;
        printMaze();
    }
    return 0;
}
