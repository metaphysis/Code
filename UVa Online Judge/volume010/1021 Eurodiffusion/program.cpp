// Eurodiffusion
// UVa ID: 1021
// Verdict: Accepted
// Submission Date: 2026-07-24
// UVa Run Time: 0.220s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int c;
    int caseNo = 0;
    while (cin >> c && c != 0) {
        ++caseNo;
        vector<string> names(c);
        vector<int> xl(c), yl(c), xh(c), yh(c);
        for (int i = 0; i < c; ++i) {
            cin >> names[i] >> xl[i] >> yl[i] >> xh[i] >> yh[i];
        }
        // 10x10 网格，坐标 1..10 转为 0..9
        int grid[10][10];
        memset(grid, -1, sizeof(grid));
        for (int i = 0; i < c; ++i) {
            for (int x = xl[i] - 1; x <= xh[i] - 1; ++x) {
                for (int y = yl[i] - 1; y <= yh[i] - 1; ++y) {
                    grid[x][y] = i; // 题目保证不重叠
                }
            }
        }
        // 给每个城市分配 id
        int cityId[10][10];
        memset(cityId, -1, sizeof(cityId));
        vector<int> cityCountry;
        int n = 0;
        for (int x = 0; x < 10; ++x) {
            for (int y = 0; y < 10; ++y) {
                if (grid[x][y] != -1) {
                    cityId[x][y] = n++;
                    cityCountry.push_back(grid[x][y]);
                }
            }
        }
        vector<vector<int>> countryCities(c);
        for (int i = 0; i < n; ++i) {
            countryCities[cityCountry[i]].push_back(i);
        }
        // 邻居
        vector<vector<int>> neighbors(n);
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        for (int x = 0; x < 10; ++x) {
            for (int y = 0; y < 10; ++y) {
                if (cityId[x][y] == -1) continue;
                int id = cityId[x][y];
                for (int k = 0; k < 4; ++k) {
                    int nx = x + dx[k], ny = y + dy[k];
                    if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && cityId[nx][ny] != -1) {
                        neighbors[id].push_back(cityId[nx][ny]);
                    }
                }
            }
        }
        // 初始硬币
        vector<vector<long long>> balance(n, vector<long long>(c, 0));
        for (int i = 0; i < n; ++i) {
            balance[i][cityCountry[i]] = 1000000;
        }
        vector<int> completedDays(c, -1);
        auto isCountryComplete = [&](int idx) -> bool {
            for (int city : countryCities[idx]) {
                for (int m = 0; m < c; ++m) {
                    if (balance[city][m] == 0) return false;
                }
            }
            return true;
        };
        // 检查第0天
        bool allDone = true;
        for (int i = 0; i < c; ++i) {
            if (isCountryComplete(i)) {
                completedDays[i] = 0;
            } else {
                allDone = false;
            }
        }
        int day = 0;
        if (!allDone) {
            while (true) {
                ++day;
                vector<vector<long long>> oldBalance = balance;
                vector<vector<long long>> receive(n, vector<long long>(c, 0));
                vector<vector<long long>> reduce(n, vector<long long>(c, 0));
                for (int i = 0; i < n; ++i) {
                    int nb = (int)neighbors[i].size();
                    if (nb == 0) continue;
                    for (int m = 0; m < c; ++m) {
                        long long amount = oldBalance[i][m];
                        if (amount == 0) continue;
                        long long send = amount / 1000;
                        if (send == 0) continue;
                        reduce[i][m] += send * nb;
                        for (int j : neighbors[i]) {
                            receive[j][m] += send;
                        }
                    }
                }
                for (int i = 0; i < n; ++i) {
                    for (int m = 0; m < c; ++m) {
                        balance[i][m] = oldBalance[i][m] - reduce[i][m] + receive[i][m];
                    }
                }
                bool allNow = true;
                for (int i = 0; i < c; ++i) {
                    if (completedDays[i] != -1) continue;
                    if (isCountryComplete(i)) {
                        completedDays[i] = day;
                    } else {
                        allNow = false;
                    }
                }
                if (allNow) break;
            }
        }
        vector<int> order(c);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            if (completedDays[a] != completedDays[b]) return completedDays[a] < completedDays[b];
            return names[a] < names[b];
        });
        cout << "Case Number " << caseNo << "\n";
        for (int idx : order) {
            cout << string(3, ' ') << names[idx] << string(3, ' ') << completedDays[idx] << "\n";
        }
    }
    return 0;
}
