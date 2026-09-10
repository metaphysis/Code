// Ignore the Blocks 
// UVa ID: 11741
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

const long long modValue = 10000007;
const int maxStateCount = 16;
const int maxPowerCount = 31;

struct Matrix {
    long long value[maxStateCount][maxStateCount];
    Matrix() {
        memset(value, 0, sizeof(value));
    }
};

using State = array<long long, maxStateCount>;

Matrix multiplyMatrix(const Matrix &leftMatrix, const Matrix &rightMatrix) {
    Matrix result;
    for (int i = 0; i < maxStateCount; i++) {
        for (int k = 0; k < maxStateCount; k++) {
            if (leftMatrix.value[i][k] == 0) continue;
            for (int j = 0; j < maxStateCount; j++) {
                if (rightMatrix.value[k][j] == 0) continue;
                result.value[i][j] = (result.value[i][j] + leftMatrix.value[i][k] * rightMatrix.value[k][j]) % modValue;
            }
        }
    }
    return result;
}

State multiplyState(const State &state, const Matrix &matrix) {
    State result{};
    for (int i = 0; i < maxStateCount; i++) {
        if (state[i] == 0) continue;
        for (int j = 0; j < maxStateCount; j++)
            result[j] = (result[j] + state[i] * matrix.value[i][j]) % modValue;
    }
    return result;
}

void enumerateTransition(int rowCount, int inputMask, int obstacleMask, int row, int occupiedMask, int outputMask, Matrix &transition) {
    if (row == rowCount) {
        transition.value[inputMask][outputMask] = (transition.value[inputMask][outputMask] + 1) % modValue;
        return;
    }
    if (occupiedMask & (1 << row)) {
        enumerateTransition(rowCount, inputMask, obstacleMask, row + 1, occupiedMask, outputMask, transition);
        return;
    }
    if (row + 1 < rowCount && !(occupiedMask & (1 << (row + 1))))
        enumerateTransition(rowCount, inputMask, obstacleMask, row + 2, occupiedMask | (1 << row) | (1 << (row + 1)), outputMask, transition);
    enumerateTransition(rowCount, inputMask, obstacleMask, row + 1, occupiedMask | (1 << row), outputMask | (1 << row), transition);
}

Matrix buildTransition(int rowCount, int obstacleMask) {
    Matrix transition;
    for (int inputMask = 0; inputMask < (1 << rowCount); inputMask++) {
        if (inputMask & obstacleMask) continue;
        int occupiedMask = inputMask | obstacleMask;
        enumerateTransition(rowCount, inputMask, obstacleMask, 0, occupiedMask, 0, transition);
    }
    return transition;
}

void applyPower(State &state, const array<Matrix, maxPowerCount> &powers, long long count) {
    int powerIndex = 0;
    while (count > 0) {
        if (count & 1) state = multiplyState(state, powers[powerIndex]);
        count >>= 1;
        powerIndex++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowCount, columnCount, unusableCount;
    int caseNumber = 1;
    while (cin >> rowCount >> columnCount >> unusableCount) {
        if (rowCount == 0 && columnCount == 0 && unusableCount == 0) break;
        map<long long, int> obstacleMap;
        for (int i = 0; i < unusableCount; i++) {
            int row, column;
            cin >> row >> column;
            obstacleMap[column] |= 1 << row;
        }
        int stateCount = 1 << rowCount;
        array<Matrix, maxStateCount> transitions;
        for (int obstacleMask = 0; obstacleMask < stateCount; obstacleMask++)
            transitions[obstacleMask] = buildTransition(rowCount, obstacleMask);
        array<Matrix, maxPowerCount> emptyPowers;
        emptyPowers[0] = transitions[0];
        for (int i = 1; i < maxPowerCount; i++)
            emptyPowers[i] = multiplyMatrix(emptyPowers[i - 1], emptyPowers[i - 1]);
        State dp{};
        dp[0] = 1;
        long long currentColumn = 0;
        for (const auto &event : obstacleMap) {
            long long obstacleColumn = event.first;
            long long emptyColumnCount = obstacleColumn - currentColumn;
            applyPower(dp, emptyPowers, emptyColumnCount);
            dp = multiplyState(dp, transitions[event.second]);
            currentColumn = obstacleColumn + 1;
        }
        applyPower(dp, emptyPowers, static_cast<long long>(columnCount) - currentColumn);
        cout << "Case " << caseNumber << ": " << dp[0] % modValue << '\n';
        caseNumber++;
    }
    return 0;
}
