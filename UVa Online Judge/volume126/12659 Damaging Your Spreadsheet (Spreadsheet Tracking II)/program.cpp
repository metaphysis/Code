#include <bits/stdc++.h>
using namespace std;

using Cell = pair<int, int>;
using Position = pair<int, int>;

int getShiftPosition(int position, const vector<int>& mark, bool insertFlag) {
    int shift = 0;
    if (insertFlag) {
        for (int i = 1; i <= position; i++)
            shift += mark[i];
        return position + shift;
    }
    if (mark[position])
        return 0;
    for (int i = 1; i < position; i++)
        shift += mark[i];
    return position - shift;
}

Cell getBaseCell(const vector<int>& rowSlots, const vector<int>& colSlots, int row, int col) {
    if (row < 1 || row > static_cast<int>(rowSlots.size()))
        return make_pair(0, 0);
    if (col < 1 || col > static_cast<int>(colSlots.size()))
        return make_pair(0, 0);
    if (rowSlots[row - 1] == 0 || colSlots[col - 1] == 0)
        return make_pair(0, 0);
    return make_pair(rowSlots[row - 1], colSlots[col - 1]);
}

long long getDistance(const Cell& cell, int row, int col) {
    return abs(cell.first - row) + abs(cell.second - col);
}

void updateAxis(vector<int>& slots, const vector<int>& mark, bool insertFlag) {
    vector<int> newSlots;
    if (insertFlag) {
        for (int i = 1; i <= static_cast<int>(slots.size()); i++) {
            if (mark[i])
                newSlots.push_back(0);
            newSlots.push_back(slots[i - 1]);
        }
    } else {
        for (int i = 1; i <= static_cast<int>(slots.size()); i++)
            if (!mark[i])
                newSlots.push_back(slots[i - 1]);
    }
    slots.swap(newSlots);
}

void updateChanges(map<Position, Cell>& changes, const vector<int>& rowMark, const vector<int>& colMark, bool rowInsert, bool colInsert) {
    map<Position, Cell> newChanges;
    for (const auto& item : changes) {
        int row = getShiftPosition(item.first.first, rowMark, rowInsert);
        int col = getShiftPosition(item.first.second, colMark, colInsert);
        if (row != 0 && col != 0)
            newChanges[make_pair(row, col)] = item.second;
    }
    changes.swap(newChanges);
}

void setChange(map<Position, Cell>& changes, const Position& position, const Cell& cell, const vector<int>& rowSlots, const vector<int>& colSlots) {
    Cell baseCell = getBaseCell(rowSlots, colSlots, position.first, position.second);
    if (cell == baseCell)
        changes.erase(position);
    else
        changes[position] = cell;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rows, cols, operationCount;
    int caseNumber = 1;
    while (cin >> rows >> cols) {
        if (rows == 0 && cols == 0)
            break;
        cin >> operationCount;
        vector<int> rowSlots(rows), colSlots(cols);
        for (int i = 0; i < rows; i++)
            rowSlots[i] = i + 1;
        for (int i = 0; i < cols; i++)
            colSlots[i] = i + 1;
        map<Position, Cell> changes;
        for (int operation = 0; operation < operationCount; operation++) {
            string command;
            cin >> command;
            if (command == "EX") {
                int row1, col1, row2, col2;
                cin >> row1 >> col1 >> row2 >> col2;
                Position firstPosition = make_pair(row1, col1), secondPosition = make_pair(row2, col2);
                Cell firstCell = getBaseCell(rowSlots, colSlots, row1, col1), secondCell = getBaseCell(rowSlots, colSlots, row2, col2);
                auto firstChange = changes.find(firstPosition);
                auto secondChange = changes.find(secondPosition);
                if (firstChange != changes.end())
                    firstCell = firstChange->second;
                if (secondChange != changes.end())
                    secondCell = secondChange->second;
                setChange(changes, firstPosition, secondCell, rowSlots, colSlots);
                setChange(changes, secondPosition, firstCell, rowSlots, colSlots);
            } else {
                int count;
                cin >> count;
                if (command == "IR" || command == "DR") {
                    vector<int> mark(rowSlots.size() + 1, 0);
                    for (int i = 0; i < count; i++) {
                        int position;
                        cin >> position;
                        mark[position] = 1;
                    }
                    bool insertFlag = command == "IR";
                    updateChanges(changes, mark, vector<int>(colSlots.size() + 1, 0), insertFlag, true);
                    updateAxis(rowSlots, mark, insertFlag);
                } else {
                    vector<int> mark(colSlots.size() + 1, 0);
                    for (int i = 0; i < count; i++) {
                        int position;
                        cin >> position;
                        mark[position] = 1;
                    }
                    bool insertFlag = command == "IC";
                    updateChanges(changes, vector<int>(rowSlots.size() + 1, 0), mark, true, insertFlag);
                    updateAxis(colSlots, mark, insertFlag);
                }
            }
        }
        vector<int> rowPosition(rows + 1, 0), colPosition(cols + 1, 0);
        for (int i = 0; i < static_cast<int>(rowSlots.size()); i++)
            if (rowSlots[i] != 0)
                rowPosition[rowSlots[i]] = i + 1;
        for (int i = 0; i < static_cast<int>(colSlots.size()); i++)
            if (colSlots[i] != 0)
                colPosition[colSlots[i]] = i + 1;
        long long rowCount = 0, colCount = 0, rowDistance = 0, colDistance = 0;
        for (int i = 1; i <= rows; i++) {
            if (rowPosition[i] != 0) {
                rowCount++;
                rowDistance += abs(i - rowPosition[i]);
            }
        }
        for (int i = 1; i <= cols; i++) {
            if (colPosition[i] != 0) {
                colCount++;
                colDistance += abs(i - colPosition[i]);
            }
        }
        long long keptCells = rowCount * colCount;
        long long totalDistance = colCount * rowDistance + rowCount * colDistance;
        for (const auto& item : changes) {
            int currentRow = item.first.first, currentCol = item.first.second;
            Cell baseCell = getBaseCell(rowSlots, colSlots, currentRow, currentCol);
            if (baseCell.first != 0)
                totalDistance -= getDistance(baseCell, currentRow, currentCol);
            totalDistance += getDistance(item.second, currentRow, currentCol);
            if (baseCell.first != 0)
                keptCells--;
            keptCells++;
            int originalRow = item.second.first, originalCol = item.second.second;
            if (rowPosition[originalRow] != 0 && colPosition[originalCol] != 0) {
                Position sourcePosition = make_pair(rowPosition[originalRow], colPosition[originalCol]);
                if (changes.find(sourcePosition) == changes.end()) {
                    totalDistance -= getDistance(item.second, sourcePosition.first, sourcePosition.second);
                    keptCells--;
                }
            }
        }
        if (caseNumber > 1) cout << '\n';
        cout << "Spreadsheet #" << caseNumber++ << '\n';
        cout << "There are " << keptCells << " cell(s) kept, total distance = " << totalDistance << '\n';
        int queryCount;
        cin >> queryCount;
        for (int i = 0; i < queryCount; i++) {
            int originalRow, originalCol;
            cin >> originalRow >> originalCol;
            Position sourcePosition = make_pair(rowPosition[originalRow], colPosition[originalCol]);
            Position answer = make_pair(0, 0);
            for (const auto& item : changes)
                if (item.second == make_pair(originalRow, originalCol))
                    answer = item.first;
            if (answer.first == 0 && sourcePosition.first != 0 && sourcePosition.second != 0 && changes.find(sourcePosition) == changes.end())
                answer = sourcePosition;
            cout << "Cell data in (" << originalRow << "," << originalCol << ")";
            if (answer.first == 0)
                cout << " GONE\n";
            else
                cout << " moved to (" << answer.first << "," << answer.second << ")\n";
        }
    }
    return 0;
}
