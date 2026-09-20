#include <bits/stdc++.h>
using namespace std;

void getCoord(int square, int &row, int &col) {
    int index = square - 1;
    row = index / 4;
    int pos = index % 4;
    col = 2 * pos + (row % 2 == 0 ? 1 : 0);
}

int getSquare(int row, int col) {
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return -1;
    if ((row + col) % 2 == 0)
        return -1;
    int offset = row % 2 == 0 ? 1 : 0;
    if (col < offset || (col - offset) % 2 != 0)
        return -1;
    int pos = (col - offset) / 2;
    if (pos < 0 || pos >= 4)
        return -1;
    return row * 4 + pos + 1;
}

bool isKing(int piece) {
    return piece == 2 || piece == 4;
}

bool isOwn(int piece, char color) {
    if (color == 'R')
        return piece == 1 || piece == 2;
    return piece == 3 || piece == 4;
}

char getColor(int piece) {
    if (piece == 1 || piece == 2)
        return 'R';
    return 'W';
}

int getKingCode(char color) {
    return color == 'R' ? 2 : 4;
}

bool hasJump(const vector<int> &board, int square, char color) {
    int piece = board[square], row, col;
    if (!isOwn(piece, color))
        return false;
    getCoord(square, row, col);
    int forward = color == 'R' ? 1 : -1;
    int start = isKing(piece) ? 0 : (forward == 1 ? 1 : 0);
    int end = isKing(piece) ? 2 : (forward == 1 ? 2 : 1);
    int dirRow[2] = {-1, 1}, dirCol[2] = {-1, 1};
    for (int i = start; i < end; i++) {
        int nextRow = row + dirRow[i] * 2, nextCol;
        for (int j = 0; j < 2; j++) {
            nextCol = col + dirCol[j] * 2;
            int middleSquare = getSquare(row + dirRow[i], col + dirCol[j]);
            int nextSquare = getSquare(nextRow, nextCol);
            if (middleSquare != -1 && nextSquare != -1 && board[middleSquare] != 0 && !isOwn(board[middleSquare], color) && board[nextSquare] == 0)
                return true;
        }
    }
    return false;
}

bool hasAnyJump(const vector<int> &board, char color) {
    for (int square = 1; square <= 32; square++)
        if (hasJump(board, square, color))
            return true;
    return false;
}

vector<int> parseMove(const string &text) {
    vector<int> path;
    string token;
    stringstream stream(text);
    while (getline(stream, token, '-')) {
        if (token.empty())
            return vector<int>();
        path.push_back(stoi(token));
    }
    return path;
}

bool applySimple(vector<int> &board, const vector<int> &path, char color) {
    if (path.size() != 2)
        return false;
    int startSquare = path[0], endSquare = path[1];
    if (startSquare < 1 || startSquare > 32 || endSquare < 1 || endSquare > 32)
        return false;
    int piece = board[startSquare], startRow, startCol, endRow, endCol;
    if (!isOwn(piece, color) || board[endSquare] != 0)
        return false;
    getCoord(startSquare, startRow, startCol);
    getCoord(endSquare, endRow, endCol);
    if (abs(endRow - startRow) != 1 || abs(endCol - startCol) != 1)
        return false;
    if (!isKing(piece)) {
        int forward = color == 'R' ? 1 : -1;
        if (endRow - startRow != forward)
            return false;
    }
    board[startSquare] = 0;
    board[endSquare] = piece;
    int promotionRow = color == 'R' ? 7 : 0;
    if (endRow == promotionRow)
        board[endSquare] = getKingCode(color);
    return true;
}

bool applyJump(vector<int> &board, const vector<int> &path, char color) {
    if (path.size() < 2)
        return false;
    int currentSquare = path[0];
    int piece = board[currentSquare];
    if (currentSquare < 1 || currentSquare > 32 || !isOwn(piece, color))
        return false;
    for (int i = 1; i < static_cast<int>(path.size()); i++) {
        int nextSquare = path[i];
        int currentRow, currentCol, nextRow, nextCol;
        if (nextSquare < 1 || nextSquare > 32)
            return false;
        getCoord(currentSquare, currentRow, currentCol);
        getCoord(nextSquare, nextRow, nextCol);
        if (abs(nextRow - currentRow) != 2 || abs(nextCol - currentCol) != 2)
            return false;
        if (!isKing(piece)) {
            int forward = color == 'R' ? 1 : -1;
            if (nextRow - currentRow != forward * 2)
                return false;
        }
        int middleRow = (currentRow + nextRow) / 2, middleCol = (currentCol + nextCol) / 2;
        int middleSquare = getSquare(middleRow, middleCol);
        if (middleSquare == -1 || board[middleSquare] == 0 || isOwn(board[middleSquare], color) || board[nextSquare] != 0)
            return false;
        board[currentSquare] = 0;
        board[middleSquare] = 0;
        board[nextSquare] = piece;
        currentSquare = nextSquare;
        int promotionRow = color == 'R' ? 7 : 0;
        if (!isKing(piece) && nextRow == promotionRow) {
            piece = getKingCode(color);
            board[currentSquare] = piece;
            if (i != static_cast<int>(path.size()) - 1)
                return false;
            return true;
        }
        if (i == static_cast<int>(path.size()) - 1) {
            if (hasJump(board, currentSquare, color))
                return false;
        } else if (!hasJump(board, currentSquare, color)) {
            return false;
        }
    }
    return true;
}

bool applyMove(vector<int> &board, const vector<int> &path, char color) {
    if (path.empty())
        return false;
    if (hasAnyJump(board, color)) {
        if (path.size() < 2)
            return false;
        int startRow, startCol, endRow, endCol;
        getCoord(path[0], startRow, startCol);
        getCoord(path[1], endRow, endCol);
        if (abs(endRow - startRow) != 2 || abs(endCol - startCol) != 2)
            return false;
        return applyJump(board, path, color);
    }
    if (path.size() == 2) {
        vector<int> tempBoard = board;
        if (applySimple(tempBoard, path, color)) {
            board = tempBoard;
            return true;
        }
    }
    if (path.size() >= 2) {
        vector<int> tempBoard = board;
        if (applyJump(tempBoard, path, color)) {
            board = tempBoard;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, w;
    while (cin >> r >> w && (r != 0 || w != 0)) {
        vector<int> board(33, 0);
        for (int i = 0; i < r; i++) {
            int square;
            cin >> square;
            board[abs(square)] = square < 0 ? 2 : 1;
        }
        for (int i = 0; i < w; i++) {
            int square;
            cin >> square;
            board[abs(square)] = square < 0 ? 4 : 3;
        }
        int moveCount;
        char color;
        cin >> moveCount >> color;
        int invalidMove = 0;
        for (int i = 1; i <= moveCount; i++) {
            string moveText;
            cin >> moveText;
            if (invalidMove != 0)
                continue;
            vector<int> path;
            try {
                path = parseMove(moveText);
            } catch (...) {
                invalidMove = i;
                continue;
            }
            vector<int> checkedPath;
            bool validPath = true;
            for (int square : path) {
                if (square < 1 || square > 32) {
                    validPath = false;
                    break;
                }
                checkedPath.push_back(square);
            }
            if (!validPath || !applyMove(board, checkedPath, color))
                invalidMove = i;
            else
                color = color == 'R' ? 'W' : 'R';
        }
        if (invalidMove == 0)
            cout << "All moves valid\n";
        else
            cout << "Move " << invalidMove << " is invalid\n";
    }
    return 0;
}
