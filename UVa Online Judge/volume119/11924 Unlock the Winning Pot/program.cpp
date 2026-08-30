#include <bits/stdc++.h>
using namespace std;

const int maxStep = 1 << 24;
const int blockSize = 1 << 12;

struct Matrix {
    int size;
    vector<vector<int> > value;
};

int getColor(char ch) {
    if (ch == 'R') return 0;
    if (ch == 'B') return 1;
    return 2;
}

int getValue(uint64_t state, int index) {
    return static_cast<int>((state >> (2 * index)) & 3ULL);
}

uint64_t applySwitch(uint64_t state, int rowCount, int columnCount, const vector<int>& source) {
    int total = rowCount * columnCount, i, j, index, below, right;
    uint64_t result = 0;
    for (i = 0; i < total; ++i)
        result |= static_cast<uint64_t>(getValue(state, source[i])) << (2 * i);
    for (i = 0; i < rowCount - 1; ++i) {
        for (j = 0; j < columnCount - 1; ++j) {
            if ((i + j) % 2 != 0) continue;
            index = i * columnCount + j;
            below = (i + 1) * columnCount + j;
            right = i * columnCount + j + 1;
            int currentColor = getValue(result, index), belowColor = getValue(result, below), rightColor = getValue(result, right);
            int newColor = (currentColor + belowColor + rightColor) % 3;
            result &= ~(3ULL << (2 * index));
            result |= static_cast<uint64_t>(newColor) << (2 * index);
        }
    }
    return result;
}

Matrix multiply(const Matrix& left, const Matrix& right) {
    int size = left.size, i, j, k;
    Matrix result;
    result.size = size;
    result.value.assign(size, vector<int>(size, 0));
    for (i = 0; i < size; ++i) {
        for (k = 0; k < size; ++k) {
            if (left.value[i][k] == 0) continue;
            for (j = 0; j < size; ++j)
                result.value[i][j] = (result.value[i][j] + left.value[i][k] * right.value[k][j]) % 3;
        }
    }
    return result;
}

Matrix getPower(Matrix base, int exponent) {
    int i;
    Matrix result;
    result.size = base.size;
    result.value.assign(result.size, vector<int>(result.size, 0));
    for (i = 0; i < result.size; ++i)
        result.value[i][i] = 1;
    while (exponent > 0) {
        if (exponent & 1) result = multiply(result, base);
        base = multiply(base, base);
        exponent >>= 1;
    }
    return result;
}

Matrix getInverse(Matrix matrix) {
    int size = matrix.size, i, j, k, pivot;
    for (i = 0; i < size; ++i)
        matrix.value[i].resize(2 * size);
    for (i = 0; i < size; ++i)
        matrix.value[i][size + i] = 1;
    for (i = 0; i < size; ++i) {
        pivot = i;
        while (pivot < size && matrix.value[pivot][i] == 0) ++pivot;
        swap(matrix.value[i], matrix.value[pivot]);
        int inversePivot = matrix.value[i][i] == 1 ? 1 : 2;
        for (j = 0; j < 2 * size; ++j)
            matrix.value[i][j] = matrix.value[i][j] * inversePivot % 3;
        for (k = 0; k < size; ++k) {
            if (k == i || matrix.value[k][i] == 0) continue;
            int factor = matrix.value[k][i];
            for (j = 0; j < 2 * size; ++j)
                matrix.value[k][j] = (matrix.value[k][j] - factor * matrix.value[i][j] % 3 + 3) % 3;
        }
    }
    for (i = 0; i < size; ++i)
        matrix.value[i].erase(matrix.value[i].begin(), matrix.value[i].begin() + size);
    return matrix;
}

uint64_t applyMatrix(const Matrix& matrix, uint64_t state) {
    int size = matrix.size, i, j, value;
    uint64_t result = 0;
    for (i = 0; i < size; ++i) {
        value = 0;
        for (j = 0; j < size; ++j)
            value = (value + matrix.value[i][j] * getValue(state, j)) % 3;
        result |= static_cast<uint64_t>(value) << (2 * i);
    }
    return result;
}

Matrix buildMatrix(int rowCount, int columnCount, const vector<int>& source) {
    int size = rowCount * columnCount, i, j;
    Matrix result;
    result.size = size;
    result.value.assign(size, vector<int>(size, 0));
    for (j = 0; j < size; ++j) {
        uint64_t basis = 1ULL << (2 * j);
        uint64_t transformed = applySwitch(basis, rowCount, columnCount, source);
        for (i = 0; i < size; ++i)
            result.value[i][j] = getValue(transformed, i);
    }
    return result;
}

int findAnswer(uint64_t start, uint64_t target, const Matrix& transform, const Matrix& reverseBlock) {
    unordered_map<uint64_t, int> baby;
    uint64_t state = start, giant = target;
    int i, q, answer = maxStep;
    for (i = 0; i < blockSize; ++i) {
        if (baby.find(state) == baby.end())
            baby[state] = i;
        state = applyMatrix(transform, state);
    }
    for (q = 0; q * blockSize < maxStep; ++q) {
        unordered_map<uint64_t, int>::const_iterator it = baby.find(giant);
        if (it != baby.end() && q * blockSize + it->second < maxStep)
            answer = min(answer, q * blockSize + it->second);
        giant = applyMatrix(reverseBlock, giant);
    }
    return answer == maxStep ? -1 : answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, rowCount, columnCount, i, j, diagonal;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        cin >> rowCount >> columnCount;
        int total = rowCount * columnCount;
        vector<char> initial(total), target(total);
        for (i = 0; i < total; ++i)
            cin >> initial[i];
        for (i = 0; i < total; ++i)
            cin >> target[i];
        vector<int> source;
        source.reserve(total);
        for (diagonal = 0; diagonal <= rowCount + columnCount - 2; ++diagonal) {
            int startRow = max(0, diagonal - columnCount + 1), endRow = min(rowCount - 1, diagonal);
            if (diagonal % 2 == 0) {
                for (i = endRow; i >= startRow; --i) {
                    j = diagonal - i;
                    source.push_back(i * columnCount + j);
                }
            } else {
                for (i = startRow; i <= endRow; ++i) {
                    j = diagonal - i;
                    source.push_back(i * columnCount + j);
                }
            }
        }
        uint64_t startState = 0, targetState = 0;
        for (i = 0; i < total; ++i) {
            startState |= static_cast<uint64_t>(getColor(initial[i])) << (2 * i);
            targetState |= static_cast<uint64_t>(getColor(target[i])) << (2 * i);
        }
        Matrix transform = buildMatrix(rowCount, columnCount, source);
        Matrix blockTransform = getPower(transform, blockSize);
        Matrix reverseBlock = getInverse(blockTransform);
        int answer = findAnswer(startState, targetState, transform, reverseBlock);
        cout << "Case " << caseId << ": " << answer << '\n';
    }
    return 0;
}
