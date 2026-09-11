// A Safe Bet
// UVa ID: 1287
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 1.160s

#include <bits/stdc++.h>
using namespace std;

struct Mirror {
    int coordinate;
    int type;
};

struct Segment {
    int direction;
    int fixed;
    int left;
    int right;
};

struct Event {
    int row;
    int left;
    int right;
    int type;
    int delta;
    int phase;
};

class SegmentTree {
private:
    int size;
    int leafCount;
    vector<int> coordinates;
    vector<array<int, 16>> values;
    vector<array<int, 4>> coverCount;

    bool isValid(int mask) {
        return ((mask & 1) && (mask & 8)) || ((mask & 4) && (mask & 2));
    }

    void pull(int node, int left, int right) {
        int coverMask = 0;
        for (int type = 0; type < 4; type++)
            if (coverCount[node][type] > 0)
                coverMask |= 1 << type;
        if (left + 1 == right) {
            int length = coordinates[left + 1] - coordinates[left];
            for (int mask = 0; mask < 16; mask++)
                values[node][mask] = isValid(mask | coverMask) ? length : 0;
            return;
        }
        int middle = (left + right) / 2;
        for (int mask = 0; mask < 16; mask++) {
            int nextMask = mask | coverMask;
            values[node][mask] = values[node * 2][nextMask] + values[node * 2 + 1][nextMask];
        }
    }

    void build(int node, int left, int right) {
        coverCount[node].fill(0);
        if (left + 1 == right) {
            int length = coordinates[left + 1] - coordinates[left];
            for (int mask = 0; mask < 16; mask++)
                values[node][mask] = isValid(mask) ? length : 0;
            return;
        }
        int middle = (left + right) / 2;
        build(node * 2, left, middle);
        build(node * 2 + 1, middle, right);
        pull(node, left, right);
    }

    void update(int node, int left, int right, int queryLeft, int queryRight, int type, int delta) {
        if (queryRight <= left || right <= queryLeft)
            return;
        if (queryLeft <= left && right <= queryRight) {
            coverCount[node][type] += delta;
            pull(node, left, right);
            return;
        }
        int middle = (left + right) / 2;
        update(node * 2, left, middle, queryLeft, queryRight, type, delta);
        update(node * 2 + 1, middle, right, queryLeft, queryRight, type, delta);
        pull(node, left, right);
    }

    int findFirst(int node, int left, int right, int inheritedMask) {
        int coverMask = 0;
        for (int type = 0; type < 4; type++)
            if (coverCount[node][type] > 0)
                coverMask |= 1 << type;
        int currentMask = inheritedMask | coverMask;
        if (left + 1 == right)
            return left;
        int middle = (left + right) / 2;
        if (values[node * 2][currentMask] > 0)
            return findFirst(node * 2, left, middle, currentMask);
        return findFirst(node * 2 + 1, middle, right, currentMask);
    }

public:
    SegmentTree(const vector<int>& inputCoordinates) {
        coordinates = inputCoordinates;
        leafCount = static_cast<int>(coordinates.size()) - 1;
        size = 1;
        while (size < leafCount)
            size <<= 1;
        values.resize(size * 2);
        coverCount.resize(size * 2);
        build(1, 0, leafCount);
    }

    void update(int left, int right, int type, int delta) {
        int queryLeft = lower_bound(coordinates.begin(), coordinates.end(), left) - coordinates.begin();
        int queryRight = lower_bound(coordinates.begin(), coordinates.end(), right + 1) - coordinates.begin();
        update(1, 0, leafCount, queryLeft, queryRight, type, delta);
    }

    int getTotal() {
        return values[1][0];
    }

    int getFirstCoordinate() {
        int index = findFirst(1, 0, leafCount, 0);
        return coordinates[index];
    }
};

int getNextDirection(int direction, int mirrorType) {
    if (mirrorType == 1) {
        if (direction == 0)
            return 3;
        if (direction == 1)
            return 2;
        if (direction == 2)
            return 1;
        return 0;
    }
    if (direction == 0)
        return 1;
    if (direction == 1)
        return 0;
    if (direction == 2)
        return 3;
    return 2;
}

long long makeStateKey(int row, int column, int direction) {
    return (static_cast<long long>(row) << 42) |
           (static_cast<long long>(column) << 21) |
           direction;
}

bool tracePath(
    int rowCount,
    int columnCount,
    const unordered_map<int, vector<Mirror>>& rowMirrors,
    const unordered_map<int, vector<Mirror>>& columnMirrors,
    int startRow,
    int startColumn,
    int startDirection,
    bool isForward,
    vector<Segment>& segments
) {
    int currentRow = startRow;
    int currentColumn = startColumn;
    int direction = startDirection;
    bool currentIsMirror = false;
    unordered_set<long long> visitedStates;
    while (true) {
        if (currentIsMirror) {
            long long stateKey = makeStateKey(currentRow, currentColumn, direction);
            if (visitedStates.count(stateKey))
                return false;
            visitedStates.insert(stateKey);
        }
        bool hasMirror = false;
        int mirrorRow = currentRow;
        int mirrorColumn = currentColumn;
        int mirrorType = 0;
        if (direction == 0 || direction == 2) {
            auto iterator = rowMirrors.find(currentRow);
            if (iterator != rowMirrors.end()) {
                const vector<Mirror>& mirrors = iterator->second;
                if (direction == 0) {
                    auto position = upper_bound(
                        mirrors.begin(),
                        mirrors.end(),
                        currentColumn,
                        [](int value, const Mirror& mirror) {
                            return value < mirror.coordinate;
                        }
                    );
                    if (position != mirrors.end()) {
                        hasMirror = true;
                        mirrorColumn = position->coordinate;
                        mirrorType = position->type;
                    }
                } else {
                    auto position = lower_bound(
                        mirrors.begin(),
                        mirrors.end(),
                        currentColumn,
                        [](const Mirror& mirror, int value) {
                            return mirror.coordinate < value;
                        }
                    );
                    if (position != mirrors.begin()) {
                        --position;
                        hasMirror = true;
                        mirrorColumn = position->coordinate;
                        mirrorType = position->type;
                    }
                }
            }
            int endColumn = hasMirror ? mirrorColumn : (direction == 0 ? columnCount + 1 : 0);
            int left = min(currentColumn, endColumn) + 1;
            int right = max(currentColumn, endColumn) - 1;
            if (left <= right)
                segments.push_back({0, currentRow, left, right});
            if (!hasMirror) {
                if (isForward)
                    return direction == 0 && currentRow == rowCount;
                return direction == 2 && currentRow == 1;
            }
        } else {
            auto iterator = columnMirrors.find(currentColumn);
            if (iterator != columnMirrors.end()) {
                const vector<Mirror>& mirrors = iterator->second;
                if (direction == 1) {
                    auto position = upper_bound(
                        mirrors.begin(),
                        mirrors.end(),
                        currentRow,
                        [](int value, const Mirror& mirror) {
                            return value < mirror.coordinate;
                        }
                    );
                    if (position != mirrors.end()) {
                        hasMirror = true;
                        mirrorRow = position->coordinate;
                        mirrorType = position->type;
                    }
                } else {
                    auto position = lower_bound(
                        mirrors.begin(),
                        mirrors.end(),
                        currentRow,
                        [](const Mirror& mirror, int value) {
                            return mirror.coordinate < value;
                        }
                    );
                    if (position != mirrors.begin()) {
                        --position;
                        hasMirror = true;
                        mirrorRow = position->coordinate;
                        mirrorType = position->type;
                    }
                }
            }
            int endRow = hasMirror ? mirrorRow : (direction == 1 ? rowCount + 1 : 0);
            int top = min(currentRow, endRow) + 1;
            int bottom = max(currentRow, endRow) - 1;
            if (top <= bottom)
                segments.push_back({1, currentColumn, top, bottom});
            if (!hasMirror) {
                if (isForward)
                    return false;
                return false;
            }
        }
        if (direction == 0 || direction == 2) {
            currentColumn = mirrorColumn;
            currentIsMirror = true;
        } else {
            currentRow = mirrorRow;
            currentIsMirror = true;
        }
        direction = getNextDirection(direction, mirrorType);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowCount, columnCount, slashCount, backslashCount;
    int caseNumber = 1;
    while (cin >> rowCount >> columnCount >> slashCount >> backslashCount) {
        unordered_map<int, vector<Mirror>> rowMirrors;
        unordered_map<int, vector<Mirror>> columnMirrors;
        auto addMirror = [&](int row, int column, int type) {
            rowMirrors[row].push_back({column, type});
            columnMirrors[column].push_back({row, type});
        };
        for (int i = 0; i < slashCount; i++) {
            int row, column;
            cin >> row >> column;
            addMirror(row, column, 1);
        }
        for (int i = 0; i < backslashCount; i++) {
            int row, column;
            cin >> row >> column;
            addMirror(row, column, 2);
        }
        for (auto& item : rowMirrors)
            sort(item.second.begin(), item.second.end(), [](const Mirror& left, const Mirror& right) {
                return left.coordinate < right.coordinate;
            });
        for (auto& item : columnMirrors)
            sort(item.second.begin(), item.second.end(), [](const Mirror& left, const Mirror& right) {
                return left.coordinate < right.coordinate;
            });
        vector<Segment> forwardSegments;
        vector<Segment> backwardSegments;
        bool forwardSuccess = tracePath(
            rowCount,
            columnCount,
            rowMirrors,
            columnMirrors,
            1,
            0,
            0,
            true,
            forwardSegments
        );
        bool backwardSuccess = tracePath(
            rowCount,
            columnCount,
            rowMirrors,
            columnMirrors,
            rowCount,
            columnCount + 1,
            2,
            false,
            backwardSegments
        );
        cout << "Case " << caseNumber++ << ": ";
        if (forwardSuccess || backwardSuccess) {
            cout << 0 << '\n';
            continue;
        }
        vector<Event> events;
        vector<int> coordinates;
        auto addSegment = [&](const Segment& segment, int type) {
            if (segment.direction == 0) {
                coordinates.push_back(segment.left);
                coordinates.push_back(segment.right + 1);
                events.push_back({segment.fixed, segment.left, segment.right, type, 1, 1});
                events.push_back({segment.fixed, segment.left, segment.right, type, -1, 2});
            } else {
                coordinates.push_back(segment.fixed);
                coordinates.push_back(segment.fixed + 1);
                events.push_back({segment.left, segment.fixed, segment.fixed, type, 1, 0});
                events.push_back({segment.right + 1, segment.fixed, segment.fixed, type, -1, 0});
            }
        };
        for (const Segment& segment : forwardSegments)
            addSegment(segment, segment.direction == 0 ? 0 : 1);
        for (const Segment& segment : backwardSegments)
            addSegment(segment, segment.direction == 0 ? 2 : 3);
        sort(coordinates.begin(), coordinates.end());
        coordinates.erase(unique(coordinates.begin(), coordinates.end()), coordinates.end());
        if (coordinates.size() < 2) {
            cout << "impossible\n";
            continue;
        }
        sort(events.begin(), events.end(), [](const Event& left, const Event& right) {
            if (left.row != right.row)
                return left.row < right.row;
            return left.phase < right.phase;
        });
        SegmentTree segmentTree(coordinates);
        long long answerCount = 0;
        int answerRow = -1;
        int answerColumn = -1;
        int eventIndex = 0;
        while (eventIndex < static_cast<int>(events.size())) {
            int currentRow = events[eventIndex].row;
            int nextEventIndex = eventIndex;
            while (nextEventIndex < static_cast<int>(events.size()) && events[nextEventIndex].row == currentRow)
                nextEventIndex++;
            if (currentRow >= 1 && currentRow <= rowCount) {
                int middleIndex = eventIndex;
                while (middleIndex < nextEventIndex && events[middleIndex].phase < 2) {
                    const Event& event = events[middleIndex];
                    segmentTree.update(event.left, event.right, event.type, event.delta);
                    middleIndex++;
                }
                if (middleIndex > eventIndex) {
                    int currentCount = segmentTree.getTotal();
                    answerCount += currentCount;
                    if (answerRow == -1 && currentCount > 0) {
                        answerRow = currentRow;
                        answerColumn = segmentTree.getFirstCoordinate();
                    }
                }
                while (middleIndex < nextEventIndex) {
                    const Event& event = events[middleIndex];
                    segmentTree.update(event.left, event.right, event.type, event.delta);
                    middleIndex++;
                }
            }
            eventIndex = nextEventIndex;
        }
        if (answerCount == 0)
            cout << "impossible\n";
        else
            cout << answerCount << ' ' << answerRow << ' ' << answerColumn << '\n';
    }
    return 0;
}
