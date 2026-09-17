#include <bits/stdc++.h>
using namespace std;

using Pos = pair<int, int>;

const int dirCount = 6;
const int dx[dirCount] = {0, 1, 1, 0, -1, -1};
const int dy[dirCount] = {1, 0, -1, -1, 0, 1};
map<Pos, string> board;

Pos getNextPos(const Pos &pos, int dir) {
    return {pos.first + dx[dir], pos.second + dy[dir]};
}

int getNeighborCount(const Pos &pos) {
    int count = 0;
    for (int dir = 0; dir < dirCount; dir++) {
        if (board.count(getNextPos(pos, dir))) count++;
    }
    return count;
}

bool isOnRay(const Pos &pos, const Pos &origin, int dir) {
    long long offsetX = pos.first - origin.first, offsetY = pos.second - origin.second;
    return offsetX * dy[dir] == offsetY * dx[dir] && offsetX * dx[dir] + offsetY * dy[dir] > 0;
}

set<Pos> getControlledSpaces(const set<Pos> &candidateSpaces, const set<Pos> &forcedSpaces) {
    set<Pos> controlledSpaces;
    for (const Pos &forcedPos : forcedSpaces) {
        for (int dir = 0; dir < dirCount; dir++) {
            if (!board.count(getNextPos(forcedPos, dir))) continue;
            int secondDir = (dir + 2) % dirCount, fourthDir = (dir + 4) % dirCount;
            if (!board.count(getNextPos(forcedPos, secondDir)) && !board.count(getNextPos(forcedPos, fourthDir))) continue;
            int rayDir = (dir + 3) % dirCount;
            for (const Pos &pos : candidateSpaces) {
                if (isOnRay(pos, forcedPos, rayDir)) controlledSpaces.insert(pos);
            }
        }
    }
    return controlledSpaces;
}

string rotateTile(const string &tile, int rotation) {
    string result(dirCount, ' ');
    for (int dir = 0; dir < dirCount; dir++) result[dir] = tile[(dir - rotation + dirCount) % dirCount];
    return result;
}

bool createsInvalidForcedSpace(const Pos &placedPos) {
    for (int dir = 0; dir < dirCount; dir++) {
        Pos emptyPos = getNextPos(placedPos, dir);
        if (board.count(emptyPos)) continue;
        int count = 0;
        char firstColor = 0;
        bool sameColor = true;
        for (int nextDir = 0; nextDir < dirCount; nextDir++) {
            auto it = board.find(getNextPos(emptyPos, nextDir));
            if (it == board.end()) continue;
            char currentColor = it->second[(nextDir + 3) % dirCount];
            if (count == 0) firstColor = currentColor;
            else if (currentColor != firstColor) sameColor = false;
            count++;
        }
        if (count == 3 && sameColor) return true;
    }
    return false;
}

bool canPlaceTile(const Pos &pos, const string &tile) {
    for (int dir = 0; dir < dirCount; dir++) {
        auto it = board.find(getNextPos(pos, dir));
        if (it != board.end() && tile[dir] != it->second[(dir + 3) % dirCount]) return false;
    }
    board[pos] = tile;
    bool valid = !createsInvalidForcedSpace(pos);
    board.erase(pos);
    return valid;
}

int solve() {
    int tileCount;
    cin >> tileCount;
    board.clear();
    for (int i = 0; i < tileCount; i++) {
        int x, y;
        string tile;
        cin >> x >> y >> tile;
        board[{x, y}] = tile;
    }
    vector<string> handTiles(5);
    for (string &tile : handTiles) cin >> tile;
    set<Pos> candidateSpaces, forcedSpaces, controlledSpaces;
    for (const auto &entry : board) {
        for (int dir = 0; dir < dirCount; dir++) {
            Pos nextPos = getNextPos(entry.first, dir);
            if (!board.count(nextPos)) candidateSpaces.insert(nextPos);
        }
    }
    for (const Pos &pos : candidateSpaces) {
        if (getNeighborCount(pos) == 3) forcedSpaces.insert(pos);
    }
    controlledSpaces = getControlledSpaces(candidateSpaces, forcedSpaces);
    int forcedMoves = 0, otherMoves = 0;
    for (const Pos &pos : candidateSpaces) {
        if (controlledSpaces.count(pos)) continue;
        bool forced = forcedSpaces.count(pos) > 0;
        for (const string &tile : handTiles) {
            for (int rotation = 0; rotation < dirCount; rotation++) {
                string rotatedTile = rotateTile(tile, rotation);
                if (!canPlaceTile(pos, rotatedTile)) continue;
                if (forced) forcedMoves++;
                else otherMoves++;
            }
        }
    }
    return forcedMoves > 0 ? forcedMoves : otherMoves;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) cout << solve() << '\n';
    return 0;
}
