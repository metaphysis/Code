// Guess
// UVa ID: 1612
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.070s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <functional>
#include <bitset>

using namespace std;

const double EPS = 1e-9;
const double INF = 1e9;

struct Player {
    int id;
    double scores[3];
    vector<double> possibleTotals; // 所有可能的得分组合总和
};

int n;
vector<Player> players;
vector<int> rankOrder;

// 生成所有可能的得分组合
void generatePossibleTotals(Player& player) {
    player.possibleTotals.clear();
    for (int mask = 0; mask < 8; ++mask) {
        double total = 0.0;
        for (int i = 0; i < 3; ++i) {
            if (mask & (1 << i)) {
                total += player.scores[i];
            }
        }
        player.possibleTotals.push_back(total);
    }
    // 排序并去重
    sort(player.possibleTotals.begin(), player.possibleTotals.end());
    player.possibleTotals.erase(unique(player.possibleTotals.begin(), player.possibleTotals.end()), 
                               player.possibleTotals.end());
}

// 检查在给定最后一名总分的情况下，排名是否可能
bool check(double lastScore) {
    // dp[i] 表示第i名选手所有可能的分数（从0开始）
    vector<vector<double>> dp(n);
    
    // 初始化最后一名
    int lastId = rankOrder[n - 1];
    for (double score : players[lastId].possibleTotals) {
        if (fabs(score - lastScore) < EPS || score > lastScore - EPS) {
            dp[n - 1].push_back(score);
        }
    }
    if (dp[n - 1].empty()) return false;
    
    // 从倒数第二名向前处理
    for (int i = n - 2; i >= 0; --i) {
        int currentId = rankOrder[i];
        int nextId = rankOrder[i + 1];
        
        for (double currentScore : players[currentId].possibleTotals) {
            // 检查是否满足与下一名的约束
            for (double nextScore : dp[i + 1]) {
                if (currentId < nextId) {
                    // ID更小，可以相等或更大
                    if (currentScore > nextScore - EPS) {
                        dp[i].push_back(currentScore);
                        break; // 找到一个满足条件的即可
                    }
                } else {
                    // ID更大，必须严格大于
                    if (currentScore > nextScore + EPS) {
                        dp[i].push_back(currentScore);
                        break; // 找到一个满足条件的即可
                    }
                }
            }
        }
        
        // 去重
        sort(dp[i].begin(), dp[i].end());
        dp[i].erase(unique(dp[i].begin(), dp[i].end()), dp[i].end());
        
        if (dp[i].empty()) return false;
    }
    
    return true;
}

double solve() {
    // 为每个选手生成所有可能的得分组合
    for (int i = 0; i < n; ++i) {
        generatePossibleTotals(players[i]);
    }
    
    // 获取最后一名的所有可能分数
    int lastId = rankOrder[n - 1];
    vector<double> candidateScores = players[lastId].possibleTotals;
    sort(candidateScores.begin(), candidateScores.end());
    
    // 二分搜索最后一名的最高可能总分
    double ans = -1.0;
    for (double score : candidateScores) {
        if (check(score)) {
            ans = score;
        }
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int caseNum = 1;
    while (cin >> n && n != 0) {
        players.resize(n);
        rankOrder.resize(n);
        
        // 读取选手数据
        for (int i = 0; i < n; ++i) {
            players[i].id = i;
            cin >> players[i].scores[0] >> players[i].scores[1] >> players[i].scores[2];
        }
        
        // 读取排名顺序
        for (int i = 0; i < n; ++i) {
            int id;
            cin >> id;
            rankOrder[i] = id - 1; // 转换为 0-based 索引
        }
        
        double result = solve();
        
        cout << "Case " << caseNum << ": ";
        if (result < 0) {
            cout << "No solution" << endl;
        } else {
            cout << fixed << setprecision(2) << result << endl;
        }
        
        caseNum++;
    }
    
    return 0;
}
