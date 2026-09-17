#include <bits/stdc++.h>
using namespace std;

struct Solver {
    int planeCount, rowCount, colCount, eventCount, visitTag;
    vector<int> cellKind, parkNum, parkPos, events, assignment, owner, visit, bfsQueue;
    vector<unsigned int> exitMask;
    unordered_set<string> failed;
    int getId(int row, int col) {
        return row * colCount + col;
    }

    vector<int> getCandidates() {
        vector<int> candidates;
        int head = 0, tail = 0, cellCount = rowCount * colCount;
        ++visitTag;
        for (int pos = 0; pos < cellCount; ++pos) {
            if (cellKind[pos] == 2) {
                visit[pos] = visitTag;
                bfsQueue[tail++] = pos;
            }
        }
        int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
        while (head < tail) {
            int pos = bfsQueue[head++], row = pos / colCount, col = pos % colCount;
            for (int dir = 0; dir < 4; ++dir) {
                int nextRow = row + dr[dir], nextCol = col + dc[dir];
                if (nextRow < 0 || nextRow >= rowCount || nextCol < 0 || nextCol >= colCount) continue;
                int nextPos = getId(nextRow, nextCol);
                if (visit[nextPos] == visitTag || cellKind[nextPos] == 1 || owner[nextPos] != -1) continue;
                visit[nextPos] = visitTag;
                bfsQueue[tail++] = nextPos;
                if (parkNum[nextPos] != -1) candidates.push_back(nextPos);
            }
        }
        return candidates;
    }

    bool canExit(int plane, unsigned int blockMask) {
        int head = 0, tail = 0, start = assignment[plane];
        ++visitTag;
        visit[start] = visitTag;
        bfsQueue[tail++] = start;
        int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
        while (head < tail) {
            int pos = bfsQueue[head++], row = pos / colCount, col = pos % colCount;
            if (cellKind[pos] == 2) return true;
            for (int dir = 0; dir < 4; ++dir) {
                int nextRow = row + dr[dir], nextCol = col + dc[dir];
                if (nextRow < 0 || nextRow >= rowCount || nextCol < 0 || nextCol >= colCount) continue;
                int nextPos = getId(nextRow, nextCol), nextOwner = owner[nextPos];
                if (visit[nextPos] == visitTag || cellKind[nextPos] == 1) continue;
                if (nextOwner != -1 && (blockMask & (1u << nextOwner))) continue;
                visit[nextPos] = visitTag;
                bfsQueue[tail++] = nextPos;
            }
        }
        return false;
    }

    int getLandingCount(int eventId) {
        int count = 0;
        while (eventId < eventCount && events[eventId] > 0) {
            ++count;
            ++eventId;
        }
        return count;
    }

    string getState(int eventId, unsigned int activeMask) {
        string state;
        state.push_back(static_cast<char>(eventId));
        for (int plane = 0; plane < planeCount; ++plane)
            if (activeMask & (1u << plane)) state.push_back(static_cast<char>(assignment[plane] + 1));
        return state;
    }

    bool dfs(int eventId, unsigned int activeMask) {
        if (eventId == eventCount) return true;
        string state = getState(eventId, activeMask);
        if (failed.count(state)) return false;
        int event = events[eventId], plane = abs(event) - 1;
        if (event > 0) {
            vector<int> candidates = getCandidates();
            int need = getLandingCount(eventId);
            if (static_cast<int>(candidates.size()) < need) {
                failed.insert(state);
                return false;
            }
            unsigned int planeBit = 1u << plane, nextMask = activeMask | planeBit;
            for (int pos : candidates) {
                assignment[plane] = pos;
                owner[pos] = plane;
                bool valid = true;
                for (int other = 0; other < planeCount; ++other) {
                    if (!(activeMask & (1u << other)) || !(exitMask[other] & planeBit)) continue;
                    unsigned int blockMask = nextMask & exitMask[other];
                    if (!canExit(other, blockMask)) {
                        valid = false;
                        break;
                    }
                }
                if (valid && dfs(eventId + 1, nextMask)) return true;
                owner[pos] = -1;
                assignment[plane] = -1;
            }
        } else {
            int pos = assignment[plane];
            owner[pos] = -1;
            if (dfs(eventId + 1, activeMask & ~(1u << plane))) return true;
            owner[pos] = plane;
        }
        failed.insert(state);
        return false;
    }

    bool solve() {
        eventCount = 2 * planeCount;
        int cellCount = rowCount * colCount;
        assignment.assign(planeCount, -1);
        owner.assign(cellCount, -1);
        visit.assign(cellCount, 0);
        bfsQueue.resize(cellCount);
        exitMask.assign(planeCount, 0);
        visitTag = 0;
        unsigned int activeMask = 0;
        for (int event : events) {
            int plane = abs(event) - 1;
            if (event > 0) {
                activeMask |= 1u << plane;
            } else {
                activeMask &= ~(1u << plane);
                exitMask[plane] = activeMask;
            }
        }
        failed.clear();
        failed.reserve(1 << 18);
        failed.max_load_factor(0.7);
        return dfs(0, 0);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 0, planeCount;
    while (cin >> planeCount && planeCount) {
        Solver solver;
        solver.planeCount = planeCount;
        cin >> solver.rowCount >> solver.colCount;
        int cellCount = solver.rowCount * solver.colCount;
        solver.cellKind.assign(cellCount, 0);
        solver.parkNum.assign(cellCount, -1);
        string cell;
        for (int row = 0; row < solver.rowCount; ++row) {
            for (int col = 0; col < solver.colCount; ++col) {
                cin >> cell;
                int pos = solver.getId(row, col);
                if (cell == "##") {
                    solver.cellKind[pos] = 1;
                } else if (cell == "==") {
                    solver.cellKind[pos] = 2;
                } else if (cell != "..") {
                    solver.parkNum[pos] = stoi(cell);
                    solver.parkPos.push_back(pos);
                }
            }
        }
        solver.events.resize(2 * planeCount);
        for (int &event : solver.events) cin >> event;
        bool possible = solver.solve();
        if (caseId) cout << '\n';
        cout << "Case " << ++caseId << ": " << (possible ? "Yes" : "No") << '\n';
        if (possible) {
            for (int plane = 0; plane < planeCount; ++plane) {
                if (plane) cout << ' ';
                cout << setw(2) << setfill('0') << solver.parkNum[solver.assignment[plane]];
            }
            cout << setfill(' ') << '\n';
        }
    }
    return 0;
}
