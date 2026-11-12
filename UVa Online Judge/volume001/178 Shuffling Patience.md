[UVa 178 Shuffling Patience](https://blog.csdn.net/metaphysis/article/details/160860926)

## 题目分析

$\texttt{Shuffling Patience}$ 是一种纸牌游戏，游戏规则如下：

- 使用一副标准 $52$ 张牌，每张牌由点数（$\texttt{A}$、$\texttt{2}$、$\texttt{3}$、$\dots$、$\texttt{9}$、$\texttt{T}$、$\texttt{J}$、$\texttt{Q}$、$\texttt{K}$）和花色（$\texttt{S}$、$\texttt{H}$、$\texttt{C}$、$\texttt{D}$）组成。
- 游戏在 $4 \times 4$ 的网格（最多 $16$ 堆）中进行，所有牌面朝上。
- 在放置新牌之前，检查已有牌堆的顶部牌中是否存在**可覆盖**的对子或三张：
    - **对子**：两张牌的点数均在 $\texttt{A}$ 到 $\texttt{T}$（即 $1$ 到 $10$）之间，且点数之和为 $11$。
    - **三张**：恰好为 $\texttt{J}$、$\texttt{Q}$、$\texttt{K}$（即点数 $11$、$12$、$13$）各一张。
- 如果存在多个可覆盖的对子或三张，按照**最早出现**的原则选择：
    - 首先选择在牌堆顺序中（从左到右、从上到下）最早出现的可覆盖组合。
    - 对于三张，三张中的每一张也按最早出现原则确定。
- 覆盖操作是**不可分割**的：一次覆盖操作（放置 $2$ 或 $3$ 张牌到对应堆顶）完成之前，不会进行新的覆盖判断。
- 如果无法在 $16$ 堆内完成全部 $52$ 张牌的放置，输出溢出信息；否则输出每堆的最终牌数（忽略空堆）。

## 解题思路

### 整体流程

1. 读取输入，每 $52$ 张牌为一副完整的牌堆（$\texttt{deck}$）。
2. 模拟游戏过程：
    - 维护 $16$ 个堆（$\texttt{piles}$），每个堆是一个栈（只关心堆顶牌）。
    - 维护当前已使用的堆数量 $\texttt{currentPile}$。
    - 按顺序处理每一张牌：
        - 获取所有非空堆的顶部牌。
        - 判断是否存在可覆盖的对子或三张。
        - 根据规则（最早出现）决定执行对子覆盖、三张覆盖还是新建堆。
        - 执行覆盖操作时，从当前牌中取出 $2$ 或 $3$ 张，依次放到对应堆的顶部。
        - 新建堆时，将当前牌放到下一个可用堆位。
    - 如果新建堆时已用了 $16$ 堆且无可覆盖组合，则溢出。
3. 输出结果：成功则输出每堆牌数（非零），失败则输出溢出信息。

### 关键数据结构

- $\texttt{cards}$：存储一副牌的所有 $52$ 张牌，每张牌包含 $\texttt{face}$（字符串）和 $\texttt{value}$（点数数值，$\texttt{A}=1$，$\dots$，$\texttt{K}=13$）。
- $\texttt{piles}[16]$：每个元素是一个 $\texttt{vector<card>}$，模拟堆（栈）。
- $\texttt{top}$：存储当前所有堆顶牌（仅存 $\texttt{value}$ 和堆索引），用于寻找对子/三张。

### 寻找对子和三张

- $\texttt{findTwoPair}$：遍历 $\texttt{top}$ 中所有点数为 $1$ 到 $10$ 的牌，寻找两数之和为 $11$ 的组合。由于题目要求“最早出现”，需要按照原始堆顺序（即 $\texttt{top}$ 中索引顺序）寻找，而不是随意组合。这里采用双重循环，按索引顺序检查。
- $\texttt{findThreePair}$：需要找到 $\texttt{J}$、$\texttt{Q}$、$\texttt{K}$ 各一张。由于点数可以排序判断，但最终仍需按原始堆顺序确定覆盖顺序。实现中先将 $\texttt{top}$ 按数值排序以确认三张是否存在，然后收集三个堆索引并排序，得到最早出现的顺序。

### 覆盖操作的选择规则

题目规定：

- 如果同时存在对子和三张，则选择**覆盖牌中最早出现的那张牌**所属的组合。
- 具体实现中，比较最早的对子中最小索引和最早的三张中最小索引，较小的优先。

### 溢出判断

- 新建堆时若 $\texttt{currentPile} \ge 16$，且没有可覆盖组合，则溢出。
- 输出时需输出“溢出在第几张牌”，注意牌号是从 $1$ 开始计数的。

## 代码实现

```cpp
// Shuffling Patience
// UVa ID: 178
// Verdict: Accepted
// Submission Date: 2016-02-22
// UVa Run Time: 0.012s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 牌的结构：面值和数值
struct card {
    string face;   // 原始字符串，如 "TS"
    int value;     // 数值：A=1, 2=2, ..., K=13
};

// 堆顶牌的信息：数值和堆索引
struct topCard {
    int value, index;
};

// 用于排序（按数值），以便判断是否存在 JQK 三张
bool operator<(topCard x, topCard y) {
    return x.value < y.value;
}

string cardValue = "A23456789TJQK";  // 点数顺序，用于转换
vector<card> cards;                   // 存储一副牌的所有牌
vector<topCard> top;                  // 当前所有堆顶牌
vector<vector<card>> piles(16);       // 最多 16 个堆
int twoPair[2], threePair[3];         // 存储找到的对子/三张的堆索引
int testcase = 0;                     // 当前是第几副牌

// 获取所有非空堆的堆顶牌（仅数值和索引）
void getTop() {
    top.clear();
    for (int i = 0; i < piles.size(); i++)
        if (piles[i].size() > 0)
            top.push_back({piles[i].back().value, i});
}

// 寻找和为 11 的对子（数值范围 1~10）
// 按堆的原始顺序（top 中顺序）寻找最早出现的一对
bool findTwoPair() {
    if (top.size() <= 1) return false;
    for (int i = 0; i < top.size() - 1; i++) {
        if (top[i].value >= 1 && top[i].value <= 10) {
            for (int j = i + 1; j < top.size(); j++) {
                if (top[j].value >= 1 && top[j].value <= 10 &&
                    (top[i].value + top[j].value) == 11) {
                    twoPair[0] = top[i].index;
                    twoPair[1] = top[j].index;
                    return true;
                }
            }
        }
    }
    return false;
}

// 寻找 JQK 三张（数值 11,12,13 各一张）
bool findThreePair() {
    if (top.size() <= 2) return false;

    // 先按数值排序，方便检查是否存在 J、Q、K
    stable_sort(top.begin(), top.end());

    // 依次寻找 J(11)、Q(12)、K(13)
    for (int i = 0; i < 3; i++) {
        bool found = false;
        for (int j = 0; j < top.size(); j++) {
            if (top[j].value == (i + 11)) {
                threePair[i] = top[j].index;
                found = true;
                break;
            }
        }
        if (!found) return false;
    }

    // 将三个堆索引排序，得到最早出现的顺序
    sort(threePair, threePair + 3);
    return true;
}

// 模拟一副牌的完整游戏过程
void play() {
    // 清空所有堆
    for (int i = 0; i <= 15; i++) piles[i].clear();

    int index = 0;          // 当前要处理的牌在 cards 中的下标
    int currentPile = 0;    // 下一个可用的新堆索引

    while (index < cards.size()) {
        getTop();  // 获取当前所有堆顶牌

        bool twoPairFound = findTwoPair();
        bool threePairFound = findThreePair();

        // 决定覆盖对子还是三张
        // 规则：如果同时存在，选择最早出现的牌所属的组合
        if ((twoPairFound && !threePairFound) ||
            (twoPairFound && threePairFound && twoPair[0] < threePair[0])) {
            // 覆盖对子：需要取 2 张新牌
            int number = 0;
            while (index < cards.size() && number < 2) {
                piles[twoPair[number++]].push_back(cards[index]);
                index++;
            }
            if (number < 2) break;  // 牌不足（正常情况不会发生）
        }
        else if ((!twoPairFound && threePairFound) ||
                 (twoPairFound && threePairFound && twoPair[0] > threePair[0])) {
            // 覆盖三张：需要取 3 张新牌
            int number = 0;
            while (index < cards.size() && number < 3) {
                piles[threePair[number++]].push_back(cards[index]);
                index++;
            }
            if (number < 3) break;
        }
        else {
            // 没有可覆盖的组合，新建堆
            if (currentPile >= 16) break;  // 超出 16 堆，溢出
            piles[currentPile++].push_back(cards[index]);
            index++;
        }
    }

    // 输出结果
    cout << setw(3) << right << testcase << ":";
    if (index == cards.size()) {
        // 成功处理完全部 52 张牌
        for (int i = 0; i < piles.size(); i++)
            if (piles[i].size() > 0)
                cout << setw(3) << right << piles[i].size();
        cout << "\n";
    } else {
        // 溢出，输出溢出时即将处理的牌号（index 是已处理的牌数，下一张是 index+1）
        cout << " Overflowed on card no";
        cout << setw(3) << right << (index + 1) << "\n";
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0);
    cout.sync_with_stdio(false);

    string oneCard;
    int counter = 0;

    // 读取多副牌，每副 52 张，以 '#' 结束
    while (cin >> oneCard, oneCard != "#") {
        // 将牌面转换为数值：例如 'T' 对应 10，'J' 对应 11，等等
        cards.push_back({oneCard, (int)(cardValue.find(oneCard[0])) + 1});
        counter++;

        // 凑齐一副牌（52 张）后开始模拟
        if (counter == 52) {
            testcase++;
            play();
            cards.clear();   // 清空，准备下一副牌
            counter = 0;
        }
    }

    return 0;
}
```

## 注意事项

- 输入中 $\texttt{T}$ 表示点数 $10$，$\texttt{J}$、$\texttt{Q}$、$\texttt{K}$ 分别对应 $11$、$12$、$13$，$\texttt{A}$ 对应 $1$。
- 覆盖操作是“不可分割的”，意味着一次覆盖必须连续取多张牌，中间不进行新的覆盖判断。
- 输出格式要求：每行以“编号:”开头，数字右对齐在宽度为 $3$ 的字段中，溢出信息中“card no”后跟右对齐的牌号。
- 当同时存在对子和三张时，必须比较最早出现的单张牌来自哪个组合，而不是简单比较对子索引和三张索引的最小值——但本题中由于对子的“最早”是由其两张牌中靠前的那张决定的，而三张的“最早”也是由其靠前的那张决定的，因此可以直接比较 `twoPair[0]` 和 `threePair[0]`。
