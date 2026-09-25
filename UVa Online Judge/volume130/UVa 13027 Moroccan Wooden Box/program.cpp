#include <bits/stdc++.h>
using namespace std;

const double jacStep = 1e-7;
const double eps = 1e-8;

bool solveSquare(vector<vector<double>> matrix, vector<double> &answer) {
    int n = matrix.size();
    answer.assign(n, 0.0);
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(matrix[j][i]) > fabs(matrix[pivot][i]))
                pivot = j;
        if (fabs(matrix[pivot][i]) < 1e-12)
            return false;
        swap(matrix[i], matrix[pivot]);
        double divisor = matrix[i][i];
        for (int j = i; j <= n; j++)
            matrix[i][j] /= divisor;
        for (int j = 0; j < n; j++) {
            if (j == i)
                continue;
            double factor = matrix[j][i];
            for (int k = i; k <= n; k++)
                matrix[j][k] -= factor * matrix[i][k];
        }
    }
    for (int i = 0; i < n; i++)
        answer[i] = matrix[i][n];
    return true;
}

bool solveLeastSquares(const vector<vector<double>> &matrix, vector<double> &answer) {
    int rowCount = matrix.size();
    int columnCount = matrix[0].size() - 1;
    if (rowCount < columnCount)
        return false;
    vector<vector<double>> normalMatrix(columnCount, vector<double>(columnCount + 1, 0.0));
    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            for (int k = 0; k < rowCount; k++)
                normalMatrix[i][j] += matrix[k][i] * matrix[k][j];
        }
        for (int k = 0; k < rowCount; k++)
            normalMatrix[i][columnCount] += matrix[k][i] * matrix[k][columnCount];
    }
    for (int i = 0; i < columnCount; i++)
        normalMatrix[i][i] += 1e-12;
    return solveSquare(normalMatrix, answer);
}

double getNorm(const vector<double> &value) {
    double result = 0.0;
    for (double item : value)
        result += item * item;
    return sqrt(result);
}

double getDistance(const vector<double> &value, int first, int second) {
    double dx, dy;
    dx = value[1 + first * 2] - value[1 + second * 2];
    dy = value[2 + first * 2] - value[2 + second * 2];
    return sqrt(dx * dx + dy * dy);
}

void addDistanceEquation(vector<double> &equation, const vector<double> &value, int first, int second) {
    double dx, dy;
    dx = value[1 + first * 2] - value[1 + second * 2];
    dy = value[2 + first * 2] - value[2 + second * 2];
    equation.push_back(dx * dx + dy * dy - 4.0);
}

void addEquation7(const vector<double> &value, vector<double> &equation) {
    double side = value[0];
    equation.clear();
    equation.push_back(value[1] - 1.0);
    equation.push_back(value[2] - 1.0);
    equation.push_back(value[5] - side + 1.0);
    equation.push_back(value[6] - 1.0);
    equation.push_back(value[7] - side + 1.0);
    equation.push_back(value[8] - 3.0);
    equation.push_back(value[11] - 1.0);
    equation.push_back(value[14] - side + 1.0);
    addDistanceEquation(equation, value, 0, 1);
    addDistanceEquation(equation, value, 1, 2);
    addDistanceEquation(equation, value, 2, 3);
    addDistanceEquation(equation, value, 1, 4);
    addDistanceEquation(equation, value, 3, 4);
    addDistanceEquation(equation, value, 4, 5);
    addDistanceEquation(equation, value, 4, 6);
    addDistanceEquation(equation, value, 5, 6);
}

void addEquation8(const vector<double> &value, vector<double> &equation) {
    double side = value[0];
    equation.clear();
    equation.push_back(value[1] - 1.0);
    equation.push_back(value[2] - 1.0);
    equation.push_back(value[3] - side + 1.0);
    equation.push_back(value[4] - 1.0);
    equation.push_back(value[12] - side + 1.0);
    equation.push_back(value[13] - 1.0);
    equation.push_back(value[15] - 1.0);
    equation.push_back(value[16] - side + 1.0);
    addDistanceEquation(equation, value, 0, 2);
    addDistanceEquation(equation, value, 1, 3);
    addDistanceEquation(equation, value, 2, 3);
    addDistanceEquation(equation, value, 2, 4);
    addDistanceEquation(equation, value, 3, 4);
    addDistanceEquation(equation, value, 4, 5);
    addDistanceEquation(equation, value, 2, 6);
    addDistanceEquation(equation, value, 5, 7);
    addDistanceEquation(equation, value, 6, 7);
}

bool isTouchPair(int first, int second, bool isSeven) {
    if (isSeven) {
        int firstList[] = {0, 1, 2, 1, 3, 4, 4, 5};
        int secondList[] = {1, 2, 3, 4, 4, 5, 6, 6};
        for (int i = 0; i < 8; i++)
            if ((firstList[i] == first && secondList[i] == second) || (firstList[i] == second && secondList[i] == first))
                return true;
    } else {
        int firstList[] = {0, 1, 2, 2, 3, 4, 2, 5, 6};
        int secondList[] = {2, 3, 3, 4, 4, 5, 6, 7, 7};
        for (int i = 0; i < 9; i++)
            if ((firstList[i] == first && secondList[i] == second) || (firstList[i] == second && secondList[i] == first))
                return true;
    }
    return false;
}

bool checkRigid(const vector<double> &value, int ballCount, bool isSeven) {
    vector<double> equation, nextEquation;
    if (isSeven)
        addEquation7(value, equation);
    else
        addEquation8(value, equation);
    int equationCount = equation.size(), variableCount = ballCount * 2;
    vector<vector<double>> matrix(equationCount, vector<double>(variableCount, 0.0));
    for (int i = 0; i < variableCount; i++) {
        vector<double> nextValue = value;
        nextValue[i + 1] += jacStep;
        if (isSeven)
            addEquation7(nextValue, nextEquation);
        else
            addEquation8(nextValue, nextEquation);
        for (int j = 0; j < equationCount; j++)
            matrix[j][i] = (nextEquation[j] - equation[j]) / jacStep;
    }
    int rank = 0;
    for (int column = 0; column < variableCount && rank < equationCount; column++) {
        int pivot = rank;
        for (int row = rank + 1; row < equationCount; row++)
            if (fabs(matrix[row][column]) > fabs(matrix[pivot][column]))
                pivot = row;
        if (fabs(matrix[pivot][column]) < 1e-7)
            continue;
        swap(matrix[pivot], matrix[rank]);
        for (int row = rank + 1; row < equationCount; row++) {
            double factor = matrix[row][column] / matrix[rank][column];
            for (int i = column; i < variableCount; i++)
                matrix[row][i] -= factor * matrix[rank][i];
        }
        rank++;
    }
    return rank >= variableCount;
}

bool checkValid(const vector<double> &value, int ballCount, bool isSeven) {
    double side = value[0];
    if (side <= 2.0)
        return false;
    for (int i = 0; i < ballCount; i++) {
        double x = value[1 + i * 2], y = value[2 + i * 2];
        if (x < 1.0 - 1e-6 || x > side - 1.0 + 1e-6)
            return false;
        if (y < 1.0 - 1e-6 || y > side - 1.0 + 1e-6)
            return false;
        for (int j = i + 1; j < ballCount; j++) {
            double distance = getDistance(value, i, j);
            if (!isTouchPair(i, j, isSeven) && distance < 2.0 - 1e-6)
                return false;
        }
    }
    if (isSeven) {
        if (value[4] <= value[2] + 1e-6)
            return false;
        if (value[8] <= value[6] + 1e-6)
            return false;
        if (value[10] <= value[8] + 1e-6)
            return false;
    } else {
        if (value[5] <= value[1] + 1e-6)
            return false;
        if (value[7] >= value[3] - 1e-6)
            return false;
        if (value[14] <= value[6] + 1e-6)
            return false;
    }
    return checkRigid(value, ballCount, isSeven);
}

bool findRoot(bool isSeven, vector<double> &bestValue) {
    int ballCount = isSeven ? 7 : 8;
    int variableCount = 1 + ballCount * 2;
    int attemptCount = isSeven ? 3000 : 5000;
    mt19937 randomEngine(isSeven ? 712367 : 912367);
    uniform_real_distribution<double> sideDistribution(4.0, 8.0);
    uniform_real_distribution<double> positionDistribution(1.0, 7.0);
    double bestSide = -1.0;
    for (int attempt = 0; attempt < attemptCount; attempt++) {
        vector<double> value(variableCount);
        value[0] = sideDistribution(randomEngine);
        for (int i = 0; i < ballCount; i++) {
            value[1 + i * 2] = min(value[0] - 1.0, positionDistribution(randomEngine));
            value[2 + i * 2] = min(value[0] - 1.0, positionDistribution(randomEngine));
        }
        vector<double> equation, nextEquation;
        bool converged = false;
        for (int iteration = 0; iteration < 150; iteration++) {
            if (isSeven)
                addEquation7(value, equation);
            else
                addEquation8(value, equation);
            double error = getNorm(equation);
            if (error < 1e-9) {
                converged = true;
                break;
            }
            int equationCount = equation.size();
            vector<vector<double>> matrix(equationCount, vector<double>(variableCount + 1, 0.0));
            for (int i = 0; i < variableCount; i++) {
                vector<double> nextValue = value;
                nextValue[i] += jacStep;
                if (isSeven)
                    addEquation7(nextValue, nextEquation);
                else
                    addEquation8(nextValue, nextEquation);
                for (int j = 0; j < equationCount; j++)
                    matrix[j][i] = (nextEquation[j] - equation[j]) / jacStep;
            }
            for (int i = 0; i < equationCount; i++)
                matrix[i][variableCount] = -equation[i];
            vector<double> delta;
            if (!solveLeastSquares(matrix, delta))
                break;
            double step = 1.0;
            bool improved = false;
            while (step > 1e-5) {
                vector<double> candidate = value;
                for (int i = 0; i < variableCount; i++)
                    candidate[i] += delta[i] * step;
                if (isSeven)
                    addEquation7(candidate, nextEquation);
                else
                    addEquation8(candidate, nextEquation);
                if (getNorm(nextEquation) < error) {
                    value = candidate;
                    improved = true;
                    break;
                }
                step *= 0.5;
            }
            if (!improved)
                break;
        }
        if (!converged || !checkValid(value, ballCount, isSeven))
            continue;
        if (value[0] > bestSide) {
            bestSide = value[0];
            bestValue = value;
        }
    }
    return bestSide > 0.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // vector<double> value7, value8;
    // if (!findRoot(true, value7) || !findRoot(false, value8)) return 0;
    // cout << fixed << setprecision(12) << value7[0] << '\n' << value8[0] << '\n';
    // double side7 = value7[0], side8 = value8[0];
    double side7 = 5.985012988387, side8 = 6.946997199143;
    double r, w;
    while (cin >> r >> w) {
        double height = 2.0 * r + 2.0 * w;
        double outerSide7 = side7 * r + 2.0 * w;
        double outerSide8 = side8 * r + 2.0 * w;
        double volume7 = outerSide7 * outerSide7 * height;
        double volume8 = outerSide8 * outerSide8 * height;
        cout << fixed << setprecision(4) << volume7 << " " << volume8 << '\n';
    }
    return 0;
}
