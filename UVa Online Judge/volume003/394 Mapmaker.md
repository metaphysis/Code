[UVa 394 Mapmaker](https://blog.csdn.net/metaphysis/article/details/161705460)

## 题目描述

$\texttt{Cybersoft}$ 计算机公司（编程语言领域的领导者）雇佣你来为一门名为 `A--` 的新编程语言工作。你的任务是处理该语言的数组映射任务。你需要接收数组引用（如 `x[5,6]`）并将其映射到实际的物理地址。

物理地址的计算公式为：
$$
\text{address} = C_0 + C_1 i_1 + C_2 i_2 + \dots + C_D i_D
$$

其中常数 $C_0 \dots C_D$ 按以下规则计算：
- $B$：数组的基地址
- $D$：数组的维数
- $L_d$：第 $d$ 维的下界
- $U_d$：第 $d$ 维的上界
- $C_D$：数组元素大小（字节）
- $C_d = C_{d+1} \times (U_{d+1} - L_{d+1} + 1)$，对于 $1 \leq d < D$
- $C_0 = B - C_1 L_1 - C_2 L_2 - \dots - C_D L_D$

### 输入格式

第一行包含两个正整数：$N$（数组定义的数量）和 $R$（数组引用数量）。

接下来 $N$ 行，每行定义一个数组：
- 数组名（最多 $10$ 个字符）
- 基地址
- 元素大小（字节）
- 维数 $D$（$1 \leq D \leq 10$）
- 随后 $D$ 对整数：每维的下界和上界

接下来 $R$ 行，每行指定一个数组引用：
- 数组名
- 各维度的索引值 $i_1, i_2, \dots, i_D$

### 输出格式

对于每个数组引用，输出一行：
```
名称[索引1, 索引2, ...] = 物理地址
```

### 样例输入

```
3 4
ONE 1500 2 2 0 3 1 5
TWO 2000 4 3 1 4 0 5 5 10
THREE 3000 1 1 1 9
ONE 2 4
THREE 7
TWO 2 0 6
TWO 3 3 9
```

### 样例输出

```
ONE[2, 4] = 1526
THREE[7] = 3006
TWO[2, 0, 6] = 2148
TWO[3, 3, 9] = 2376
```

---

## 题目分析

### 问题的本质

这是一个**数组地址计算**问题。根据公式计算多维数组元素在内存中的物理地址。

### 公式推导

对于 $D$ 维数组，地址公式为：
$$
\text{address} = B + \sum_{d=1}^{D} \left( (i_d - L_d) \times \prod_{k=d+1}^{D} (U_k - L_k + 1) \right) \times \text{bytes}
$$

等价地：
- 计算从最低维到最高维的累积跨度
- 偏移量 = $\sum (i_d - L_d) \times \textit{stride}_d$
- 最终地址 = 基地址 + 偏移量 × 元素大小

### 算法步骤

1. 存储每个数组的基地址、元素大小、各维边界
2. 对于每个引用：
   - 从最高维到最低维计算累积跨度
   - 计算偏移量
   - 计算最终地址

---
## 参考代码

```cpp
// Mapmaker
// UVa ID: 394
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct arrayInfo
{
    int base, bytes, dimensions;
    vector<pair<int, int>> bounds;  // 各维的下界和上界
};

int main(int argc, char *argv[])
{
    int N, R;
    while (cin >> N >> R)
    {
        vector<arrayInfo> arrays;
        map<string, int> indexer;  // 数组名到索引的映射
        
        // 读取数组定义
        for (int i = 1; i <= N; i++)
        {
            string name;
            int base, bytes, dim;
            
            cin >> name >> base >> bytes >> dim;
            
            arrayInfo info;
            info.base = base;
            info.bytes = bytes;
            info.dimensions = dim;
            
            for (int j = 1; j <= dim; j++)
            {
                int low, up;
                cin >> low >> up;
                info.bounds.push_back({low, up});
            }
            
            indexer[name] = arrays.size();
            arrays.push_back(info);
        }
        
        // 处理数组引用
        for (int i = 1; i <= R; i++)
        {
            string name;
            cin >> name;
            
            int idx = indexer[name];
            int dim = arrays[idx].dimensions;
            vector<int> indices(dim);
            
            // 输出数组引用
            cout << name << "[";
            for (int j = 0; j < dim; j++)
            {
                if (j > 0) cout << ", ";
                cin >> indices[j];
                cout << indices[j];
            }
            cout << "] = ";
            
            // 计算物理地址
            int address = 0, length = 1;
            for (int j = dim - 1; j >= 0; j--)
            {
                address += (indices[j] - arrays[idx].bounds[j].first) * length;
                length *= (arrays[idx].bounds[j].second - arrays[idx].bounds[j].first + 1);
            }
            address = arrays[idx].base + address * arrays[idx].bytes;
            
            cout << address << endl;
        }
    }
    
    return 0;
}
```
