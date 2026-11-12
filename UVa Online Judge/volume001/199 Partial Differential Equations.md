[UVa 199 Partial Differential Equations](https://blog.csdn.net/metaphysis/article/details/160944824)

## 题目分析

本题要求通过有限差分法（$\texttt{Finite Difference Method}$）求解二维泊松方程（$\texttt{Poisson Equation}$）的边界值问题。给定一个 $[0, 1] \times [0, 1]$ 的正方形区域，将其离散化为 $(n+1) \times (n+1)$ 个网格点，步长 $h = \frac{1}{n}$。边界上的函数值由 $b_1, b_2, b_3, b_4$ 给出，内部点的值未知。

核心公式是将泊松方程 $\frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} = f(x, y)$ 离散化为：

$$
\frac{1}{h^2}(u_{i-1,j} + u_{i,j-1} + u_{i+1,j} + u_{i,j+1} - 4u_{i,j}) = f_{i,j}
$$

更一般地，题目引入两个 $3 \times 3$ 矩阵 $v$ 和 $g$，将方程扩展为：

$$
\frac{1}{h^2} \sum_{p=-1}^{1} \sum_{q=-1}^{1} v_{p+1,q+1} \cdot u_{i+p, j+q} = \sum_{p=-1}^{1} \sum_{q=-1}^{1} g_{p+1,q+1} \cdot f_{i+p, j+q}
$$

对于边界附近的点，当索引超出 $[0, n]$ 范围时，使用给定的边界条件替换。

## 解题思路

1. **离散化**：内部点共有 $(n-1)^2$ 个，按行优先顺序编号（从左到右、从上到下）。

2. **矩阵构建**：对于每个内部点 $(i, j)$（其中 $1 \le i, j \le n-1$ 对应离散化后的索引，但注意代码中使用 $i, j$ 从 $2$ 到 $n$ 表示内部点），遍历 $3 \times 3$ 邻域中的 $9$ 个点。如果邻域点在边界上，则使用边界条件值并移到方程右侧；如果邻域点在内部，则将其系数加入系数矩阵的相应列。

3. **系数处理**：由于 $\frac{1}{h^2} = n^2$ 是整数，所有计算均可使用整数运算。$v$ 矩阵的系数乘以 $n^2$ 后作为系数矩阵的元素。

4. **右侧向量**：$b$ 向量由两部分组成：
   - 边界条件贡献：$-\text{左值} \times n^2$
   - $f$ 函数贡献：$g_{p,q} \times f_{i+p, j+q}$

## 注意事项

- 输入中函数 $f$ 的矩阵表示：每行对应固定的 $y$ 值（从 $y=0$ 到 $y=1$），每列对应固定的 $x$ 值（从 $x=0$ 到 $x=1$）。
- 边界条件 $b_3$ 和 $b_4$ 的索引需注意对应关系：$b_3(y)$ 对应左边界 $x=0$，$b_4(y)$ 对应右边界 $x=1$。
- 输出格式要求：矩阵 $a$ 按行输出 $(n-1)^2$ 行，每行 $(n-1)^2$ 个整数；向量 $b$ 输出一行 $(n-1)^2$ 个整数。

## 代码实现

```cpp
// Partial Differential Equations
// UVa ID: 199
// Verdict: Accepted
// Submission Date: 2016-03-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int a[35][35], b[1000], v[3][3], g[3][3], boundary[4][35], f[35][35], temp[1000], n;

int main() {
    int m;
    cin >> m;
    
    while (m--) {
        cin >> n;
        
        // 读取 3x3 矩阵 v
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cin >> v[i][j];

        // 读取 3x3 矩阵 g
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cin >> g[i][j];
        
        // 读取四个边界条件：b1(上边界), b2(下边界), b3(左边界), b4(右边界)
        for (int i = 0; i < 4; i++)
            for (int j = 0; j <= n; j++)
                cin >> boundary[i][j];
        
        // 读取函数 f 在网格点上的值
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                cin >> f[i][j];
        
        int counter = 0;
        // 遍历所有内部点 (i, j)，i 和 j 从 2 到 n 对应内部点的实际索引
        // 内部点在离散化区域中对应 (1..n-1) 的索引，但这里 i,j 从 2 开始是为了方便处理 3x3 邻域
        for (int i = 2; i <= n; i++)
            for (int j = 2; j <= n; j++) {
                // 临时数组存储系数矩阵的一行，长度为 (n-1)^2
                fill(temp, temp + 1000, 0);
                
                int right = 0;
                // 遍历当前点 (i, j) 周围的 3x3 邻域
                for (int x = i - 2; x <= i; x++)
                    for (int y = j - 2; y <= j; y++) {
                        int left = 0;
                        // 根据邻域点的位置判断处理方式
                        if (x == 0)  // 上边界（y 方向，对应 b2？需注意索引）
                        {
                            left = v[x + 2 - i][y + 2 - j] * boundary[1][y];
                        }
                        else if (x == n)  // 下边界（对应 b1）
                        {
                            left = v[x + 2 - i][y + 2 - j] * boundary[0][y];
                        }
                        else if (y == 0)  // 左边界（对应 b3）
                        {
                            left = v[x + 2 - i][y + 2 - j] * boundary[2][n - x];
                        }
                        else if (y == n)  // 右边界（对应 b4）
                        {
                            left = v[x + 2 - i][y + 2 - j] * boundary[3][n - x];
                        }
                        else  // 内部点，记录系数
                        {
                            // 内部点的线性索引：(x-1)*(n-1) + (y-1)
                            temp[(x - 1) * (n - 1) + y - 1] = v[x + 2 - i][y + 2 - j] * n * n;
                        }
                        
                        // 右侧项：减去边界贡献 * n^2，加上 g * f 的贡献
                        right += -left * n * n + g[x + 2 - i][y + 2 - j] * f[x][y];
                    }
                    
                b[counter++] = right;
               
                // 输出系数矩阵的当前行
                for (int k = 0; k < (n - 1) * (n - 1); k++)
                    cout << (k > 0 ? " " : "") << temp[k];
                cout << endl;
            }
        
        // 输出右侧向量 b
        for (int i = 0; i < (n - 1) * (n - 1); i++)
            cout << (i > 0 ? " " : "") << b[i];
        cout << endl;
    }
    
    return 0;
}
```

## 复杂度分析

- **时间复杂度**：$O(n^4)$，因为对于每个内部点（共 $(n-1)^2$ 个），需要遍历 $9$ 个邻域点并更新系数矩阵的一行。由于 $n \le 30$，完全可接受。
- **空间复杂度**：$O(n^2)$，用于存储边界条件、函数 $f$ 和临时数组。
