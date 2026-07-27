// Rinse 
// UVa ID: 11109
// Verdict: Accepted
// Submission Date: 2026-07-27
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163251079

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rinseCount;
    while (cin >> rinseCount && rinseCount != 0) {
        long double waterBarrel;
        long double whiskeyVolume;
        long double residualVolume;
        long double canVolume;
        cin >> waterBarrel >> whiskeyVolume >> residualVolume >> canVolume;
        vector<long double> baseVolume(rinseCount);
        vector<long double> waterLimit(rinseCount);
        baseVolume[0] = whiskeyVolume;
        waterLimit[0] = canVolume - whiskeyVolume;
        for (int i = 1; i < rinseCount; i++) {
            baseVolume[i] = residualVolume;
            waterLimit[i] = canVolume - residualVolume;
        }
        long double totalLimit = 0;
        for (int i = 0; i < rinseCount; i++) totalLimit += waterLimit[i];
        long double targetWater = min(waterBarrel, totalLimit);
        long double left = 0;
        long double right = canVolume;
        for (int iteration = 0; iteration < 100; iteration++) {
            long double middle = (left + right) / 2;
            long double usedWater = 0;
            for (int i = 0; i < rinseCount; i++) {
                long double currentWater = middle - baseVolume[i];
                if (currentWater < 0) currentWater = 0;
                if (currentWater > waterLimit[i]) currentWater = waterLimit[i];
                usedWater += currentWater;
            }
            if (usedWater < targetWater) left = middle;
            else right = middle;
        }
        long double waterLevel = (left + right) / 2;
        cout << rinseCount;
        for (int i = 0; i < rinseCount; i++) {
            long double currentWater = waterLevel - baseVolume[i];
            if (currentWater < 0) currentWater = 0;
            if (currentWater > waterLimit[i]) currentWater = waterLimit[i];
            cout << fixed << setprecision(2) << " " << (double)currentWater;
        }
        cout << '\n';
    }
    return 0;
}
