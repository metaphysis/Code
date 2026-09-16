#include <bits/stdc++.h>
using namespace std;

const int MAX_STATE = 117649, MAX_N = 6, MAX_MOVE = 12;

const int powerOfSeven[MAX_N] = {
    1, 7, 49, 343, 2401, 16807
};

struct Board {
    char cell[MAX_N][MAX_N];
    char hand;
};

short answer[MAX_N * MAX_N + 1], distanceTable[MAX_STATE], columnHeight[MAX_N];

Board stateStack[MAX_N * MAX_N + 1];

int n, b;
int targetColumn[MAX_MOVE];
bool rowTarget[MAX_MOVE];

short maxDepth;
int caseNumber = 0;

char playerName[105];

void buildDistanceTable() {
    int stateLimit = 0;
    for (short i = 0; i < n; ++i)
        stateLimit += n * powerOfSeven[i];
    for (int state = 0; state < stateLimit; ++state) {
        int value = state;
        short blockCount = 0;
        bool invalid = false;
        for (short column = 0; column < n; ++column) {
            columnHeight[column] = value % 7;
            value /= 7;
            if (columnHeight[column] > n) {
                invalid = true;
                break;
            }
            blockCount += columnHeight[column];
        }
        if (invalid)
            continue;
        if (blockCount <= b) {
            distanceTable[state] = 0;
            continue;
        }
        distanceTable[state] = n * n;
        for (short move = 0; move < MAX_MOVE; ++move) {
            if (targetColumn[move] < 0)
                continue;
            short index = targetColumn[move];
            if (rowTarget[move]) {
                int nextState = state;
                nextState -= min<int>(columnHeight[0], index + 1);
                for (short column = 1; column < n; ++column) {
                    if (columnHeight[column] > index)
                        nextState -= powerOfSeven[column];
                }
                distanceTable[state] = min(
                    distanceTable[state],
                    short(distanceTable[nextState] + 1)
                );
            } else {
                if (columnHeight[index] == 0)
                    continue;
                int nextState = state - columnHeight[index] * powerOfSeven[index];
                distanceTable[state] = min(
                    distanceTable[state],
                    short(distanceTable[nextState] + 1)
                );
            }
        }
    }
}

short heuristic(const Board &board) {
    int state = 0;
    for (short column = 0; column < n; ++column) {
        short height = 0;
        while (height < n && board.cell[height][column])
            ++height;
        state += height * powerOfSeven[column];
    }
    return distanceTable[state];
}

bool fireRow(const Board &current, Board &next, short row) {
    next = current;
    char &hand = next.hand;
    short removed = 0;
    short column;
    for (column = n - 1; column >= 0; --column) {
        if (!current.cell[row][column])
            continue;
        if (hand == 'M' || current.cell[row][column] == hand) {
            hand = current.cell[row][column];
            next.cell[n - 1][column] = 0;
            for (short k = row + 1; k < n; ++k)
                next.cell[k - 1][column] = current.cell[k][column];
            ++removed;
        } else {
            next.cell[row][column] = hand;
            hand = current.cell[row][column];
            break;
        }
    }
    if (column < 0) {
        for (column = row - 1; column >= 0; --column) {
            if (!current.cell[column][0])
                continue;
            if (hand == 'M' || current.cell[column][0] == hand) {
                hand = current.cell[column][0];
                ++removed;
                for (short k = column + 1; k < n; ++k)
                    next.cell[k - 1][0] = next.cell[k][0];
                next.cell[n - 1][0] = 0;
            } else {
                next.cell[column][0] = hand;
                hand = current.cell[column][0];
                break;
            }
        }
    }
    return removed > 0;
}

bool fireColumn(const Board &current, Board &next, short column) {
    next = current;
    char &hand = next.hand;
    short removed = 0;
    for (short row = n - 1; row >= 0; --row) {
        if (!current.cell[row][column])
            continue;
        if (hand == 'M' || current.cell[row][column] == hand) {
            hand = current.cell[row][column];
            next.cell[row][column] = 0;
            ++removed;
        } else {
            next.cell[row][column] = hand;
            hand = current.cell[row][column];
            break;
        }
    }
    return removed > 0;
}

bool idaStar(short depth) {
    if (depth == maxDepth)
        return heuristic(stateStack[depth]) == 0;
    Board &next = stateStack[depth + 1];
    for (short move = 0; move < MAX_MOVE; ++move) {
        if (targetColumn[move] < 0)
            continue;
        bool valid;
        if (rowTarget[move]) {
            valid = fireRow(
                stateStack[depth],
                next,
                targetColumn[move]
            );
        } else {
            valid = fireColumn(
                stateStack[depth],
                next,
                targetColumn[move]
            );
        }
        if (!valid)
            continue;
        if (depth + heuristic(next) >= maxDepth)
            continue;
        answer[depth + 1] = move;
        if (idaStar(depth + 1))
            return true;
    }
    return false;
}

void printAnswer() {
    cout << "Case " << ++caseNumber << ": " << playerName << '\n';
    cout << maxDepth << '\n';
    for (short i = 1; i <= maxDepth; ++i) {
        if (i > 1)
            cout << ' ';
        cout << answer[i] + 1;
    }
    cout << "\n\n";
}

void solveCase() {
    cin >> b >> stateStack[0].hand >> playerName;
    memset(stateStack[0].cell, 0, sizeof(stateStack[0].cell));
    for (short row = n - 1; row >= 0; --row) {
        for (short column = 0; column < n; ++column)
            cin >> stateStack[0].cell[row][column];
    }
    for (short move = 0; move < MAX_MOVE; ++move) {
        char type;
        cin >> type;
        if (type == 'X') {
            targetColumn[move] = -1;
            rowTarget[move] = false;
        } else {
            rowTarget[move] = type == 'r';
            cin >> targetColumn[move];
            --targetColumn[move];
        }
    }
    buildDistanceTable();
    for (maxDepth = 1; maxDepth < n * n; ++maxDepth) {
        if (idaStar(0)) {
            printAnswer();
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n && n != 0)
        solveCase();
    return 0;
}
