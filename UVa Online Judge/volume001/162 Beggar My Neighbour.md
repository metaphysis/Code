[UVa 162 Beggar My Neighbour](https://blog.csdn.net/metaphysis/article/details/158732232)

### 题目大意

`Beggar My Neighbour`（又称 `Strip Jack Naked`）是一种传统的两人纸牌游戏，适合用来帮助初学者熟悉纸牌及其点数。游戏使用一副标准扑克牌（$52$ 张），洗牌后轮流发给两位玩家（第一张发给非发牌者，第二张发给发牌者，依次类推），每人得到 $26$ 张牌，发牌者拿到最后一张。

游戏开始时，非发牌者从自己的牌堆顶部翻出一张牌（即倒数第二张发给她的那张牌），放在桌面上作为起始牌。然后发牌者也从自己牌堆顶部翻出一张牌盖在上面。如此轮流翻牌，直到有人翻出一张“人头牌”（$A$、$K$、$Q$、$J$）为止。此时，对方必须“覆盖”这张人头牌：翻 $J$ 需要盖 $1$ 张牌，翻 $Q$ 需要盖 $2$ 张，翻 $K$ 需要盖 $3$ 张，翻 $A$ 需要盖 $4$ 张。如果在覆盖过程中又翻出了人头牌，则攻守互换，轮到另一位玩家去覆盖新的人头牌。当一轮覆盖结束后，最后翻出人头牌的一方将桌面上所有的牌收起，放在自己牌堆底部，然后由他重新开始下一轮（翻一张牌）。游戏一直进行，直到某一方轮到他翻牌时无牌可翻，则对方获胜。

本题要求模拟这个游戏的过程，输入多副牌的顺序（按发牌时的顺序给出），输出每副牌对应的获胜者（$1$ 表示发牌者，$2$ 表示非发牌者）以及获胜者手中的剩余牌数（忽略桌面上的牌），要求数字右对齐，宽度为 $3$。

---

### 解题思路

这是一道模拟题，难度不大，但需要注意细节。

#### 数据结构设计

我们用两个 $\texttt{vector}$ 分别存储两位玩家的手牌：
- $\texttt{nonDealer}$：非发牌者的手牌（即游戏开始时先翻牌的一方）。
- $\texttt{dealer}$：发牌者的手牌。

另外用一个 $\texttt{vector}$ 表示桌面上的牌堆（$\texttt{piles}$）。

#### 翻牌顺序

在模拟中，我们使用两个 $\texttt{goto}$ 标签 $\texttt{firstPlayer}$ 和 $\texttt{secondPlayer}$ 来切换当前翻牌的玩家。这样做的好处是代码逻辑直观，不需要维护复杂的状态机。

#### 关键变量
- $\texttt{cardNeeded}$：当前还需要翻多少张牌才能结束本轮。初始值为 $1$，表示正常轮流翻牌状态。当有人翻出人头牌后，这个值被设置为需要覆盖的张数。
- $\texttt{newCardNeeded}$：临时变量，用于在翻出一张牌时判断是否是人头牌，若是则得到对应的覆盖张数。
- $\texttt{exposer}$：记录本轮最后翻出人头牌的玩家（$1$ 表示非发牌者，$2$ 表示发牌者）。用于决定本轮结束后谁收走桌面牌。
- $\texttt{cover}$：一个字符串 $\texttt{"JQKA"}$，用于判断牌的点数是否为人头牌，同时通过下标 $+1$ 得到需要覆盖的张数（$J$ 对应下标 $0$，需要 $1$ 张；$Q$ 对应下标 $1$，需要 $2$ 张；$K$ 对应下标 $2$，需要 $3$ 张；$A$ 对应下标 $3$，需要 $4$ 张）。

#### 游戏流程模拟

1. **初始化**：将输入的一副牌（$52$ 张）按发牌顺序交替存入 $\texttt{nonDealer}$ 和 $\texttt{dealer}$。注意第一张牌给非发牌者，最后一张给发牌者。  
   为了便于从顶部取牌，我们在模拟开始前将两个手牌 $\texttt{vector}$ 反转，这样 $\texttt{front()}$ 就是顶部牌。

2. **游戏主循环**：
   - 当前玩家翻出一张牌（从自己的 $\texttt{vector}$ 头部取出，放入 $\texttt{piles}$）。
   - 判断这张牌是否为人头牌（通过查找 $\texttt{cover}$ 字符串）：
     - 如果是，则记录 $\texttt{exposer}$ 为当前玩家，设置 $\texttt{cardNeeded}$ 为对应覆盖张数，并切换到对方玩家继续翻牌。
     - 如果不是，则将 $\texttt{cardNeeded}$ 减 $1$。
   - 如果 $\texttt{cardNeeded}$ 减到 $0$，表示本轮结束：
     - 根据 $\texttt{exposer}$ 将桌面牌堆 $\texttt{piles}$ 加入到对应玩家的手牌底部。
     - 清空桌面牌堆。
     - 重置 $\texttt{cardNeeded} = 1$，$\texttt{exposer} = 0$。
     - 由上一轮最后翻出人头牌的玩家（即收牌者）开始下一轮。
   - 如果某玩家需要翻牌时手牌为空，则对方获胜，输出结果。

3. **输出格式**：获胜者编号（$1$ 或 $2$）和获胜者手牌数量，右对齐，宽度为 $3$。

---

### 代码实现细节

- 使用 $\texttt{reverse}$ 将手牌反转，方便从头部取牌（因为 $\texttt{vector}$ 的头部插入删除效率低，但本题数据量小，可以接受）。
- 使用 $\texttt{goto}$ 实现玩家切换，逻辑清晰。
- 注意每次收牌后，要将 $\texttt{piles}$ 清空。
- 输入处理：读入每张牌的字符串，取第二个字符（点数）存入手牌，忽略花色。因为游戏规则只关心点数是否为人头牌。
- 当一副牌读完（$\texttt{dealer.size() == 26}$）时，开始模拟，然后清空手牌，准备处理下一副牌。

---

### 参考代码

```cpp
// Beggar My Neighbour
// UVa ID: 162
// Verdict: Accepted
// Submission Date: 2016-02-10
// UVa Run Time: 0.033s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<char> nonDealer;
vector<char> dealer;
vector<char> piles;
int cardNeeded, newCardNeeded, exposer;
char card;

void display() {
    cout << "non-dealer: ";
    for (int i = 0; i < nonDealer.size(); i++) cout << nonDealer[i] << " ";
    cout << endl;
    cout << "dealer: ";
    for (int i = 0; i < dealer.size(); i++) cout << dealer[i] << " ";
    cout << endl;  
    cout << "piles: ";
    for (int i = 0; i < piles.size(); i++) cout << piles[i] << " ";
    cout << endl;  
}

void collect() {
    if (exposer == 1) nonDealer.insert(nonDealer.end(), piles.begin(), piles.end());
    else dealer.insert(dealer.end(), piles.begin(), piles.end());
    piles.clear();
    //display();
}

void play() {
    string cover = "JQKA";
    reverse(nonDealer.begin(), nonDealer.end());
    reverse(dealer.begin(), dealer.end());
    piles.clear();
    cardNeeded = 1;
    exposer = 0;
firstPlayer:    
    while (nonDealer.size() > 0) {
        cardNeeded--;
        card = nonDealer[0];
        piles.push_back(nonDealer[0]);
        nonDealer.erase(nonDealer.begin());
        //display();
        if ((newCardNeeded = cover.find(card)) != cover.npos) {
            exposer = 1;
            cardNeeded = newCardNeeded + 1;
            goto secondPlayer;
        }
        
        if (cardNeeded == 0) {
            cardNeeded = 1;
            if (exposer > 0) {
                collect();
                if (exposer == 1) {
                    exposer = 0;
                    goto firstPlayer;
                } else {
                    exposer = 0;
                    goto secondPlayer;
                }
            } else goto secondPlayer;
        }
    }
    cout << "1" << setw(3) << right << dealer.size() << endl;
    goto end;
secondPlayer:
    while (dealer.size() > 0) {
        cardNeeded--;
        card = dealer[0];
        piles.push_back(dealer[0]);
        dealer.erase(dealer.begin());
        //display();
        if ((newCardNeeded = cover.find(card)) != cover.npos) {
            exposer = 2;
            cardNeeded = newCardNeeded + 1;
            goto firstPlayer;
        }
        if (cardNeeded == 0) {
            cardNeeded = 1;
            if (exposer > 0) {
                collect();
                if (exposer == 1) {
                    exposer = 0;
                    goto firstPlayer;
                } else {
                    exposer = 0;
                    goto secondPlayer;
                }
            } else goto firstPlayer;
        }
    }
    cout << "2" << setw(3) << right << nonDealer.size() << endl;
end:
    ;
}

int main() {
    string card;
    int index = 1;
    while (cin >> card, card != "#") {
        if ((index++ % 2) == 1) nonDealer.push_back(card[1]);
        else dealer.push_back(card[1]);
        if (dealer.size() == 26) {
            play();
            nonDealer.clear();
            dealer.clear();
            index = 1;
        }
    }
	return 0;
}
```

---

### 总结

本题是一个典型的模拟题，核心在于正确理解游戏规则并准确模拟翻牌、覆盖、收牌等流程。使用 $\texttt{goto}$ 可以让代码逻辑更贴近游戏的实际流程，易于理解和调试。注意输入处理和输出格式即可轻松通过。
