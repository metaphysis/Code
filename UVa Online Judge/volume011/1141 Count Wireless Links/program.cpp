#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

long long getCellKey(int cellX, int cellY) {
    return (static_cast<long long>(cellX) << 32) | static_cast<unsigned int>(cellY);
}

long long solve(int radioRange, int nodeCount) {
    unordered_map<long long, vector<Point>> cellMap;
    long long linkCnt = 0, rangeSq = 1LL * radioRange * radioRange;
    cellMap.reserve(nodeCount * 2);
    for (int i = 0; i < nodeCount; i++) {
        Point point;
        cin >> point.x >> point.y;
        int cellX = point.x / radioRange, cellY = point.y / radioRange;
        for (int offsetX = -1; offsetX <= 1; offsetX++) {
            for (int offsetY = -1; offsetY <= 1; offsetY++) {
                long long cellKey = getCellKey(cellX + offsetX, cellY + offsetY);
                auto iter = cellMap.find(cellKey);
                if (iter == cellMap.end()) continue;
                for (const Point &other : iter->second) {
                    long long dx = point.x - other.x, dy = point.y - other.y;
                    if (dx * dx + dy * dy < rangeSq) linkCnt++;
                }
            }
        }
        cellMap[getCellKey(cellX, cellY)].push_back(point);
    }
    return linkCnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int length, height, radioRange, nodeCount;
    while (cin >> length >> height >> radioRange >> nodeCount)
        cout << solve(radioRange, nodeCount) << '\n';
    return 0;
}
