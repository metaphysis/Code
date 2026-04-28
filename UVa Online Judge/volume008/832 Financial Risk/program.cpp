// Financial Risk
// UVa ID: 832
// Verdict: Accepted
// Submission Date: 2026-04-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int day;
    long long delta;  // 债务变化量
};

void solve() {
    int numClients;
    cin >> numClients;

    double totalRisk = 0.0;           // 所有客户的总风险
    double totalUncoveredRisk = 0.0;  // 所有客户的未覆盖风险

    for (int i = 0; i < numClients; ++i) {
        long long limit;  // 债务上限
        int numSales;
        cin >> limit >> numSales;

        vector<Event> events;

        for (int j = 0; j < numSales; ++j) {
            long long value;
            int invoiceDay, receiptDay;
            cin >> value >> invoiceDay >> receiptDay;

            events.push_back({invoiceDay, value});   // 发票日增加债务
            events.push_back({receiptDay, -value});  // 收款日减少债务
        }

        // 按天排序事件
        sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
            return a.day < b.day;
        });

        long long currentDebt = 0;
        int prevDay = -1;

        // 扫描时间轴
        for (size_t j = 0; j < events.size(); ++j) {
            int curDay = events[j].day;

            if (prevDay != -1 && curDay > prevDay) {
                double intervalLen = curDay - prevDay;
                totalRisk += currentDebt * intervalLen;
                if (currentDebt > limit)
                    totalUncoveredRisk += (currentDebt - limit) * intervalLen;
            }

            // 应用当前天的所有变化（同一天可能有多笔）
            currentDebt += events[j].delta;
            prevDay = curDay;
        }
    }

    double percent = (totalRisk == 0) ? 0.0 : (totalUncoveredRisk / totalRisk) * 100.0;
    // 截断到两位小数
    percent = floor(percent * 100.0) / 100.0;

    printf("%.2f%%\n", percent);
}

int main() {
    int caseCount;
    cin >> caseCount;

    for (int caseIdx = 0; caseIdx < caseCount; ++caseIdx) {
        if (caseIdx > 0) cout << endl;  // 用例之间空行
        solve();
    }
    return 0;
}
