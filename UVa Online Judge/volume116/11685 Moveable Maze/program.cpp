#include <bits/stdc++.h>
using namespace std;

struct State {
    int time, pos, rot, count;
    bool operator<(const State &other) const {
        return time > other.time;
    }
};

int getRotDist(int from, int to) {
    int diff = abs(from - to);
    return min(diff, 4 - diff);
}

int rotateMask(int mask, int rot) {
    int result = 0;
    for (int dir = 0; dir < 4; ++dir)
        if (mask & (1 << dir)) result |= 1 << ((dir + rot) % 4);
    return result;
}

int getMask(const string &s) {
    if (s == "x") return 0;
    int mask = 0;
    for (char ch : s) {
        if (ch == 'N') mask |= 1 << 0;
        else if (ch == 'E') mask |= 1 << 1;
        else if (ch == 'S') mask |= 1 << 2;
        else if (ch == 'W') mask |= 1 << 3;
    }
    return mask;
}

int solveCase(int rowCount, int colCount, int startRow, int startCol, int endRow, int endCol, const vector<int> &masks) {
    int start = startRow * colCount + startCol, target = endRow * colCount + endCol;
    if (start == target) return 0;
    int nodeCount = rowCount * colCount, maxCount = 4 * nodeCount + 2;
    int stateCount = nodeCount * 4, inf = INT_MAX / 4;
    vector<vector<int>> dist(stateCount, vector<int>(maxCount + 1, inf));
    priority_queue<State> pq;
    for (int rot = 0; rot < 4; ++rot) {
        int count = getRotDist(0, rot), stateId = start * 4 + rot;
        if (dist[stateId][count] > 0) {
            dist[stateId][count] = 0;
            pq.push({0, start, rot, count});
        }
    }
    int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        int stateId = cur.pos * 4 + cur.rot;
        if (dist[stateId][cur.count] != cur.time) continue;
        if (cur.pos == target) return cur.time;
        int row = cur.pos / colCount, col = cur.pos % colCount;
        for (int dir = 0; dir < 4; ++dir) {
            int nextRow = row + dr[dir], nextCol = col + dc[dir];
            if (nextRow < 0 || nextRow >= rowCount || nextCol < 0 || nextCol >= colCount) continue;
            int nextPos = nextRow * colCount + nextCol, opposite = (dir + 2) % 4;
            for (int outRot = 0; outRot < 4; ++outRot) {
                if (!(rotateMask(masks[cur.pos], outRot) & (1 << dir))) continue;
                int curCost = getRotDist(cur.rot, outRot);
                for (int nextRot = 0; nextRot < 4; ++nextRot) {
                    if (!(rotateMask(masks[nextPos], nextRot) & (1 << opposite))) continue;
                    int nextCost = getRotDist(0, nextRot);
                    int nextCount = cur.count + curCost + nextCost;
                    if (nextCount > maxCount) continue;
                    int nextTime = max(max(cur.time + 1, cur.time + curCost), nextCount);
                    int nextStateId = nextPos * 4 + nextRot;
                    if (nextTime >= dist[nextStateId][nextCount]) continue;
                    dist[nextStateId][nextCount] = nextTime;
                    pq.push({nextTime, nextPos, nextRot, nextCount});
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowCount, colCount;
    while (cin >> rowCount >> colCount) {
        if (rowCount == 0 && colCount == 0) break;
        int startRow, startCol, endRow, endCol;
        cin >> startRow >> startCol >> endRow >> endCol;
        --startRow;
        --startCol;
        --endRow;
        --endCol;
        vector<int> masks(rowCount * colCount);
        string s;
        for (int row = 0; row < rowCount; ++row) {
            for (int col = 0; col < colCount; ++col) {
                cin >> s;
                masks[row * colCount + col] = getMask(s);
            }
        }
        cout << solveCase(rowCount, colCount, startRow, startCol, endRow, endCol, masks) << '\n';
    }
    return 0;
}
