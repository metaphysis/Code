// Dinner Hall
// UVa ID: 12189
// Verdict: Accepted
// Submission Date: 2026-01-19
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Card {
    int time; // 转换为秒，方便比较
    char event;
};

bool compareCard(const Card& a, const Card& b) { return a.time < b.time; }

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<Card> cards(n);
        for (int i = 0; i < n; ++i) {
            int h, m, s;
            char colon;
            cin >> h >> colon >> m >> colon >> s;
            cards[i].time = h * 3600 + m * 60 + s;
            cin >> cards[i].event;
        }
        // 按时间排序
        sort(cards.begin(), cards.end(), compareCard);
        // 统计已知事件
        int knownE = 0, knownX = 0, unknown = 0;
        for (const auto& card : cards) {
            if (card.event == 'E') knownE++;
            else if (card.event == 'X') knownX++;
            else unknown++;
        }
        // 计算未知事件中应分配为 'E' 的数量
        int eCount = (knownX - knownE + unknown) / 2;
        // 最早的一些 '?' 分配为 'E'，其余为 'X'
        int eUsed = 0;
        vector<char> assigned(n);
        for (int i = 0; i < n; ++i) {
            if (cards[i].event == '?') {
                if (eUsed < eCount) {
                    assigned[i] = 'E';
                    eUsed++;
                } else assigned[i] = 'X';
            } else assigned[i] = cards[i].event;
        }
        // 模拟过程，计算最大人数
        int current = 0, maxPeople = 0;
        for (int i = 0; i < n; ++i) {
            if (assigned[i] == 'E') current++;
            else current--;
            maxPeople = max(maxPeople, current);
        }
        cout << maxPeople << endl;
    }
    return 0;
}
