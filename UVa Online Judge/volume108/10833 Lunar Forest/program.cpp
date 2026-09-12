// Lunar Forest
// UVa ID: 108833
// Verdict: Accepted
// Submission Date: 2026-08-02
// UVa Run Time: 0.250s

#include <bits/stdc++.h>
using namespace std;

int harvestPoint1, harvestPoint2, targetTreeCount, currentBound, nextBound;

struct State {
    int heightArray[16];
    int treeNum;
    int seedCount;
    int elapsedDays;
};

void normalizeState(State &s) {
    sort(s.heightArray, s.heightArray + s.treeNum);
    if (s.seedCount + s.treeNum > targetTreeCount) s.seedCount = targetTreeCount - s.treeNum;
}

int heuristicValue(const State &s) {
    int maxHeight = 0;
    for (int i = 0; i < s.treeNum; ++i) maxHeight = max(maxHeight, s.heightArray[i]);
    int diffSum = 0;
    for (int i = 0; i < s.treeNum; ++i) diffSum += maxHeight - s.heightArray[i];
    if (s.treeNum == targetTreeCount) return diffSum;
    int needTrees = targetTreeCount - s.treeNum;
    if (s.seedCount >= needTrees) return diffSum + needTrees * maxHeight;
    else return diffSum + needTrees * maxHeight + (needTrees - s.seedCount);
}

bool dfs(State &s) {
    int bound = s.elapsedDays + heuristicValue(s);
    if (bound > currentBound) { nextBound = min(nextBound, bound); return false; }
    if (s.treeNum == targetTreeCount) { nextBound = bound; return true; }
    for (int k = s.seedCount; k >= 0; --k) {
        State child;
        child.treeNum = s.treeNum + k;
        if (child.treeNum > targetTreeCount) continue;
        child.elapsedDays = s.elapsedDays + 1;
        child.seedCount = s.seedCount - k;
        for (int i = 0; i < s.treeNum; ++i) {
            child.heightArray[i] = s.heightArray[i] + 1;
            if (child.heightArray[i] == harvestPoint1 || child.heightArray[i] == harvestPoint2) child.seedCount++;
        }
        for (int i = 0; i < k; ++i) child.heightArray[s.treeNum + i] = 1;
        if (child.treeNum == 0) continue;
        normalizeState(child);
        for (int i = child.treeNum - 1; i >= 0; --i) {
            if (i > 0 && child.heightArray[i - 1] == child.heightArray[i]) continue;
            child.heightArray[i]++;
            if (child.heightArray[i] == harvestPoint1 || child.heightArray[i] == harvestPoint2) child.seedCount++;
            if (dfs(child)) return true;
            if (child.heightArray[i] == harvestPoint1 || child.heightArray[i] == harvestPoint2) child.seedCount--;
            child.heightArray[i]--;
        }
    }
    return false;
}

int ida() {
    for (nextBound = 0; ; ) {
        currentBound = nextBound;
        nextBound = INT_MAX;
        State start;
        start.treeNum = 0;
        start.elapsedDays = 0;
        start.seedCount = 1;
        if (dfs(start)) return nextBound;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int testCases, caseNo = 1;
    cin >> testCases;
    while (caseNo <= testCases && cin >> harvestPoint1 >> harvestPoint2 >> targetTreeCount) {
        cout << "Case " << caseNo << ": " << ida() << "\n";
        ++caseNo;
    }
    return 0;
}
