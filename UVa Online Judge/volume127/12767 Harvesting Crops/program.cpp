#include <bits/stdc++.h>
using namespace std;

const int maxTime = 2880;
const int maxCrop = 1000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        int bestProfit[maxTime + 1], cropGrow[maxCrop + 1], cropProfit[maxCrop + 1], dp[maxTime + 2];
        bool available[maxTime + 1];
        fill(bestProfit, bestProfit + maxTime + 1, 0);
        fill(available, available + maxTime + 1, false);
        for (int i = 0; i < n; i++) {
            int grow, profit;
            cin >> grow >> profit;
            bestProfit[grow] = max(bestProfit[grow], profit);
        }
        int cropCount = 0, maxSeen = 0;
        for (int grow = 1; grow <= maxTime; grow++) {
            if (bestProfit[grow] > maxSeen) {
                maxSeen = bestProfit[grow];
                cropGrow[cropCount] = grow;
                cropProfit[cropCount] = bestProfit[grow];
                cropCount++;
            }
        }
        for (int i = 0; i < m; i++) {
            int start, end;
            cin >> start >> end;
            for (int time = start; time <= end; time++)
                available[time] = true;
        }
        dp[maxTime + 1] = 0;
        for (int time = maxTime; time >= 1; time--) {
            dp[time] = dp[time + 1];
            if (available[time]) {
                for (int i = 0; i < cropCount; i++) {
                    int nextTime = time + cropGrow[i];
                    if (nextTime <= maxTime + 1)
                        dp[time] = max(dp[time], cropProfit[i] + dp[nextTime]);
                }
            }
        }
        cout << dp[1] << '\n';
    }
    return 0;
}
