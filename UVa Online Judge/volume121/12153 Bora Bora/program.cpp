// Bora Bora
// UVa ID: 12153
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int P, M, N;
    while (cin >> P >> M >> N && (P || M || N)) {
        vector<int> allCards;
        for (int i = 0; i < N; ++i) {
            int rank;
            char suitChar;
            cin >> rank >> suitChar;
            int suit;
            if (suitChar == 'C') suit = 0;
            else if (suitChar == 'D') suit = 1;
            else if (suitChar == 'H') suit = 2;
            else suit = 3;
            allCards.push_back(rank * 4 + suit);
        }
        vector<deque<int>> hands(P);
        for (int i = 0; i < P; ++i)
            for (int j = 0; j < M; ++j)
                hands[i].push_back(allCards[i * M + j]);
        int topCard = allCards[P * M];
        int topRank = topCard / 4;
        int topSuit = topCard % 4;
        deque<int> stock;
        for (int i = P * M + 1; i < N; ++i)
            stock.push_back(allCards[i]);
        int direction = 1; // 1 顺时针, -1 逆时针
        int cur = 0;       // 当前玩家编号(0‑based)
        // 处理初始弃牌堆顶牌的特殊效果
        if (topRank == 12) {            // Queen
            direction = -direction;
        } else if (topRank == 7) {      // Seven
            for (int i = 0; i < 2 && !stock.empty(); ++i) {
                int c = stock.front();
                stock.pop_front();
                hands[0].push_back(c);
            }
            cur = (cur + direction + P) % P;
        } else if (topRank == 1) {      // Ace
            if (!stock.empty()) {
                int c = stock.front();
                stock.pop_front();
                hands[0].push_back(c);
            }
            cur = (cur + direction + P) % P;
        } else if (topRank == 11) {     // Jack
            cur = (cur + direction + P) % P;
        }
        // 主游戏循环
        while (true) {
            int player = cur;
            // 在手中寻找最高价值的可出牌
            int bestIdx = -1, bestRank = -1, bestSuit = -1;
            for (int i = 0; i < (int)hands[player].size(); ++i) {
                int code = hands[player][i];
                int r = code / 4;
                int s = code % 4;
                if (r == topRank || s == topSuit) {
                    if (bestIdx == -1 || r > bestRank || (r == bestRank && s > bestSuit)) {
                        bestIdx = i;
                        bestRank = r;
                        bestSuit = s;
                    }
                }
            }
            if (bestIdx != -1) {
                // 出牌
                int cardCode = hands[player][bestIdx];
                hands[player].erase(hands[player].begin() + bestIdx);
                topRank = cardCode / 4;
                topSuit = cardCode % 4;
                if (hands[player].empty()) {
                    cout << player + 1 << "\n";
                    break;
                }
                int r = topRank;
                if (r == 12) {          // Queen
                    direction = -direction;
                    cur = (player + direction + P) % P;
                } else if (r == 7) {    // Seven
                    int next = (player + direction + P) % P;
                    for (int i = 0; i < 2 && !stock.empty(); ++i) {
                        int c = stock.front();
                        stock.pop_front();
                        hands[next].push_back(c);
                    }
                    cur = (next + direction + P) % P;
                } else if (r == 1) {    // Ace
                    int next = (player + direction + P) % P;
                    if (!stock.empty()) {
                        int c = stock.front();
                        stock.pop_front();
                        hands[next].push_back(c);
                    }
                    cur = (next + direction + P) % P;
                } else if (r == 11) {   // Jack
                    int next = (player + direction + P) % P;
                    cur = (next + direction + P) % P;
                } else {                // 普通牌
                    cur = (player + direction + P) % P;
                }
            } else {
                // 无牌可出，必须从stock抽一张
                if (stock.empty()) break; // 题目保证不会发生
                int cardCode = stock.front();
                stock.pop_front();
                hands[player].push_back(cardCode);
                int r = cardCode / 4;
                int s = cardCode % 4;
                if (r == topRank || s == topSuit) {
                    // 刚抽到的牌可以出，必须出它
                    hands[player].pop_back(); // 移除刚加入的牌
                    topRank = r;
                    topSuit = s;
                    if (hands[player].empty()) {
                        cout << player + 1 << "\n";
                        break;
                    }
                    if (r == 12) {
                        direction = -direction;
                        cur = (player + direction + P) % P;
                    } else if (r == 7) {
                        int next = (player + direction + P) % P;
                        for (int i = 0; i < 2 && !stock.empty(); ++i) {
                            int c = stock.front();
                            stock.pop_front();
                            hands[next].push_back(c);
                        }
                        cur = (next + direction + P) % P;
                    } else if (r == 1) {
                        int next = (player + direction + P) % P;
                        if (!stock.empty()) {
                            int c = stock.front();
                            stock.pop_front();
                            hands[next].push_back(c);
                        }
                        cur = (next + direction + P) % P;
                    } else if (r == 11) {
                        int next = (player + direction + P) % P;
                        cur = (next + direction + P) % P;
                    } else {
                        cur = (player + direction + P) % P;
                    }
                } else {
                    // 抽到的牌不能出，回合结束
                    cur = (player + direction + P) % P;
                }
            }
        }
    }
    return 0;
}
