// The Wall Pushers
// UVa ID: 10384
// Verdict: Accepted
// Submission Date: 2025-11-14
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int ROWS = 4;
const int COLS = 6;

const int WEST = 0, NORTH = 1, EAST = 2, SOUTH = 3;
const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};
const char dirChar[] = {'W', 'N', 'E', 'S'};

const int WALL_MASK[] = {1, 2, 4, 8};

struct State {
    int x, y;
    string wallState;
    string path;
    State(int x, int y, const string ws, string p) : x(x), y(y), wallState(ws), path(p) {}
};

int oppositeDir(int dir) { return (dir + 2) % 4; }

bool isValid(int x, int y) { return x >= 0 && x < ROWS && y >= 0 && y < COLS; }

bool isBorder(int x, int y, int dir) {
    return (dir == WEST && y == 0) ||
           (dir == EAST && y == COLS - 1) ||
           (dir == NORTH && x == 0) ||
           (dir == SOUTH && x == ROWS - 1);
}

bool hasWall(const string wallState, int x, int y, int dir) {
    return wallState[x * COLS + y] & WALL_MASK[dir];
}
string getInitialWallState(vector<vector<int>>& maze) {
    string state;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
                state += (char)maze[i][j];
    return state;
}

void setWall(string& wallState, int x, int y, int dir, bool has) {
    if (has) wallState[x * COLS + y] |= WALL_MASK[dir];
    else wallState[x * COLS + y] &= ~WALL_MASK[dir];
}

bool isExit(int x, int y, int dir, const string& wallState) {
    return isBorder(x, y, dir) && !hasWall(wallState, x, y, dir);
}

string solveMaze(int startX, int startY, vector<vector<int>>& maze) {
    int startRow = startY - 1, startCol = startX - 1;
    string initialWallState = getInitialWallState(maze);
    for (int dir = 0; dir < 4; dir++)
        if (isExit(startRow, startCol, dir, initialWallState))
            return string(1, dirChar[dir]);
    queue<State> q;
    q.push(State(startRow, startCol, initialWallState, ""));
    map<pair<int, int>, set<string>> visited;
    while (!q.empty()) {
        State current = q.front();
        q.pop();
        int x = current.x, y = current.y;
        string wallState = current.wallState, path = current.path;
        if (visited[{x, y}].count(wallState)) continue;
        visited[{x, y}].insert(wallState);
        for (int dir = 0; dir < 4; dir++)
            if (isExit(x, y, dir, wallState))
                return path + dirChar[dir];
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir], ny = y + dy[dir];
            if (!hasWall(wallState, x, y, dir)) {
                if (isValid(nx, ny)) {
                    if (!visited[{nx, ny}].count(wallState)) {
                        string newPath = path + dirChar[dir];
                        q.push(State(nx, ny, wallState, newPath));
                    }
                } else return path + dirChar[dir];
            } else if (!isBorder(x, y, dir) && isValid(nx, ny)) {
                int beyondX = nx + dx[dir], beyondY = ny + dy[dir];
                if (!hasWall(wallState, nx, ny, dir)) {
                    string newWallState = wallState;
                    setWall(newWallState, x, y, dir, false);
                    setWall(newWallState, nx, ny, oppositeDir(dir), false);
                    setWall(newWallState, nx, ny, dir, true);
                    if (isValid(beyondX, beyondY))
                        setWall(newWallState, beyondX, beyondY, oppositeDir(dir), true);
                    if (!visited[{nx, ny}].count(newWallState)) {
                        string newPath = path + dirChar[dir];
                        q.push(State(nx, ny, newWallState, newPath));
                    }
                }
            }
        }
    }
    return "";
}

int main() {
    int startX, startY;
    while (cin >> startX >> startY) {
        if (startX == 0 && startY == 0) break;
        vector<vector<int>> maze(ROWS, vector<int>(COLS));
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                cin >> maze[i][j];
        string result = solveMaze(startX, startY, maze);
        cout << result << endl;
    }
    return 0;
}
