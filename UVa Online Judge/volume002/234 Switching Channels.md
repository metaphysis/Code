[UVa 234 Switching Channels](https://blog.csdn.net/metaphysis/article/details/161210413)

## 题目分析

$\texttt{CPN}$ 电视台希望合理安排节目播出顺序，使得观众在切换频道时尽可能少地错过节目开头或结尾。题目定义了若干个“对齐点”，每个对齐点具有重要性等级（$1$ 级最重要，$2$ 级次之，依此类推）和一个时间点。

“错过时间”是指对齐点时间与最近的节目开始或结束时间之差的绝对值。对于每个重要性等级，需要计算该等级下所有对齐点的错过时间之和，然后将所有等级的错过时间之和相加得到总错过时间。目标是通过调整节目顺序，使总错过时间最小。

输入包含多个数据集，每个数据集第一行为节目数量 $p$（$0 \leqslant p \leqslant 8$）和 $p$ 个节目时长，第二行为对齐点数量 $a$（$0 \leqslant a \leqslant 8$）和 $a$ 对整数（重要性、时间点）。当 $p = 0$ 时输入结束。

## 解题思路

由于 $p$ 和 $a$ 的最大值均为 $8$，节目数量的排列最多有 $8! = 40320$ 种，完全可以在时限内枚举所有排列。两种解法均基于枚举思想：

### 解法一：递归回溯

使用 `backtrack` 函数递归生成所有节目顺序，当所有节目都安排完毕时，计算当前顺序下每个重要性等级的错过时间，然后与当前最优解比较。比较规则按重要性等级从 $1$ 到 $5$ 依次比较，若当前错过时间更小则更新最优解。

### 解法二：$\texttt{next\_permutation}$ 枚举

先对节目时长排序，然后使用 `next_permutation` 生成所有排列，对于每个排列计算错过时间并更新最优解。这种方法代码更简洁。

两种解法的时间复杂度均为 $O(p! \times a \times p)$，在 $p \leqslant 8$ 时完全可行。

## 代码实现

```cpp
// Switching Channels
// UVa ID: 234
// Verdict: Accepted
// Submission Date: 2016-06-01
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int programme[10], alignment[10][2], used[8], minutes[10], p, a;
int indexer[10], bestIndex[10], bestMiss[10], initialized = false;

// 深度优先搜索生成所有节目排列
void backtrack(int index)
{
    // 已安排好所有节目，计算错过时间
    if (index == (p + 1))
    {
        // miss[i] 存储重要性等级 i 的错过时间总和
        int miss[10] = { 0 };
        
        // 遍历每个对齐点
        for (int i = 1; i <= a; i++)
        {
            // 二分查找第一个不小于对齐点时间的节目结束时间位置
            int j = lower_bound(minutes, minutes + p, alignment[i][1]) - minutes;
            
            // 若对齐点时间晚于所有节目结束时间
            if (j > p)
                miss[alignment[i][0]] += alignment[i][1] - minutes[p];
            else
                // 取对齐点与相邻两个节目结束时间的最小差值
                miss[alignment[i][0]] += min(abs(alignment[i][1] - minutes[j - 1]),
                    abs(alignment[i][1] - minutes[j]));
        }

        // 第一个合法排列，直接保存为最优解
        if (!initialized)
        {
            copy(miss, miss + 10, bestMiss);
            copy(indexer, indexer + 10, bestIndex);
            initialized = true;
        }
        else
        {
            // 按重要性等级从低到高比较错过时间
            for (int i = 0; i < 10; i++)
                if (miss[i] == bestMiss[i])
                    continue;
                else
                {
                    // 若当前排列的错过时间更小，更新最优解
                    if (miss[i] < bestMiss[i])
                    {
                        copy(miss, miss + 10, bestMiss);
                        copy(indexer, indexer + 10, bestIndex);
                    }
                    break;
                }
        }
        return;
    }

    // 尝试将未使用的节目安排在当前位置
    for (int i = 1; i <= p; i++)
        if (used[i] == false)
        {
            used[i] = true;
            indexer[index] = i;
            // 计算当前节目的结束时间
            minutes[index] = minutes[index - 1] + programme[i];
            backtrack(index + 1);
            used[i] = false;
        }
}

int main()
{
    int cases = 0;
    while (cin >> p, p)
    {
        // 读取节目时长
        for (int i = 1; i <= p; i++)
            cin >> programme[i];

        // 读取对齐点信息
        cin >> a;
        for (int i = 1; i <= a; i++)
            cin >> alignment[i][0] >> alignment[i][1];

        // 初始化状态
        memset(used, 0, sizeof(used));
        memset(minutes, 0, sizeof(minutes));
        initialized = false;

        // 开始搜索最优排列
        backtrack(1);

        // 输出结果
        cout << "Data set " << ++cases << endl;
        cout << "  Order:";

        for (int i = 1; i <= p; i++)
            cout << " " << programme[bestIndex[i]];
        cout << endl;

        int bestTotalMiss = 0;
        for (int i = 1; i <= a; i++)
            bestTotalMiss += bestMiss[i];

        cout << "  Error: " << bestTotalMiss << endl;
    }

    return 0;
}
```

```cpp
// Switching Channels
// UVa ID: 234
// Verdict: Accepted
// Submission Date: 2016-06-02
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    vector <int> programme;
    int alignment[10][2], minutes[10] = {0}, bestTime[10], bestMiss[10] = {0};
    int p, a, cases = 0;

    while (cin >> p, p)
    {
        int times;
        programme.clear();
        for (int i = 1; i <= p; i++)
        {
            cin >> times;
            programme.push_back(times);
        }

        cin >> a;
        for (int i = 1; i <= a; i++)
            cin >> alignment[i][0] >> alignment[i][1];

        bool initialized = false;
        sort(programme.begin(), programme.end());

        do
        {
            for (int i = 0; i < programme.size(); i++)
                minutes[i + 1] = minutes[i] + programme[i];

            int miss[10] = { 0 };
            for (int i = 1; i <= a; i++)
            {
                bool flag = false;
                for (int j = 0; j < p; j++)
                    if (minutes[j] >= alignment[i][1])
                    {
                        miss[alignment[i][0]] += min(abs(alignment[i][1] - minutes[j - 1]),
                                                     abs(alignment[i][1] - minutes[j]));
                        flag = true;
                        break;
                    }
                if (!flag)
                    miss[alignment[i][0]] += alignment[i][1] - minutes[p];
            }

            if (!initialized)
            {
                copy(miss, miss + 10, bestMiss);
                for (int i = 1; i <= p; i++)
                    bestTime[i] = programme[i - 1];
                initialized = true;
            }
            else
            {
                for (int i = 0; i < 10; i++)
                    if (miss[i] == bestMiss[i])
                        continue;
                    else
                    {
                        if (miss[i] < bestMiss[i])
                        {
                            copy(miss, miss + 10, bestMiss);
                            for (int i = 1; i <= p; i++)
                                bestTime[i] = programme[i - 1];
                        }
                        break;
                    }
            }
        }
        while (next_permutation(programme.begin(), programme.end()));

        cout << "Data set " << ++cases << endl;
        cout << "  Order:";

        for (int i = 1; i <= p; i++)
            cout << " " << bestTime[i];
        cout << endl;

        int bestTotalMiss = 0;
        for (int i = 1; i <= a; i++)
            bestTotalMiss += bestMiss[i];

        cout << "  Error: " << bestTotalMiss << endl;
    }

    return 0;
}
```
