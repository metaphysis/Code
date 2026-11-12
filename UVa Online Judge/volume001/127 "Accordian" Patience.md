[UVa 127 "Accordian" Patience](https://blog.csdn.net/metaphysis/article/details/156746725)

## 题目分析与解题思路

本题要求模拟“手风琴”接龙游戏的进行过程。游戏规则如下：

- 将一副 $52$ 张牌从左到右依次发牌，每张牌成为一个牌堆。
- 任何时候，若某张牌与其左边相邻牌堆的最上方一张牌匹配（花色相同或点数相同），或与其左边第三堆的最上方一张牌匹配，则可以将其移动到匹配的牌堆上。
- 移动后，如果出现空堆，立即将所有右侧牌堆左移填充空隙。
- 当有多种可能的移动时，优先移动最左边可以移动的牌；若一张牌既可以左移一单位也可以左移三单位，则选择移动三单位。
- 游戏结束条件为无法再移动任何牌，目标是尽可能合并牌堆，最终可能只剩一个牌堆获胜。

**问题理解：**

由于移动操作会影响后续移动的可能性，而且移动顺序和选择策略影响最终结果，因此需要严格按照题目描述的规则进行模拟。关键在于如何高效实现移动、合并和空堆压缩。

**数据结构选择：**

- 使用 `vector<vector<string>> piles` 存储所有牌堆，每个牌堆是一个 `string` 的向量，底部为最早发的牌，顶部为最后发的牌（即最上方的一张）。
- 由于需要频繁访问每个牌堆的顶部牌，以及可能需要删除空牌堆和插入新牌，使用 `vector` 可以提供较好的随机访问和尾部操作性能。

**算法流程：**

1. **发牌：** 每次读取两行，每行 $26$ 张牌，每张牌作为一个单独的牌堆加入 `piles` 中。
2. **游戏循环：**
   - 每次移动前，先清除所有空堆（即 `piles[i].size() == 0` 的堆）。
   - 从最左边的牌堆开始向右检查，对于每个牌堆，先判断是否能向左移动三格（如果左边第三堆存在且匹配），若可以则移动并更新索引；否则判断是否能向左移动一格，若可以则移动；否则继续向右检查。
   - 移动后，将当前牌堆的顶部牌移动到目标牌堆的顶部（即 `push_back`），并删除原牌堆的顶部牌（即 `pop_back` 或 `erase`）。
   - 循环直到一次完整扫描中没有发生任何移动，游戏结束。
3. **输出：** 输出剩余牌堆的数量及各堆的牌数。

**移动策略：**

- 由于要求移动最左边可能的牌，并且优先移动三格，因此在检查每个牌堆时，先判断能否移动三格，再判断能否移动一格。
- 移动后，索引回退到目标堆的位置，继续从该位置向左检查可能的移动，这是因为移动可能导致新的匹配机会。

**时间复杂度：**

- 最坏情况下，每张牌可能需要多次移动，每次移动可能需要遍历整个牌堆列表。
- 由于牌的总数是固定的 $52$ 张，且每次移动至少减少一个牌堆（合并或删除空堆），因此操作次数有限，实际运行时间可接受。

**注意事项：**

- 输入以 `#` 开头的一行结束。
- 输出格式：剩余牌堆数 + `pile(s) remaining:` + 各堆牌数。
- 注意空堆的及时清除。

## 参考代码

```cpp
// "Accordian" Patience
// UVa ID: 127
// Verdict: Accepted
// Submission Date: 2015-11-28
// UVa Run Time: 1.159s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector< vector<string> > piles;

void print() {
    cout << piles.size();
    cout << (piles.size() > 1 ? " piles" : " pile") <<" remaining:";
    for (int i = 0; i < piles.size(); i++) cout << " " << piles[i].size();
    cout << endl;
}

void getCards(string line) {
    istringstream iss(line);
    string card;
    while (iss >> card) {
        vector<string> pile;
        pile.push_back(card);
        piles.push_back(pile);
    }
}

bool canMoveToLeft(int index) {
    return (index > 0 && (piles[index].back()[0] == piles[index - 1].back()[0] ||
        piles[index].back()[1] == piles[index - 1].back()[1]));
}

bool canMoveToThirdLeft(int index) {
    return (index > 2 && (piles[index].back()[0] == piles[index - 3].back()[0] ||
        piles[index].back()[1] == piles[index - 3].back()[1]));
}

void play() {
    while (true) {
        for (int i = piles.size() - 1; i >= 0; i--)
            if (piles[i].size() == 0)
                piles.erase(piles.begin() + i);
        int index = 0;
        bool moved = false;
        while (index >= 0 && index < piles.size()) {
            if (piles[index].size() == 0) break;
            if (canMoveToThirdLeft(index)) {
                piles[index - 3].push_back(piles[index].back());
                piles[index].erase(piles[index].end());
                index -= 3;
                moved = true;
                continue;
            }
            if (canMoveToLeft(index)) {   
                piles[index - 1].push_back(piles[index].back());
                piles[index].erase(piles[index].end());
                index -= 1;
                moved = true;
                continue;
            }
            index++;
        }
        if (!moved) break;
    }
}

int main() {
    string line1, line2;
    while (true) {
        piles.clear();
        getline(cin, line1);
        if (line1.front() == '#') break;
        getCards(line1);
        getline(cin, line2);
        getCards(line2);
        play();
        print();
    }
	return 0;
}
```
