// Double Patience
// UVa ID: 1637
// Verdict: Accepted
// Submission Date: 2025-10-26
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 全局变量存储输入牌堆（反向存储：索引0是顶部牌，索引3是底部牌）
vector<vector<string>> piles(9, vector<string>(4));
map<int, double> dp; // 记忆化：state -> 获胜概率

// 从状态编码中获取各堆顶部位置
void decode(int state, vector<int>& tops) {
    for (int i = 0; i < 9; i++) tops[i] = state % 5, state /= 5;
}

// 将各堆顶部位置编码为整数
int encode(const vector<int>& tops) {
    int state = 0, base = 1;
    for (int i = 0; i < 9; i++) state += tops[i] * base, base *= 5;
    return state;
}

// 递归计算获胜概率
double dfs(int state) {
    if (dp.count(state)) return dp[state];
    vector<int> tops(9);
    decode(state, tops);
    // 检查是否所有堆都空了
    bool allEmpty = true;
    for (int i = 0; i < 9; i++) {
        if (tops[i] < 4) {
            allEmpty = false;
            break;
        }
    }
    if (allEmpty) return 1.0;
    // 找出所有可移除的牌对
    vector<pair<int, int>> moves;
    for (int i = 0; i < 9; i++) {
        if (tops[i] >= 4) continue; // 堆空
        for (int j = i + 1; j < 9; j++) {
            if (tops[j] >= 4) continue;
            // 现在 piles[i][tops[i]] 是顶部牌（因为反向存储）
            string card1 = piles[i][tops[i]];
            string card2 = piles[j][tops[j]];
            if (card1[0] == card2[0]) // 相同点数
                moves.push_back({i, j});
        }
    }
    if (moves.empty()) return 0.0; // 无合法移动，输
    double p = 0.0;
    int k = moves.size();
    for (auto& move : moves) {
        int i = move.first, j = move.second;
        vector<int> newTops = tops;
        newTops[i]++;  // 移除顶部牌，索引递增访问下面的牌
        newTops[j]++;
        int newState = encode(newTops);
        p += dfs(newState);
    }
    p /= k;
    dp[state] = p;
    return p;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (true) {
        // 读取输入并反向存储
        for (int i = 0; i < 9; i++)
            // 正向读入：底部牌 → 顶部牌
            // 反向存储：索引0存顶部牌，索引3存底部牌
            for (int j = 3; j >= 0; j--)
                if (!(cin >> piles[i][j]))
                    return 0; // 输入结束
        dp.clear();
        // 初始时每堆顶部是第0张牌（因为反向存储后索引0是顶部牌）
        vector<int> startTops(9, 0);
        int startState = encode(startTops);
        double r = dfs(startState);
        cout << fixed << setprecision(6) << r << "\n";
    }
    return 0;
}
