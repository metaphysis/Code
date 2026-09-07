#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double infValue = 1e100;

class Simplex {
private:
    int rowCount, colCount;
    vector<int> rowBase, colBase;
    vector<vector<double>> table;

    void pivot(int row, int col) {
        double inv = 1.0 / table[row][col];
        for (int i = 0; i < rowCount + 2; i++)
            if (i != row)
                for (int j = 0; j < colCount + 2; j++)
                    if (j != col)
                        table[i][j] -= table[row][j] * table[i][col] * inv;
        for (int j = 0; j < colCount + 2; j++)
            if (j != col)
                table[row][j] *= inv;
        for (int i = 0; i < rowCount + 2; i++)
            if (i != row)
                table[i][col] *= -inv;
        table[row][col] = inv;
        swap(rowBase[row], colBase[col]);
    }

    bool simplex(int phase) {
        int objectiveRow = phase == 1 ? rowCount + 1 : rowCount;
        while (true) {
            int entering = -1;
            for (int j = 0; j <= colCount; j++) {
                if (phase == 2 && colBase[j] == -1)
                    continue;
                if (entering == -1 || table[objectiveRow][j] < table[objectiveRow][entering] - eps || fabs(table[objectiveRow][j] - table[objectiveRow][entering]) <= eps && colBase[j] < colBase[entering])
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
                    if (first < second - eps || fabs(first - second) <= eps && rowBase[i] < rowBase[leaving])
                        leaving = i;
                }
            }
            if (leaving == -1)
                return false;
            pivot(leaving, entering);
        }
    }

public:
    Simplex(const vector<vector<double>> &matrix, const vector<double> &right, const vector<double> &cost) {
        rowCount = right.size();
        colCount = cost.size();
        rowBase.resize(rowCount);
        colBase.resize(colCount + 1);
        table.assign(rowCount + 2, vector<double>(colCount + 2, 0.0));
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < colCount; j++)
                table[i][j] = matrix[i][j];
        for (int i = 0; i < rowCount; i++) {
            rowBase[i] = colCount + i;
            table[i][colCount] = -1.0;
            table[i][colCount + 1] = right[i];
        }
        for (int j = 0; j < colCount; j++) {
            colBase[j] = j;
            table[rowCount][j] = -cost[j];
        }
        colBase[colCount] = -1;
        table[rowCount + 1][colCount] = 1.0;
    }

    double solve(vector<double> &answer) {
        int artificialRow = 0;
        for (int i = 1; i < rowCount; i++)
            if (table[i][colCount + 1] < table[artificialRow][colCount + 1])
                artificialRow = i;
        if (table[artificialRow][colCount + 1] < -eps) {
            pivot(artificialRow, colCount);
            if (!simplex(1) || table[rowCount + 1][colCount + 1] < -eps)
                return -infValue;
            if (fabs(table[rowCount + 1][colCount + 1]) > eps)
                return -infValue;
            if (find(rowBase.begin(), rowBase.end(), -1) != rowBase.end()) {
                int row = find(rowBase.begin(), rowBase.end(), -1) - rowBase.begin();
                int col = -1;
                for (int j = 0; j <= colCount; j++)
                    if (table[row][j] < -eps && (col == -1 || table[row][j] < table[row][col]))
                        col = j;
                if (col != -1)
                    pivot(row, col);
            }
        }
        if (!simplex(2))
            return infValue;
        answer.assign(colCount, 0.0);
        for (int i = 0; i < rowCount; i++)
            if (rowBase[i] < colCount)
                answer[rowBase[i]] = table[i][colCount + 1];
        return table[rowCount][colCount + 1];
    }
};

struct Edge {
    int from, to, low, high, cost;
};

void addInequality(vector<vector<double>> &matrix, vector<double> &right, const vector<double> &coeff, double value) {
    matrix.push_back(coeff);
    right.push_back(value);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 1;
    while (true) {
        int n, m, k;
        cin >> n;
        if (n == 0)
            break;
        cin >> m >> k;
        vector<Edge> edges(k);
        int variableCount = k + 1;
        double fixedCost = 0.0;
        for (int i = 0; i < k; i++) {
            cin >> edges[i].from >> edges[i].to >> edges[i].low >> edges[i].high >> edges[i].cost;
            fixedCost += 1.0 * edges[i].low * edges[i].cost;
        }
        vector<vector<double>> matrix;
        vector<double> right;
        for (int vertex = 1; vertex <= n + m; vertex++) {
            vector<double> equation(variableCount, 0.0);
            double value = 0.0;
            for (int i = 0; i < k; i++) {
                int coefficient = 0;
                if (edges[i].to == vertex)
                    coefficient++;
                if (edges[i].from == vertex)
                    coefficient--;
                if (coefficient != 0) {
                    equation[i] = coefficient;
                    value -= 1.0 * coefficient * edges[i].low;
                }
            }
            if (vertex <= n)
                equation[k] = -1.0;
            addInequality(matrix, right, equation, value);
            for (int i = 0; i < variableCount; i++)
                equation[i] = -equation[i];
            addInequality(matrix, right, equation, -value);
        }
        for (int i = 0; i < k; i++) {
            vector<double> equation(variableCount, 0.0);
            equation[i] = 1.0;
            addInequality(matrix, right, equation, edges[i].high - edges[i].low);
        }
        vector<double> speedLimit(variableCount, 0.0);
        speedLimit[k] = 1.0;
        addInequality(matrix, right, speedLimit, 100.0 * k);
        vector<double> objective(variableCount, 0.0);
        for (int i = 0; i < k; i++)
            objective[i] = -edges[i].cost;
        Simplex simplex(matrix, right, objective);
        vector<double> answer;
        double bestValue = simplex.solve(answer);
        double minCost = fixedCost - bestValue;
        if (fabs(minCost) < 0.005)
            minCost = 0.0;
        cout << "Case " << caseId++ << ": " << fixed << setprecision(2) << minCost << '\n';
    }
    return 0;
}
