#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9, inf = 1.0 / 0.0;

struct LpSolver {
    int rowCount, colCount;
    vector<int> base, nonBase;
    vector<vector<double>> table;

    LpSolver(const vector<vector<double>> &matrix, const vector<double> &right, const vector<double> &cost) {
        rowCount = right.size();
        colCount = cost.size();
        base.resize(rowCount);
        nonBase.resize(colCount + 1);
        table.assign(rowCount + 2, vector<double>(colCount + 2));
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < colCount; j++)
                table[i][j] = matrix[i][j];
        for (int i = 0; i < rowCount; i++) {
            base[i] = colCount + i;
            table[i][colCount] = -1;
            table[i][colCount + 1] = right[i];
        }
        for (int j = 0; j < colCount; j++) {
            nonBase[j] = j;
            table[rowCount][j] = -cost[j];
        }
        nonBase[colCount] = -1;
        table[rowCount + 1][colCount] = 1;
    }

    void pivot(int pivotRow, int pivotCol) {
        double inverse = 1.0 / table[pivotRow][pivotCol];
        for (int i = 0; i < rowCount + 2; i++)
            if (i != pivotRow)
                for (int j = 0; j < colCount + 2; j++)
                    if (j != pivotCol)
                        table[i][j] -= table[pivotRow][j] * table[i][pivotCol] * inverse;
        for (int j = 0; j < colCount + 2; j++)
            if (j != pivotCol)
                table[pivotRow][j] *= inverse;
        for (int i = 0; i < rowCount + 2; i++)
            if (i != pivotRow)
                table[i][pivotCol] *= -inverse;
        table[pivotRow][pivotCol] = inverse;
        swap(base[pivotRow], nonBase[pivotCol]);
    }

    bool simplex(int phase) {
        int objectiveRow = phase == 1 ? rowCount + 1 : rowCount;
        while (true) {
            int enteringCol = -1;
            for (int j = 0; j <= colCount; j++) {
                if (phase == 2 && nonBase[j] == -1)
                    continue;
                if (enteringCol == -1 || table[objectiveRow][j] < table[objectiveRow][enteringCol] - eps || fabs(table[objectiveRow][j] - table[objectiveRow][enteringCol]) <= eps && nonBase[j] < nonBase[enteringCol])
                    enteringCol = j;
            }
            if (table[objectiveRow][enteringCol] >= -eps)
                return true;
            int leavingRow = -1;
            for (int i = 0; i < rowCount; i++) {
                if (table[i][enteringCol] <= eps)
                    continue;
                if (leavingRow == -1)
                    leavingRow = i;
                else {
                    double firstValue = table[i][colCount + 1] / table[i][enteringCol];
                    double secondValue = table[leavingRow][colCount + 1] / table[leavingRow][enteringCol];
                    if (firstValue < secondValue - eps || fabs(firstValue - secondValue) <= eps && base[i] < base[leavingRow])
                        leavingRow = i;
                }
            }
            if (leavingRow == -1)
                return false;
            pivot(leavingRow, enteringCol);
        }
    }

    double solve(vector<double> &answer) {
        int minimumRow = 0;
        for (int i = 1; i < rowCount; i++)
            if (table[i][colCount + 1] < table[minimumRow][colCount + 1])
                minimumRow = i;
        if (table[minimumRow][colCount + 1] < -eps) {
            pivot(minimumRow, colCount);
            if (!simplex(1) || table[rowCount + 1][colCount + 1] < -eps)
                return -inf;
            if (fabs(table[rowCount + 1][colCount + 1]) > eps)
                return -inf;
            for (int i = 0; i < rowCount; i++)
                if (base[i] == -1) {
                    int enteringCol = -1;
                    for (int j = 0; j <= colCount; j++)
                        if (enteringCol == -1 || table[i][j] < table[i][enteringCol] - eps || fabs(table[i][j] - table[i][enteringCol]) <= eps && nonBase[j] < nonBase[enteringCol])
                            enteringCol = j;
                    pivot(i, enteringCol);
                }
        }
        if (!simplex(2))
            return inf;
        answer.assign(colCount, 0);
        for (int i = 0; i < rowCount; i++)
            if (base[i] < colCount)
                answer[base[i]] = table[i][colCount + 1];
        return table[rowCount][colCount + 1];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 1;
    int n, low, high;
    while (cin >> n) {
        if (n == 0)
            break;
        cin >> low >> high;
        vector<vector<double>> matrix;
        vector<double> right;
        for (int i = 0; i < n; i++) {
            int water, milk, wine, price;
            cin >> water >> milk >> wine >> price;
            vector<double> row(3);
            row[0] = water + milk + wine;
            row[1] = milk + wine;
            row[2] = wine;
            matrix.push_back(row);
            right.push_back(price - low);
            for (int j = 0; j < 3; j++)
                row[j] = -row[j];
            matrix.push_back(row);
            right.push_back(-(price - high));
        }
        int water, milk, wine;
        cin >> water >> milk >> wine;
        vector<double> cost(3);
        cost[0] = water + milk + wine;
        cost[1] = milk + wine;
        cost[2] = wine;
        LpSolver solver(matrix, right, cost);
        vector<double> answer;
        double result = solver.solve(answer);
        cout << "Case " << caseNumber++ << ": ";
        if (result == -inf)
            cout << "Inconsistent data\n";
        else if (result == inf)
            cout << "Too expensive!\n";
        else
            cout << fixed << setprecision(4) << result + high << '\n';
    }
    return 0;
}
