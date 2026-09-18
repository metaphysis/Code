#include <bits/stdc++.h>
using namespace std;

using Cell = pair<int, int>;
using Shape = vector<Cell>;

bool isFilled(char ch) {
    return ch == '#' || ch == 'X';
}

Shape normalize(Shape cells) {
    int minRow = INT_MAX, minCol = INT_MAX;
    for (const auto &cell : cells) {
        minRow = min(minRow, cell.first);
        minCol = min(minCol, cell.second);
    }
    for (auto &cell : cells) {
        cell.first -= minRow;
        cell.second -= minCol;
    }
    sort(cells.begin(), cells.end());
    return cells;
}

vector<Shape> getForms(const Shape &cells) {
    vector<Shape> forms;
    for (int flip = 0; flip < 2; ++flip) {
        Shape cur = cells;
        if (flip) for (auto &cell : cur) cell.second = -cell.second;
        for (int turn = 0; turn < 4; ++turn) {
            forms.push_back(normalize(cur));
            for (auto &cell : cur) {
                int row = cell.first;
                cell.first = cell.second;
                cell.second = -row;
            }
        }
    }
    sort(forms.begin(), forms.end());
    forms.erase(unique(forms.begin(), forms.end()), forms.end());
    return forms;
}

struct Dlx {
    struct Node {
        int left, right, up, down, col, type;
    };
    vector<Node> nodes;
    vector<int> colSize, leftCount;
    int cellCount;

    Dlx(int cellCnt, const vector<int> &counts, int nodeLimit) {
        cellCount = cellCnt;
        leftCount = counts;
        int colCount = cellCnt + (int)counts.size();
        colSize.assign(colCount + 1, 0);
        nodes.reserve(nodeLimit);
        for (int i = 0; i <= colCount; ++i) nodes.push_back({i, i, i, i, i, -1});
        nodes[0].left = cellCnt;
        nodes[0].right = cellCnt ? 1 : 0;
        for (int i = 1; i <= cellCnt; ++i) {
            nodes[i].left = i - 1;
            nodes[i].right = i == cellCnt ? 0 : i + 1;
        }
    }

    void addRow(const vector<int> &cols, int type) {
        int first = -1;
        for (int col : cols) {
            int id = (int)nodes.size();
            nodes.push_back({id, id, nodes[col].up, col, col, type});
            nodes[nodes[col].up].down = id;
            nodes[col].up = id;
            ++colSize[col];
            if (first == -1) first = id;
            else {
                int last = nodes[first].left;
                nodes[id].left = last;
                nodes[id].right = first;
                nodes[last].right = id;
                nodes[first].left = id;
            }
        }
    }

    void cover(int col) {
        nodes[nodes[col].left].right = nodes[col].right;
        nodes[nodes[col].right].left = nodes[col].left;
        for (int row = nodes[col].down; row != col; row = nodes[row].down) {
            for (int id = nodes[row].right; id != row; id = nodes[id].right) {
                nodes[nodes[id].up].down = nodes[id].down;
                nodes[nodes[id].down].up = nodes[id].up;
                --colSize[nodes[id].col];
            }
        }
    }

    void uncover(int col) {
        for (int row = nodes[col].up; row != col; row = nodes[row].up) {
            for (int id = nodes[row].left; id != row; id = nodes[id].left) {
                ++colSize[nodes[id].col];
                nodes[nodes[id].up].down = id;
                nodes[nodes[id].down].up = id;
            }
        }
        nodes[nodes[col].left].right = col;
        nodes[nodes[col].right].left = col;
    }

    bool search() {
        if (nodes[0].right == 0) return true;
        int best = nodes[0].right;
        for (int col = nodes[best].right; col != 0; col = nodes[col].right) if (colSize[col] < colSize[best]) best = col;
        if (colSize[best] == 0) return false;
        cover(best);
        for (int row = nodes[best].down; row != best; row = nodes[row].down) {
            int type = nodes[row].type, typeCol = cellCount + type + 1;
            --leftCount[type];
            if (leftCount[type] == 0) cover(typeCol);
            for (int id = nodes[row].right; id != row; id = nodes[id].right) if (nodes[id].col <= cellCount) cover(nodes[id].col);
            if (search()) return true;
            for (int id = nodes[row].left; id != row; id = nodes[id].left) if (nodes[id].col <= cellCount) uncover(nodes[id].col);
            if (leftCount[type] == 0) uncover(typeCol);
            ++leftCount[type];
        }
        uncover(best);
        return false;
    }
};

bool solve(const vector<vector<int>> &cellId, int cellCount,
           const vector<vector<Shape>> &allForms, const vector<int> &counts) {
    int height = (int)cellId.size(), width = (int)cellId[0].size();
    int typeCount = (int)counts.size(), nodeLimit = cellCount + typeCount + 1;
    for (const auto &forms : allForms) {
        for (const auto &shape : forms) {
            int shapeH = 0, shapeW = 0;
            for (const auto &cell : shape) {
                shapeH = max(shapeH, cell.first + 1);
                shapeW = max(shapeW, cell.second + 1);
            }
            if (shapeH <= height && shapeW <= width) nodeLimit += (height - shapeH + 1) * (width - shapeW + 1) * ((int)shape.size() + 1);
        }
    }
    Dlx dlx(cellCount, counts, nodeLimit);
    vector<int> cols;
    for (int type = 0; type < typeCount; ++type) {
        for (const auto &shape : allForms[type]) {
            int shapeH = 0, shapeW = 0;
            for (const auto &cell : shape) {
                shapeH = max(shapeH, cell.first + 1);
                shapeW = max(shapeW, cell.second + 1);
            }
            for (int row = 0; row + shapeH <= height; ++row) {
                for (int col = 0; col + shapeW <= width; ++col) {
                    cols.clear();
                    bool valid = true;
                    for (const auto &cell : shape) {
                        int id = cellId[row + cell.first][col + cell.second];
                        if (id == 0) {
                            valid = false;
                            break;
                        }
                        cols.push_back(id);
                    }
                    if (valid) {
                        cols.push_back(cellCount + type + 1);
                        dlx.addRow(cols, type);
                    }
                }
            }
        }
    }
    return dlx.search();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int height, width;
    while (cin >> height >> width) {
        vector<vector<int>> cellId(height, vector<int>(width, 0));
        int cellCount = 0, pieceCount, totalArea = 0;
        string line;
        for (int row = 0; row < height; ++row) {
            cin >> line;
            for (int col = 0; col < width; ++col) if (isFilled(line[col])) cellId[row][col] = ++cellCount;
        }
        cin >> pieceCount;
        map<Shape, int> typeMap;
        vector<vector<Shape>> allForms;
        vector<int> counts;
        for (int i = 0; i < pieceCount; ++i) {
            int pieceH, pieceW;
            cin >> pieceH >> pieceW;
            Shape cells;
            for (int row = 0; row < pieceH; ++row) {
                cin >> line;
                for (int col = 0; col < pieceW; ++col) if (isFilled(line[col])) cells.push_back({row, col});
            }
            totalArea += (int)cells.size();
            vector<Shape> forms = getForms(cells);
            auto it = typeMap.find(forms[0]);
            if (it == typeMap.end()) {
                int type = (int)counts.size();
                typeMap[forms[0]] = type;
                allForms.push_back(move(forms));
                counts.push_back(1);
            } else {
                ++counts[it->second];
            }
        }
        if (totalArea != cellCount) cout << "No\n";
        else cout << (solve(cellId, cellCount, allForms, counts) ? "Yes\n" : "No\n");
    }
    return 0;
}
