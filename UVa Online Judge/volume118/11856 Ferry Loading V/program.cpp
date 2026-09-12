// Ferry Loading V
// UVa ID: 11856
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 2.800s

#include <bits/stdc++.h>
using namespace std;

void solveCase(int vehicleCount) {
    vector<long double> weight(vehicleCount + 1);
    long double totalWeight = 0;
    for (int i = 1; i <= vehicleCount; i++) {
        cin >> weight[i];
        totalWeight += weight[i];
    }
    long double halfWeight = totalWeight / 2;
    long double unit = 0.001L * halfWeight / vehicleCount;
    vector<int> scaledWeight(vehicleCount + 1);
    int target = 0;
    for (int i = 1; i <= vehicleCount; i++) {
        scaledWeight[i] = (int)floor(weight[i] / unit + 1e-12L);
        target += scaledWeight[i];
    }
    target /= 2;
    vector<bool> canReach(target + 1, false);
    vector<int> previousSum(target + 1, -1);
    vector<int> previousItem(target + 1, -1);
    canReach[0] = true;
    for (int i = 1; i <= vehicleCount; i++) {
        for (int currentSum = target - scaledWeight[i]; currentSum >= 0; currentSum--) {
            int nextSum = currentSum + scaledWeight[i];
            if (canReach[currentSum] && !canReach[nextSum]) {
                canReach[nextSum] = true;
                previousSum[nextSum] = currentSum;
                previousItem[nextSum] = i;
            }
        }
    }
    int bestSum = target;
    while (bestSum > 0 && !canReach[bestSum]) bestSum--;
    vector<bool> onStarboard(vehicleCount + 1, false);
    while (bestSum > 0) {
        int item = previousItem[bestSum];
        if (item == -1) break;
        onStarboard[item] = true;
        bestSum = previousSum[bestSum];
    }
    bool first = true;
    for (int i = 1; i <= vehicleCount; i++) {
        if (onStarboard[i]) {
            if (!first) cout << ' ';
            cout << i;
            first = false;
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int vehicleCount;
    while (cin >> vehicleCount && vehicleCount != 0) solveCase(vehicleCount);
    return 0;
}
