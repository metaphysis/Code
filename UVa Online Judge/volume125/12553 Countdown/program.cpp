// Countdown
// UVa ID: 12553
// Verdict: Accepted
// Submission Date: 2026-06-05
// UVa Run Time: 1.530s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct State {
    int value;
    string expr;
    vector<string> steps;
};

int target, bestDiff, bestValue;
vector<string> bestSteps;

// dp[mask][value] = 该子集能产生该value的最佳表达式及步骤
map<int, State> dp[1 << 6];

void updateBest(int value, const vector<string>& steps) {
    int diff = abs(value - target);
    if (diff < bestDiff || (diff == bestDiff && value > bestValue)) {
        bestDiff = diff;
        bestValue = value;
        bestSteps = steps;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int C;
    cin >> C;
    while (C--) {
        vector<int> nums(6);
        for (int i = 0; i < 6; ++i) cin >> nums[i];
        cin >> target;
        
        int n = 6;
        int totalMask = 1 << n;
        for (int i = 0; i < totalMask; ++i) dp[i].clear();
        
        // 初始化单数字状态
        for (int i = 0; i < n; ++i) {
            int mask = 1 << i;
            dp[mask][nums[i]] = {nums[i], to_string(nums[i]), {}};
        }
        
        // 枚举所有子集
        for (int mask = 1; mask < totalMask; ++mask) {
            // 枚举mask的非平凡子集分割
            for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
                int other = mask ^ sub;
                if (sub > other) continue; // 避免重复枚举
                if (dp[sub].empty() || dp[other].empty()) continue;
                
                // 合并sub和other的所有可能值
                for (auto& p1 : dp[sub]) {
                    for (auto& p2 : dp[other]) {
                        int a = p1.first, b = p2.first;
                        State& s1 = p1.second, s2 = p2.second;
                        
                        // 加法
                        int v = a + b;
                        string expr = "(" + s1.expr + " + " + s2.expr + ")";
                        vector<string> steps = s1.steps;
                        steps.insert(steps.end(), s2.steps.begin(), s2.steps.end());
                        steps.push_back(to_string(a) + " + " + to_string(b) + " = " + to_string(v));
                        if (dp[mask].find(v) == dp[mask].end() || steps.size() < dp[mask][v].steps.size())
                            dp[mask][v] = {v, expr, steps};
                        
                        // 乘法
                        v = a * b;
                        expr = "(" + s1.expr + " * " + s2.expr + ")";
                        steps = s1.steps;
                        steps.insert(steps.end(), s2.steps.begin(), s2.steps.end());
                        steps.push_back(to_string(a) + " * " + to_string(b) + " = " + to_string(v));
                        if (dp[mask].find(v) == dp[mask].end() || steps.size() < dp[mask][v].steps.size())
                            dp[mask][v] = {v, expr, steps};
                        
                        // 减法 a - b
                        if (a > b) {
                            v = a - b;
                            expr = "(" + s1.expr + " - " + s2.expr + ")";
                            steps = s1.steps;
                            steps.insert(steps.end(), s2.steps.begin(), s2.steps.end());
                            steps.push_back(to_string(a) + " - " + to_string(b) + " = " + to_string(v));
                            if (dp[mask].find(v) == dp[mask].end() || steps.size() < dp[mask][v].steps.size())
                                dp[mask][v] = {v, expr, steps};
                        }
                        
                        // 减法 b - a
                        if (b > a) {
                            v = b - a;
                            expr = "(" + s2.expr + " - " + s1.expr + ")";
                            steps = s2.steps;
                            steps.insert(steps.end(), s1.steps.begin(), s1.steps.end());
                            steps.push_back(to_string(b) + " - " + to_string(a) + " = " + to_string(v));
                            if (dp[mask].find(v) == dp[mask].end() || steps.size() < dp[mask][v].steps.size())
                                dp[mask][v] = {v, expr, steps};
                        }
                        
                        // 除法 a / b
                        if (b != 0 && a % b == 0) {
                            v = a / b;
                            expr = "(" + s1.expr + " / " + s2.expr + ")";
                            steps = s1.steps;
                            steps.insert(steps.end(), s2.steps.begin(), s2.steps.end());
                            steps.push_back(to_string(a) + " / " + to_string(b) + " = " + to_string(v));
                            if (dp[mask].find(v) == dp[mask].end() || steps.size() < dp[mask][v].steps.size())
                                dp[mask][v] = {v, expr, steps};
                        }
                        
                        // 除法 b / a
                        if (a != 0 && b % a == 0) {
                            v = b / a;
                            expr = "(" + s2.expr + " / " + s1.expr + ")";
                            steps = s2.steps;
                            steps.insert(steps.end(), s1.steps.begin(), s1.steps.end());
                            steps.push_back(to_string(b) + " / " + to_string(a) + " = " + to_string(v));
                            if (dp[mask].find(v) == dp[mask].end() || steps.size() < dp[mask][v].steps.size())
                                dp[mask][v] = {v, expr, steps};
                        }
                    }
                }
            }
        }
        
        // 找最优解（考虑所有子集，不一定用完所有数字）
        bestDiff = INT_MAX;
        bestValue = -1;
        bestSteps.clear();
        
        for (int mask = 1; mask < totalMask; ++mask) {
            for (auto& p : dp[mask]) {
                int val = p.first;
                State& st = p.second;
                updateBest(val, st.steps);
            }
        }
        
        cout << "Target: " << target << "\n";
        for (const string& step : bestSteps) cout << step << "\n";
        cout << "Best approx: " << bestValue << "\n\n";
    }
    return 0;
}
