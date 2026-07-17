// Takeover Wars
// UVa ID: 1290
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.730s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    int caseNumber = 1;
    while (cin >> N >> M) {
        multiset<long long> takeoverHeap, buyoutHeap;
        long long val;
        for (int i = 0; i < N; ++i) { cin >> val; takeoverHeap.insert(val); }
        for (int i = 0; i < M; ++i) { cin >> val; buyoutHeap.insert(val); }
        bool turn = true; // true 表示 Takeover 行动
        while (!takeoverHeap.empty() && !buyoutHeap.empty()) {
            multiset<long long>& cur = turn ? takeoverHeap : buyoutHeap;
            multiset<long long>& opp = turn ? buyoutHeap : takeoverHeap;
            long long curMax = *cur.rbegin();
            long long curSum = curMax;
            if (cur.size() >= 2) {
                auto itMax = prev(cur.end());
                long long second = *prev(itMax);
                curSum = curMax + second;
            }
            long long oppMax = *opp.rbegin();
            long long oppSum = oppMax;
            if (opp.size() >= 2) {
                auto itMax = prev(opp.end());
                long long second = *prev(itMax);
                oppSum = oppMax + second;
            }
            if (cur.size() >= 2 && curSum > oppSum) {
                auto itMax = prev(cur.end());
                long long a = *itMax;
                cur.erase(itMax);
                auto itSecond = prev(cur.end());
                long long b = *itSecond;
                cur.erase(itSecond);
                cur.insert(a + b);
            } else if (curMax > oppMax) {
                opp.erase(prev(opp.end()));
            } else if (cur.size() >= 2) {
                auto itMax = prev(cur.end());
                long long a = *itMax;
                cur.erase(itMax);
                auto itSecond = prev(cur.end());
                long long b = *itSecond;
                cur.erase(itSecond);
                cur.insert(a + b);
            }
            turn = !turn;
        }
        cout << "Case " << caseNumber++ << ": ";
        if (takeoverHeap.empty()) cout << "Buyout Limited\n";
        else cout << "Takeover Incorporated\n";
    }
    return 0;
}
