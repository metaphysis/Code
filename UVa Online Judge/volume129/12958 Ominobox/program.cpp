#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long Ull;

const int maxWords = 15;

struct Shape {
    string cells;
    vector<int> children;
    int size, offsetId;
};

vector<Shape> shapes;
vector<pair<int, int>> offsets;
int offsetIds[10][19], levelBegin[11], levelEnd[11];
int targetN, wordCount, offsetCount;
const Ull *activeMasks;

int getOffsetId(int row, int col) {
    int &id = offsetIds[row][col + 9];
    if (id == -1) {
        id = static_cast<int>(offsets.size());
        offsets.push_back(make_pair(row, col));
    }
    return id;
}

void buildShapes() {
    memset(offsetIds, -1, sizeof(offsetIds));
    shapes.reserve(50148);
    Shape root;
    root.cells = string(1, static_cast<char>(9));
    root.size = 1;
    root.offsetId = getOffsetId(0, 0);
    shapes.push_back(root);
    levelBegin[1] = 0;
    levelEnd[1] = 1;
    int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    for (int size = 1; size < 10; ++size) {
        unordered_map<string, int> seen;
        seen.reserve(50000);
        levelBegin[size + 1] = static_cast<int>(shapes.size());
        for (int id = levelBegin[size]; id < levelEnd[size]; ++id) {
            string cells = shapes[id].cells;
            for (unsigned char cell : cells) {
                int row = cell / 19, col = cell % 19 - 9;
                for (int dir = 0; dir < 4; ++dir) {
                    int nextRow = row + dr[dir], nextCol = col + dc[dir];
                    if (nextRow < 0 || nextRow > 9 || nextCol < -9 || nextCol > 9) continue;
                    if (nextRow == 0 && nextCol < 0) continue;
                    char nextCell = static_cast<char>(nextRow * 19 + nextCol + 9);
                    if (cells.find(nextCell) != string::npos) continue;
                    string nextCells = cells;
                    nextCells.push_back(nextCell);
                    sort(nextCells.begin(), nextCells.end());
                    int nextId = static_cast<int>(shapes.size());
                    if (!seen.emplace(nextCells, nextId).second) continue;
                    Shape nextShape;
                    nextShape.cells = nextCells;
                    nextShape.size = size + 1;
                    nextShape.offsetId = getOffsetId(nextRow, nextCol);
                    shapes.push_back(move(nextShape));
                    shapes[id].children.push_back(nextId);
                }
            }
        }
        levelEnd[size + 1] = static_cast<int>(shapes.size());
    }
    offsetCount = static_cast<int>(offsets.size());
}

int countWays(int nodeId, const Ull *positions) {
    if (shapes[nodeId].size == targetN) return 1;
    int result = 0;
    bool lastLevel = shapes[nodeId].size + 1 == targetN;
    Ull nextPositions[maxWords];
    for (int childId : shapes[nodeId].children) {
        const Ull *cellMask = activeMasks + shapes[childId].offsetId * wordCount;
        if (lastLevel) {
            for (int word = 0; word < wordCount; ++word) {
                if ((positions[word] & cellMask[word]) != 0) {
                    ++result;
                    break;
                }
            }
        } else {
            Ull any = 0;
            for (int word = 0; word < wordCount; ++word) {
                nextPositions[word] = positions[word] & cellMask[word];
                any |= nextPositions[word];
            }
            if (any != 0) result += countWays(childId, nextPositions);
        }
    }
    return result;
}

long long solveCase(int rowCount, int colCount, int boxHeight, const vector<int> &heights) {
    if (rowCount * colCount < targetN) return 0;
    wordCount = (rowCount * colCount + 63) / 64;
    int layerSize = offsetCount * wordCount;
    vector<Ull> masks(boxHeight * layerSize, 0);
    vector<int> levels;
    for (int height : heights) if (height < boxHeight) levels.push_back(height);
    sort(levels.begin(), levels.end());
    levels.erase(unique(levels.begin(), levels.end()), levels.end());
    if (levels.empty()) return 0;
    for (int offsetId = 0; offsetId < offsetCount; ++offsetId) {
        int dr = offsets[offsetId].first, dc = offsets[offsetId].second;
        for (int row = 0; row < rowCount; ++row) {
            for (int col = 0; col < colCount; ++col) {
                int anchorRow = row - dr, anchorCol = col - dc;
                int height = heights[row * colCount + col];
                if (height == boxHeight) continue;
                if (anchorRow < 0 || anchorRow >= rowCount || anchorCol < 0 || anchorCol >= colCount) continue;
                int pos = anchorRow * colCount + anchorCol;
                masks[height * layerSize + offsetId * wordCount + pos / 64] |= 1ULL << (pos % 64);
            }
        }
    }
    for (int height = 1; height < boxHeight; ++height) {
        Ull *current = masks.data() + height * layerSize;
        const Ull *previous = current - layerSize;
        for (int index = 0; index < layerSize; ++index) current[index] |= previous[index];
    }
    long long answer = 0;
    for (int index = 0; index < static_cast<int>(levels.size()); ++index) {
        int height = levels[index], nextHeight = boxHeight;
        if (index + 1 < static_cast<int>(levels.size())) nextHeight = levels[index + 1];
        activeMasks = masks.data() + height * layerSize;
        const Ull *rootPositions = activeMasks + shapes[0].offsetId * wordCount;
        answer += 1LL * countWays(0, rootPositions) * (nextHeight - height);
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildShapes();
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int rowCount, colCount, boxHeight;
        cin >> rowCount >> colCount >> boxHeight >> targetN;
        vector<int> heights(rowCount * colCount);
        for (int &height : heights) cin >> height;
        cout << solveCase(rowCount, colCount, boxHeight, heights) << '\n';
    }
    return 0;
}
