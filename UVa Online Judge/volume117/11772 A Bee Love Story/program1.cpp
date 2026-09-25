#include <bits/stdc++.h>
using namespace std;

const int cellCount = 19;
const int groupCount = 5;
const int maxMove = 20;
const int hashSize = 1 << 18;
const int hashMask = hashSize - 1;
const int dirX[6] = {0, 1, 1, 0, -1, -1};
const int dirY[6] = {1, 0, -1, -1, 0, 1};
const int pow19[5] = {1, 19, 361, 6859, 130321};

struct Point {
    int x, y;
};

struct HashEntry {
    unsigned long long low, high;
    unsigned int stamp;
    unsigned char depth;
};

struct Move {
    int next, distSum, heuristic;
    int code[groupCount];
};

Point localPos[cellCount];
int adj[cellCount][6], adjCount[cellCount];
int cellDist[cellCount][cellCount];
int tileGroup[cellCount], tileWeight[cellCount];
int board[cellCount], curCode[groupCount];
int searchLimit;
unsigned int searchStamp;
unsigned long long stateLow, stateHigh;
HashEntry hashTable[hashSize];

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
            if (cellDist[i][j] == 1) adj[i][adjCount[i]++] = j;
        }
    }
}

struct PatternDb {
    int firstTile, tileCount, stateCount;
    vector<unsigned char> dist;

    void build(int startTile, int count) {
        firstTile = startTile;
        tileCount = count;
        stateCount = pow19[tileCount] * cellCount;
        dist.assign(stateCount, 255);
        vector<unsigned char> settled(stateCount, 0);
        deque<int> que;
        int goalCode = 0;
        for (int i = 1; i <= tileCount; i++) goalCode += (firstTile + i - 1) * pow19[i];
        dist[goalCode] = 0;
        que.push_back(goalCode);
        while (!que.empty()) {
            int code = que.front();
            que.pop_front();
            if (settled[code]) continue;
            settled[code] = 1;
            int pos[5], value = code;
            for (int i = 0; i <= tileCount; i++) {
                pos[i] = value % cellCount;
                value /= cellCount;
            }
            int blank = pos[0], curDist = dist[code];
            for (int i = 0; i < adjCount[blank]; i++) {
                int next = adj[blank][i], hit = 0;
                for (int j = 1; j <= tileCount; j++) {
                    if (pos[j] == next) {
                        hit = j;
                        break;
                    }
                }
                int delta = next - blank, nextCode = code + delta;
                int cost = hit != 0;
                if (hit != 0) nextCode -= delta * pow19[hit];
                if (curDist + cost >= dist[nextCode]) continue;
                dist[nextCode] = curDist + cost;
                if (cost == 0) que.push_front(nextCode);
                else que.push_back(nextCode);
            }
        }
    }
};

PatternDb patternDb[groupCount];

void initPatterns() {
    for (int group = 0; group < groupCount; group++) {
        int first = group * 4 + 1, count = min(4, cellCount - first);
        patternDb[group].build(first, count);
        for (int i = 0; i < count; i++) {
            tileGroup[first + i] = group;
            tileWeight[first + i] = pow19[i + 1];
        }
    }
}

void toggleCell(int pos, int tile) {
    if (pos < 12) stateLow ^= (unsigned long long)tile << (pos * 5);
    else stateHigh ^= (unsigned long long)tile << ((pos - 12) * 5);
}

unsigned int getHash() {
    unsigned long long value = stateLow ^ (stateHigh + 0x9e3779b97f4a7c15ULL);
    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
    return (value ^ (value >> 31)) & hashMask;
}

bool pruneRepeat(int depth) {
    HashEntry &entry = hashTable[getHash()];
    if (entry.stamp == searchStamp && entry.low == stateLow && entry.high == stateHigh) {
        if (entry.depth <= depth) return true;
        entry.depth = depth;
        return false;
    }
    entry.low = stateLow;
    entry.high = stateHigh;
    entry.stamp = searchStamp;
    entry.depth = depth;
    return false;
}

bool lessMove(const Move &left, const Move &right) {
    if (left.heuristic != right.heuristic) return left.heuristic < right.heuristic;
    return left.distSum < right.distSum;
}

bool search(int depth, int blank, int previous, int distSum) {
    if (distSum == 0) return true;
    if (depth == searchLimit) return false;
    if (pruneRepeat(depth)) return false;
    Move moves[6];
    int moveCount = 0, remaining = searchLimit - depth - 1;
    for (int i = 0; i < adjCount[blank]; i++) {
        int next = adj[blank][i];
        if (next == previous) continue;
        int tile = board[next];
        int nextSum = distSum - cellDist[next][tile] + cellDist[blank][tile];
        if (nextSum > remaining) continue;
        Move &move = moves[moveCount];
        int delta = next - blank, group = tileGroup[tile], heuristic = 0;
        for (int j = 0; j < groupCount; j++) {
            move.code[j] = curCode[j] + delta;
            if (j == group) move.code[j] -= delta * tileWeight[tile];
            heuristic += patternDb[j].dist[move.code[j]];
        }
        if (heuristic > remaining) continue;
        move.next = next;
        move.distSum = nextSum;
        move.heuristic = heuristic;
        moveCount++;
    }
    sort(moves, moves + moveCount, lessMove);
    int oldCode[groupCount];
    for (int i = 0; i < groupCount; i++) oldCode[i] = curCode[i];
    for (int i = 0; i < moveCount; i++) {
        int next = moves[i].next, tile = board[next];
        swap(board[blank], board[next]);
        toggleCell(blank, tile);
        toggleCell(next, tile);
        for (int j = 0; j < groupCount; j++) curCode[j] = moves[i].code[j];
        bool found = search(depth + 1, next, blank, moves[i].distSum);
        for (int j = 0; j < groupCount; j++) curCode[j] = oldCode[j];
        toggleCell(blank, tile);
        toggleCell(next, tile);
        swap(board[blank], board[next]);
        if (found) return true;
    }
    return false;
}

int solveCase(const int input[]) {
    Point inputPos[cellCount];
    int tilePos[cellCount], sumX = 0, sumY = 0;
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
    int distSum = 0;
    for (int tile = 1; tile < cellCount; tile++) distSum += cellDist[tilePos[tile]][tile];
    if (distSum == 0) return 0;
    if (distSum > maxMove) return -1;
    int heuristic = 0;
    for (int group = 0; group < groupCount; group++) curCode[group] = tilePos[0];
    for (int tile = 1; tile < cellCount; tile++) curCode[tileGroup[tile]] += tilePos[tile] * tileWeight[tile];
    for (int group = 0; group < groupCount; group++) heuristic += patternDb[group].dist[curCode[group]];
    int lowerBound = max(distSum, heuristic);
    if (lowerBound > maxMove) return -1;
    stateLow = 0;
    stateHigh = 0;
    for (int pos = 0; pos < cellCount; pos++) toggleCell(pos, board[pos]);
    for (searchLimit = lowerBound; searchLimit <= maxMove; searchLimit++) {
        searchStamp++;
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
    initPatterns();
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int input[cellCount];
        for (int i = 0; i < cellCount; i++) cin >> input[i];
        int answer = solveCase(input);
        cout << "Case " << caseId << ": ";
        if (answer == -1) cout << "Not possible with in 20 move(s).\n";
        else cout << "Possible with " << answer << " move(s).\n";
    }
    return 0;
}
