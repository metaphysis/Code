#include <bits/stdc++.h>
using namespace std;

const int Inf = 1000000007;

int modValue(long long value, int mod) {
    value %= mod;
    if (value < 0)
        value += mod;
    return (int)value;
}

void gauss(vector<vector<int>>& matrix, int varCount, int mod) {
    int i, j, k, row, rate, temp;
    for (i = 0; i < varCount; i++) {
        row = i;
        for (j = i + 1; j < varCount; j++)
            if (matrix[j][i] != 0)
                row = j;
        if (matrix[row][i] == 0)
            continue;
        if (row != i) {
            for (k = 0; k <= varCount; k++)
                swap(matrix[i][k], matrix[row][k]);
        }
        for (j = i + 1; j < varCount; j++) {
            while (matrix[j][i] != 0) {
                rate = matrix[i][i] / matrix[j][i];
                for (k = 0; k <= varCount; k++) {
                    temp = matrix[j][k];
                    matrix[j][k] = modValue((long long)matrix[i][k] - (long long)rate * matrix[j][k], mod);
                    matrix[i][k] = temp;
                }
            }
        }
    }
}

void dfs(int pos, int varCount, int mod, const vector<vector<int>>& matrix, vector<int>& value, int sum, int& answer) {
    int i, j, now;
    if (sum >= answer)
        return;
    if (pos == -1) {
        answer = sum;
        return;
    }
    for (i = 0; i < mod; i++) {
        value[pos] = i;
        now = 0;
        for (j = pos; j < varCount; j++)
            now = modValue((long long)now + (long long)matrix[pos][j] * value[j], mod);
        if (now == matrix[pos][varCount])
            dfs(pos - 1, varCount, mod, matrix, value, sum + i, answer);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int varCount, mod, i, j, count, gear, rotate, answer;
    while (cin >> varCount >> mod) {
        if (varCount == 0 && mod == 0)
            break;
        vector<vector<int>> matrix(varCount, vector<int>(varCount + 1, 0));
        vector<int> value(varCount, 0);
        for (i = 0; i < varCount; i++) {
            cin >> count;
            matrix[i][varCount] = modValue(mod + 1 - count, mod);
        }
        for (i = 0; i < varCount; i++) {
            cin >> count;
            for (j = 0; j < count; j++) {
                cin >> gear >> rotate;
                matrix[gear - 1][i] = modValue(rotate, mod);
            }
        }
        gauss(matrix, varCount, mod);
        answer = Inf;
        dfs(varCount - 1, varCount, mod, matrix, value, 0, answer);
        if (answer == Inf)
            cout << "No solution\n";
        else
            cout << answer << '\n';
    }
    return 0;
}
