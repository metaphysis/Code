#include <bits/stdc++.h>
using namespace std;

const int directionCount = 4;
const int deltaRow[directionCount] = {-1, 1, 0, 0};
const int deltaColumn[directionCount] = {0, 0, -1, 1};

int rowCount;
int columnCount;
int cellCount;
int rockCount;
int coinCount;
vector<string> maze;
vector<int> initialRockPositions;
vector<int> coinPositions;
vector<int> coinIndex;
vector<vector<int>> pushDestinations;
vector<int> stateBase;
vector<int> stateMultiplier;
unordered_map<long long, int> memo;

bool isInside(int row, int column) {
    return row >= 0 && row < rowCount && column >= 0 && column < columnCount;
}

int getPosition(int row, int column) {
    return row * columnCount + column;
}

int getRow(int position) {
    return position / columnCount;
}

int getColumn(int position) {
    return position % columnCount;
}

void decodeRockPositions(int stateCode, vector<int> &rockPositions) {
    rockPositions.assign(rockCount, 0);
    for (int i = 0; i < rockCount; ++i) {
        int option = stateCode / stateMultiplier[i] % stateBase[i];
        if (option == 0) rockPositions[i] = initialRockPositions[i];
        else rockPositions[i] = pushDestinations[i][option - 1];
    }
}

int searchState(int stateCode, int startPosition, int collectedMask) {
    vector<int> rockPositions;
    decodeRockPositions(stateCode, rockPositions);
    vector<bool> occupied(cellCount, false);
    for (int position : rockPositions) occupied[position] = true;
    vector<bool> reachable(cellCount, false);
    queue<int> positions;
    positions.push(startPosition);
    reachable[startPosition] = true;
    while (!positions.empty()) {
        int currentPosition = positions.front();
        positions.pop();
        int currentRow = getRow(currentPosition);
        int currentColumn = getColumn(currentPosition);
        for (int direction = 0; direction < directionCount; ++direction) {
            int nextRow = currentRow + deltaRow[direction];
            int nextColumn = currentColumn + deltaColumn[direction];
            if (!isInside(nextRow, nextColumn)) continue;
            int nextPosition = getPosition(nextRow, nextColumn);
            if (maze[nextRow][nextColumn] == 'X') continue;
            if (occupied[nextPosition]) continue;
            if (reachable[nextPosition]) continue;
            reachable[nextPosition] = true;
            positions.push(nextPosition);
        }
    }
    int newCollectedMask = collectedMask;
    for (int i = 0; i < coinCount; ++i)
        if (reachable[coinPositions[i]]) newCollectedMask |= 1 << i;
    int componentRepresentative = cellCount;
    for (int position = 0; position < cellCount; ++position)
        if (reachable[position]) componentRepresentative = min(componentRepresentative, position);
    long long stateKey = (static_cast<long long>(stateCode) * cellCount + componentRepresentative) * (1 << coinCount) + newCollectedMask;
    if (memo.find(stateKey) != memo.end()) return memo[stateKey];
    int answer = __builtin_popcount(static_cast<unsigned int>(newCollectedMask));
    for (int i = 0; i < rockCount; ++i) {
        int option = stateCode / stateMultiplier[i] % stateBase[i];
        if (option != 0) continue;
        int rockPosition = initialRockPositions[i];
        int rockRow = getRow(rockPosition);
        int rockColumn = getColumn(rockPosition);
        for (int destinationIndex = 0; destinationIndex < static_cast<int>(pushDestinations[i].size()); ++destinationIndex) {
            int destination = pushDestinations[i][destinationIndex];
            int destinationRow = getRow(destination);
            int destinationColumn = getColumn(destination);
            int behindRow = 2 * rockRow - destinationRow;
            int behindColumn = 2 * rockColumn - destinationColumn;
            if (!isInside(behindRow, behindColumn)) continue;
            int behindPosition = getPosition(behindRow, behindColumn);
            if (!reachable[behindPosition]) continue;
            if (maze[destinationRow][destinationColumn] == 'X') continue;
            if (coinIndex[destination] != -1 && (newCollectedMask & (1 << coinIndex[destination])) == 0) continue;
            bool hasOtherRock = false;
            for (int j = 0; j < rockCount; ++j)
                if (j != i && rockPositions[j] == destination) hasOtherRock = true;
            if (hasOtherRock) continue;
            int newStateCode = stateCode + stateMultiplier[i] * (destinationIndex + 1);
            answer = max(answer, searchState(newStateCode, rockPosition, newCollectedMask));
        }
    }
    memo[stateKey] = answer;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCaseCount;
    cin >> testCaseCount;
    while (testCaseCount--) {
        cin >> rowCount >> columnCount;
        maze.resize(rowCount);
        for (string &line : maze) cin >> line;
        cellCount = rowCount * columnCount;
        rockCount = 0;
        coinCount = 0;
        initialRockPositions.clear();
        coinPositions.clear();
        int startPosition = -1;
        for (int i = 0; i < rowCount; ++i) {
            for (int j = 0; j < columnCount; ++j) {
                int position = getPosition(i, j);
                if (maze[i][j] == 'S') startPosition = position;
                else if (maze[i][j] == 'O') initialRockPositions.push_back(position);
                else if (maze[i][j] == 'C') coinPositions.push_back(position);
            }
        }
        rockCount = static_cast<int>(initialRockPositions.size());
        coinCount = static_cast<int>(coinPositions.size());
        coinIndex.assign(cellCount, -1);
        for (int i = 0; i < coinCount; ++i) coinIndex[coinPositions[i]] = i;
        pushDestinations.assign(rockCount, vector<int>());
        stateBase.assign(rockCount, 1);
        stateMultiplier.assign(rockCount, 1);
        for (int i = 0; i < rockCount; ++i) {
            int rockRow = getRow(initialRockPositions[i]);
            int rockColumn = getColumn(initialRockPositions[i]);
            for (int direction = 0; direction < directionCount; ++direction) {
                int destinationRow = rockRow + deltaRow[direction];
                int destinationColumn = rockColumn + deltaColumn[direction];
                if (!isInside(destinationRow, destinationColumn)) continue;
                if (maze[destinationRow][destinationColumn] == 'X') continue;
                pushDestinations[i].push_back(getPosition(destinationRow, destinationColumn));
            }
            stateBase[i] = static_cast<int>(pushDestinations[i].size()) + 1;
            if (i > 0) stateMultiplier[i] = stateMultiplier[i - 1] * stateBase[i - 1];
        }
        memo.clear();
        cout << searchState(0, startPosition, 0) << '\n';
    }
    return 0;
}
