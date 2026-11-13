[UVa 219 Department of Redundancy Department](https://blog.csdn.net/metaphysis/article/details/161047706)

## 题目分析

本题要求在给定的函数依赖（$\texttt{Functional Dependency，FD}$）集合中，找出所有可以被其他依赖推导出的冗余依赖。对于每个冗余依赖，还需输出一组用于证明其冗余的依赖序列。

函数依赖的数学表示为 $\mathbf{X} \rightarrow \mathbf{Y}$，含义是：给定属性集 $\mathbf{X}$ 的值，可以唯一确定属性集 $\mathbf{Y}$ 的值。例如，如果有依赖 $\texttt{A} \rightarrow \texttt{B}$ 和 $\texttt{B} \rightarrow \texttt{C}$，那么 $\texttt{A} \rightarrow \texttt{C}$ 就是冗余的，因为由 $\texttt{A}$ 可推出 $\texttt{B}$，再由 $\texttt{B}$ 可推出 $\texttt{C}$。

输入包含多组数据，每组第一行是一个不超过 $100$ 的整数 $n$，表示该组依赖的数量。随后 $n$ 行每行一个依赖，格式如 `A->BD`，表示左部为属性 $\texttt{A}$，右部为属性 $\texttt{B}$ 和 $\texttt{D}$。输入以 $n = 0$ 结束。每组输出需要按照样例格式，列出所有冗余依赖及其证明序列。如果存在多种证明序列，任意一种均可接受。

## 解题思路

### 1. 属性集的掩码表示

由于属性均为大写字母，最多 $26$ 个不同属性，可以用一个 $32$ 位整数的二进制位表示属性集合。每位对应一个字母，例如 `A` 对应第 $0$ 位，`B` 对应第 $1$ 位，以此类推。这样，依赖的左部和右部都可以用整数掩码高效表示。

### 2. 冗余依赖的判断

一个依赖 $\mathbf{X} \rightarrow \mathbf{Y}$ 是冗余的，当且仅当：从 $\mathbf{X}$ 出发，利用除自身以外的其他依赖进行推导，最终能够得到 $\mathbf{Y}$。推导过程即为经典的闭包计算：

- 初始闭包为 $\mathbf{X}$。
- 反复应用所有可用的依赖：若当前闭包包含某依赖的左部，则将右部并入闭包。
- 直到闭包不再扩大为止。

若最终闭包包含 $\mathbf{Y}$，则该依赖冗余。

### 3. 证明序列的构造

题目要求输出一组用于证明冗余的依赖序列，并且该序列中的每一个依赖都是“必要”的（即去掉任何一个都无法完成推导）。这本质上是一个寻找最短或任意可行推导路径的问题。由于 $n \leq 100$，可以接受 $\texttt{DFS}$ 试探。

解题代码采用深度优先搜索（$\texttt{DFS}$）来构造证明序列：

- 从目标依赖的左部开始，递归地尝试应用其他依赖。
- 每次应用一个依赖后，将右部加入当前属性集。
- 当当前属性集包含目标右部时，找到一条路径。
- 为了保证序列中每个依赖都是必要的，代码在搜索中采用了剪枝策略：先检查在不使用当前已选依赖的情况下能否推导出目标右部，若能则无需继续该分支（因为说明当前路径不是最简）。
- 搜索过程中使用 `visited` 数组标记已使用过的依赖，避免循环应用。

### 4. 算法步骤

对于每个依赖 $i$（编号从 $1$ 开始）：

1. 将该依赖标记为“禁用”，即不在推导中使用它。
2. 从该依赖的左部出发，尝试使用其他依赖进行闭包扩展。
3. 若扩展后得到右部，则依赖 $i$ 冗余，输出证明序列。
4. 否则，依赖 $i$ 不冗余。

## 代码实现

```cpp
// Department of Redundancy Department
// UVa ID: 219
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_N = 105;      // 最大FD数量
bool hasRedundant;          // 标记当前组是否存在冗余FD
int n;                      // FD数量
int lhsMask[MAX_N], rhsMask[MAX_N];  // 每个FD的左右部字段掩码
int path[MAX_N], visited[MAX_N];     // 记录推导路径和访问标记

// 解析输入字符串，转换为掩码形式
void parseFD(char* str, int idx) {
    bool isRight = false;   // 是否遇到->符号，进入右部解析
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            if (isRight)
                rhsMask[idx] |= (1 << (str[i] - 'A'));  // 设置右部对应位
            else
                lhsMask[idx] |= (1 << (str[i] - 'A'));  // 设置左部对应位
        } else if (str[i] == '-') {
            isRight = true;  // 遇到->，开始解析右部
            i++;             // 跳过下一个字符'>'
        }
    }
}

// 初始化：读取输入并解析
void initialize() {
    char inputStr[MAX_N];
    hasRedundant = true;     // 初始假设存在冗余
    memset(lhsMask, 0, sizeof(lhsMask));
    memset(rhsMask, 0, sizeof(rhsMask));
    for (int i = 0; i < n; i++) {
        scanf("%s", inputStr);
        parseFD(inputStr, i);
    }
}

// 输出找到的冗余FD及其推导路径
void outputRedundantFD(int idx) {
    printf("     FD %d is redundant using FDs:", idx + 1);
    for (int i = 0; path[i] != -1; i++)
        printf(" %d", path[i]);
    printf("\n");
}

// 检查当前字段集合是否能推导出目标FD的右部（不使用目标FD）
bool canDerive(int currentSet, int targetIdx) {
    int used[MAX_N];
    memset(used, 0, sizeof(used));
    while (true) {
        bool noChange = true;   // 标记是否无法继续扩展
        for (int i = 0; i < n; i++) {
            if (used[i] || visited[i])   // 跳过已使用或标记为忽略的FD
                continue;
            if ((currentSet & lhsMask[i]) != lhsMask[i])  // 检查左部是否满足
                continue;
            used[i] = 1;
            currentSet |= rhsMask[i];   // 扩展当前字段集合
            noChange = false;
        }
        if (noChange) break;    // 无法继续扩展，退出循环
    }
    // 检查是否包含目标右部
    return (currentSet | rhsMask[targetIdx]) != currentSet;
}

// DFS搜索推导路径
bool searchPath(int depth, int currentSet, int targetIdx) {
    path[depth] = -1;   // 路径结束标记
    // 若当前集合已包含目标右部，则找到路径
    if ((currentSet & rhsMask[targetIdx]) == rhsMask[targetIdx])
        return true;
    // 若无法继续推导，剪枝
    if (canDerive(currentSet, targetIdx))
        return false;
    // 尝试应用每个未使用的FD
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        if ((currentSet & lhsMask[i]) != lhsMask[i]) continue;  // 左部不满足
        if ((currentSet | rhsMask[i]) == currentSet) continue;  // 右部已包含
        visited[i] = 1;
        if (searchPath(depth, currentSet, targetIdx))   // 不选择当前FD
            return true;
        path[depth] = i + 1;    // 记录当前FD编号（从1开始）
        if (searchPath(depth + 1, currentSet | rhsMask[i], targetIdx))  // 选择当前FD
            return true;
        visited[i] = 0;
    }
    return false;
}

// 主处理函数：检测每个FD是否冗余
void findRedundantFDs() {
    for (int i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited));
        visited[i] = 1;         // 标记当前FD为忽略
        if (searchPath(0, lhsMask[i], i)) {  // 从当前FD的左部开始搜索
            outputRedundantFD(i);
            hasRedundant = false;   // 标记存在冗余
        }
    }
}

int main() {
    int caseNum = 1;
    while (scanf("%d", &n) == 1 && n) {
        initialize();
        printf("Set number %d\n", caseNum++);
        findRedundantFDs();
        if (hasRedundant)
            printf("     No redundant FDs.\n");
        printf("\n");
    }
    return 0;
}
```

## 总结

本题的核心是函数依赖的闭包计算和推导路径的 $\texttt{DFS}$ 搜索。利用掩码表示属性集可以极大提升运算效率。在构造证明序列时，需要保证序列中每个依赖都是必要的，代码通过剪枝函数 `canDerive` 提前判断当前状态下是否已经“注定”能推出目标，从而避免无效搜索。按此方法即可正确求解所有输入组。
