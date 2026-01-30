// Mountain Road
// UVa ID: 12222
// Verdict: Accepted
// Submission Date: 2026-01-21
// UVa Run Time: 0.170s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct Car { int arrive, drive; };

int main() {
    int c; cin >> c;
    while (c--) {
        int n; cin >> n;
        vector<Car> carsA(1), carsB(1);
        for (int i = 0; i < n; i++) {
            char dir; cin >> dir;
            if (dir == 'A') {
                Car car; cin >> car.arrive >> car.drive;
                carsA.push_back(car);
            } else {
                Car car; cin >> car.arrive >> car.drive;
                carsB.push_back(car);
            }
        }
        int ca = carsA.size() - 1, cb = carsB.size() - 1;
        vector<vector<vector<int>>> dp(ca + 1, vector<vector<int>>(cb + 1, vector<int>(2, INF)));
        dp[0][0][0] = dp[0][0][1] = 0;
        for (int i = 0; i <= ca; i++) {
            for (int j = 0; j <= cb; j++) {
                // 状态0：道路最后被A车占用，下一辆可以进入的是B车
                // 所以我们可以连续调度多辆B车
                if (dp[i][j][0] < INF) {
                    int s = dp[i][j][0];  // 当前时间
                    int end = 0;          // 最后结束时间
                    // 尝试连续调度B车：从j+1到cb
                    for (int k = j + 1; k <= cb; k++) {
                        // 当前B车进入时间 = max(到达时间, 当前时间)
                        s = max(s, carsB[k].arrive);
                        // 当前B车离开时间 = 进入时间 + 行驶时间
                        end = max(s + carsB[k].drive, end);
                        // 更新状态：调度了i辆A车，k辆B车，道路最后被B车占用[1]
                        dp[i][k][1] = min(dp[i][k][1], end);
                        // 下一辆B车必须至少10秒后进入（安全间隔）
                        s += 10;
                        end += 10;
                    }
                }
                // 状态1：道路最后被B车占用，下一辆可以进入的是A车
                // 所以我们可以连续调度多辆A车
                if (dp[i][j][1] < INF) {
                    int s = dp[i][j][1];
                    int end = 0;
                    // 尝试连续调度A车：从i+1到ca
                    for (int k = i + 1; k <= ca; k++) {
                        s = max(s, carsA[k].arrive);
                        end = max(s + carsA[k].drive, end);
                        dp[k][j][0] = min(dp[k][j][0], end);
                        s += 10;
                        end += 10;
                    }
                }
            }
        }
        int r = min(dp[ca][cb][0], dp[ca][cb][1]);
        cout << r << '\n';
    }
    return 0;
}
