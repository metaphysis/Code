#include <bits/stdc++.h>
using namespace std;

struct Slot {
    int row, col, dir;
};

int n;
char board[10][10];
vector<Slot> slots;
vector<string> words;
vector<int> used;
vector<int> assignWord;
vector<int> answer;

bool inside(int row, int col) {
    return row >= 0 && row < 10 && col >= 0 && col < 10;
}

bool canPut(int slotId, int wordId) {
    Slot &slot = slots[slotId];
    string &word = words[wordId];
    int dr = slot.dir == 1 ? 1 : 0, dc = slot.dir == 0 ? 1 : 0;
    int endRow = slot.row + dr * ((int)word.size() - 1);
    int endCol = slot.col + dc * ((int)word.size() - 1);
    if (!inside(endRow, endCol)) return false;
    int preRow = slot.row - dr, preCol = slot.col - dc;
    if (inside(preRow, preCol) && board[preRow][preCol] != '.') return false;
    int nextRow = endRow + dr, nextCol = endCol + dc;
    if (inside(nextRow, nextCol) && board[nextRow][nextCol] != '.') return false;
    for (int i = 0; i < (int)word.size(); i++) {
        int row = slot.row + dr * i, col = slot.col + dc * i;
        if (board[row][col] != '.' && board[row][col] != word[i]) return false;
    }
    return true;
}

vector<pair<int, int>> putWord(int slotId, int wordId) {
    Slot &slot = slots[slotId];
    string &word = words[wordId];
    int dr = slot.dir == 1 ? 1 : 0, dc = slot.dir == 0 ? 1 : 0;
    vector<pair<int, int>> changed;
    for (int i = 0; i < (int)word.size(); i++) {
        int row = slot.row + dr * i, col = slot.col + dc * i;
        if (board[row][col] == '.') {
            board[row][col] = word[i];
            changed.push_back({row, col});
        }
    }
    return changed;
}

void undoWord(vector<pair<int, int>> &changed) {
    for (auto &cell : changed) board[cell.first][cell.second] = '.';
}

bool validBoard() {
    for (int i = 0; i < n; i++) {
        Slot &slot = slots[i];
        string &word = words[assignWord[i]];
        int dr = slot.dir == 1 ? 1 : 0, dc = slot.dir == 0 ? 1 : 0;
        int preRow = slot.row - dr, preCol = slot.col - dc;
        int endRow = slot.row + dr * ((int)word.size() - 1);
        int endCol = slot.col + dc * ((int)word.size() - 1);
        int nextRow = endRow + dr, nextCol = endCol + dc;
        if (inside(preRow, preCol) && board[preRow][preCol] != '.') return false;
        if (inside(nextRow, nextCol) && board[nextRow][nextCol] != '.') return false;
        for (int j = 0; j < (int)word.size(); j++) {
            int row = slot.row + dr * j, col = slot.col + dc * j;
            if (board[row][col] != word[j]) return false;
        }
    }
    return true;
}

void dfs(int depth) {
    if (depth == n) {
        if (!validBoard()) return;
        for (int i = 0; i < n + 1; i++)
            if (!used[i]) answer[i] = 1;
        return;
    }
    int slotId = -1, bestCount = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (assignWord[i] != -1) continue;
        int count = 0;
        for (int j = 0; j < n + 1; j++)
            if (!used[j] && canPut(i, j)) count++;
        if (count == 0) return;
        if (count < bestCount) {
            bestCount = count;
            slotId = i;
        }
    }
    for (int i = 0; i < n + 1; i++) {
        if (used[i] || !canPut(slotId, i)) continue;
        vector<pair<int, int>> changed = putWord(slotId, i);
        used[i] = 1;
        assignWord[slotId] = i;
        dfs(depth + 1);
        assignWord[slotId] = -1;
        used[i] = 0;
        undoWord(changed);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int trial = 1;
    while (cin >> n && n) {
        slots.clear();
        words.clear();
        memset(board, '.', sizeof(board));
        for (int i = 0; i < n; i++) {
            int row, col;
            char direction;
            cin >> row >> col >> direction;
            Slot slot;
            slot.row = row - 1;
            slot.col = col - 1;
            slot.dir = direction == 'A' ? 0 : 1;
            slots.push_back(slot);
        }
        for (int i = 0; i < n + 1; i++) {
            string word;
            cin >> word;
            words.push_back(word);
        }
        used.assign(n + 1, 0);
        assignWord.assign(n, -1);
        answer.assign(n + 1, 0);
        dfs(0);
        cout << "Trial " << trial << ":";
        bool possible = false;
        for (int i = 0; i < n + 1; i++) {
            if (!answer[i]) continue;
            cout << " " << words[i];
            possible = true;
        }
        if (!possible) cout << " Impossible";
        cout << "\n\n";
        trial++;
    }
    return 0;
}
