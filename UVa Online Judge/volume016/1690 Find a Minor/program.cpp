#include <bits/stdc++.h>
using namespace std;

int vertexCount, targetSize, leftSize, rightSize, requiredEdges;
int nearMask[1 << 12], groupMask[12];
bool connected[1 << 12], completeTarget;

void buildMasks() {
    int limit = 1 << vertexCount;
    nearMask[0] = 0;
    connected[0] = false;
    for (int mask = 1; mask < limit; mask++) {
        int lowBit = mask & -mask;
        nearMask[mask] = nearMask[mask ^ lowBit] | nearMask[lowBit];
    }
    for (int mask = 1; mask < limit; mask++) {
        int reached = mask & -mask, nextMask;
        while (true) {
            nextMask = reached | (nearMask[reached] & mask);
            if (nextMask == reached) break;
            reached = nextMask;
        }
        connected[mask] = reached == mask;
    }
}

bool checkPartition() {
    for (int i = 0; i < targetSize; i++) if (!connected[groupMask[i]]) return false;
    if (completeTarget) {
        for (int i = 0; i < targetSize; i++) {
            int neighbors = nearMask[groupMask[i]];
            for (int j = i + 1; j < targetSize; j++) if (!(neighbors & groupMask[j])) return false;
        }
        return true;
    }
    int badMask[12] = {}, edgeCount = 0;
    for (int i = 0; i < targetSize; i++) {
        int neighbors = nearMask[groupMask[i]];
        for (int j = i + 1; j < targetSize; j++) {
            if (neighbors & groupMask[j]) edgeCount++;
            else {
                badMask[i] |= 1 << j;
                badMask[j] |= 1 << i;
            }
        }
    }
    if (edgeCount < requiredEdges) return false;
    int remaining = (1 << targetSize) - 1, possible = 1;
    while (remaining) {
        int startBit = remaining & -remaining, frontier = startBit, componentSize = 0;
        remaining ^= startBit;
        while (frontier) {
            int lowBit = frontier & -frontier, vertex = __builtin_ctz(lowBit);
            int nextMask = badMask[vertex] & remaining;
            frontier ^= lowBit;
            frontier |= nextMask;
            remaining ^= nextMask;
            componentSize++;
        }
        if (componentSize > max(leftSize, rightSize)) return false;
        possible |= possible << componentSize;
    }
    return (possible & (1 << leftSize)) != 0;
}

bool searchPartition(int vertex, int groupCount) {
    if (groupCount + vertexCount - vertex < targetSize) return false;
    if (vertex == vertexCount) return checkPartition();
    int vertexBit = 1 << vertex;
    if (groupCount + vertexCount - vertex > targetSize) {
        for (int i = 0; i < groupCount; i++) {
            groupMask[i] |= vertexBit;
            if (searchPartition(vertex + 1, groupCount)) return true;
            groupMask[i] ^= vertexBit;
        }
    }
    if (groupCount < targetSize) {
        groupMask[groupCount] = vertexBit;
        if (searchPartition(vertex + 1, groupCount + 1)) return true;
        groupMask[groupCount] = 0;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 0;
    while (cin >> vertexCount && vertexCount) {
        string target;
        cin >> target;
        size_t commaPos = target.find(',');
        completeTarget = commaPos == string::npos;
        leftSize = stoi(target.substr(1, commaPos - 1));
        rightSize = 0;
        if (!completeTarget) rightSize = stoi(target.substr(commaPos + 1));
        targetSize = leftSize + rightSize;
        requiredEdges = completeTarget ? targetSize * (targetSize - 1) / 2 : leftSize * rightSize;
        memset(nearMask, 0, sizeof(nearMask));
        int edgeCount = 0;
        for (int pos = 0; pos < vertexCount * vertexCount; pos++) {
            char value;
            cin >> value;
            int row = pos / vertexCount, col = pos % vertexCount;
            if (value == '1') {
                nearMask[1 << row] |= 1 << col;
                if (row < col) edgeCount++;
            }
        }
        bool found = false;
        if (targetSize <= vertexCount && edgeCount >= vertexCount - targetSize + requiredEdges) {
            buildMasks();
            memset(groupMask, 0, sizeof(groupMask));
            groupMask[0] = 1;
            found = searchPartition(1, 1);
        }
        cout << "Case " << ++caseNumber << ": " << (found ? "Found" : "Not found") << '\n';
    }
    return 0;
}
