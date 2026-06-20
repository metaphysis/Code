// Helicopter
// UVa ID: 1523
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.370s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算给定重量排列下的合力矩
double calcMoment(const vector<int>& weights, const vector<pair<int,int>>& seats) {
    int sumV = 0, sumH = 0;
    for (int i = 0; i < 8; ++i) {
        sumV += weights[i] * seats[i].first;
        sumH += weights[i] * seats[i].second;
    }
    return sqrt((double)sumV * sumV + (double)sumH * sumH);
}

int main() {
    // 8个座位的坐标（相对于螺旋桨中心）
    vector<pair<int,int>> seats = {
        {-1,-1}, {-1,0}, {-1,1},
        {0,-1},           {0,1},
        {1,-1},  {1,0},  {1,1}
    };

    vector<int> weights(8);
    while (true) {
        bool allZero = true;
        for (int i = 0; i < 8; ++i) {
            cin >> weights[i];
            if (weights[i] != 0) allZero = false;
        }
        if (allZero) break;  // 结束标记

        sort(weights.begin(), weights.end());
        double best = 1e100;
        do {
            double cur = calcMoment(weights, seats);
            if (cur < best) best = cur;
        } while (next_permutation(weights.begin(), weights.end()));

        cout << fixed << setprecision(3) << best << endl;
    }
    return 0;
}
