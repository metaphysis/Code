#include <bits/stdc++.h>
using namespace std;

const int modVal = 2011;
vector<string> grid;

int modPow(int base, int expVal) {
    int res = 1;
    while (expVal > 0) {
        if (expVal & 1) res = res * base % modVal;
        base = base * base % modVal;
        expVal >>= 1;
    }
    return res;
}

int eval(int top, int bottom, int left, int right);

struct Parser {
    int top, bottom, right, baseRow, pos;
    Parser(int topVal, int bottomVal, int rightVal, int rowVal, int leftVal)
        : top(topVal), bottom(bottomVal), right(rightVal), baseRow(rowVal), pos(leftVal) {}
    void skipDots() {
        while (pos <= right && grid[baseRow][pos] == '.') ++pos;
    }

    int parseExpr() {
        int res = parseTerm(), val;
        char op;
        skipDots();
        while (pos <= right && (grid[baseRow][pos] == '+' || grid[baseRow][pos] == '-')) {
            op = grid[baseRow][pos++];
            val = parseTerm();
            if (op == '+') res = (res + val) % modVal;
            else res = (res - val + modVal) % modVal;
            skipDots();
        }
        return res;
    }

    int parseTerm() {
        int res = parseFactor();
        skipDots();
        while (pos <= right && grid[baseRow][pos] == '*') {
            ++pos;
            res = res * parseFactor() % modVal;
            skipDots();
        }
        return res;
    }

    int parseFactor() {
        skipDots();
        if (grid[baseRow][pos] == '-' && (pos == right || grid[baseRow][pos + 1] != '-')) {
            ++pos;
            return (modVal - parseFactor()) % modVal;
        }
        return parsePower();
    }

    int parsePower() {
        int res = parsePrimary(), expVal;
        if (baseRow > top && pos <= right && grid[baseRow - 1][pos] >= '0' && grid[baseRow - 1][pos] <= '9') {
            expVal = grid[baseRow - 1][pos] - '0';
            ++pos;
            res = modPow(res, expVal);
        }
        return res;
    }

    int parsePrimary() {
        int res, start, numerator, denominator;
        skipDots();
        if (grid[baseRow][pos] >= '0' && grid[baseRow][pos] <= '9') return grid[baseRow][pos++] - '0';
        if (grid[baseRow][pos] == '(') {
            ++pos;
            res = parseExpr();
            skipDots();
            ++pos;
            return res;
        }
        start = pos;
        while (pos <= right && grid[baseRow][pos] == '-') ++pos;
        numerator = eval(top, baseRow - 1, start, pos - 1);
        denominator = eval(baseRow + 1, bottom, start, pos - 1);
        return numerator * modPow(denominator, modVal - 2) % modVal;
    }
};

int eval(int top, int bottom, int left, int right) {
    int minRow = bottom + 1, maxRow = top - 1, minCol = right + 1, maxCol = left - 1, baseRow;
    for (int row = top; row <= bottom; ++row) {
        for (int col = left; col <= right; ++col) {
            if (grid[row][col] != '.') {
                minRow = min(minRow, row);
                maxRow = max(maxRow, row);
                minCol = min(minCol, col);
                maxCol = max(maxCol, col);
            }
        }
    }
    baseRow = minRow;
    while (grid[baseRow][minCol] == '.') ++baseRow;
    Parser parser(minRow, maxRow, maxCol, baseRow, minCol);
    return parser.parseExpr();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowCount;
    while (cin >> rowCount && rowCount != 0) {
        grid.resize(rowCount);
        for (int row = 0; row < rowCount; ++row) cin >> grid[row];
        cout << eval(0, rowCount - 1, 0, static_cast<int>(grid[0].size()) - 1) << '\n';
    }
    return 0;
}
