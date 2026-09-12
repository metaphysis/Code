// Traveler of Gridland
// UVa ID: 11918
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.370s

#include <bits/stdc++.h>
using namespace std;

using LongLong = long long;

const LongLong lowerBound = -1000000000LL;
const LongLong upperBound = 1000000000LL;
const LongLong infinityValue = (1LL << 62);

struct Monster {
    int type;
    LongLong x1;
    LongLong y1;
    LongLong x2;
    LongLong y2;
};

void addCoordinate(vector<LongLong>& coordinates, LongLong value) {
    if (value >= lowerBound && value <= upperBound)
        coordinates.push_back(value);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseNumber = 1; caseNumber <= testCount; caseNumber++) {
        LongLong sourceX, sourceY, destinationX, destinationY;
        cin >> sourceX >> sourceY >> destinationX >> destinationY;
        int pointCount, lineCount, rectangleCount;
        cin >> pointCount >> lineCount >> rectangleCount;
        vector<Monster> monsters;
        vector<LongLong> xCoordinates, yCoordinates;
        addCoordinate(xCoordinates, lowerBound);
        addCoordinate(xCoordinates, upperBound);
        addCoordinate(yCoordinates, lowerBound);
        addCoordinate(yCoordinates, upperBound);
        addCoordinate(xCoordinates, sourceX);
        addCoordinate(xCoordinates, destinationX);
        addCoordinate(yCoordinates, sourceY);
        addCoordinate(yCoordinates, destinationY);
        auto addMonsterCoordinates = [&](LongLong x1, LongLong y1, LongLong x2, LongLong y2) {
            addCoordinate(xCoordinates, x1 - 1);
            addCoordinate(xCoordinates, x1);
            addCoordinate(xCoordinates, x2);
            addCoordinate(xCoordinates, x2 + 1);
            addCoordinate(yCoordinates, y1 - 1);
            addCoordinate(yCoordinates, y1);
            addCoordinate(yCoordinates, y2);
            addCoordinate(yCoordinates, y2 + 1);
        };
        for (int i = 0; i < pointCount; i++) {
            LongLong x, y;
            cin >> x >> y;
            monsters.push_back({1, x, y, x, y});
            addMonsterCoordinates(x, y, x, y);
        }
        for (int i = 0; i < lineCount; i++) {
            LongLong x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 > x2)
                swap(x1, x2);
            if (y1 > y2)
                swap(y1, y2);
            monsters.push_back({2, x1, y1, x2, y2});
            addMonsterCoordinates(x1, y1, x2, y2);
        }
        for (int i = 0; i < rectangleCount; i++) {
            LongLong x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 > x2)
                swap(x1, x2);
            if (y1 > y2)
                swap(y1, y2);
            monsters.push_back({3, x1, y1, x2, y2});
            addMonsterCoordinates(x1, y1, x2, y2);
        }
        sort(xCoordinates.begin(), xCoordinates.end());
        xCoordinates.erase(unique(xCoordinates.begin(), xCoordinates.end()), xCoordinates.end());
        sort(yCoordinates.begin(), yCoordinates.end());
        yCoordinates.erase(unique(yCoordinates.begin(), yCoordinates.end()), yCoordinates.end());
        int xCount = static_cast<int>(xCoordinates.size());
        int yCount = static_cast<int>(yCoordinates.size());
        vector<vector<int>> difference(yCount + 1, vector<int>(xCount + 1, 0));
        auto getXIndex = [&](LongLong value) {
            return static_cast<int>(lower_bound(xCoordinates.begin(), xCoordinates.end(), value) - xCoordinates.begin());
        };
        auto getYIndex = [&](LongLong value) {
            return static_cast<int>(lower_bound(yCoordinates.begin(), yCoordinates.end(), value) - yCoordinates.begin());
        };
        auto addBlockedRectangle = [&](int x1, int y1, int x2, int y2) {
            difference[y1][x1]++;
            difference[y2 + 1][x1]--;
            difference[y1][x2 + 1]--;
            difference[y2 + 1][x2 + 1]++;
        };
        for (const Monster& monster : monsters) {
            int x1 = getXIndex(monster.x1);
            int y1 = getYIndex(monster.y1);
            int x2 = getXIndex(monster.x2);
            int y2 = getYIndex(monster.y2);
            addBlockedRectangle(x1, y1, x2, y2);
        }
        vector<vector<bool>> blocked(yCount, vector<bool>(xCount, false));
        for (int y = 0; y < yCount; y++)
            for (int x = 0; x < xCount; x++) {
                if (x > 0)
                    difference[y][x] += difference[y][x - 1];
                if (y > 0)
                    difference[y][x] += difference[y - 1][x];
                if (x > 0 && y > 0)
                    difference[y][x] -= difference[y - 1][x - 1];
                blocked[y][x] = difference[y][x] > 0;
            }
        int sourceIndexX = getXIndex(sourceX);
        int sourceIndexY = getYIndex(sourceY);
        int destinationIndexX = getXIndex(destinationX);
        int destinationIndexY = getYIndex(destinationY);
        int nodeCount = xCount * yCount;
        auto getNodeId = [&](int x, int y) {
            return y * xCount + x;
        };
        vector<LongLong> distances(nodeCount, infinityValue);
        priority_queue<pair<LongLong, int>, vector<pair<LongLong, int>>, greater<pair<LongLong, int>>> priorityQueue;
        int sourceId = getNodeId(sourceIndexX, sourceIndexY);
        int destinationId = getNodeId(destinationIndexX, destinationIndexY);
        distances[sourceId] = 0;
        priorityQueue.push({0, sourceId});
        int directionX[4] = {1, -1, 0, 0};
        int directionY[4] = {0, 0, 1, -1};
        while (!priorityQueue.empty()) {
            auto current = priorityQueue.top();
            priorityQueue.pop();
            LongLong currentDistance = current.first;
            int currentId = current.second;
            if (currentDistance != distances[currentId])
                continue;
            if (currentId == destinationId)
                break;
            int currentX = currentId % xCount;
            int currentY = currentId / xCount;
            for (int direction = 0; direction < 4; direction++) {
                int nextX = currentX + directionX[direction];
                int nextY = currentY + directionY[direction];
                if (nextX < 0 || nextX >= xCount || nextY < 0 || nextY >= yCount)
                    continue;
                if (blocked[nextY][nextX])
                    continue;
                LongLong moveDistance;
                if (currentX != nextX)
                    moveDistance = abs(xCoordinates[currentX] - xCoordinates[nextX]);
                else
                    moveDistance = abs(yCoordinates[currentY] - yCoordinates[nextY]);
                int nextId = getNodeId(nextX, nextY);
                LongLong nextDistance = currentDistance + moveDistance;
                if (nextDistance < distances[nextId]) {
                    distances[nextId] = nextDistance;
                    priorityQueue.push({nextDistance, nextId});
                }
            }
        }
        cout << "Case " << caseNumber << ": ";
        if (distances[destinationId] == infinityValue)
            cout << "Impossible\n";
        else
            cout << distances[destinationId] << '\n';
    }
    return 0;
}
