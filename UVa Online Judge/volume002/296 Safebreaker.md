[UVa 296 Safebreaker](https://blog.csdn.net/metaphysis/article/details/161388999)

## 题目分析

本题是经典猜数字游戏（$\texttt{Mastermind}$）的变种。游戏的目标是猜出一个 $4$ 位数的密码，密码范围从 $0000$ 到 $9999$。每次猜测后，会得到两个数字作为提示：

- **正确位置正确的数字个数**（记为 `right`）
- **数字正确但位置错误的个数**（记为 `wrong`）

需要注意的是，这两个数字是互斥的：一个数字如果已经被计入 `right`，就不会再被计入 `wrong`。

### 输入格式

- 第一行：测试用例数 $N$
- 每个测试用例：
  - 第一行：猜测次数 $G$（$0 \leq G \leq 10$）
  - 接下来 $G$ 行：每行格式为 `ABCD X/Y`，其中 `ABCD` 是 $4$ 位猜测数字，`X` 是 `right` 值，`Y` 是 `wrong` 值

### 输出格式

对每个测试用例输出一行：

- `impossible`：没有密码与所有猜测一致
- `the secret code`：恰好有一个密码与所有猜测一致
- `indeterminate`：多于一个密码与所有猜测一致

### 样例分析

输入的第一个测试用例有 $6$ 条猜测，最终输出 `3411`，说明在所有 $10000$ 种可能的密码中，只有 `3411` 满足所有 $6$ 条猜测的条件。

---

## 解题思路

### 总体框架

由于密码空间非常有限（只有 $10000$ 种可能，从 $0000$ 到 $9999$），最直接的思路是 **暴力枚举**：枚举所有可能的密码，检查每个密码是否与所有给定的猜测一致，然后统计满足条件的密码数量。

这种方法的复杂度为：
- 密码总数：$10000$
- 每个测试用例最多 $10$ 条猜测
- 每条猜测需要 $O(4^2)$ 时间比较（因为要分别计算 `right` 和 `wrong`）

总时间复杂度约为 $O(N \times 10000 \times 10 \times 16)$，对于本题的数据范围完全可行。

### 核心问题：如何判断一个候选密码与一条猜测是否匹配？

判断的过程需要仔细处理 `right` 和 `wrong` 的计算，确保两者互斥。具体步骤如下：

#### 步骤 1：计算 `right`（位置和数字都正确）

遍历 $4$ 个位置，如果候选密码的第 $k$ 位与猜测的第 $k$ 位相同，则：
- `right` 计数器加 $1$
- 标记候选密码的这一位为已匹配（例如用 `*` 替代），避免后续被重复用于 `wrong` 的计算

#### 步骤 2：检查 `right` 是否匹配

如果计算出的 `right` 与给定的 `right` 不等，则该候选密码不满足这条猜测，直接排除。

#### 步骤 3：计算 `wrong`（数字正确但位置错误）

对于猜测中每一个未被匹配的位置（即该位置上的数字在步骤 1 中没有与候选密码对应位置匹配），在候选密码中寻找相同的数字（但该位置必须是未被匹配的，即不是 `*`）。找到后：
- `wrong` 计数器加 $1$
- 将候选密码中该位置标记为已使用（例如用 `-` 替代），避免一个数字被重复计数

#### 步骤 4：检查 `wrong` 是否匹配

如果计算出的 `wrong` 与给定的 `wrong` 不等，则该候选密码不满足这条猜测。

### 为什么需要标记已匹配的数字？

考虑一个例子：候选密码 `1122`，猜测 `1212`，给定 `right=1, wrong=3`。

- 计算 `right`：位置 $0$ 都是 `1`，匹配；位置 $1$ 候选为 `1` 猜测为 `2`，不匹配；位置 $2$ 候选为 `2` 猜测为 `1`，不匹配；位置 $3$ 候选为 `2` 猜测为 `2`，匹配。所以 `right = 2`（位置 $0$ 和 $3$）。标记后候选变为 `*1*2`。

- 如果不标记，计算 `wrong` 时，猜测的 `1` 和 `2` 会与候选中的 `1` 和 `2` 多次匹配，导致计数错误。标记后，每个数字只能被匹配一次，保证了正确性。

### 优化措施

虽然 $10000 \times 10 \times 16 = 1.6 \times 10^6$ 次操作已经很小，但代码中仍有一个小优化：

```cpp
if (good.size() > 1) break;
```

一旦发现超过 $1$ 个候选密码满足条件，就可以提前终止枚举，因为最终结果只关心是否唯一。这在 $G$ 较小导致大量候选密码时能略微提升效率。

### 特殊情况处理

- **$G = 0$**：没有任何猜测，所有 $10000$ 个密码都是可能的，因此输出 `indeterminate`
- **$G \ge 1$**：正常判断即可

---

## 代码实现

```cpp
// Safebreaker
// UVa ID: 296
// Verdict: Accepted
// Submission Date: 2016-05-13
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 存储每条猜测的数据结构
struct guess
{
    string number;  // 4 位猜测数字
    int right;      // 正确位置的数字个数
    int wrong;      // 数字正确但位置错误的个数
};

int main(int argc, char *argv[])
{
    // 预先生成所有可能的候选密码（从 0000 到 9999）
    vector<string> candidates;
    for (int i = 0; i <= 9999; i++)
    {
        // 将整数转换为字符串，并补足前导零至 4 位
        candidates.push_back(to_string(i));
        while (candidates.back().length() < 4)
            candidates.back().insert(candidates.back().begin(), '0');
    }
    
    int N, G;
    cin >> N;
    
    while (N--)
    {
        string line;
        cin >> G;
        cin.ignore();  // 忽略行尾换行符
        
        // 读取所有猜测
        vector<guess> guesses;
        while (G--)
        {
            getline(cin, line);
            // 解析格式：前 4 位是数字，第 5 位是空格，第 6 位是 right 值，
            // 第 7 位是 '/'，第 8 位是 wrong 值
            guesses.push_back(
                (guess){line.substr(0, 4), line[5] - '0', line[7] - '0'});
        }
        
        set<string> good;  // 存储满足所有猜测的候选密码
        
        // 枚举所有候选密码
        for (int i = 0; i < candidates.size(); i++)
        {
            bool isGood = true;  // 假设当前候选密码满足所有猜测
            
            // 逐一检查每条猜测
            for (int j = 0; j < guesses.size(); j++)
            {
                // 复制一份候选密码，因为后续需要标记已匹配的数字
                string temp = candidates[i];
                
                // ---- 第一步：计算 right（位置和数字都正确） ----
                int right = 0;
                for (int k = 0; k < 4; k++)
                    if (temp[k] == guesses[j].number[k])
                    {
                        temp[k] = '*';  // 标记为已匹配正确位置
                        right++;
                    }
                
                // 检查 right 是否匹配
                if (right != guesses[j].right)
                {
                    isGood = false;
                    break;
                }
                
                // ---- 第二步：计算 wrong（数字正确但位置错误） ----
                int wrong = 0;
                for (int k = 0; k < 4; k++)
                {
                    // 只处理猜测中未被匹配的位置（即该位置上的数字未在第一步中命中）
                    if (temp[k] != '*')
                    {
                        // 在候选密码的未匹配部分中查找该数字
                        int location = temp.find(guesses[j].number[k]);
                        if (location != temp.npos)
                        {
                            temp[location] = '-';  // 标记为已用于 wrong
                            wrong++;
                        }
                    }
                }
                
                // 检查 wrong 是否匹配
                if (wrong != guesses[j].wrong)
                {
                    isGood = false;
                    break;
                }
            }
            
            // 如果当前候选密码满足所有猜测，加入集合
            if (isGood)
                good.insert(candidates[i]);
            
            // 优化：一旦发现多于 1 个可行解，可以提前终止枚举
            if (good.size() > 1)
                break;
        }
        
        // 根据可行解的数量输出结果
        if (good.size() == 1)
        {
            cout << *(good.begin()) << endl;  // 唯一解
        }
        else if (good.size() == 0)
        {
            cout << "impossible" << endl;      // 无解
        }
        else
        {
            cout << "indeterminate" << endl;   // 多解
        }
    }
    
    return 0;
}
```

---

## 复杂度分析

- **时间复杂度**：$O(N \times 10000 \times G \times 16)$，其中 $N$ 为测试用例数，$G \leq 10$。最坏情况下约 $1.6 \times 10^7$ 次基本操作，在 $1$ 秒内可以完成。
- **空间复杂度**：$O(10000)$，用于存储候选密码列表。

---

## 总结

本题的核心思想是利用 **暴力枚举 + 精确匹配验证**，由于密码空间固定且较小，这种方法简单可靠。关键在于正确实现 `right` 和 `wrong` 的互斥计数逻辑，通过标记已匹配位置来避免重复计数。代码实现时注意字符串的复制和修改操作，确保每次判断都使用独立的副本。
