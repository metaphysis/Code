// Water Crisis
// UVa ID: 11187
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.080s
// https://blog.csdn.net/metaphysis/article/details/163268999

#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
const int maxTime = 1200;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; ++testCase) {
        int n;
        cin >> n;
        vector<int> demand(n, 0);
        for (int i = 1; i < n; ++i)
            cin >> demand[i];
        vector<vector<int>> distance(n, vector<int>(n, inf));
        for (int i = 0; i < n; ++i)
            distance[i][i] = 0;
        while (true) {
            int u, v, t;
            cin >> u >> v >> t;
            if (u == 0 && v == 0 && t == 0)
                break;
            --u;
            --v;
            distance[u][v] = min(distance[u][v], t);
            distance[v][u] = min(distance[v][u], t);
        }
        // 使用 Floyd 算法求任意两点之间的最短路
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (distance[i][k] < inf && distance[k][j] < inf)
                        distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
        vector<int> tasks;
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < demand[i]; ++j)
                tasks.push_back(distance[0][i] * 2);
        int wordCount = (maxTime + 64) / 64;
        int rowSize = wordCount;
        vector<unsigned long long> dp((maxTime + 1) * rowSize, 0);
        dp[0] = 1ULL;
        int processedTime = 0;
        for (int taskTime : tasks) {
            vector<unsigned long long> nextDp = dp;
            // 将当前任务分配给第一辆卡车
            if (taskTime <= maxTime)
                for (int firstTime = 0; firstTime + taskTime <= maxTime; ++firstTime)
                    for (int word = 0; word < wordCount; ++word)
                        nextDp[(firstTime + taskTime) * rowSize + word] |= dp[firstTime * rowSize + word];
            // 将当前任务分配给第二辆卡车
            int wordShift = taskTime / 64;
            int bitShift = taskTime % 64;
            for (int firstTime = 0; firstTime <= maxTime; ++firstTime) {
                int sourceBase = firstTime * rowSize;
                int targetBase = firstTime * rowSize;
                for (int word = wordCount - 1; word >= 0; --word) {
                    unsigned long long value = dp[sourceBase + word];
                    if (value == 0)
                        continue;
                    int targetWord = word + wordShift;
                    if (targetWord >= wordCount)
                        continue;
                    nextDp[targetBase + targetWord] |= value << bitShift;
                    if (bitShift > 0 && targetWord + 1 < wordCount)
                        nextDp[targetBase + targetWord + 1] |= value >> (64 - bitShift);
                }
            }
            dp.swap(nextDp);
            processedTime += taskTime;
        }
        int answer = inf;
        for (int firstTime = 0; firstTime <= maxTime; ++firstTime) {
            int base = firstTime * rowSize;
            for (int word = 0; word < wordCount; ++word) {
                unsigned long long state = dp[base + word];
                while (state != 0) {
                    int bit = __builtin_ctzll(state);
                    int secondTime = word * 64 + bit;
                    if (secondTime <= maxTime && firstTime + secondTime <= processedTime) {
                        int thirdTime = processedTime - firstTime - secondTime;
                        if (thirdTime <= maxTime)
                            answer = min(answer, max(firstTime, max(secondTime, thirdTime)));
                    }
                    state &= state - 1;
                }
            }
        }
        cout << "Test Case #: " << testCase << '\n';
        if (answer > maxTime) cout << "Too few trucks\n";
        else cout << answer << " mins\n";
    }
    return 0;
}
