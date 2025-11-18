// A Day in Math-land
// UVa ID: 10512
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.130s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int caseNum = 1; caseNum <= n; caseNum++) {
        long long p, q;
        cin >> p >> q;
        
        vector<pair<long long, long long>> solutions;
        
        // 情况1: P = 0, Q = 0
        if (p == 0 && q == 0) {
            solutions.push_back({0, 0});
        }
        // 情况2: P = 0, Q ≠ 0
        else if (p == 0 && q != 0) {
            // 子情况2.1: Y = 0
            if (q >= 0) {
                long long x = sqrt(q);
                if (x * x == q) {
                    if (x >= 0) solutions.push_back({x, 0});
                    if (-x >= 0 && x != 0) solutions.push_back({-x, 0});
                }
            }
            // 子情况2.2: X = -Y
            if (q % 2 == 0 && q >= 0) {
                long long ySq = q / 2;
                long long y = sqrt(ySq);
                if (y * y == ySq) {
                    solutions.push_back({-y, y});
                    if (y != 0) solutions.push_back({y, -y});
                }
            }
        }
        // 情况3: P ≠ 0, Q = 0
        else if (p != 0 && q == 0) {
            // 子情况3.1: X = 0
            if (p >= 0) {
                long long y = sqrt(p);
                if (y * y == p) {
                    if (0 >= y) solutions.push_back({0, y});
                    if (0 >= -y && y != 0) solutions.push_back({0, -y});
                }
            }
            // 子情况3.2: X = Y
            if (p % 2 == 0 && p >= 0) {
                long long xSq = p / 2;
                long long x = sqrt(xSq);
                if (x * x == xSq) {
                    solutions.push_back({x, x});
                    if (x != 0) solutions.push_back({-x, -x});
                }
            }
        }
        // 情况4: P ≠ 0, Q ≠ 0
        else {
            long long delta = p * p + 6 * p * q + q * q;
            if (delta >= 0) {
                long long sqrtDelta = sqrt(delta);
                if (sqrtDelta * sqrtDelta == delta) {
                    for (int sign = -1; sign <= 1; sign += 2) {
                        long long numerator = 3 * p + q + sign * sqrtDelta;
                        if (numerator % 4 == 0) {
                            long long u = numerator / 4;
                            if (u >= 0) {
                                long long y = sqrt(u);
                                if (y * y == u && y != 0) {
                                    for (int ySign = -1; ySign <= 1; ySign += 2) {
                                        long long yy = y * ySign;
                                        if (p % yy == 0) {
                                            long long xx = p / yy - yy;
                                            if (xx >= yy && xx * (xx - yy) == q) {
                                                solutions.push_back({xx, yy});
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // 过滤有效解（在16位有符号整数范围内且满足 X ≥ Y）
        vector<pair<long long, long long>> validSolutions;
        for (auto sol : solutions) {
            if (sol.first >= -32768 && sol.first <= 32767 &&
                sol.second >= -32768 && sol.second <= 32767 &&
                sol.first >= sol.second) {
                validSolutions.push_back(sol);
            }
        }
        
        // 去重和排序
        if (validSolutions.empty()) {
            cout << "Case " << caseNum << ":\nImpossible.\n";
        } else {
            sort(validSolutions.begin(), validSolutions.end());
            auto uniqueEnd = unique(validSolutions.begin(), validSolutions.end());
            validSolutions.erase(uniqueEnd, validSolutions.end());
            cout << "Case " << caseNum << ":\n" << validSolutions[0].first << " " << validSolutions[0].second << "\n";
        }
    }
    return 0;
}
