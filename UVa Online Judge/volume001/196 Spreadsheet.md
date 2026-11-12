[UVa 196 Spreadsheet](https://blog.csdn.net/metaphysis/article/details/160943069)

## 题目分析

本题要求实现一个简单的电子表格计算程序。电子表格由若干单元格组成，每个单元格要么是一个整数数值，要么是一个求和公式。公式以等号 `=` 开头，后面跟着若干用加号 `+` 连接的单元格引用，表示这些单元格数值的总和。题目保证没有循环依赖，因此所有单元格都可以被正确计算。

输入的第一行是电子表格的数量。每个电子表格的第一行包含两个整数：列数和行数。接下来是表格的每一行数据，行内的单元格用空格分隔。

输出的格式与输入相同，但所有公式都要替换为计算后的数值。

**难点**：单元格命名规则不是简单的 `A1, B1, ... , Z1, AA1, AB1, ...` 这样的 26 进制表示，而是类似于 Excel 的列命名方式，其中 `A` 对应 $1$，`Z` 对应 $26$，`AA` 对应 $27$，依此类推，最大为 `ZZZ` 对应 $18278$。

## 解题思路

### 1. 单元格命名转换

需要实现两个转换：
- 从行列坐标 `(row, col)` 转换为单元格名称 `getCellId(row, col)`
- 从单元格名称解析出行列坐标（本题用不到）

`getCellId` 的实现采用 $26$ 进制转换，但需要注意普通的 $26$ 进制中 `A` 对应 $0$，而本题中 `A` 对应 $1$，因此需要特殊处理：当余数为 $0$ 时，对应字母 `Z`，并将商减 $1$。

### 2. 数据存储

使用两个 `map` 结构：
- `cells`：存储已经计算出的单元格数值（键为单元格名称，值为整数）
- `formula`：存储公式的依赖关系（键为单元格名称，值为引用的单元格名称列表）

### 3. 递归计算

`getValue(x)` 函数采用类似深度优先搜索的方式计算单元格 `x` 的值：
- 如果 `x` 已经在 `cells` 中，直接返回其数值
- 否则，`x` 是一个公式，遍历其依赖的所有单元格，递归调用 `getValue` 求和
- 将计算结果存入 `cells` 并返回

由于题目保证无环，递归可以正确终止。

### 4. 输入解析

读取每个单元格内容时：
- 如果以 `=` 开头，则解析公式：在末尾添加 `+` 作为哨兵，然后用 `find` 定位 `+` 的位置，提取每个引用的单元格名称
- 否则，直接转换为整数存入 `cells`

### 5. 输出

按行按列遍历所有单元格，调用 `getValue` 获取计算结果并输出。

## 代码实现

```cpp
// Spreadsheet
// UVa ID: 196
// Verdict: Accepted
// Submission Date: 2016-03-15
// UVa Run Time: 0.093s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<string, int> cells;                  // 存储已计算的单元格数值
map<string, vector<string>> formula;     // 存储公式的依赖关系
string columns = "ZABCDEFGHIJKLMNOPQRSTUVWXY";  // 列名映射，索引 1~26 对应 A~Z

// 将行列坐标转换为单元格名称，例如 (1,1) -> "A1"
string getCellId(int i, int j) {
    string id;
    while (j > 0) {
        // 取余数，columns[j % 26] 得到对应字母
        id.insert(id.begin(), columns[j % 26]);
        // 当余数为 0 时表示 Z，需要将 j 减去 26 以正确处理进位
        if (j % 26 == 0)
            j -= 26;
        j /= 26;
    }
    return id + to_string(i);
}

// 递归计算单元格 x 的值
int getValue(string x) {
    // 如果已经计算过，直接返回
    if (cells.count(x)) return cells[x];
        
    int sum = 0;    
    // 遍历公式中引用的所有单元格，递归求和
    for (int i = 0; i < formula[x].size(); i++)
        sum += getValue(formula[x][i]);
    
    // 记忆化存储结果
    cells[x] = sum;
    return sum;
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int n;
    cin >> n;
    
    while (n--) {
        int row, column;
        cin >> column >> row;
        
        // 清空上一次的数据
        cells.clear();
        formula.clear();
        
        // 读取整个电子表格
        for (int i = 1; i <= row; i++)
            for (int j = 1; j <= column; j++) {
                string block;
                cin >> block;
                
                string id = getCellId(i, j);
                
                // 判断是否为公式（以等号开头）
                if (block.front() == '=') {
                    // 在末尾添加 '+' 作为哨兵，方便解析
                    block += '+';
                    int start = 1, next = start;
                    while (start < block.length()) {
                        // 找到下一个 '+' 的位置
                        next = block.find('+', start);
                        // 提取两个 '+' 之间的单元格名称
                        formula[id].push_back(block.substr(start, next - start));
                        start = next + 1;
                    }
                } else {
                    // 数值直接存入 cells
                    cells[id] = stoi(block);
                }
            }
        
        // 输出结果
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= column; j++)
                cout << (j > 1 ? " ": "") << getValue(getCellId(i, j));
            cout << "\n";
        }
            
    }
    
	return 0;
}
```

## 复杂度分析

- **时间复杂度**：每个单元格最多被计算一次，且每次计算需要遍历其引用的单元格，总时间复杂度为 $O(R \times C)$，其中 $R$ 和 $C$ 分别为行数和列数。
- **空间复杂度**：$O(R \times C)$，用于存储所有单元格的数值和公式依赖关系。
