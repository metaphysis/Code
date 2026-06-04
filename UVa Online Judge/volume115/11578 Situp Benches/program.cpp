// Situp Benches
// UVa ID: 11578
// Verdict: Accepted
// Submission Date: 2026-06-04
// UVa Run Time: 0.890s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int ANGLES[] = {10, 20, 30, 40, 50};
const int ANGLE_CNT = 5;

struct Student {
    int idx, timeSlot, angle;
};

void solve() {
    int n;
    cin >> n;
    vector<Student> stu(n);
    for (int i = 0; i < n; ++i) {
        cin >> stu[i].timeSlot >> stu[i].angle;
        stu[i].idx = i;
    }
    // 按时间槽排序
    sort(stu.begin(), stu.end(), [](const Student& a, const Student& b) {
        return a.timeSlot < b.timeSlot;
    });

    int angleToIdx[60] = {0};
    for (int i = 0; i < ANGLE_CNT; ++i) angleToIdx[ANGLES[i]] = i;

    // dp[pos][a][b] = 最小调整成本
    vector<map<pair<int, int>, int>> dp(n + 1);
    vector<map<pair<int, int>, pair<int, int>>> pre(n + 1);
    vector<map<pair<int, int>, int>> choice(n + 1);

    dp[0][{angleToIdx[10], angleToIdx[10]}] = 0;

    int pos = 0;
    while (pos < n) {
        int curTime = stu[pos].timeSlot;
        int nextPos = pos + 1;
        while (nextPos < n && stu[nextPos].timeSlot == curTime) nextPos++;
        int cnt = nextPos - pos; // 当前时间槽的学生数: 1或2

        if (cnt == 1) {
            // 只有一个学生，可任选凳子
            int curAngle = angleToIdx[stu[pos].angle];
            for (auto& kv : dp[pos]) {
                int a = kv.first.first, b = kv.first.second;
                int curCost = kv.second;
                // 选凳1
                int cost1 = curCost + abs(ANGLES[curAngle] - ANGLES[a]);
                pair<int, int> state1 = {curAngle, b};
                if (!dp[pos + 1].count(state1) || dp[pos + 1][state1] > cost1) {
                    dp[pos + 1][state1] = cost1;
                    pre[pos + 1][state1] = {a, b};
                    choice[pos + 1][state1] = 1;
                }
                // 选凳2
                int cost2 = curCost + abs(ANGLES[curAngle] - ANGLES[b]);
                pair<int, int> state2 = {a, curAngle};
                if (!dp[pos + 1].count(state2) || dp[pos + 1][state2] > cost2) {
                    dp[pos + 1][state2] = cost2;
                    pre[pos + 1][state2] = {a, b};
                    choice[pos + 1][state2] = 2;
                }
            }
        } else { // cnt == 2
            int angle1 = angleToIdx[stu[pos].angle];
            int angle2 = angleToIdx[stu[pos + 1].angle];
            for (auto& kv : dp[pos]) {
                int a = kv.first.first, b = kv.first.second;
                int curCost = kv.second;
                // 分配方式1: 学生1凳1, 学生2凳2
                int cost1 = curCost + abs(ANGLES[angle1] - ANGLES[a]) 
                                   + abs(ANGLES[angle2] - ANGLES[b]);
                pair<int, int> state1 = {angle1, angle2};
                if (!dp[pos + 2].count(state1) || dp[pos + 2][state1] > cost1) {
                    dp[pos + 2][state1] = cost1;
                    pre[pos + 2][state1] = {a, b};
                    choice[pos + 2][state1] = 1; // 第一个学生凳1, 第二个凳2
                }
                // 分配方式2: 学生1凳2, 学生2凳1
                int cost2 = curCost + abs(ANGLES[angle1] - ANGLES[b]) 
                                   + abs(ANGLES[angle2] - ANGLES[a]);
                pair<int, int> state2 = {angle2, angle1};
                if (!dp[pos + 2].count(state2) || dp[pos + 2][state2] > cost2) {
                    dp[pos + 2][state2] = cost2;
                    pre[pos + 2][state2] = {a, b};
                    choice[pos + 2][state2] = 2; // 第一个学生凳2, 第二个凳1
                }
            }
        }
        pos = nextPos;
    }

    // 找最优，加上结束时调回10度的费用
    int minAdjust = INF;
    pair<int, int> bestState;
    for (auto& kv : dp[n]) {
        int a = kv.first.first, b = kv.first.second;
        int totalAdjust = kv.second + abs(ANGLES[a] - 10) + abs(ANGLES[b] - 10);
        if (totalAdjust < minAdjust) {
            minAdjust = totalAdjust;
            bestState = kv.first;
        }
    }

    // 回溯分配方案
    vector<int> assign(n);
    pair<int, int> curState = bestState;
    int curPos = n;
    while (curPos > 0) {
        int timeSlot = stu[curPos - 1].timeSlot;
        int start = curPos - 1;
        while (start > 0 && stu[start - 1].timeSlot == timeSlot) start--;
        int cnt = curPos - start;
        
        if (cnt == 1) {
            int ch = choice[curPos][curState];
            assign[stu[start].idx] = ch;
            curState = pre[curPos][curState];
            curPos = start;
        } else {
            int ch = choice[curPos][curState];
            if (ch == 1) {
                assign[stu[start].idx] = 1;
                assign[stu[start + 1].idx] = 2;
            } else {
                assign[stu[start].idx] = 2;
                assign[stu[start + 1].idx] = 1;
            }
            curState = pre[curPos][curState];
            curPos = start;
        }
    }

    int totalCost = minAdjust + n * 15;
    cout << totalCost << "\n";
    for (int i = 0; i < n; ++i) cout << assign[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
