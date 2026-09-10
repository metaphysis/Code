#include <bits/stdc++.h>
using namespace std;

const int maxNum = 16;
const int maxKind = 16;
const int maxPattern = 5000;
const int maxPerm = 24;

int numList[maxNum], numCount;
int valueList[maxKind], valueCount, valueCnt[maxKind];
int squareSize, totalSum, targetSum;
int patternCount, patternNeed[maxPattern][maxKind];
int permCount[maxPattern], patternPerm[maxPattern][maxPerm][4];
int tempNeed[maxKind], tempValue[4];
int remCnt[maxKind], colSum[4], diagSum1, diagSum2;
unordered_set<string> badStates;

void makePerm(int patternId) {
    int arr[4];
    for (int i = 0; i < squareSize; i++)
        arr[i] = tempValue[i];
    sort(arr, arr + squareSize);
    permCount[patternId] = 0;
    do {
        for (int i = 0; i < squareSize; i++)
            patternPerm[patternId][permCount[patternId]][i] = arr[i];
        permCount[patternId]++;
    } while (next_permutation(arr, arr + squareSize));
}

void makePattern(int kindId, int left, int sum) {
    if (kindId == valueCount) {
        if (left != 0 || sum != targetSum)
            return;
        int pos = 0;
        for (int i = 0; i < valueCount; i++)
            for (int j = 0; j < tempNeed[i]; j++)
                tempValue[pos++] = valueList[i];
        for (int i = 0; i < valueCount; i++)
            patternNeed[patternCount][i] = tempNeed[i];
        makePerm(patternCount);
        patternCount++;
        return;
    }
    int maxTake = min(valueCnt[kindId], left);
    for (int take = 0; take <= maxTake; take++) {
        tempNeed[kindId] = take;
        makePattern(kindId + 1, left - take, sum + take * valueList[kindId]);
    }
    tempNeed[kindId] = 0;
}

string makeKey(int rowId) {
    string key;
    key += to_string(rowId);
    key += ',';
    for (int i = 0; i < valueCount; i++) {
        key += to_string(remCnt[i]);
        key += ',';
    }
    for (int i = 0; i < squareSize; i++) {
        key += to_string(colSum[i]);
        key += ',';
    }
    key += to_string(diagSum1);
    key += ',';
    key += to_string(diagSum2);
    return key;
}

bool canFinish(int rowId) {
    int leftRow = squareSize - rowId;
    if (leftRow == 0) {
        for (int i = 0; i < squareSize; i++)
            if (colSum[i] != targetSum)
                return false;
        if (diagSum1 != targetSum || diagSum2 != targetSum)
            return false;
        return true;
    }
    int leftNum = 0;
    for (int i = 0; i < valueCount; i++)
        leftNum += remCnt[i];
    if (leftNum != leftRow * squareSize)
        return false;
    int minAdd = 0, maxAdd = 0, needNum = leftRow;
    for (int i = 0; i < valueCount && needNum > 0; i++) {
        int take = min(remCnt[i], needNum);
        minAdd += take * valueList[i];
        needNum -= take;
    }
    needNum = leftRow;
    for (int i = valueCount - 1; i >= 0 && needNum > 0; i--) {
        int take = min(remCnt[i], needNum);
        maxAdd += take * valueList[i];
        needNum -= take;
    }
    for (int i = 0; i < squareSize; i++) {
        int need = targetSum - colSum[i];
        if (need < minAdd || need > maxAdd)
            return false;
    }
    int need = targetSum - diagSum1;
    if (need < minAdd || need > maxAdd)
        return false;
    need = targetSum - diagSum2;
    if (need < minAdd || need > maxAdd)
        return false;
    return true;
}

bool solve(int);

bool fillRow(int rowId, int pos, int patternId, int permId) {
    if (pos == squareSize)
        return solve(rowId + 1);
    int value = patternPerm[patternId][permId][pos];
    colSum[pos] += value;
    if (rowId == pos)
        diagSum1 += value;
    if (rowId + pos == squareSize - 1)
        diagSum2 += value;
    bool result = fillRow(rowId, pos + 1, patternId, permId);
    colSum[pos] -= value;
    if (rowId == pos)
        diagSum1 -= value;
    if (rowId + pos == squareSize - 1)
        diagSum2 -= value;
    return result;
}

bool solve(int rowId) {
    if (!canFinish(rowId))
        return false;
    if (rowId == squareSize)
        return true;
    string key = makeKey(rowId);
    if (badStates.find(key) != badStates.end())
        return false;
    badStates.insert(key);
    for (int i = 0; i < patternCount; i++) {
        bool fit = true;
        for (int j = 0; j < valueCount; j++)
            if (patternNeed[i][j] > remCnt[j])
                fit = false;
        if (!fit)
            continue;
        for (int j = 0; j < valueCount; j++)
            remCnt[j] -= patternNeed[i][j];
        for (int j = 0; j < permCount[i]; j++) {
            if (fillRow(rowId, 0, i, j)) {
                for (int k = 0; k < valueCount; k++)
                    remCnt[k] += patternNeed[i][k];
                return true;
            }
        }
        for (int j = 0; j < valueCount; j++)
            remCnt[j] += patternNeed[i][j];
    }
    return false;
}

bool checkMagicSquare() {
    if (numCount == 0)
        return false;
    squareSize = static_cast<int>(sqrt(numCount));
    if (squareSize * squareSize != numCount)
        return false;
    totalSum = 0;
    for (int i = 0; i < numCount; i++)
        totalSum += numList[i];
    if (totalSum % squareSize != 0)
        return false;
    targetSum = totalSum / squareSize;
    sort(numList, numList + numCount);
    valueCount = 0;
    for (int i = 0; i < numCount; i++) {
        if (valueCount == 0 || valueList[valueCount - 1] != numList[i]) {
            valueList[valueCount] = numList[i];
            valueCnt[valueCount] = 1;
            valueCount++;
        } else {
            valueCnt[valueCount - 1]++;
        }
    }
    patternCount = 0;
    for (int i = 0; i < valueCount; i++)
        tempNeed[i] = 0;
    makePattern(0, squareSize, 0);
    if (patternCount == 0)
        return false;
    for (int i = 0; i < valueCount; i++)
        remCnt[i] = valueCnt[i];
    for (int i = 0; i < 4; i++)
        colSum[i] = 0;
    diagSum1 = 0;
    diagSum2 = 0;
    badStates.clear();
    return solve(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (line.empty())
            continue;
        stringstream input(line);
        numCount = 0;
        while (input >> numList[numCount])
            numCount++;
        cout << (checkMagicSquare() ? "Y" : "N") << '\n';
    }
    return 0;
}
