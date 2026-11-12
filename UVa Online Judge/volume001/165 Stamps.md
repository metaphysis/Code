[UVa 165 Stamps](https://blog.csdn.net/metaphysis/article/details/158732855)

## 题目大意

某国政府要求各类法律文件必须贴邮票，以便从中获取财政收入。根据最新法规，每类文件对可贴的邮票数量有限制。政府需要知道应该印制多少种不同面值的邮票，以及这些面值应该是多少，以便在给定条件下能够组成最广泛的连续数值序列。

邮票面值以 $1$ 元为单位。定义 $n(h,k)$，其中：
- $h$ 表示一份文件最多可以贴的邮票数量
- $k$ 表示可用的邮票面值种类数
- $n$ 表示从 $1$ 开始能够连续组成的最大数值

例如：当 $h=3, k=2$，面值为 $1$ 和 $4$ 时，可以组成 $1$ 到 $6$，以及 $8,9,12$，但无法组成 $7$。若使用面值 $1$ 和 $3$，则可以组成 $1$ 到 $7$（以及 $9$），这是最优的，因此 $n(3,2)=7$。

由于 $h+k \leq 9$（总统在一次射击事故中失去了小指，数不到 $9$），需要编写程序计算给定 $h$ 和 $k$ 时的最优邮票面值组合及对应的 $n(h,k)$。

## 问题分析

这是一个典型的邮票问题（$\texttt{Stamps Problem}$），本质上是一个组合优化问题。我们需要在以下约束下寻找最优解：
1. 有 $k$ 种不同面值的邮票，面值为正整数
2. 最多可以使用 $h$ 张邮票
3. 从 $1$ 开始，能够连续组成的数值越大越好
4. $h+k \leq 9$，问题规模较小，可以使用回溯法

## 解题思路

### 状态表示
- 使用回溯法逐步确定 $k$ 种面值
- 对于给定的一组面值，计算从 $1$ 开始能连续组成到多少

### 剪枝优化
由于 $h+k \leq 9$，最坏情况 $h=5, k=4$ 时，搜索空间依然可控，可以使用回溯法暴力求解。

### 计算连续最大值的方法
对于给定的一组面值，需要确定从 $1$ 开始最多能连续组成到多少。可以使用深度优先搜索枚举所有可能的邮票组合：
- 对于每种面值，可以选择使用 $0$ 到 $h$ 张
- 检查产生的总和，记录从 $1$ 开始的连续长度

### 面值上界
面值不需要太大，可以通过分析得出一个合理的上界。当确定前 $i$ 种面值后，第 $i+1$ 种面值最大不超过当前能组成的最大值加 $1$（否则会产生无法组成的数）。

## 算法实现

### 生成解的程序
该程序使用两层回溯：
1. 外层回溯确定 $k$ 种面值
2. 内层回溯枚举每种面值的使用数量，计算连续最大值

程序遍历所有 $h$ 和 $k$ 的组合（$h \geq 1, k \geq 1, h+k \leq 9$），生成最优解并输出格式化的结果。

### 最终解题代码
将生成的最优解硬编码到程序中，对于给定的 $h$ 和 $k$，直接查表输出结果。

## 代码实现

### 生成解的代码

```cpp

#include <bits/stdc++.h>
using namespace std;

int kLimit = 40;

vector<int> hCandidate, kCandidate, kValue;
set<int> valueProduced;
int maxK, maxH, maxSequenceLength;
int countH;

void backtrackH(int index) {
    if (countH > maxH) return;
    if (index == maxK) {
        int value = 0;
        for (int i = 0; i < hCandidate.size(); i++)
            value += (hCandidate[i] * kCandidate[i]);
        valueProduced.insert(value);
    } else {
        for (int i = 0; i <= maxH; i++) {
            countH += i;
            hCandidate[index] = i;
            backtrackH(index + 1);
            countH -= i;
        }
    }
}

void findMaxSequenceLength() {
    valueProduced.clear();
    countH = 0;
    backtrackH(0);
    int length = 0;
    while (valueProduced.count(length + 1) == 1) length++;
    if (length > maxSequenceLength) {
        kValue.clear();
        for (int i = 0; i < kCandidate.size(); i++) kValue.push_back(kCandidate[i]);
        maxSequenceLength = length;
    }
}

void backtrackK(int index, int start) {
    if (index == maxK) {
        findMaxSequenceLength();
        return;
    }
    for (int i = start + 1; i <= kLimit; i++) {
        kCandidate[index] = i;
        backtrackK(index + 1, i);
    } 
}

void search(int h, int k) {
    cout << "maxSequence[" << (h * 10 + k) << "] = \"";
    if (h == 0 || k == 0) {
        cout << "  0 ->  0\";\n";
        return;
    }
    if (h == 1) {
        for (int i = 1; i <= k; i++)
            cout << setw(3) << right << i;
        cout << " ->" << setw(3) << right << k;
        cout << "\";\n";
        return;
    }
    
    if (k == 1) {
        cout << "  1 ->  " << h << "\";\n";
        return;
    }

    maxH= h;
    maxK = k;
    maxSequenceLength = 0;

    hCandidate.clear();
    for (int i = 1; i <= k; i++) hCandidate.push_back(0);
    kCandidate.clear();
    kCandidate.push_back(1);
    for (int i = 2; i <= k; i++)
        kCandidate.push_back(0);
    backtrackK(1, 1);
    sort(kValue.begin(), kValue.end());
    for (int i = 0; i < kValue.size(); i++)
        cout << right << setw(3) << kValue[i];
    cout << " ->" << right << setw(3) << maxSequenceLength << "\";\n";
}

int main() {
    for (int h = 1; h <= 9; h++)
        for (int k = 1; k <= 9 - h; k++)
            search(h, k);
    return 0;
}
```

### 最终解题代码

```cpp
// Stamps
// UVa ID: 165
// Verdict: Accepted
// Submission Date: 2016-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

map<int, string> maxSequence;

int main() {
    int h, k;
    
    maxSequence[11] = "  1 ->  1";
    maxSequence[12] = "  1  2 ->  2";
    maxSequence[13] = "  1  2  3 ->  3";
    maxSequence[14] = "  1  2  3  4 ->  4";
    maxSequence[15] = "  1  2  3  4  5 ->  5";
    maxSequence[16] = "  1  2  3  4  5  6 ->  6";
    maxSequence[17] = "  1  2  3  4  5  6  7 ->  7";
    maxSequence[18] = "  1  2  3  4  5  6  7  8 ->  8";
    maxSequence[21] = "  1 ->  2";
    maxSequence[22] = "  1  2 ->  4";
    maxSequence[23] = "  1  3  4 ->  8";
    maxSequence[24] = "  1  3  5  6 -> 12";
    maxSequence[25] = "  1  3  5  7  8 -> 16";
    maxSequence[26] = "  1  2  5  8  9 10 -> 20";
    maxSequence[27] = "  1  2  5  8 11 12 13 -> 26";
    maxSequence[31] = "  1 ->  3";
    maxSequence[32] = "  1  3 ->  7";
    maxSequence[33] = "  1  4  5 -> 15";
    maxSequence[34] = "  1  4  7  8 -> 24";
    maxSequence[35] = "  1  4  6 14 15 -> 36";
    maxSequence[36] = "  1  3  7  9 19 24 -> 52";
    maxSequence[41] = "  1 ->  4";
    maxSequence[42] = "  1  3 -> 10";
    maxSequence[43] = "  1  5  8 -> 26";
    maxSequence[44] = "  1  3 11 18 -> 44";
    maxSequence[45] = "  1  3 11 15 32 -> 70";
    maxSequence[51] = "  1 ->  5";
    maxSequence[52] = "  1  4 -> 14";
    maxSequence[53] = "  1  6  7 -> 35";
    maxSequence[54] = "  1  4 12 21 -> 71";
    maxSequence[61] = "  1 ->  6";
    maxSequence[62] = "  1  4 -> 18";
    maxSequence[63] = "  1  7 12 -> 52";
    maxSequence[71] = "  1 ->  7";
    maxSequence[72] = "  1  5 -> 23";
    maxSequence[81] = "  1 ->  8";

    while (cin >> h >> k, h || k) {
        if (h * k == 0) {
            cout << "  0 ->   0" << endl;
            continue;
        }
        cout << maxSequence[h * 10 + k] << endl;
    }
	return 0;
}
```

## 复杂度分析

由于使用预先生成的结果表，时间复杂度为 $O(1)$。空间复杂度为 $O(h \times k)$，用于存储结果映射。

## 总结

本题虽然表面上要求寻找数学公式，但由于问题规模很小，完全可以通过暴力搜索找出所有可能的最优解。这种方法避免了寻找复杂数学公式的困难，同时也保证了程序的正确性和效率。
