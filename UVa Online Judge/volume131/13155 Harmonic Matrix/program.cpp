#include <bits/stdc++.h>
using namespace std;

struct Operation {
    int r1, c1, r2, c2;
};

int rowCount, colCount;
int matrixData[1005][1005];
vector<Operation> operations;

void swapCell(int r1, int c1, int r2, int c2) {
    swap(matrixData[r1][c1], matrixData[r2][c2]);
    operations.push_back({r1 + 1, c1 + 1, r2 + 1, c2 + 1});
}

void horizontalStage(int startCol) {
    for (int r = 0; r < rowCount; r++)
        for (int c = startCol; c + 1 < colCount; c += 2) {
            bool needSwap = (c % 2 == 0 && matrixData[r][c] > matrixData[r][c + 1]) || (c % 2 == 1 && matrixData[r][c] < matrixData[r][c + 1]);
            if (needSwap)
                swapCell(r, c, r, c + 1);
        }
}

void verticalStage(int startRow) {
    for (int r = startRow; r + 1 < rowCount; r += 2)
        for (int c = 0; c < colCount; c++) {
            bool needSwap = (r % 2 == 0 && matrixData[r][c] > matrixData[r + 1][c]) || (r % 2 == 1 && matrixData[r][c] < matrixData[r + 1][c]);
            if (needSwap)
                swapCell(r, c, r + 1, c);
        }
}

void solveCase() {
    operations.clear();
    horizontalStage(0);
    verticalStage(0);
    horizontalStage(1);
    verticalStage(1);
    horizontalStage(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        cin >> rowCount >> colCount;
        for (int r = 0; r < rowCount; r++)
            for (int c = 0; c < colCount; c++)
                cin >> matrixData[r][c];
        solveCase();
        cout << "Case " << caseId << ":\n";
        cout << operations.size() << '\n';
        for (const Operation &operation : operations)
            cout << operation.r1 << ' ' << operation.c1 << ' ' << operation.r2 << ' ' << operation.c2 << '\n';
    }
    return 0;
}
