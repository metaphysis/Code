#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double inf = 1e100;

struct Simplex {
    int rowCount, colCount;
    vector<int> rowId, colId;
    vector<vector<double>> table;

    Simplex(const vector<vector<double>> &matrix, const vector<double> &right, const vector<double> &target) {
        rowCount = (int)right.size();
        colCount = (int)target.size();
        rowId.resize(rowCount + 2);
        colId.resize(colCount + 2);
        table.assign(rowCount + 2, vector<double>(colCount + 2, 0));
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < colCount; j++)
                table[i][j] = matrix[i][j];
        for (int i = 0; i < rowCount; i++) {
            rowId[i] = colCount + i;
            table[i][colCount] = -1;
            table[i][colCount + 1] = right[i];
        }
        for (int j = 0; j < colCount; j++) {
            colId[j] = j;
            table[rowCount][j] = -target[j];
        }
        colId[colCount] = -1;
        table[rowCount + 1][colCount] = 1;
    }

    void pivot(int row, int col) {
        double value = 1.0 / table[row][col];
        for (int i = 0; i < rowCount + 2; i++)
            if (i != row)
                for (int j = 0; j < colCount + 2; j++)
                    if (j != col)
                        table[i][j] -= table[row][j] * table[i][col] * value;
        for (int j = 0; j < colCount + 2; j++)
            if (j != col)
                table[row][j] *= value;
        for (int i = 0; i < rowCount + 2; i++)
            if (i != row)
                table[i][col] *= -value;
        table[row][col] = value;
        swap(rowId[row], colId[col]);
    }

    bool runSimplex(int phase) {
        int objectiveRow = phase == 1 ? rowCount + 1 : rowCount;
        while (true) {
            int entering = -1;
            for (int j = 0; j <= colCount; j++) {
                if (phase == 2 && colId[j] == -1)
                    continue;
                if (entering == -1 || table[objectiveRow][j] < table[objectiveRow][entering] - eps || (fabs(table[objectiveRow][j] - table[objectiveRow][entering]) <= eps && colId[j] < colId[entering]))
                    entering = j;
            }
            if (table[objectiveRow][entering] >= -eps)
                return true;
            int leaving = -1;
            for (int i = 0; i < rowCount; i++) {
                if (table[i][entering] <= eps)
                    continue;
                if (leaving == -1)
                    leaving = i;
                else {
                    double first = table[i][colCount + 1] / table[i][entering];
                    double second = table[leaving][colCount + 1] / table[leaving][entering];
                    if (first < second - eps || (fabs(first - second) <= eps && rowId[i] < rowId[leaving]))
                        leaving = i;
                }
            }
            if (leaving == -1)
                return false;
            pivot(leaving, entering);
        }
    }

    double solve(vector<double> &answer) {
        int leaving = 0;
        for (int i = 1; i < rowCount; i++)
            if (table[i][colCount + 1] < table[leaving][colCount + 1])
                leaving = i;
        if (table[leaving][colCount + 1] < -eps) {
            pivot(leaving, colCount);
            if (!runSimplex(1) || table[rowCount + 1][colCount + 1] < -eps)
                return -inf;
            if (fabs(table[rowCount + 1][colCount + 1]) > eps)
                return -inf;
            if (find(colId.begin(), colId.end(), -1) != colId.end()) {
                int column = find(colId.begin(), colId.end(), -1) - colId.begin();
                int row = -1;
                for (int i = 0; i < rowCount; i++)
                    if (rowId[i] == -1)
                        row = i;
                if (row != -1) {
                    int bestColumn = -1;
                    for (int j = 0; j <= colCount; j++)
                        if (bestColumn == -1 || table[row][j] < table[row][bestColumn] - eps)
                            bestColumn = j;
                    if (fabs(table[row][bestColumn]) > eps)
                        pivot(row, bestColumn);
                }
            }
        }
        if (!runSimplex(2))
            return inf;
        answer.assign(colCount, 0);
        for (int i = 0; i < rowCount; i++)
            if (rowId[i] < colCount)
                answer[rowId[i]] = table[i][colCount + 1];
        return table[rowCount][colCount + 1];
    }
};

struct Pipe {
    int from, to, low, high;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int nodeCount, pipeCount;
        cin >> nodeCount >> pipeCount;
        vector<Pipe> pipes(pipeCount);
        for (int i = 0; i < pipeCount; i++)
            cin >> pipes[i].from >> pipes[i].to >> pipes[i].low >> pipes[i].high;
        int variableCount = pipeCount + 2, lowerVariable = pipeCount, upperVariable = pipeCount + 1;
        vector<vector<double>> matrix, balanceMatrix(nodeCount, vector<double>(variableCount, 0));
        vector<double> right, target(variableCount, 0);
        target[lowerVariable] = 1;
        target[upperVariable] = -1;
        for (int i = 0; i < pipeCount; i++) {
            vector<double> line(variableCount, 0);
            line[i] = 1;
            matrix.push_back(line);
            right.push_back(pipes[i].high);
            line.assign(variableCount, 0);
            line[i] = -1;
            matrix.push_back(line);
            right.push_back(-pipes[i].low);
            line.assign(variableCount, 0);
            line[lowerVariable] = 1;
            line[i] = -1;
            matrix.push_back(line);
            right.push_back(0);
            line.assign(variableCount, 0);
            line[i] = 1;
            line[upperVariable] = -1;
            matrix.push_back(line);
            right.push_back(0);
            balanceMatrix[pipes[i].from - 1][i] += -1;
            balanceMatrix[pipes[i].to - 1][i] += 1;
        }
        for (int i = 0; i < nodeCount; i++) {
            matrix.push_back(balanceMatrix[i]);
            right.push_back(0);
            for (int j = 0; j < variableCount; j++)
                balanceMatrix[i][j] *= -1;
            matrix.push_back(balanceMatrix[i]);
            right.push_back(0);
        }
        Simplex simplex(matrix, right, target);
        vector<double> answer;
        double result = simplex.solve(answer);
        cout << "Case " << caseId << ": ";
        if (result <= -inf / 2) {
            cout << "-1\n";
        } else {
            double difference = -result;
            if (fabs(difference) < 0.000005)
                difference = 0;
            cout << fixed << setprecision(5) << difference << '\n';
        }
    }
    return 0;
}
