[UVa 131 The Psychic Poker Player](https://blog.csdn.net/metaphysis/article/details/156786863)

## 题目描述

在 $5$ 张牌抽牌扑克（$5$$\texttt{-card draw poker}$）游戏中，玩家先获得 $5$ 张手牌（可以查看）。然后玩家可以选择丢弃 $0$ 到 $5$ 张牌，并从牌堆顶部取相同数量的牌替换。目标是通过替换使最终手牌的牌型价值最大化。扑克牌型的价值从高到低依次为（完整列表见题目末尾）：

- 同花顺（$\texttt{straight-flush}$）
- 四条（$\texttt{four-of-a-kind}$）
- 葫芦（$\texttt{full-house}$）
- 同花（$\texttt{flush}$）
- 顺子（$\texttt{straight}$）
- 三条（$\texttt{three-of-a-kind}$）
- 两对（$\texttt{two-pairs}$）
- 一对（$\texttt{one-pair}$）
- 高牌（$\texttt{highest-card}$）

**本题假设玩家有“透视”能力，可以提前知道牌堆顶部的 $5$ 张牌。** 要求编写程序，告诉玩家应该丢弃哪些牌，才能使得最终手牌的牌型价值最高。

---

## 输入格式

输入包含多行，每行包含 $10$ 张牌：前 $5$ 张是初始手牌，后 $5$ 张是牌堆顶部的牌（按从上到下的顺序给出）。每张牌用一个两个字符的字符串表示：
- 第一个字符表示牌面：$\texttt{A（Ace）}$、$2$–$9$、$\texttt{T}$（$10$）、$\texttt{J（Jack）}$、$\texttt{Q（Queen）}$、$\texttt{K（King）}$。
- 第二个字符表示花色：$\texttt{C（Clubs）}$、$\texttt{D（Diamonds）}$、$\texttt{H（Hearts）}$、$\texttt{S（Spades）}$。

牌与牌之间用一个空格分隔。每行的 $10$ 张牌都来自同一副扑克，不会出现重复的牌。

---

## 输出格式

对于每行输入，输出一行，包含以下内容：
- 初始手牌（格式如示例）
- 牌堆顶部的 $5$ 张牌（格式如示例）
- 可能获得的最佳牌型名称

示例输出展示了所有可能的牌型，并按价值从高到低排列。

---

## 解题思路

本题的核心是**枚举所有可能的换牌方案**，并对每种方案评估牌型，取最佳结果。

### 关键点

1. **换牌规则**  
   - 玩家可以选择丢弃 $0$ 到 $5$ 张牌。
   - 丢弃 $k$ 张牌后，从牌堆顶部按顺序取 $k$ 张牌替换。
   - 牌堆的顺序是固定的，丢弃的牌不会放回牌堆。

2. **枚举策略**  
   由于 $k$ 最多为 $5$，总换牌方案数等于从 $5$ 张手牌中选择 $k$ 张保留的组合数，即：
   $$
   \sum_{k=0}^{5} \binom{5}{k} = 32
   $$
   实际上，因为牌堆顶部只有 $5$ 张牌，所以当 $k < 5$ 时，我们只能从牌堆取前 $(5-k)$ 张牌。因此枚举量很小，可以直接暴力搜索。

3. **牌型判断**  
   需要实现一个函数 `findBestHand`，给定 $5$ 张牌，判断其牌型。判断顺序应按照牌型价值从高到低进行：
- 同花顺（$\texttt{straight-flush}$）
- 四条（$\texttt{four-of-a-kind}$）
- 葫芦（$\texttt{full-house}$）
- 同花（$\texttt{flush}$）
- 顺子（$\texttt{straight}$）
- 三条（$\texttt{three-of-a-kind}$）
- 两对（$\texttt{two-pairs}$）
- 一对（$\texttt{one-pair}$）
- 高牌（$\texttt{highest-card}$）

4. **算法步骤**
   - 读入初始手牌和牌堆牌。
   - 对于 $k = 0$ 到 $5$（表示保留 $k$ 张手牌）：
     - 枚举所有保留 $k$ 张手牌的方案（共 $\binom{5}{k}$ 种）。
     - 对于每种方案，用牌堆前 $(5-k)$ 张牌补全 $5$ 张牌。
     - 调用 `findBestHand` 判断牌型，更新最佳牌型索引（数值越小，牌型越强）。
   - 输出最佳牌型名称。

5. **牌型判断细节**
   - **同花顺**：既是顺子又是同花。
   - **顺子**：牌面连续，注意 $\texttt{A}$ 可作为最小（$\texttt{A-2-3-4-5}$）或最大（$\texttt{10-J-Q-K-A}$）。
   - **同花**：所有牌花色相同。
   - **四条**：有 $4$ 张相同牌面。
   - **葫芦**：$3$ 张相同牌面 + $2$ 张相同牌面。
   - **三条**：有 $3$ 张相同牌面。
   - **两对**：两个对子。
   - **一对**：一个对子。
   - **高牌**：以上都不是。

---

## 代码实现

```cpp
// The Psychic Poker Player
// UVa ID: 131
// Verdict: Accepted
// Submission Date: 2015-12-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int NOTHING = 8, ONE_PAIR = 7, TWO_PAIR = 6, THREE_KIND = 5, STRAIGHT = 4,
    FLUSH = 3, FULL_HOUSE = 2, FOUR_KIND = 1, STRAIGHT_FLUSH = 0;
    
int findBestHand(vector<string>& cards) {
    map<char, int> ranks;
    set<char> suits;
    vector<int> sequence;
    for (int i = 0; i < 5; i++) {
        ranks[cards[i].front()]++;
        suits.insert(cards[i].back());
    }
    for (auto pair : ranks) sequence.push_back(pair.second);
    // straight flush, AC 2C 3C 4C 5C, TC JC QC KC AC are straight flush
    bool is_straight = false;
    string straight = "A23456789TJQKA";
    for (int i = 0; i <= straight.length() - 5; i++) {
        is_straight = true;
        for (int j = i; j <= i + 4; j++)
            if (ranks.find(straight[j]) == ranks.end()) {
                is_straight = false;
                break;
            }
        if (is_straight) break;
    }
    bool is_flush = (suits.size() == 1);
    if (is_straight && is_flush) return STRAIGHT_FLUSH;
    // four of a kind
    bool four_kind = *max_element(sequence.begin(), sequence.end()) >= 4;
    if (four_kind) return FOUR_KIND;
    // full house
    bool is_full_house = (ranks.size() == 2 && accumulate(sequence.begin(), sequence.end(), int(0)) == 5);
    if (is_full_house) return FULL_HOUSE;
    // flush
    if (is_flush) return FLUSH;
    // straight
    if (is_straight) return STRAIGHT;
    // three of a kind
    bool three_kind = *max_element(sequence.begin(), sequence.end()) >= 3;
    if (three_kind) return THREE_KIND;
    // two pair
    bool is_two_pair = ranks.size() == 3;
    if (is_two_pair) return TWO_PAIR;
    // one pair
    bool is_one_pair = *max_element(sequence.begin(), sequence.end()) >= 2;
    if (is_one_pair) return ONE_PAIR;
    // nothing
    return NOTHING;
}

int minCardIndex;
bool fetched[5];
vector<string> cardInHand, cardInDeck;

void backtrack(int start, int target) {
    if (start == target) {
        vector<string> cards;
        for (int i = 0; i < 5; i++)
            if (fetched[i])
                cards.push_back(cardInHand[i]);
        for (int j = 0; j < (5 - target); j++)
            cards.push_back(cardInDeck[j]);
        minCardIndex = min(minCardIndex, findBestHand(cards));
    } else {
        for (int i = 0; i < 5; i++)
            if (fetched[i] == false) {
                fetched[i] = true;
                backtrack(start + 1, target);
                fetched[i] = false;
            }
    }
}

int main() {
    string line;
    string result[9] = {
        "straight-flush", "four-of-a-kind", "full-house", "flush", "straight",
        "three-of-a-kind", "two-pairs", "one-pair", "highest-card"
    };
    while (getline(cin, line), line.length() > 0) {
        cardInHand.clear();
        cardInDeck.clear();
        string card;
        istringstream iss(line);
        while (iss >> card && cardInHand.size() < 5) cardInHand.push_back(card);
        cardInDeck.push_back(card);
        while (iss >> card) cardInDeck.push_back(card);
        minCardIndex = 8;
        for (int i = 0; i <= 5; i++) {
            memset(fetched, 0, sizeof(fetched));
            backtrack(0, i);
        }
        line = "Hand: " + line.insert(15, "Deck: ") + " Best hand: ";
        line = line + result[minCardIndex];
        cout << line << endl;
    }
    return 0;
}
```

---

## 样例分析

以样例第一行为例：

输入：
```
TH JH QC QD QS QH KH AH 2S 6S
```

- 手牌：`TH（10♥）`、`JH（J♥）`、`QC（Q♣）`、`QD（Q♦）`、`QS（Q♠）`
- 牌堆：`QH（Q♥）`、`KH（K♥）`、`AH（A♥）`、`2S（2♠）`、`6S（6♠）`

通过枚举换牌方案，最佳结果是保留 `TH`、`JH`，从牌堆取 `QH`、`KH`、`AH`，得到 `TH JH QH KH AH`，构成同花顺（`♥` 的 `10-J-Q-K-A`），输出为 `straight-flush`。

---

## 总结

本题是一个典型的**枚举 + 模拟**题，由于数据规模小，可以直接暴力搜索所有换牌可能。关键点在于正确实现扑克牌型的判断逻辑，并注意顺子中 `A` 既可作最小也可作最大的特殊情况。代码中使用了回溯法枚举保留的手牌，并逐一评估牌型，最终输出最佳结果。
