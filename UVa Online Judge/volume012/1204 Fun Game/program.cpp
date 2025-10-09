// Fun Game
// UVa ID: 1204
// Verdict: Accepted
// Submission Date: 2025-10-09
// UVa Run Time: 0.200s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

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

