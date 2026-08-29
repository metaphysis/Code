#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long long openTime = 8LL * 60 * 60;
    long long s, e, r, f, days;
    bool firstCase = true;
    while (cin >> s >> e >> r >> f >> days) {
        if (!firstCase) cout << '\n';
        firstCase = false;
        // 使用整数除法，即 floor(28800 / s)。
        long long saleCount = openTime / s;
        long long repairCapacity = (openTime / r) * e;
        // qCnt[day] 表示第 day 天早晨因夜间损坏而进入队列的客户数。
        vector<long long> qCnt(days, 0);
        long long faultyCount = 0;
        long long repairCount = 0;
        long long replaceCount = 0;
        long long totalQueue = 0;
        // 指向当前队列中最早的、尚未处理完的批次。
        long long frontDay = 0;
        for (long long day = 0; day < days; ++day) {
            // 1. 前一天夜间损坏的故障产品，在当天早晨进入维修队列。
            long long brokenCount = faultyCount * f / 100;
            qCnt[day] = brokenCount;
            totalQueue += brokenCount;
            faultyCount -= brokenCount;
            // 2. 当天销售。
            faultyCount += saleCount;
            // 3. 仅周一至周五营业、维修及替换。
            if (day % 7 < 5) {
                long long remainRepair = repairCapacity;
                // 按先进先出原则维修。
                while (remainRepair > 0 && frontDay <= day) {
                    if (qCnt[frontDay] == 0) {
                        ++frontDay;
                        continue;
                    }
                    long long repaired = min(remainRepair, qCnt[frontDay]);
                    qCnt[frontDay] -= repaired;
                    remainRepair -= repaired;
                    repairCount += repaired;
                    totalQueue -= repaired;

                    if (qCnt[frontDay] == 0)
                        ++frontDay;
                }
                // 营业结束后，替换已经等待至少三天的客户。
                // 周末不提供替换服务，因此该逻辑必须在 workday 内。
                while (frontDay <= day - 2) {
                    if (qCnt[frontDay] > 0) {
                        long long replaced = qCnt[frontDay];
                        replaceCount += replaced;
                        faultyCount += replaced;
                        totalQueue -= replaced;
                        qCnt[frontDay] = 0;
                    }
                    ++frontDay;
                }
            }
        }
        cout << replaceCount << '\n';
        cout << repairCount << '\n';
        cout << faultyCount << '\n';
        cout << totalQueue << '\n';
    }
    return 0;
}
