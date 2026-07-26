// A Vexing Problem
// UVa ID: 1008
// Verdict: Accepted
// Submission Date: 2026-07-24
// UVa Run Time: 17.490s
// https://blog.csdn.net/metaphysis/article/details/163174146

#include <bits/stdc++.h>
using namespace std;

struct MoveInfo {
    char mark;
    int row;
    int column;
    char direction;
};

struct SearchNode {
    string state;
    int parentIndex;
    MoveInfo move;
};

bool isMovable(char value) {
    return value >= 'A' && value <= 'Z';
}

vector<string> decodeBoard(const string& state, int rowCount, int columnCount) {
    vector<string> board(rowCount, string(columnCount, '-'));
    for (int row = 0; row < rowCount; ++row)
        for (int column = 0; column < columnCount; ++column)
            board[row][column] = state[row * columnCount + column];
    return board;
}

string encodeBoard(const vector<string>& board, int rowCount, int columnCount) {
    string state;
    state.reserve(rowCount * columnCount);
    for (int row = 0; row < rowCount; ++row)
        state += board[row];
    return state;
}

void applyGravity(vector<string>& board, int rowCount, int columnCount) {
    for (int column = 0; column < columnCount; ++column) {
        int writeRow = rowCount - 1;
        for (int row = rowCount - 1; row >= 0; --row) {
            if (board[row][column] == '#') {
                writeRow = row - 1;
                continue;
            }
            if (isMovable(board[row][column])) {
                char mark = board[row][column];
                board[row][column] = '-';
                board[writeRow][column] = mark;
                --writeRow;
            }
        }
    }
}

bool removeGroups(vector<string>& board, int rowCount, int columnCount) {
    vector<vector<bool>> visited(rowCount, vector<bool>(columnCount, false));
    vector<vector<bool>> shouldRemove(rowCount, vector<bool>(columnCount, false));
    const int rowOffset[4] = {-1, 1, 0, 0};
    const int columnOffset[4] = {0, 0, -1, 1};
    bool removed = false;
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {
            if (!isMovable(board[row][column]) || visited[row][column])
                continue;
            char mark = board[row][column];
            queue<pair<int, int>> pending;
            vector<pair<int, int>> group;
            pending.push({row, column});
            visited[row][column] = true;
            while (!pending.empty()) {
                int currentRow = pending.front().first;
                int currentColumn = pending.front().second;
                pending.pop();
                group.push_back({currentRow, currentColumn});
                for (int direction = 0; direction < 4; ++direction) {
                    int nextRow = currentRow + rowOffset[direction];
                    int nextColumn = currentColumn + columnOffset[direction];
                    if (nextRow < 0 || nextRow >= rowCount || nextColumn < 0 || nextColumn >= columnCount)
                        continue;
                    if (visited[nextRow][nextColumn] || board[nextRow][nextColumn] != mark)
                        continue;
                    visited[nextRow][nextColumn] = true;
                    pending.push({nextRow, nextColumn});
                }
            }
            if (group.size() >= 2) {
                removed = true;
                for (const auto& position : group)
                    shouldRemove[position.first][position.second] = true;
            }
        }
    }
    if (!removed)
        return false;
    for (int row = 0; row < rowCount; ++row)
        for (int column = 0; column < columnCount; ++column)
            if (shouldRemove[row][column])
                board[row][column] = '-';
    return true;
}

void stabilizeBoard(vector<string>& board, int rowCount, int columnCount) {
    while (true) {
        applyGravity(board, rowCount, columnCount);
        if (!removeGroups(board, rowCount, columnCount))
            break;
    }
}

bool isGoal(const vector<string>& board, int rowCount, int columnCount) {
    for (int row = 0; row < rowCount; ++row)
        for (int column = 0; column < columnCount; ++column)
            if (isMovable(board[row][column]))
                return false;
    return true;
}

vector<MoveInfo> findMinimumSolution(const vector<string>& initialBoard, int rowCount, int columnCount) {
    vector<SearchNode> nodes;
    unordered_map<string, int> stateIndex;
    queue<int> pending;
    string initialState = encodeBoard(initialBoard, rowCount, columnCount);
    SearchNode initialNode;
    initialNode.state = initialState;
    initialNode.parentIndex = -1;
    nodes.push_back(initialNode);
    stateIndex[initialState] = 0;
    pending.push(0);
    int goalIndex = -1;
    while (!pending.empty()) {
        int currentIndex = pending.front();
        pending.pop();
        vector<string> currentBoard = decodeBoard(nodes[currentIndex].state, rowCount, columnCount);
        if (isGoal(currentBoard, rowCount, columnCount)) {
            goalIndex = currentIndex;
            break;
        }
        for (int row = 0; row < rowCount; ++row) {
            for (int column = 0; column < columnCount; ++column) {
                if (!isMovable(currentBoard[row][column]))
                    continue;
                for (int direction = -1; direction <= 1; direction += 2) {
                    int nextColumn = column + direction;
                    if (nextColumn < 0 || nextColumn >= columnCount)
                        continue;
                    if (currentBoard[row][nextColumn] != '-')
                        continue;
                    vector<string> nextBoard = currentBoard;
                    char mark = nextBoard[row][column];
                    nextBoard[row][column] = '-';
                    nextBoard[row][nextColumn] = mark;
                    stabilizeBoard(nextBoard, rowCount, columnCount);
                    string nextState = encodeBoard(nextBoard, rowCount, columnCount);
                    if (stateIndex.find(nextState) != stateIndex.end())
                        continue;
                    MoveInfo move;
                    move.mark = mark;
                    move.row = row;
                    move.column = column;
                    move.direction = direction == -1 ? 'L' : 'R';
                    SearchNode nextNode;
                    nextNode.state = nextState;
                    nextNode.parentIndex = currentIndex;
                    nextNode.move = move;
                    int nextIndex = static_cast<int>(nodes.size());
                    nodes.push_back(nextNode);
                    stateIndex[nextState] = nextIndex;
                    pending.push(nextIndex);
                }
            }
        }
    }
    vector<MoveInfo> solution;
    if (goalIndex == -1)
        return solution;
    int currentIndex = goalIndex;
    while (nodes[currentIndex].parentIndex != -1) {
        solution.push_back(nodes[currentIndex].move);
        currentIndex = nodes[currentIndex].parentIndex;
    }
    reverse(solution.begin(), solution.end());
    return solution;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowCount;
    int columnCount;
    string puzzleName;
    while (cin >> rowCount >> columnCount) {
        if (rowCount == 0 && columnCount == 0)
            break;
        cin >> puzzleName;
        vector<string> board(rowCount);
        for (int row = 0; row < rowCount; ++row)
            cin >> board[row];
        vector<MoveInfo> solution = findMinimumSolution(board, rowCount, columnCount);
        cout << puzzleName << ": Minimum solution length = " << solution.size() << '\n';
        for (int index = 0; index < static_cast<int>(solution.size()); ++index) {
            if (index > 0)
                cout << ' ';
            const MoveInfo& move = solution[index];
            cout << '(' << move.mark << ',' << move.row << ',' << move.column << ',' << move.direction << ')';
        }
        cout << '\n';
    }
    return 0;
}
