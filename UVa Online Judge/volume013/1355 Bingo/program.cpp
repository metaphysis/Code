#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000007, MAX_VALUE = 100, MAX_CARD = 5;

class Board {
public:
    vector<vector<int>> lines;
    void read(int size) {
        vector<vector<int>> table(size, vector<int>(size));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
                scanf("%d", &table[i][j]);
        }
        lines.clear();
        for (int i = 0; i < size; i++)
            lines.push_back(table[i]);
        for (int j = 0; j < size; j++) {
            vector<int> column;
            for (int i = 0; i < size; i++)
                column.push_back(table[i][j]);
            lines.push_back(column);
        }
        vector<int> diagonal, reverseDiagonal;
        for (int i = 0; i < size; i++) {
            diagonal.push_back(table[i][i]);
            reverseDiagonal.push_back(table[i][size - i - 1]);
        }
        lines.push_back(diagonal);
        lines.push_back(reverseDiagonal);
    }
    int minMissing(const vector<int>& valueId) const {
        int result = INF;
        for (const vector<int>& line : lines) {
            int missing = 0;
            for (int value : line)
                if (valueId[value] == -1)
                    missing++;
            result = min(result, missing);
        }
        return result;
    }
};

int cardCount, answer;
Board boards[MAX_CARD];

bool isPowerOfTwo(int value) { return value > 0 && (value & (value - 1)) == 0; }

bool canBuildInOrder(const vector<int>& numbers) {
    int numberCount = numbers.size(), stateCount = 1 << numberCount;
    vector<int> valueId(MAX_VALUE, -1);
    for (int i = 0; i < numberCount; i++)
        valueId[numbers[i]] = i;
    vector<int> completed(stateCount, 0);
    for (int card = 0; card < cardCount; card++) {
        for (const vector<int>& line : boards[card].lines) {
            int lineMask = 0;
            bool possible = true;
            for (int value : line) {
                if (valueId[value] == -1) {
                    possible = false;
                    break;
                }
                lineMask |= 1 << valueId[value];
            }
            if (possible)
                completed[lineMask] |= 1 << card;
        }
    }
    for (int bit = 0; bit < numberCount; bit++) {
        for (int mask = 0; mask < stateCount; mask++)
            if ((mask & (1 << bit)) == 0)
                completed[mask | (1 << bit)] |= completed[mask];
    }
    vector<bool> reachable(stateCount, false);
    reachable[0] = true;
    for (int mask = 0; mask < stateCount; mask++) {
        if (!reachable[mask])
            continue;
        for (int bit = 0; bit < numberCount; bit++) {
            if (mask & (1 << bit)) continue;
            int nextMask = mask | (1 << bit), finished = completed[nextMask];
            if (!isPowerOfTwo(finished + 1)) continue;
            reachable[nextMask] = true;
        }
    }
    return reachable[stateCount - 1];
}

void dfs(int card, vector<int>& selectedValues) {
    if (card == cardCount - 1) {
        vector<int> numbers = selectedValues;
        sort(numbers.begin(), numbers.end());
        numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
        vector<int> valueId(MAX_VALUE, -1);
        for (int i = 0; i < (int)numbers.size(); i++)
            valueId[numbers[i]] = i;
        int candidate = numbers.size() + boards[card].minMissing(valueId);
        if (candidate >= answer) return;
        if (canBuildInOrder(numbers)) answer = candidate;
        return;
    }
    for (const vector<int>& line : boards[card].lines) {
        int oldSize = selectedValues.size();
        selectedValues.insert(selectedValues.end(), line.begin(), line.end());
        dfs(card + 1, selectedValues);
        selectedValues.resize(oldSize);
    }
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n == 0 && m == 0)
            break;
        cardCount = n;
        for (int i = 0; i < cardCount; i++) boards[i].read(m);
        answer = INF;
        vector<int> selectedValues;
        dfs(0, selectedValues);
        if (answer == INF) answer = 0;
        printf("%d\n", answer);
    }
    return 0;
}
