#include <bits/stdc++.h>
using namespace std;

struct Option {
    int mask;
    long long value;
};

vector<Option> buildOptions(int rows, int cols, const vector<vector<int>> &productivity, char kind, int cost, int minCount, int maxCount) {
    int cellCount = rows * cols, limit = 1 << cellCount;
    vector<Option> options;
    for (int mask = 0; mask < limit; mask++) {
        int count = __builtin_popcount(static_cast<unsigned int>(mask));
        if (count < minCount || count > maxCount)
            continue;
        bool valid = true;
        for (int row = 0; row < rows; row++) {
            int rowCount = 0;
            for (int col = 0; col < cols; col++)
                if (mask & (1 << (row * cols + col)))
                    rowCount++;
            if (kind == 'M' && rowCount > 1) {
                valid = false;
                break;
            }
        }
        if (!valid)
            continue;
        for (int col = 0; col < cols; col++) {
            int colCount = 0;
            for (int row = 0; row < rows; row++)
                if (mask & (1 << (row * cols + col)))
                    colCount++;
            if (kind == 'F' && colCount > 1) {
                valid = false;
                break;
            }
        }
        if (!valid)
            continue;
        long long sum = 0;
        for (int row = 0; row < rows; row++)
            for (int col = 0; col < cols; col++)
                if (mask & (1 << (row * cols + col)))
                    sum += productivity[row][col];
        options.push_back({mask, sum * cost});
    }
    return options;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rows, cols, speciesCount;
    while (cin >> rows >> cols >> speciesCount) {
        if (rows == 0 && cols == 0 && speciesCount == 0)
            break;
        vector<vector<int>> productivity(rows, vector<int>(cols));
        for (int row = 0; row < rows; row++)
            for (int col = 0; col < cols; col++)
                cin >> productivity[row][col];
        int cellCount = rows * cols, stateCount = 1 << cellCount;
        vector<long long> dp(stateCount, -1);
        dp[0] = 0;
        for (int i = 0; i < speciesCount; i++) {
            char kind;
            int cost, minCount, maxCount;
            cin >> kind >> cost >> minCount >> maxCount;
            vector<Option> options = buildOptions(rows, cols, productivity, kind, cost, minCount, maxCount);
            vector<long long> nextDp(stateCount, -1);
            for (int mask = 0; mask < stateCount; mask++) {
                if (dp[mask] < 0)
                    continue;
                for (const Option &option : options) {
                    if ((mask & option.mask) != 0)
                        continue;
                    int nextMask = mask | option.mask;
                    nextDp[nextMask] = max(nextDp[nextMask], dp[mask] + option.value);
                }
            }
            dp.swap(nextDp);
        }
        long long answer = 0;
        for (long long value : dp)
            answer = max(answer, value);
        cout << answer << '\n';
    }
    return 0;
}
