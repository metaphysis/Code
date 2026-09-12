// Complete the Set
// UVa ID: 12011
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.110s

#include <bits/stdc++.h>
using namespace std;

long long countUpSets(int state, const vector<int>& upMask, vector<long long>& memory) {
    if (state == 0)
        return 1;
    if (memory[state] != -1)
        return memory[state];
    int element = -1;
    int current = state;
    while (current) {
        int bit = current & -current;
        int index = __builtin_ctz(bit);
        bool isMinimal = true;
        int other = state ^ bit;
        while (other) {
            int otherBit = other & -other;
            int otherIndex = __builtin_ctz(otherBit);
            if ((upMask[otherIndex] & bit) != 0) {
                isMinimal = false;
                break;
            }
            other ^= otherBit;
        }
        if (isMinimal) {
            element = index;
            break;
        }
        current ^= bit;
    }
    int elementBit = 1 << element;
    int includeState = state & ~upMask[element];
    int excludeState = state & ~elementBit;
    memory[state] = countUpSets(excludeState, upMask, memory) + countUpSets(includeState, upMask, memory);
    return memory[state];
}

int solveComponent(const vector<int>& elements, const vector<vector<char>>& lessEqual) {
    int componentSize = static_cast<int>(elements.size());
    if (componentSize == 1)
        return 2;
    vector<int> upMask(componentSize, 0);
    for (int i = 0; i < componentSize; ++i)
        for (int j = 0; j < componentSize; ++j)
            if (lessEqual[elements[i]][elements[j]])
                upMask[i] |= 1 << j;
    int stateLimit = 1 << componentSize;
    vector<long long> memory(stateLimit, -1);
    return static_cast<int>(countUpSets(stateLimit - 1, upMask, memory));
}

int solveCase(const vector<int>& numbers) {
    const int bitCount = 18;
    vector<vector<char>> lessEqual(bitCount, vector<char>(bitCount, 1));
    for (int firstBit = 0; firstBit < bitCount; ++firstBit)
        for (int secondBit = 0; secondBit < bitCount; ++secondBit)
            for (int number : numbers)
                if ((number & (1 << firstBit)) && !(number & (1 << secondBit))) {
                    lessEqual[firstBit][secondBit] = 0;
                    break;
                }
    vector<int> representatives;
    vector<char> used(bitCount, 0);
    for (int bit = 0; bit < bitCount; ++bit) {
        if (used[bit])
            continue;
        used[bit] = 1;
        for (int otherBit = bit + 1; otherBit < bitCount; ++otherBit)
            if (lessEqual[bit][otherBit] && lessEqual[otherBit][bit])
                used[otherBit] = 1;
        representatives.push_back(bit);
    }
    vector<int> middleBits;
    for (int bit : representatives) {
        bool isZeroColumn = true;
        bool isOneColumn = true;
        for (int number : numbers) {
            if (number & (1 << bit))
                isZeroColumn = false;
            else
                isOneColumn = false;
        }
        if (!isZeroColumn && !isOneColumn)
            middleBits.push_back(bit);
    }
    int middleSize = static_cast<int>(middleBits.size());
    vector<char> visited(middleSize, 0);
    long long completeSize = 1;
    for (int start = 0; start < middleSize; ++start) {
        if (visited[start])
            continue;
        vector<int> component;
        queue<int> pending;
        pending.push(start);
        visited[start] = 1;
        while (!pending.empty()) {
            int current = pending.front();
            pending.pop();
            component.push_back(current);
            for (int next = 0; next < middleSize; ++next) {
                if (visited[next])
                    continue;
                int firstBit = middleBits[current];
                int secondBit = middleBits[next];
                if (lessEqual[firstBit][secondBit] || lessEqual[secondBit][firstBit]) {
                    visited[next] = 1;
                    pending.push(next);
                }
            }
        }
        vector<int> realComponent;
        for (int index : component)
            realComponent.push_back(middleBits[index]);
        completeSize *= solveComponent(realComponent, lessEqual);
    }
    return static_cast<int>(completeSize) - static_cast<int>(numbers.size());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        int numberCount;
        cin >> numberCount;
        vector<int> numbers(numberCount);
        for (int& number : numbers)
            cin >> number;
        cout << "Case #" << caseIndex << ": " << solveCase(numbers) << '\n';
    }
    return 0;
}
