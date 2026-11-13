## 题目理解

有 $k$ 个小孩围成一圈（至少 $2$ 个），进行 $N$ 轮游戏。每轮游戏随机选择一个小孩开始，他/她在纸条上写下自己的性别（`B` 或 `G`），然后选择一个方向（顺时针或逆时针）将纸条传递给邻居。接到纸条的小孩同样写下性别并沿相同方向传递，直到某个小孩决定结束这一轮。

我们得到 $N$ 个由 `B` 和 `G` 组成的字符串，需要根据这些字符串推断**最少有多少个小孩**。

## 算法思路

### 问题抽象

将每个小孩视为环上的一个节点，性别用 `B` 或 `G` 表示。我们需要找到一个最短的环，使得每个给定的字符串都是环上某段连续弧的子串（可以是正序或逆序）。

这相当于**带方向的最短公共超环问题**。

### 关键步骤

1. **预处理与去重**
   - 为每个字符串生成反转版本
   - 按长度降序排序
   - 移除被其他字符串（或其反转）包含的字符串

2. **重叠计算**
   - 对于每对字符串（考虑正序和逆序），计算最大重叠长度
   - 重叠长度定义为：字符串 $A$ 的结尾与字符串 $B$ 的开头能匹配的最大字符数

3. **状态压缩动态规划**
   - 状态：$dp[mask][last][dir]$ 表示已使用字符串集合 $mask$，最后一个字符串为 $last$，方向为 $dir$ 时的最小长度
   - 转移：添加新字符串时，利用预处理的重叠减少总长度

4. **环闭合处理**
   - 找到完整路径后，减去最后一个字符串与第一个字符串的重叠
   - 确保结果至少为 $2$

### 复杂度分析

- **时间复杂度**：$O(2^N \times N^2 \times 4)$，其中 $N \leq 16$
- **空间复杂度**：$O(2^N \times N \times 2)$

## 代码实现

```cpp
// Fun Game
// UVa ID: 1204
// Verdict: Accepted
// Submission Date: 2025-10-10
// UVa Run Time: 0.200s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int kMaxLength = 105;
const int kMaxStrings = 18;

char originalStrings[kMaxStrings][kMaxLength];
char reversedStrings[kMaxStrings][kMaxLength];
int overlap[kMaxStrings][2][kMaxStrings][2];
int dpState[1 << kMaxStrings][kMaxStrings][2];
int sortedIndices[kMaxStrings];
int stringLengths[kMaxStrings];
int stringCount, uniqueCount;

// 按字符串长度降序排序
bool compareByLength(int idx1, int idx2) {
    return stringLengths[idx1] > stringLengths[idx2];
}

// 检查当前字符串是否被已选字符串包含
bool isContained(int currentIdx) {
    for (int i = 0; i < uniqueCount; ++i) {
        int existingIdx = sortedIndices[i];
        int maxOffset = stringLengths[existingIdx] - stringLengths[currentIdx];
        
        for (int offset = maxOffset; offset >= 0; --offset) {
            if (!strncmp(originalStrings[currentIdx], originalStrings[existingIdx] + offset, stringLengths[currentIdx]) ||
                !strncmp(originalStrings[currentIdx], reversedStrings[existingIdx] + offset, stringLengths[currentIdx])) {
                return true;
            }
        }
    }
    return false;
}

// 计算两个字符串的最大重叠长度
int calculateOverlap(int str1, int dir1, int str2, int dir2) {
    const char* string1 = (dir1 == 0) ? originalStrings[str1] : reversedStrings[str1];
    const char* string2 = (dir2 == 0) ? originalStrings[str2] : reversedStrings[str2];
    
    for (int k = stringLengths[str2] - 1; k > 0; --k) {
        if (!strncmp(string1 + stringLengths[str1] - k, string2, k)) {
            return k;
        }
    }
    return 0;
}

void solveTestCase() {
    // 读入并预处理字符串
    for (int i = 0; i < stringCount; ++i) {
        cin >> originalStrings[i];
        stringLengths[i] = strlen(originalStrings[i]);
        sortedIndices[i] = i;
        
        // 生成反转字符串
        for (int j = stringLengths[i] - 1, k = 0; j >= 0; --j, ++k) {
            reversedStrings[i][k] = originalStrings[i][j];
        }
    }
    
    // 按长度降序排序
    sort(sortedIndices, sortedIndices + stringCount, compareByLength);
    
    // 去重：移除被包含的字符串
    uniqueCount = 0;
    for (int i = 0; i < stringCount; ++i) {
        if (!isContained(sortedIndices[i])) {
            sortedIndices[uniqueCount++] = sortedIndices[i];
        }
    }
    
    // 预处理所有字符串对之间的重叠长度
    for (int i = 0; i < uniqueCount; ++i) {
        for (int j = 0; j < uniqueCount; ++j) {
            for (int dir1 = 0; dir1 < 2; ++dir1) {
                for (int dir2 = 0; dir2 < 2; ++dir2) {
                    overlap[i][dir1][j][dir2] = calculateOverlap(
                        sortedIndices[i], dir1, sortedIndices[j], dir2);
                }
            }
        }
    }
    
    int totalMask = (1 << uniqueCount) - 1;
    memset(dpState, 0, sizeof(dpState));
    
    // 初始状态：只包含第一个字符串
    dpState[1 << 0][0][0] = stringLengths[sortedIndices[0]];
    
    // 状态压缩动态规划
    for (int mask = 1; mask <= totalMask; ++mask) {
        for (int lastStr = 0; lastStr < uniqueCount; ++lastStr) {
            if (!(mask & (1 << lastStr))) continue;
            
            for (int lastDir = 0; lastDir < 2; ++lastDir) {
                if (!dpState[mask][lastStr][lastDir]) continue;
                
                for (int nextStr = 0; nextStr < uniqueCount; ++nextStr) {
                    if (mask & (1 << nextStr)) continue;
                    
                    for (int nextDir = 0; nextDir < 2; ++nextDir) {
                        int currentLength = dpState[mask][lastStr][lastDir];
                        int nextLength = stringLengths[sortedIndices[nextStr]];
                        int overlapLength = overlap[lastStr][lastDir][nextStr][nextDir];
                        
                        int newLength = currentLength + nextLength - overlapLength;
                        int newMask = mask | (1 << nextStr);
                        
                        if (!dpState[newMask][nextStr][nextDir] || 
                            newLength < dpState[newMask][nextStr][nextDir]) {
                            dpState[newMask][nextStr][nextDir] = newLength;
                        }
                    }
                }
            }
        }
    }
    
    // 寻找最短环
    int minCircleLength = kMaxLength * kMaxStrings;
    for (int lastStr = 0; lastStr < uniqueCount; ++lastStr) {
        for (int lastDir = 0; lastDir < 2; ++lastDir) {
            if (dpState[totalMask][lastStr][lastDir]) {
                int finalOverlap = overlap[lastStr][lastDir][0][0];
                int circleLength = dpState[totalMask][lastStr][lastDir] - finalOverlap;
                minCircleLength = min(minCircleLength, circleLength);
            }
        }
    }
    
    cout << max(minCircleLength, 2) << endl;
}

int main() {
    while (cin >> stringCount && stringCount) {
        solveTestCase();
    }
    return 0;
}
```

## 总结

本题通过字符串去重、重叠计算和状态压缩动态规划，高效解决了最短公共超环问题。算法充分利用了 $N \leq 16$ 的条件，在合理时间内找到最优解。关键思路是将问题转化为带方向的哈密顿环问题，并利用字符串的特殊性质进行优化。
