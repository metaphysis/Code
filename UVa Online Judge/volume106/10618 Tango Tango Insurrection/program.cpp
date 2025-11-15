// Tango Tango Insurrection
// UVa ID: 10618
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define NO_MOVE 0
#define LEFT_FOOT 1
#define RIGHT_FOOT 2

const int INF = INT_MAX / 2;
const int MAXN = 75;

#define REST -1
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

int charToPos(char c) {
    switch(c) {
        case 'U': return UP;
        case 'L': return LEFT;
        case 'D': return DOWN;
        case 'R': return RIGHT;
        default: return REST;
    }
}

bool canMove(int foot, int left, int right, int to) {
    if (foot == LEFT_FOOT) {
        // 交叉状态，左脚只能原地踏
        if (left == UP && right == LEFT)
            if (to != UP)
                return false;
        if (left == DOWN && right == LEFT)
            if (to != DOWN)
                return false;
        // 不能移动到右脚所在位置
        if (to == right) return false;
    } else {
        // 交叉状态，右脚只能原地踏
        if (right == UP && left == RIGHT)
            if (to != UP)
                return false;
        if (right == DOWN && left == RIGHT)
            if (to != DOWN)
                return false;
        // 不能移动到左脚所在位置
        if (to == left) return false;
    }
    return true;
}

int getCost(int lastFoot, int currentFoot, int from, int to) {
    // 原地踏
    if (from == to) return lastFoot == currentFoot ? 3 : 1;
    // 对向踏
    if (from + to == LEFT + RIGHT || from + to == UP + DOWN) return lastFoot == currentFoot ? 7 : 1;
    // 相邻踏
    return lastFoot == currentFoot ? 5 : 1;
}

struct State {
    int cost;
    int prevLeft;
    int prevRight;
    int prevAction;
};

State dp[MAXN][4][4][3];

int main() {
    string sequence;
    while (cin >> sequence) {
        if (sequence == "#") break;
        
        int n = sequence.length();
        
        // 初始化dp数组
        for (int i = 0; i <= n; i++) {
            for (int l = 0; l < 4; l++) {
                for (int r = 0; r < 4; r++) {
                    for (int a = 0; a < 3; a++) {
                        dp[i][l][r][a] = {INF, -1, -1, -1};
                    }
                }
            }
        }
        
        dp[0][1][3][0] = {0, -1, -1, -1};
        
        for (int t = 0; t < n; t++) {
            int target = charToPos(sequence[t]);
            
            for (int left = 0; left < 4; left++) {
                for (int right = 0; right < 4; right++) {
                    if (left == right) continue;
                    for (int lastAction = 0; lastAction < 3; lastAction++) {
                        if (dp[t][left][right][lastAction].cost == INF) continue;
                        int currentCost = dp[t][left][right][lastAction].cost;
                        if (target == REST) {
                            // 不移动
                            if (dp[t + 1][left][right][0].cost > currentCost) {
                                dp[t + 1][left][right][0] = {currentCost, left, right, lastAction};
                            }
                            // 左脚移动
                            for (int newLeft = 0; newLeft < 4; newLeft++) {
                                if (canMove(LEFT_FOOT, left, right, newLeft)) {
                                    int cost = getCost(lastAction, LEFT_FOOT, left, newLeft);
                                    if (dp[t + 1][newLeft][right][LEFT_FOOT].cost > currentCost + cost) {
                                        dp[t + 1][newLeft][right][LEFT_FOOT] = {currentCost + cost, left, right, lastAction};
                                    }
                                }
                            }
                            // 右脚移动
                            for (int newRight = 0; newRight < 4; newRight++) {
                                if (canMove(RIGHT_FOOT, left, right, newRight)) {
                                    int cost = getCost(lastAction, RIGHT_FOOT, right, newRight);
                                    if (dp[t + 1][left][newRight][RIGHT_FOOT].cost > currentCost + cost) {
                                        dp[t + 1][left][newRight][RIGHT_FOOT] = {currentCost + cost, left, right, lastAction};
                                    }
                                }
                            }
                        } else {
                            // 左脚能否踩踏目标
                            if (canMove(LEFT_FOOT, left, right, target)) {
                                int cost = getCost(lastAction, LEFT_FOOT, left, target);
                                if (dp[t + 1][target][right][LEFT_FOOT].cost > currentCost + cost) {
                                    dp[t + 1][target][right][LEFT_FOOT] = {currentCost + cost, left, right, lastAction};
                                }
                            }
                            // 右脚能否踩踏目标
                            if (canMove(RIGHT_FOOT, left, right, target)) {
                                int cost = getCost(lastAction, RIGHT_FOOT, right, target);
                                if (dp[t + 1][left][target][RIGHT_FOOT].cost > currentCost + cost) {
                                    dp[t + 1][left][target][RIGHT_FOOT] = {currentCost + cost, left, right, lastAction};
                                }
                            }
                        }
                    }
                }
            }
        }
        
        int minCost = INF;
        int bestLeft = 0, bestRight = 0, bestAction = 0;
        for (int left = 0; left < 4; left++) {
            for (int right = 0; right < 4; right++) {
                if (left == right) continue;
                for (int action = 0; action < 3; action++) {
                    if (dp[n][left][right][action].cost < minCost) {
                        minCost = dp[n][left][right][action].cost;
                        bestLeft = left;
                        bestRight = right;
                        bestAction = action;
                    }
                }
            }
        }
        
        string result(n, '.');
        int leftPos = bestLeft, rightPos = bestRight, action = bestAction;
        
        for (int t = n; t > 0; t--) {
            if (action == LEFT_FOOT) {
                result[t - 1] = 'L';
            } else if (action == RIGHT_FOOT) {
                result[t - 1] = 'R';
            }
            
            State prev = dp[t][leftPos][rightPos][action];
            leftPos = prev.prevLeft;
            rightPos = prev.prevRight;
            action = prev.prevAction;
        }
        
        cout << result << endl;
    }
    
    return 0;
}
