// Sokoban 
// UVa ID: 10770
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.020s

#include <bits/stdc++.h>
using namespace std;

struct State {
    vector<int> boxes;
    int man;
    int step;
};

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool isGoal(const vector<int> &boxes, const vector<string> &board, int width) {
    for (int pos : boxes) {
        int row = pos / width, col = pos % width;
        if (board[row][col] != '.' && board[row][col] != '*' && board[row][col] != '+')
            return false;
    }
    return true;
}

bool inside(int row, int col, int height, int width) {
    return row >= 0 && row < height && col >= 0 && col < width;
}

int normalize(const vector<int> &boxes, int man, const vector<string> &board, int height, int width) {
    vector<char> hasBox(height * width, 0), visited(height * width, 0);
    queue<int> que;
    int result = man;
    for (int pos : boxes) hasBox[pos] = 1;
    que.push(man);
    visited[man] = 1;
    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        result = min(result, cur);
        int row = cur / width, col = cur % width;
        for (int dir = 0; dir < 4; dir++) {
            int nextRow = row + dr[dir], nextCol = col + dc[dir];
            if (!inside(nextRow, nextCol, height, width))
                continue;
            int next = nextRow * width + nextCol;
            if (visited[next] || hasBox[next] || board[nextRow][nextCol] == '#')
                continue;
            visited[next] = 1;
            que.push(next);
        }
    }
    return result;
}

string getKey(const vector<int> &boxes, int man) {
    string key;
    for (int pos : boxes) {
        key.push_back(static_cast<char>(pos & 255));
        key.push_back(static_cast<char>((pos >> 8) & 255));
    }
    key.push_back(static_cast<char>(man & 255));
    key.push_back(static_cast<char>((man >> 8) & 255));
    return key;
}

bool solveCase(int limit, const vector<string> &rows) {
    int height = rows.size(), width = 0;
    for (const string &row : rows) width = max(width, static_cast<int>(row.size()));
    vector<string> board(height, string(width, '#'));
    vector<int> boxes;
    int man = -1;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < static_cast<int>(rows[row].size()); col++) {
            char cell = rows[row][col];
            board[row][col] = cell;
            if (cell == '$' || cell == '*')
                boxes.push_back(row * width + col);
            if (cell == '@' || cell == '+')
                man = row * width + col;
        }
    }
    sort(boxes.begin(), boxes.end());
    man = normalize(boxes, man, board, height, width);
    queue<State> que;
    unordered_set<string> visited;
    que.push({boxes, man, 0});
    visited.insert(getKey(boxes, man));
    while (!que.empty()) {
        State cur = que.front();
        que.pop();
        if (isGoal(cur.boxes, board, width))
            return true;
        if (cur.step == limit)
            continue;
        vector<char> reachable(height * width, 0);
        queue<int> area;
        area.push(cur.man);
        reachable[cur.man] = 1;
        vector<char> hasBox(height * width, 0);
        for (int pos : cur.boxes) hasBox[pos] = 1;
        while (!area.empty()) {
            int now = area.front();
            area.pop();
            int row = now / width, col = now % width;
            for (int dir = 0; dir < 4; dir++) {
                int nextRow = row + dr[dir], nextCol = col + dc[dir];
                if (!inside(nextRow, nextCol, height, width))
                    continue;
                int next = nextRow * width + nextCol;
                if (reachable[next] || hasBox[next] || board[nextRow][nextCol] == '#')
                    continue;
                reachable[next] = 1;
                area.push(next);
            }
        }
        for (int index = 0; index < static_cast<int>(cur.boxes.size()); index++) {
            int box = cur.boxes[index];
            int row = box / width, col = box % width;
            for (int dir = 0; dir < 4; dir++) {
                int standRow = row - dr[dir], standCol = col - dc[dir];
                int destRow = row + dr[dir], destCol = col + dc[dir];
                if (!inside(standRow, standCol, height, width) || !inside(destRow, destCol, height, width))
                    continue;
                int stand = standRow * width + standCol;
                int dest = destRow * width + destCol;
                if (!reachable[stand] || hasBox[dest] || board[destRow][destCol] == '#')
                    continue;
                vector<int> nextBoxes = cur.boxes;
                nextBoxes[index] = dest;
                sort(nextBoxes.begin(), nextBoxes.end());
                int nextMan = normalize(nextBoxes, box, board, height, width);
                string key = getKey(nextBoxes, nextMan);
                if (visited.insert(key).second)
                    que.push({nextBoxes, nextMan, cur.step + 1});
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (line.empty())
            continue;
        stringstream input(line);
        int limit;
        if (!(input >> limit))
            continue;
        vector<string> rows;
        while (getline(cin, line) && !line.empty()) {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();
            rows.push_back(line);
        }
        if (!rows.empty())
            cout << (solveCase(limit, rows) ? "YES" : "NO") << '\n';
    }
    return 0;
}
