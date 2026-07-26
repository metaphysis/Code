// Net Loss
// UVa ID: 1074
// Verdict: Accepted
// Submission Date: 2026-07-24
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163174051

#include <bits/stdc++.h>
using namespace std;

long double integratePower(int power, long double left, long double right) {
    return (powl(right, power + 1) - powl(left, power + 1)) / (power + 1);
}

long double integratePolynomial(const vector<long double>& coefficient, int extraPower, long double left, long double right) {
    long double result = 0;
    for (int i = 0; i < static_cast<int>(coefficient.size()); i++)
        result += coefficient[i] * integratePower(i + extraPower, left, right);
    return result;
}

void addInterval(const vector<long double>& coefficient, long double left, long double right, int offset, vector<vector<long double>>& matrix, vector<long double>& rightSide) {
    matrix[offset][offset] += integratePower(2, left, right);
    matrix[offset][offset + 1] += integratePower(1, left, right);
    matrix[offset + 1][offset] += integratePower(1, left, right);
    matrix[offset + 1][offset + 1] += integratePower(0, left, right);
    rightSide[offset] += integratePolynomial(coefficient, 1, left, right);
    rightSide[offset + 1] += integratePolynomial(coefficient, 0, left, right);
}

vector<long double> solveLinearSystem(vector<vector<long double>> matrix, vector<long double> rightSide) {
    int size = static_cast<int>(rightSide.size());
    for (int column = 0; column < size; column++) {
        int pivot = column;
        for (int row = column + 1; row < size; row++)
            if (fabsl(matrix[row][column]) > fabsl(matrix[pivot][column]))
                pivot = row;
        swap(matrix[column], matrix[pivot]);
        swap(rightSide[column], rightSide[pivot]);
        for (int row = column + 1; row < size; row++) {
            long double factor = matrix[row][column] / matrix[column][column];
            for (int j = column; j < size; j++)
                matrix[row][j] -= factor * matrix[column][j];
            rightSide[row] -= factor * rightSide[column];
        }
    }
    vector<long double> answer(size, 0);
    for (int row = size - 1; row >= 0; row--) {
        answer[row] = rightSide[row];
        for (int j = row + 1; j < size; j++)
            answer[row] -= matrix[row][j] * answer[j];
        answer[row] /= matrix[row][row];
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 1;
    int degree;
    while (cin >> degree && degree != 0) {
        vector<long double> coefficient(degree + 1);
        for (int i = degree; i >= 0; i--)
            cin >> coefficient[i];
        long double c;
        cin >> c;
        vector<vector<long double>> matrix(5, vector<long double>(5, 0));
        vector<long double> rightSide(5, 0);
        addInterval(coefficient, -1, c, 0, matrix, rightSide);
        addInterval(coefficient, c, 1, 2, matrix, rightSide);
        matrix[0][4] = c;
        matrix[1][4] = 1;
        matrix[2][4] = -c;
        matrix[3][4] = -1;
        matrix[4][0] = c;
        matrix[4][1] = 1;
        matrix[4][2] = -c;
        matrix[4][3] = -1;
        vector<long double> answer = solveLinearSystem(matrix, rightSide);
        cout << "Case " << caseNumber++ << ":";
        cout << fixed << setprecision(3);
        for (int i = 0; i < 4; i++)
            cout << " " << static_cast<double>(answer[i]);
        cout << '\n';
    }
    return 0;
}
