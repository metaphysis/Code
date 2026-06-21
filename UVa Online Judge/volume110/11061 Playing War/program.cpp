// Playing War
// UVa ID: 11061
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.640s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

double prob[4][4][4]; // prob[A][D][k]：A个攻击骰子、D个防御骰子时，攻击方胜k次的概率

// 生成所有长度为num的骰子点数（1~6）组合
void genRolls(int num, vector<int>& cur, vector<vector<int>>& all) {
    if ((int)cur.size() == num) {
        all.push_back(cur);
        return;
    }
    for (int i = 1; i <= 6; ++i) {
        cur.push_back(i);
        genRolls(num, cur, all);
        cur.pop_back();
    }
}

// 预计算所有(A,D)组合下的概率分布
void precompute() {
    for (int A = 1; A <= 3; ++A) {
        for (int D = 1; D <= 3; ++D) {
            vector<vector<int>> att, def;
            vector<int> cur;
            genRolls(A, cur, att);
            genRolls(D, cur, def);
            int total = (int)att.size() * (int)def.size();
            int m = min(A, D);
            vector<int> cnt(m + 1, 0);
            for (auto& a : att) {
                sort(a.begin(), a.end(), greater<int>());
                for (auto& d : def) {
                    sort(d.begin(), d.end(), greater<int>());
                    int win = 0;
                    for (int i = 0; i < m; ++i)
                        if (a[i] > d[i]) ++win;
                    ++cnt[win];
                }
            }
            for (int k = 0; k <= m; ++k)
                prob[A][D][k] = (double)cnt[k] / total;
        }
    }
}

int main() {
    precompute();

    vector<int> queries;
    int x;
    while (cin >> x && x != 0)
        queries.push_back(x);
    if (queries.empty()) return 0;

    int maxX = *max_element(queries.begin(), queries.end());
    vector<int> ans(maxX + 1, 0);
    vector<bool> found(maxX + 1, false);

    // dp[4][maxX+1] 滚动数组，dp[i][d] 表示进攻方军队数为 i（取模4）时的概率
    vector<vector<double>> dp(4, vector<double>(maxX + 1, 0.0));

    int foundCount = 0;
    for (int a = 2; ; ++a) {
        int A = min(3, a - 1);
        int curIdx = a % 4;

        for (int d = 1; d <= maxX; ++d) {
            int D = min(3, d);
            int m = min(A, D);
            double sum = 0.0;
            for (int k = 0; k <= m; ++k) {
                int la = m - k; // 进攻方损失
                int ld = k;     // 防守方损失
                double p = prob[A][D][k];
                if (d - ld == 0) sum += p;
                else if (a - la <= 1) sum += 0.0;
                else sum += p * dp[(a - la) % 4][d - ld];
            }
            dp[curIdx][d] = sum;
        }

        // 检查是否有查询首次满足条件
        for (int X : queries) {
            if (!found[X] && dp[curIdx][X] > 0.5 + 1e-9) {
                found[X] = true;
                ans[X] = a;
                ++foundCount;
            }
        }
        if (foundCount == (int)queries.size()) break;
        // 安全上限（理论上足够，防止意外）
        if (a > 100000) break;
    }

    for (int X : queries)
        cout << ans[X] << '\n';

    return 0;
}
