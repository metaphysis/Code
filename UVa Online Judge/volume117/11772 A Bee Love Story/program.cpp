#include <bits/stdc++.h>
using namespace std;

const int cellCount = 19;
const int maxMove = 20;
const size_t cacheLimit = 300000;
const int dirX[6] = {0, 1, 1, 0, -1, -1};
const int dirY[6] = {1, 0, -1, -1, 0, 1};

struct Point {
    int x, y;
};

Point localPos[cellCount];
vector<int> adj[cellCount];
int cellDist[cellCount][cellCount];

Point getCoord(int id) {
    if (id == 0) return {0, 0};
    int left = 1, right = 20000;
    while (left < right) {
        int mid = (left + right) / 2;
        if (3LL * mid * (mid + 1) >= id) right = mid;
        else left = mid + 1;
    }
    int radius = left, offset = id - (3LL * radius * (radius - 1) + 1);
    int x = 1 - radius, y = radius, step = min(offset, radius - 1);
    x += step;
    offset -= step;
    for (int dir = 2; dir <= 6; dir++) {
        step = min(offset, radius);
        x += dirX[dir % 6] * step;
        y += dirY[dir % 6] * step;
        offset -= step;
    }
    return {x, y};
}

void initBoard() {
    for (int i = 0; i < cellCount; i++) localPos[i] = getCoord(i);
    for (int i = 0; i < cellCount; i++) {
        for (int j = 0; j < cellCount; j++) {
            int dx = localPos[i].x - localPos[j].x;
            int dy = localPos[i].y - localPos[j].y;
            cellDist[i][j] = max(abs(dx), max(abs(dy), abs(dx + dy)));
            if (cellDist[i][j] == 1) adj[i].push_back(j);
        }
    }
}

struct PatternDb {
    int firstTile, tileCount, posCount, stateCount;
    vector<unsigned char> dist;

    int getRank(const int pos[]) const {
        unsigned int used = 0;
        int rank = 0;
        for (int i = 0; i < posCount; i++) {
            unsigned int lower = (1U << pos[i]) - 1;
            int digit = pos[i] - __builtin_popcount(used & lower);
            rank = rank * (cellCount - i) + digit;
            used |= 1U << pos[i];
        }
        return rank;
    }

    void getPositions(int rank, int pos[]) const {
        int digit[5];
        unsigned int available = (1U << cellCount) - 1;
        for (int i = posCount - 1; i >= 0; i--) {
            digit[i] = rank % (cellCount - i);
            rank /= cellCount - i;
        }
        for (int i = 0; i < posCount; i++) {
            unsigned int bits = available;
            for (int j = 0; j < digit[i]; j++) bits &= bits - 1;
            pos[i] = __builtin_ctz(bits);
            available &= ~(1U << pos[i]);
        }
    }

    void build(int startTile, int count) {
        firstTile = startTile;
        tileCount = count;
        posCount = tileCount + 1;
        stateCount = 1;
        for (int i = 0; i < posCount; i++) stateCount *= cellCount - i;
        dist.assign(stateCount, 255);
        int pos[5];
        pos[0] = 0;
        for (int i = 1; i < posCount; i++) pos[i] = firstTile + i - 1;
        int goalRank = getRank(pos);
        deque<int> que;
        dist[goalRank] = 0;
        que.push_back(goalRank);
        while (!que.empty()) {
            int rank = que.front();
            que.pop_front();
            getPositions(rank, pos);
            int blank = pos[0], curDist = dist[rank];
            for (int next : adj[blank]) {
                int hit = 0;
                for (int i = 1; i < posCount; i++) {
                    if (pos[i] == next) {
                        hit = i;
                        break;
                    }
                }
                pos[0] = next;
                if (hit != 0) pos[hit] = blank;
                int nextRank = getRank(pos), cost = hit != 0;
                if (curDist + cost < dist[nextRank]) {
                    dist[nextRank] = curDist + cost;
                    if (cost == 0) que.push_front(nextRank);
                    else que.push_back(nextRank);
                }
                pos[0] = blank;
                if (hit != 0) pos[hit] = next;
            }
        }
    }

    int getValue(const int tilePos[]) const {
        int pos[5];
        pos[0] = tilePos[0];
        for (int i = 1; i < posCount; i++) pos[i] = tilePos[firstTile + i - 1];
        return dist[getRank(pos)];
    }
};

struct StateKey {
    unsigned long long low, high;

    bool operator==(const StateKey &other) const {
        return low == other.low && high == other.high;
    }
};

struct StateHash {
    size_t operator()(const StateKey &key) const {
        unsigned long long value = key.low ^ (key.high + 0x9e3779b97f4a7c15ULL);
        value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
        value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
        return value ^ (value >> 31);
    }
};

PatternDb patternDb[5];
unordered_map<StateKey, unsigned char, StateHash> seen;
int board[cellCount], tilePos[cellCount], searchLimit;
unsigned long long stateLow, stateHigh;

int getHeuristic() {
    int result = 0;
    for (int i = 0; i < 5; i++) result += patternDb[i].getValue(tilePos);
    return result;
}

void toggleCell(int pos, int tile) {
    if (pos < 12) stateLow ^= (unsigned long long)tile << (pos * 5);
    else stateHigh ^= (unsigned long long)tile << ((pos - 12) * 5);
}

bool search(int depth, int blank, int previous, int distSum) {
    if (depth + distSum > searchLimit) return false;
    if (distSum == 0) return true;
    int heuristic = getHeuristic();
    if (depth + heuristic > searchLimit) return false;
    StateKey key = {stateLow, stateHigh};
    auto it = seen.find(key);
    if (it != seen.end()) {
        if (it->second <= depth) return false;
        it->second = depth;
    } else if (seen.size() < cacheLimit) {
        seen.emplace(key, (unsigned char)depth);
    }
    pair<int, int> moves[6];
    int moveCount = 0;
    for (int next : adj[blank]) {
        if (next == previous) continue;
        int tile = board[next];
        int nextSum = distSum - cellDist[next][tile] + cellDist[blank][tile];
        if (depth + 1 + nextSum <= searchLimit) moves[moveCount++] = {nextSum, next};
    }
    sort(moves, moves + moveCount);
    for (int i = 0; i < moveCount; i++) {
        int nextSum = moves[i].first, next = moves[i].second, tile = board[next];
        swap(board[blank], board[next]);
        tilePos[0] = next;
        tilePos[tile] = blank;
        toggleCell(blank, tile);
        toggleCell(next, tile);
        bool found = search(depth + 1, next, blank, nextSum);
        toggleCell(blank, tile);
        toggleCell(next, tile);
        tilePos[0] = blank;
        tilePos[tile] = next;
        swap(board[blank], board[next]);
        if (found) return true;
    }
    return false;
}

int solveCase(const vector<int> &input) {
    Point inputPos[cellCount];
    int sumX = 0, sumY = 0;
    for (int i = 0; i < cellCount; i++) {
        inputPos[i] = getCoord(input[i]);
        sumX += inputPos[i].x;
        sumY += inputPos[i].y;
    }
    int centerX = sumX / cellCount, centerY = sumY / cellCount;
    for (int tile = 0; tile < cellCount; tile++) {
        int x = inputPos[tile].x - centerX, y = inputPos[tile].y - centerY;
        for (int pos = 0; pos < cellCount; pos++) {
            if (localPos[pos].x == x && localPos[pos].y == y) {
                board[pos] = tile;
                tilePos[tile] = pos;
                break;
            }
        }
    }
    stateLow = 0;
    stateHigh = 0;
    int distSum = 0;
    for (int pos = 0; pos < cellCount; pos++) toggleCell(pos, board[pos]);
    for (int tile = 1; tile < cellCount; tile++) distSum += cellDist[tilePos[tile]][tile];
    if (distSum > maxMove) return -1;
    int lowerBound = max(distSum, getHeuristic());
    for (searchLimit = lowerBound; searchLimit <= maxMove; searchLimit++) {
        seen.clear();
        if (search(0, tilePos[0], -1, distSum)) return searchLimit;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    initBoard();
    for (int i = 0; i < 4; i++) patternDb[i].build(i * 4 + 1, 4);
    patternDb[4].build(17, 2);
    seen.max_load_factor(0.7f);
    seen.reserve(cacheLimit);
    for (int caseId = 1; caseId <= testCount; caseId++) {
        vector<int> input(cellCount);
        for (int i = 0; i < cellCount; i++) cin >> input[i];
        int answer = solveCase(input);
        cout << "Case " << caseId << ": ";
        if (answer == -1) cout << "Not possible with in 20 move(s).\n";
        else cout << "Possible with " << answer << " move(s).\n";
    }
    return 0;
}
