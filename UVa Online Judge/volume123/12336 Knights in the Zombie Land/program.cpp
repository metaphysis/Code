#include <bits/stdc++.h>
using namespace std;

class FastInput {
private:
    static const int bufferSize = 1 << 20;
    char buffer[bufferSize];
    int bufferIndex, bufferLength;
public:
    FastInput() : bufferIndex(0), bufferLength(0) {}
    char getChar() {
        if (bufferIndex >= bufferLength) {
            bufferLength = fread(buffer, 1, bufferSize, stdin);
            bufferIndex = 0;
            if (bufferLength == 0) return 0;
        }
        return buffer[bufferIndex++];
    }
    int nextInt() {
        char ch = getChar();
        while (ch <= ' ' && ch) ch = getChar();
        int value = 0;
        while (ch >= '0' && ch <= '9') {
            value = value * 10 + ch - '0';
            ch = getChar();
        }
        return value;
    }
};

class FastHashSet {
private:
    vector<unsigned long long> table;
    size_t mask;
    size_t hashValue(unsigned long long value) const {
        value += 0x9e3779b97f4a7c15ULL;
        value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
        value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
        return (value ^ (value >> 31)) & mask;
    }
public:
    void init(size_t expected) {
        size_t capacity = 1;
        while (capacity < expected * 2) capacity <<= 1;
        table.assign(capacity, 0);
        mask = capacity - 1;
    }
    void insert(unsigned long long value) {
        size_t position = hashValue(value);
        while (table[position] != 0 && table[position] != value) position = (position + 1) & mask;
        table[position] = value;
    }
    size_t size() const {
        size_t result = 0;
        for (auto value : table) if (value != 0) result++;
        return result;
    }
};

struct Shape {
    vector<pair<int, int>> point;
    int height, width;
};

bool isMove(int row, int col) {
    row = abs(row);
    col = abs(col);
    return (row == 1 && col == 2) || (row == 2 && col == 1);
}

vector<Shape> buildShapes() {
    vector<pair<int, int>> moves = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
    set<vector<pair<int, int>>> shapeSet;
    for (auto move1 : moves) {
        for (auto move2 : moves) {
            if (move1 == move2) continue;
            for (auto move3 : moves) {
                int row = move1.first + move3.first;
                int col = move1.second + move3.second;
                if (row == 0 && col == 0) continue;
                if (!isMove(row - move2.first, col - move2.second)) continue;
                vector<pair<int, int>> point = {{0, 0}, move1, {row, col}, move2};
                int minRow = point[0].first, minCol = point[0].second;
                for (auto item : point) {
                    minRow = min(minRow, item.first);
                    minCol = min(minCol, item.second);
                }
                for (auto &item : point) {
                    item.first -= minRow;
                    item.second -= minCol;
                }
                sort(point.begin(), point.end());
                shapeSet.insert(point);
            }
        }
    }
    vector<Shape> shapes;
    for (auto point : shapeSet) {
        int maxRow = 0, maxCol = 0;
        for (auto item : point) {
            maxRow = max(maxRow, item.first);
            maxCol = max(maxCol, item.second);
        }
        shapes.push_back({point, maxRow, maxCol});
    }
    return shapes;
}

unsigned long long makeKey(int id, int row, int col) {
    return ((unsigned long long)(id + 1) << 34) | ((unsigned long long)row << 17) | (unsigned long long)col;
}

int main() {
    FastInput input;
    vector<Shape> shapes = buildShapes();
    int testCount = input.nextInt();
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int rowCount = input.nextInt(), colCount = input.nextInt(), stoneCount = input.nextInt();
        vector<pair<int, int>> stones(stoneCount);
        for (auto &stone : stones) {
            stone.first = input.nextInt();
            stone.second = input.nextInt();
        }
        long long total = 0;
        for (auto &shape : shapes) total += 1LL * (rowCount - shape.height) * (colCount - shape.width);
        FastHashSet used;
        used.init((size_t)stoneCount * shapes.size() * 4 + 1);
        for (int id = 0; id < (int)shapes.size(); id++) {
            const Shape &shape = shapes[id];
            for (auto stone : stones) {
                for (auto point : shape.point) {
                    int baseRow = stone.first - point.first;
                    int baseCol = stone.second - point.second;
                    if (baseRow < 1 || baseRow + shape.height > rowCount) continue;
                    if (baseCol < 1 || baseCol + shape.width > colCount) continue;
                    used.insert(makeKey(id, baseRow, baseCol));
                }
            }
        }
        long long answer = (total - (long long)used.size()) * 8;
        printf("Case %d: %lld\n", caseId, answer);
    }
    return 0;
}
