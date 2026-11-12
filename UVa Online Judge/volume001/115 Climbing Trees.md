[UVa 115 Climbing Trees](https://blog.csdn.net/metaphysis/article/details/156642438)

## 题目分析

本题要求根据输入的父子关系对（$\texttt{child-parent pairs}$）构建一个家族树，然后对一系列查询对（$\texttt{query pairs}$）判断两人之间的亲属关系，并按照特定格式输出。关系包括直接父子、祖孙、兄弟姐妹、堂表亲等。

**关键定义**：
- $p$ 是 $q$ 的 $k$-$\texttt{descendent}$（$k$-$\texttt{ancestor}$）当且仅当存在一条长度为 $k$ 的父子链。
- 关系分类：
  1. **$\texttt{child / parent}$**：直接父子（$k=0$），$\texttt{grand child/parent}$（$k=1$），$\texttt{great grand child/parent}$（$k \ge 2$，前缀 $\texttt{great}$ 重复 $k-1$ 次）。
  2. **$\texttt{sibling}$**：共享同一父母（即 $0$ 代表 $0$ 次 $\texttt{removed}$ 的 $0$-$\texttt{th cousin}$）。
  3. **$\texttt{cousin}$**：设 $p$ 和 $q$ 的最小公共祖先为 $r$，$p$ 是 $r$ 的 $m$-$\texttt{descendent}$，$q$ 是 $r$ 的 $n$-$\texttt{descendent}$，则：
     - 他们是 $k$-$\texttt{th cousin}$，其中 $k = \min(m, n)$。
     - $\texttt{removed}$ $j$ 次，其中 $j = |m - n|$。
  4. **$\texttt{no relation}$**：不在同一家族树中。

**输入限制**：
- 最多 $300$ 个不同名字，名字长度不超过 $30$。
- 最多 $100$ 个查询对。
- 无循环关系。

**输出要求**：
- 按格式输出关系，若 $\texttt{removed}$ 次数为 $0$ 则不输出 `removed 0`。
- 数字后不加序数后缀（如 `st`, `nd`, `rd`, `th`）。

## 解题思路

本题虽然名为“树”，但不需要显式建树，只需维护每个节点的父节点映射即可。由于名字是字符串，我们使用 `map<string, int>` 将名字映射为整数编号，便于处理。

**步骤**：

1. **读取父子关系**：
   - 每行读入 $\texttt{child}$ 和 $\texttt{parent}$，直到遇到 `no.child no.parent`。
   - 为新名字分配编号，记录 `parent[child] = parent`。

2. **处理查询**：
   对每个查询对 $(p, q)$：
   - **检查是否存在**：若任一名字不在映射中，输出 `no relation`。
   - **检查是否在同一棵树**：分别找到 $p$ 和 $q$ 的根祖先（不断找父节点直到 `DUMMY`），若不同则输出 `no relation`。
   - **判断直接关系**：
     - 若 $p$ 是 $q$ 的祖先：根据深度输出 $\texttt{parent / grand parent / great ... grand parent}$。
     - 若 $p$ 是 $q$ 的后代：根据深度输出 $\texttt{child / grand child / great ... grand child}$。
     - 若 $p$ 和 $q$ 是兄弟姐妹（同一父母）：输出 `sibling`。
   - **判断堂表亲关系**：
     - 先计算 $p$ 和 $q$ 到根节点的深度（$m$ 和 $n$）。
     - 将 $p$ 和 $q$ 提升到同一深度，然后同时向上找，直到找到同一父母。
     - 计算 $k = \min(m', n')$（提升后剩余深度），$j = |m - n|$（深度差）。
     - 输出 `k cousin`（若 $j=0$）或 `k cousin removed j`。

**注意**：题目要求 $\texttt{removed}$ 为 $0$ 时不输出 `removed 0`，且数字后不加序数词。

## 代码

```cpp
// Climbing Trees
// UVa ID: 115
// Verdict: Accepted
// Submission Date: 2011-11-27
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 模拟题。由于只需要保存父子关系，不一定要构建树。虽然方法是直接的，但是有点繁琐。

#include <bits/stdc++.h>

using namespace std;

#define MAXN 310
#define DUMMY (-1)

int parent[MAXN];
map<string, int> genealogy;
    
bool isAncestor(string fName, string sName) {
    int nFirst = genealogy[fName];
    int nSecond = genealogy[sName];
    int depth = 0;
    bool found = false;
    while (parent[nSecond] != DUMMY) {
        if (parent[nSecond] == nFirst) {
            found = true;
            break;
        }
        nSecond = parent[nSecond];
        depth++;
    }
    if (found) {
        if (depth == 0) cout << "parent\n";
        else if (depth == 1) cout << "grand parent\n";
        else {
            for (int i = 1; i < depth; i++) cout << "great ";
            cout << "grand parent\n";        
        }
        return true;
    }
    return false;
}

bool isDescendent(string fName, string sName) {
    int nFirst = genealogy[fName];
    int nSecond = genealogy[sName];
    int depth = 0;
    bool found = false;
    while (parent[nFirst] != DUMMY) {
        if (parent[nFirst] == nSecond) {
            found = true;
            break;
        }
        nFirst = parent[nFirst];
        depth++;
    }
    if (found) {
        if (depth == 0) cout << "child\n";
        else if (depth == 1) cout << "grand child\n";
        else {
            for (int i = 1; i < depth; i++) cout << "great ";
            cout << "grand child\n";        
        }
        return true;
    }
    return false;
}

bool isInTree(string fName, string sName) {
    if (genealogy.find(fName) == genealogy.end() ||
            genealogy.find(sName) == genealogy.end()) {
        cout << "no relation\n";
        return false;
    }
    return true;
}

bool isInSameTree(string fName, string sName) {
    int nFirst = genealogy[fName];
    int nSecond = genealogy[sName];
    while (parent[nFirst] != DUMMY) nFirst = parent[nFirst];
    while (parent[nSecond] != DUMMY) nSecond = parent[nSecond];
    if (nFirst != nSecond) {
        cout << "no relation\n";
        return false;        
    }
    return true;
}

bool isSibling(string fName, string sName) {
    int nFirst = genealogy[fName];
    int nSecond = genealogy[sName];    
    if (parent[nFirst] != DUMMY && parent[nSecond] != DUMMY &&
        parent[nFirst] == parent[nSecond]) {
        cout << "sibling\n";
        return true;
    }
    return false;
}

bool isCousin(string fName, string sName) {
    int nFirst = genealogy[fName];
    int nSecond = genealogy[sName];
    int n = 0, m = 0;
    while (parent[nFirst] != DUMMY) {
        nFirst = parent[nFirst];
        n++;
    }
    while (parent[nSecond] != DUMMY) {
        nSecond = parent[nSecond];
        m++;
    }
    nFirst = genealogy[fName];
    nSecond = genealogy[sName];
    int backN = n, backM = m;
    if (n > m) {
        while (n > m) {
            nFirst = parent[nFirst];
            n--;
        }
        while (parent[nFirst] != parent[nSecond]) {
            nFirst = parent[nFirst];
            nSecond = parent[nSecond];
            n--;
        }
        backN -= n;
        backM -= n;
        cout << backM << " cousin removed " << (backN - backM) << "\n";
    } else if (m > n) {
        while (m > n) {
            nSecond = parent[nSecond];
            m--;
        }
        while (parent[nFirst] != parent[nSecond]) {
            nFirst = parent[nFirst];
            nSecond = parent[nSecond];
            m--;
        }
        backN -= m;
        backM -= m;
        cout << backN << " cousin removed " << (backM - backN) << "\n";    
    } else {
        while (parent[nFirst] != parent[nSecond]) {
            nFirst = parent[nFirst];
            nSecond = parent[nSecond];
            n--;
            m--;
        }
        cout << (backN - n) << " cousin\n";
    }
    return true;
}

int main (int argc, char const* argv[]) {
    int nNames = 0;
    string allNames[MAXN];
    string childName, parentName;
    for (int i = 0; i < MAXN; i++) parent[i] = DUMMY;
    while (cin >> childName >> parentName) {
        if (childName == "no.child" && parentName == "no.parent") break;
        if (genealogy.find(childName) == genealogy.end()) {
            genealogy[childName] = nNames;
            allNames[nNames++] = childName;
        }
        if (genealogy.find(parentName) == genealogy.end()) {
            genealogy[parentName] = nNames;
            allNames[nNames++] = parentName;
        }
        parent[genealogy[childName]] = genealogy[parentName];
    }
    while (cin >> childName >> parentName) {
        if (!isInTree(childName, parentName)) continue;
        if (!isInSameTree(childName, parentName)) continue;
        if (isAncestor(childName, parentName)) continue;
        if (isDescendent(childName, parentName)) continue;
        if (isSibling(childName, parentName)) continue;
        if (isCousin(childName, parentName)) continue;
    }
    return 0;
}
```

## 复杂度分析

- 每次查询需要向上遍历祖先链，最坏深度为 $O(N)$，$N$ 为节点数（$\le 300$）。
- 总查询次数 $\le 100$，因此总时间复杂度为 $O(N \cdot Q)$，完全可行。

本题关键在于理清亲属关系的定义，并仔细实现各种情况的判断与输出格式。
