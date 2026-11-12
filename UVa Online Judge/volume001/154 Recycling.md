[UVa 154 Recycling](https://blog.csdn.net/metaphysis/article/details/158571042)

## 题目大意

新西兰的各个城市都在推行路边回收计划，每个城市用五种不同颜色的垃圾桶（红、橙、黄、绿、蓝）来回收五种废弃物（塑料、玻璃、铝、钢铁、报纸）。由于缺乏协调，每个城市都随意地将废弃物分配到不同颜色的垃圾桶中。

现在政府想要推行一项 "废弃物分配规范化法案"，需要从现有的城市中选择一个城市的分配方案作为国家标准。选择的标准是：这个方案如果强制推行到全国，需要其他城市改变的分配项数最少（即与其他城市现有方案的差异最小）。注意每个城市拥有平等的投票权，城市规模不影响结果。

输入包含多个数据块，每个块代表一组城市的数据，以 `e` 结尾，整个文件以 `#` 结尾。需要为每个数据块输出当选城市的编号（从 $1$ 开始计数）。

## 问题分析

这道题本质上是一个 **最小差异选择问题**。我们需要理解几个关键点：

1. **分配方案的表示**：每个城市有 $5$ 种颜色的垃圾桶，每种颜色对应回收一种废弃物。所以一个城市的方案可以用一个长度为 $5$ 的数组表示，数组的每个位置表示某种颜色垃圾桶对应的废弃物类型。

2. **差异的计算**：如果选择城市 $i$ 的方案作为标准，那么对于城市 $j$，需要改变的项数就是城市 $j$ 与城市 $i$ 在 $5$ 个位置上不一致的数量。

3. **优化目标**：我们需要找到这样的城市 $i$，使得 $\sum_{j \neq i} \text{diff}(i, j)$ 最小。题目保证存在唯一的最优解。

## 解题思路

### 1. 数据结构设计

代码中使用：
- `string colours = "roygb"`：表示五种颜色（红、橙、黄、绿、蓝）的缩写
- `string wastes = "PGASN"`：表示五种废弃物（塑料、玻璃、铝、钢铁、报纸）的缩写
- `matrix[110][5]`：存储每个城市的分配方案，`matrix[i][j]` 表示城市 $i$ 的第 $j$ 种颜色对应的废弃物索引
- `counter[5][5]`：统计在所有城市中，对于每种颜色，各种废弃物被分配的次数

### 2. 数据处理流程

对于每个城市的数据行（例如 `r/P,o/G,y/S,g/A,b/N`）：
1. 去除空格和制表符
2. 对于五种颜色，分别找到该颜色对应的废弃物
3. 更新计数器：`counter[颜色索引][废弃物索引]++`
4. 将当前城市的分配存入 `matrix`

### 3. 核心算法

关键创新点在于 **如何高效计算总差异数**，而不是采用 $O(n^2)$ 的暴力两两比较。

假设我们选择城市 $k$ 作为标准，那么所有城市的总差异数可以这样计算：

对于城市 $k$ 的每种颜色 $c$，它所回收的废弃物类型为 $w_k$。对于其他城市，如果它们在颜色 $c$ 上回收的废弃物不是 $w_k$，就需要改变。那么颜色 $c$ 上需要改变的总次数就是：**所有城市中颜色 $c$ 对应废弃物不是 $w_k$ 的城市数量**。

而所有城市中颜色 $c$ 对应废弃物是 $w_k$ 的城市数量正是 `counter[c][w_k]`。所以颜色 $c$ 上需要改变的次数为：
$$\texttt{changes}_c = \text{总城市数} - \texttt{counter}[c][w_k]$$

因此，选择城市 $k$ 的总差异数为：
$$\texttt{totalChanges}(k) = \sum_{c=0}^{4} (\texttt{cities} - \texttt{counter}[c][\texttt{matrix}[k][c]])$$

由于 $\texttt{cities}$ 是常数，最大化 $\sum \texttt{counter}[c][\texttt{matrix}[k][c]]$ 等价于最小化总差异数。

### 4. 算法复杂度

- 时间复杂度：$O(n \times m)$，其中 $n$ 是城市数量，$m$ 是废弃物种类数（$m=5$）
- 空间复杂度：$O(n \times m + m^2)$

## 代码实现

```cpp
// Recycling
// UVa ID: 154
// Verdict: Accepted
// Submission Date: 2016-02-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string colours = "roygb", wastes = "PGASN";

int matrix[110][5] = {0}, counter[5][5] = {0}, cities = 0;

void getIndex(void) {
    int minChanges = -1, minIndex = 0;
    for (int i = 0; i < cities; i++) {
        int allChanges = 0;
        for (int j = 0; j < 5; j++) allChanges += counter[j][matrix[i][j]];
        if (allChanges > minChanges) {
            minChanges = allChanges;
            minIndex = i;
        }
    }
    cout << (minIndex + 1) << endl;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line[0] == '#') break;
        if (line[0] == 'e') {
            getIndex();
            cities = 0;
            memset(counter, 0, sizeof(counter));
            memset(matrix, 0, sizeof(matrix));
        } else {
            for (int i = line.length() - 1; i >= 0; i--)
                if (line[i] == ' ' || line[i] == '\t')
                    line.erase(line.begin() + i);
            for (int i = 0; i < colours.length(); i++) {
                int colourIndex = line.find(colours[i]);
                int wasteIndex = wastes.find(line[colourIndex + 2]);
                counter[i][wasteIndex]++;
                matrix[cities][i] = wasteIndex;
            }
            cities++;
        }
    }
	return 0;
}
```

## 关键点说明

1. **字符串处理**：输入格式中每个分配项用逗号分隔，如 `r/P` 表示红色桶回收塑料。代码通过查找颜色字符的位置来解析。

2. **索引对应**：
   - 颜色顺序：$0$ 红 (`r`)、$1$ 橙 (`o`)、$2$ 黄 (`y`)、$3$ 绿 (`g`)、$4$ 蓝 (`b`)
   - 废弃物顺序：$0$ 塑料 (`P`)、$1$ 玻璃 (`G`)、$2$ 铝 (`A`)、$3$ 钢铁 (`S`)、$4$ 报纸 (`N`)

3. **计数器的使用**：`counter[i][j]` 表示在所有城市中，颜色 $i$ 被用来回收废弃物 $j$ 的次数。这个统计量大大简化了后续的计算。

4. **最优城市的选取**：通过比较 $\sum \texttt{counter}[c][\texttt{matrix}[i][c]]$ 的值，取最大值对应的城市，因为这样可以最大化 "无需改变" 的项数。

## 示例验证

对于样例输入：
```
r/P,o/G,y/S,g/A,b/N
r/G,o/P,y/S,g/A,b/N
r/P,y/S,o/G,g/N,b/A
r/P,o/S,y/A,g/G,b/N
e
r/G,o/P,y/S,g/A,b/N
r/P,y/S,o/G,g/N,b/A
r/P,o/S,y/A,g/G,b/N
r/P,o/G,y/S,g/A,b/N
ecclesiastical
#
```

程序会正确输出每个数据块中当选城市的编号：

```
1
4
```
