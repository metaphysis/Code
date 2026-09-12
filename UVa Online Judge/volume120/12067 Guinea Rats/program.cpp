#include <bits/stdc++.h>
using namespace std;

const int maxCell = 400;
const int dirCount = 4;
const int deltaRow[dirCount] = {-1, 0, 1, 0};
const int deltaCol[dirCount] = {0, 1, 0, -1};

struct Maze {
    int row, col, cellCount, start;
    int go[maxCell + 1][dirCount];
    bool cheese[maxCell + 1];
};

void readMaze(Maze &maze) {
    cin >> maze.row >> maze.col;
    maze.cellCount = maze.row * maze.col;
    for (int i = 0; i < maze.cellCount; i++) {
        int mask;
        cin >> mask;
        int currentRow = i / maze.col, currentCol = i % maze.col;
        for (int d = 0; d < dirCount; d++) {
            int nextRow = currentRow + deltaRow[d], nextCol = currentCol + deltaCol[d];
            if ((mask & (1 << d)) == 0 || nextRow < 0 || nextRow >= maze.row || nextCol < 0 || nextCol >= maze.col)
                maze.go[i][d] = maze.cellCount;
            else
                maze.go[i][d] = nextRow * maze.col + nextCol;
        }
        maze.cheese[i] = false;
    }
    maze.go[maze.cellCount][0] = maze.cellCount;
    maze.go[maze.cellCount][1] = maze.cellCount;
    maze.go[maze.cellCount][2] = maze.cellCount;
    maze.go[maze.cellCount][3] = maze.cellCount;
    maze.cheese[maze.cellCount] = false;
    cin >> maze.start;
    int cheeseCount;
    cin >> cheeseCount;
    for (int i = 0; i < cheeseCount; i++) {
        int cell;
        cin >> cell;
        maze.cheese[cell] = true;
    }
}

bool isSame(const Maze &firstMaze, const Maze &secondMaze) {
    static bool visited[maxCell + 1][maxCell + 1];
    memset(visited, false, sizeof(visited));
    queue<pair<int, int> > states;
    states.push(make_pair(firstMaze.start, secondMaze.start));
    visited[firstMaze.start][secondMaze.start] = true;
    while (!states.empty()) {
        int firstState = states.front().first, secondState = states.front().second;
        states.pop();
        if (firstMaze.cheese[firstState] != secondMaze.cheese[secondState])
            return false;
        for (int d = 0; d < dirCount; d++) {
            int nextFirst = firstMaze.go[firstState][d], nextSecond = secondMaze.go[secondState][d];
            if (!visited[nextFirst][nextSecond]) {
                visited[nextFirst][nextSecond] = true;
                states.push(make_pair(nextFirst, nextSecond));
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        Maze firstMaze, secondMaze;
        readMaze(firstMaze);
        readMaze(secondMaze);
        cout << "Case " << testCase << ": " << (isSame(firstMaze, secondMaze) ? "Yes" : "No") << '\n';
    }
    return 0;
}
