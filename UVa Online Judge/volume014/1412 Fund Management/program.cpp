// Fund Management
// UVa ID: 1412
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 0.170s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_STATES = 15000;
const double INF = -1e18;

double initialCash;
int totalDays, stockCount, maxTotalLots;
char stockNames[10][10];
int lotSizes[10], maxLotsPerStock[10];
double stockCosts[10][105]; // 存储每手股票的成本 = price * lotSize

vector<vector<int>> allStates;
map<vector<int>, int> stateToId;
int buyTransitions[MAX_STATES][10];
int sellTransitions[MAX_STATES][10];
double dp[105][MAX_STATES];
int previousState[105][MAX_STATES];
int operations[105][MAX_STATES];

void generateStates(vector<int>& currentState, int stockIndex, int currentTotalLots) {
    if (stockIndex == stockCount) {
        stateToId[currentState] = allStates.size();
        allStates.push_back(currentState);
        return;
    }
    
    for (int lots = 0; lots <= maxLotsPerStock[stockIndex] && currentTotalLots + lots <= maxTotalLots; lots++) {
        currentState[stockIndex] = lots;
        generateStates(currentState, stockIndex + 1, currentTotalLots + lots);
    }
}

void initializeTransitions() {
    for (int stateId = 0; stateId < allStates.size(); stateId++) {
        for (int stockIdx = 0; stockIdx < stockCount; stockIdx++) {
            // 计算当前状态的总手数
            int totalLots = 0;
            for (int lots : allStates[stateId]) totalLots += lots;
            
            buyTransitions[stateId][stockIdx] = sellTransitions[stateId][stockIdx] = -1;
            
            // 卖出转移：如果持有该股票，可以卖出一手
            if (allStates[stateId][stockIdx] > 0) {
                vector<int> newState = allStates[stateId];
                newState[stockIdx]--;
                sellTransitions[stateId][stockIdx] = stateToId[newState];
            }
            
            // 买入转移：如果未达到该股票和总手数限制，可以买入一手
            if (allStates[stateId][stockIdx] < maxLotsPerStock[stockIdx] && totalLots < maxTotalLots) {
                vector<int> newState = allStates[stateId];
                newState[stockIdx]++;
                buyTransitions[stateId][stockIdx] = stateToId[newState];
            }
        }
    }
}

void updateState(int day, int currentState, int nextState, double newCash, int operation) {
    if (newCash > dp[day + 1][nextState]) {
        dp[day + 1][nextState] = newCash;
        previousState[day + 1][nextState] = currentState;
        operations[day + 1][nextState] = operation;
    }
}

void reconstructSolution(int day, int state) {
    if (day == 0) return;
    reconstructSolution(day - 1, previousState[day][state]);
    
    int op = operations[day][state];
    if (op == 0) cout << "HOLD" << endl;
    else if (op > 0) cout << "BUY " << stockNames[op - 1] << endl;
    else cout << "SELL " << stockNames[-op - 1] << endl;
}

void solve() {
    allStates.clear();
    stateToId.clear();
    
    vector<int> initialState(stockCount, 0);
    generateStates(initialState, 0, 0);
    initializeTransitions();
    
    // 初始化DP数组
    for (int day = 0; day <= totalDays; day++)
        for (int stateId = 0; stateId < allStates.size(); stateId++)
            dp[day][stateId] = INF;
    
    dp[0][0] = initialCash; // 初始状态：空仓
    
    // DP主循环
    for (int day = 0; day < totalDays; day++) {
        for (int stateId = 0; stateId < allStates.size(); stateId++) {
            double currentCash = dp[day][stateId];
            if (currentCash < -1e10) continue; // 跳过不可达状态
            
            // HOLD操作：保持当前状态
            updateState(day, stateId, stateId, currentCash, 0);
            
            // 尝试买入和卖出各股票
            for (int stockIdx = 0; stockIdx < stockCount; stockIdx++) {
                // 买入操作
                if (buyTransitions[stateId][stockIdx] != -1) {
                    double cost = stockCosts[stockIdx][day + 1]; // 注意：这里使用day+1的价格
                    if (currentCash >= cost - 1e-9) { // 现金足够
                        int nextState = buyTransitions[stateId][stockIdx];
                        updateState(day, stateId, nextState, currentCash - cost, stockIdx + 1);
                    }
                }
                
                // 卖出操作
                if (sellTransitions[stateId][stockIdx] != -1) {
                    double revenue = stockCosts[stockIdx][day + 1]; // 注意：这里使用day+1的价格
                    int nextState = sellTransitions[stateId][stockIdx];
                    updateState(day, stateId, nextState, currentCash + revenue, -stockIdx - 1);
                }
            }
        }
    }
    
    // 输出最终现金（必须回到空仓状态）
    printf("%.2lf\n", dp[totalDays][0]);
    
    // 重构操作序列
    reconstructSolution(totalDays, 0);
}

int main() {
    while (scanf("%lf%d%d%d", &initialCash, &totalDays, &stockCount, &maxTotalLots) != EOF) {
        for (int i = 0; i < stockCount; i++) {
            scanf("%s%d%d", stockNames[i], &lotSizes[i], &maxLotsPerStock[i]);
            for (int day = 1; day <= totalDays; day++) {
                double price;
                scanf("%lf", &price);
                stockCosts[i][day] = price * lotSizes[i]; // 预计算每手成本
            }
        }
        solve();
        printf("\n");
    }
    return 0;
}
