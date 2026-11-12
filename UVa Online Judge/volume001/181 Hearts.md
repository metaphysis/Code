[UVa 181 Hearts](https://blog.csdn.net/metaphysis/article/details/160890313)

## 题目分析

$\texttt{Hearts}$ 是一种纸牌游戏，本题描述的是该游戏的简化版本。游戏使用一副标准的 $52$ 张扑克牌，包含 $4$ 种花色（梅花 $\texttt{C}$、方块 $\texttt{D}$、红心 $\texttt{H}$、黑桃 $\texttt{S}$，按此顺序从小到大）和 $13$ 种点数（$2$ 到 $10$、$\texttt{J}$、$\texttt{Q}$、$\texttt{K}$、$\texttt{A}$，按此顺序从小到大）。

游戏规则要点：
- 共 $5$ 名玩家（包括庄家），每人发 $10$ 张牌，剩余 $2$ 张牌亮出，点数较大的那张牌的花色确定为 **将牌花色**；若点数相同，则选择花色等级较高的作为将牌。
- 游戏进行 $10$ 轮（称为“墩”）。每轮由一位玩家 **引牌**，其余玩家按顺时针方向 **跟牌**。第一轮由庄家左侧的玩家引牌，之后每轮由上一轮的赢家引牌。
- 跟牌时，必须 **优先跟同花色**；若无同花色，则必须 **出将牌**（称为“将吃”）；若无将牌，则 **垫牌**（出任意牌）。
- 每轮中，若有人出将牌，则出最大将牌者赢；否则出引牌花色最大者赢。
- **计分**：每轮结束后，赢家收取该轮的所有牌。整局结束后，统计每名玩家手中 **红心牌** 的点数之和（$\texttt{J}=11$，$\texttt{Q}=12$，$\texttt{K}=13$，$\texttt{A}=14$）。

## 解题思路

本题要求模拟完整的游戏过程，输入包含多副牌（每副牌 $4$ 行，每行若干张牌），输出 $5$ 名玩家的最终得分，输出顺序为：庄家、庄家左侧、…、庄家右侧。

### 牌的数据表示
每张牌包含三个属性：
- 字符串形式（如 `"TS"` 表示黑桃 $10$）
- 点数索引（`0` ~ `12`，对应 `2` ~ `A`）
- 花色索引（`0` ~ `3`，对应 `C` ~ `S`）

### 发牌规则
发牌从庄家左侧玩家开始，顺时针每人一张，共发 $5 \times 10 = 50$ 张。剩余两张牌确定将牌花色。

### 模拟每轮游戏
1. **引牌**：引牌者根据策略出牌 —— 从手牌中选出 **点数最大** 的牌；若点数相同且其中一张是将牌，则出将牌；否则出花色等级较高的牌。
2. **跟牌**：其余玩家依次出牌，策略为：
   - 优先出手牌中 **同花色点数最大** 的牌；
   - 若无同花色，则出 **将牌中点数最大** 的牌（将吃）；
   - 若无将牌，则出 **手牌中点数最大** 的牌（垫牌）。
3. **确定赢家**：比较本轮的 $5$ 张牌，规则同题述。
4. **计分**：赢家收取本轮所有牌，其中每张红心牌的点数累加到该玩家得分中。

### 数据结构
- `players`：$5$ 个向量，每个向量存储一名玩家的手牌。
- `scores`：$5$ 个整数，存储玩家得分。
- 每轮结束后，赢家成为下一轮的引牌者。

### 输入处理
输入中一副牌分 $4$ 行，每行包含若干张牌（每张牌由两个字符表示，如 `TS`）。遇到单独一行 `#` 时终止输入。

## 关键实现细节

- 发牌时，输入字符串需先合并再去除空白字符。
- 剩余两张牌从输入末尾取得，注意字符串索引位置（前 $100$ 个字符对应 $50$ 张牌，剩余 $4$ 个字符是最后两张牌）。
- 排序比较函数需严格遵循题目中的策略。
- 输出格式：每个分数占据 $3$ 个字符宽度，右对齐，输出顺序为庄家、庄家左侧、庄家对面、庄家右侧、庄家左侧的左侧（即按 $4 \to 0 \to 1 \to 2 \to 3$ 的顺序）。

## 代码实现

```cpp
// Hearts
// UVa ID: 181
// Verdict: Accepted
// Submission Date: 2016-03-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct card {
    string text;   // 牌的字符串表示，如 "TS"
    int face;      // 点数索引，0~12 对应 2~A
    int suit;      // 花色索引，0~3 对应 C~S
};

vector<vector<card>> players;  // 5 名玩家的手牌
vector<card> followerCards;     // 当前轮所有玩家出的牌
vector<int> scores;             // 5 名玩家的得分
string faces = "23456789TJQKA"; // 点数顺序
string suits = "CDHS";          // 花色顺序
int leader, winner, trump;      // 当前引牌者、当前赢家、将牌花色
card winnerCard;                // 当前轮中暂时领先的牌

// 判断新出的牌是否能成为当前轮的赢家
void getWinnerCard(int index, card followerCard) {
    if ((followerCard.suit != winnerCard.suit && followerCard.suit == trump) ||
            (followerCard.suit == winnerCard.suit && followerCard.face > winnerCard.face))
    {
        winner = index;
        winnerCard = followerCard;
    }
}

// 跟牌时的排序规则：点数大的优先，点数相同时花色大的优先
bool followerCmp(card x, card y) {
    return (x.face != y.face) ? x.face > y.face : x.suit > y.suit;
}

// 获取某位玩家的跟牌
card getFollowerCard(int index, card leaderCard) {
    card followerCard;
    // 按跟牌策略排序手牌
    sort(players[index].begin(), players[index].end(), followerCmp);

    // 1. 优先出同花色中的最大牌
    bool found = false;
    for (int i = 0; i < players[index].size(); i++)
        if (players[index][i].suit == leaderCard.suit)
        {
            followerCard = players[index][i];
            players[index].erase(players[index].begin() + i);
            found = true;
            break;
        }

    // 2. 若无同花色，则出将牌中的最大牌（将吃）
    if (found == false)
    {
        for (int i = 0; i < players[index].size(); i++)
            if (players[index][i].suit == trump)
            {
                followerCard = players[index][i];
                players[index].erase(players[index].begin() + i);
                found = true;
                break;
            }
    }

    // 3. 若既无同花色也无将牌，则垫出手牌中最大牌
    if (found == false)
    {
        followerCard = players[index][0];
        players[index].erase(players[index].begin());
    }

    // 更新当前轮的赢家信息
    getWinnerCard(index, followerCard);

    return followerCard;
}

// 引牌时的排序规则：点数大的优先；点数相同时，将牌优先；否则花色大的优先
bool leaderCmp(card x, card y) {
    if (x.face != y.face)
        return x.face > y.face;
    else
    {
        if (x.suit == trump && y.suit != trump)
            return true;

        if (x.suit != trump && y.suit == trump)
            return false;

        return x.suit > y.suit;
    }
}

// 获取引牌者的出牌
card getLeaderCard(int index) {
    sort(players[index].begin(), players[index].end(), leaderCmp);
    card leaderCard = players[index][0];
    players[index].erase(players[index].begin());
    return leaderCard;
}

// 模拟一轮游戏
void play() {
    followerCards.clear();
    followerCards.push_back(getLeaderCard(leader));  // 引牌者出牌

    winner = leader;
    winnerCard = followerCards.front();

    // 其余 4 名玩家依次跟牌
    for (int i = 1; i <= 4; i++)
    {
        leader = (leader + 1) % 5;
        followerCards.push_back(getFollowerCard(leader, followerCards.front()));
    }

    // 赢家收取本轮所有牌，统计红心牌分数
    for (int i = 0; i < followerCards.size(); i++)
        if (followerCards[i].text[1] == 'H')
            scores[winner] += (followerCards[i].face + 2);  // face+2 得到实际点数

    leader = winner;  // 下一轮由赢家引牌
}

int main(int argc, char *argv[])
{
    string line, deck;
    int lineNumber = 0;

    // 初始化 5 名玩家的手牌和得分
    for (int i = 1; i <= 5; i++)
    {
        vector<card> cards;
        players.push_back(cards);
        scores.push_back(0);
    }

    while (getline(cin, line), line != "#")
    {
        lineNumber++;
        deck += line;   // 合并多行输入

        // 每副牌共 4 行，读满后处理
        if (lineNumber == 4)
        {
            // 去除所有空白字符
            for (int i = deck.length() - 1; i >= 0; i--)
                if (isblank(deck[i]))
                    deck.erase(deck.begin() + i);

            // 发牌：前 100 个字符对应 50 张牌，每人 10 张
            for (int i = 0, j = 0; i < deck.length() - 4; i += 2, j++)
            {
                string text = deck.substr(i, 2);
                players[j % 5].push_back((card){
                    text,
                    (int)faces.find(text[0]),
                    (int)suits.find(text[1])
                });
            }

            // 剩余两张牌（第 51 张和第 52 张）确定将牌花色
            string last1 = deck.substr(102, 2);  // 第 52 张
            string last2 = deck.substr(100, 2);  // 第 51 张

            int face1 = faces.find(last1[0]);
            int face2 = faces.find(last2[0]);
            int suit1 = suits.find(last1[1]);
            int suit2 = suits.find(last2[1]);

            if (face1 == face2)
                trump = suit1 > suit2 ? suit1 : suit2;  // 点数相同，花色等级高的为将牌
            else
                trump = face1 > face2 ? suit1 : suit2;  // 点数大的那张牌的花色为将牌

            // 重置得分
            fill(scores.begin(), scores.end(), 0);

            // 第一轮由庄家左侧（索引0）引牌，共进行 10 轮
            leader = 0;
            for (int i = 1; i <= 10; i++)
                play();

            // 输出结果：顺序为庄家（索引4）、庄家左侧（0）、...、庄家右侧（3）
            cout << setw(3) << right << scores[4];
            for (int i = 0; i <= 3; i++)
                cout << setw(3) << right << scores[i];
            cout << endl;

            // 重置，准备处理下一副牌
            deck.clear();
            lineNumber = 0;
            leader = 0;
        }
    }

    return 0;
}
```

## 样例验证

输入样例：
```
TS QC 8S 8D QH 2D 3H KH 9H 2H TH KS KC 9D JH 7H JD 2S QS TD 2C 4H 5H AD 4D 5D 6D 4S 9S 5S 7S JS 8H 3D 8C 3S 4C 6S 9C AS 7C AH 6H KD JC 7D AC 5C TC QD 6C 3C #
```

输出：
```
22 0 68 0 14
```

与题目给出的输出一致，说明模拟正确。
