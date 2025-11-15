// The Hendrie Sequence
// UVa ID: 10479
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 使用128位整数处理大数，避免溢出
typedef __int128_t BigInt;

/**
 * 打印BigInt类型的数字
 * @param n 要打印的大整数
 */
void printBigInt(BigInt n) {
    if (n == 0) { 
        cout << "0"; 
        return; 
    }
    if (n < 0) { 
        cout << "-"; 
        n = -n; 
    }
    string s;
    while (n) { 
        s += '0' + (n % 10); 
        n /= 10; 
    }
    reverse(s.begin(), s.end());
    cout << s;
}

/**
 * 求解Hendrie序列的第n个元素
 * @param n 位置索引（从1开始）
 * @return 序列的第n个元素值
 */
BigInt solveHendrie(BigInt n) {
    // 基础情况：第一个元素是0
    if (n == 1) return 0;
    
    // 去掉第一个元素0，在剩余序列中定位
    n--;
    
    // 找到n所在的块
    BigInt blockStart = 1;    // 当前块的起始位置
    BigInt blockIndex = 1;    // 当前块的索引
    BigInt blockSize = 1;     // 当前块的大小
    
    // 定位n所在的块
    while (blockStart + blockSize <= n) {
        blockStart += blockSize;
        blockIndex++;
        blockSize *= 2;
    }
    
    // n在当前块中的位置（从1开始）
    BigInt posInBlock = n - blockStart + 1;
    
    // 在块内递归定位
    while (blockIndex > 1) {
        BigInt currentPos = 0;  // 当前在块内的位置
        
        // 处理子块内容：第i块的内容出现(blockIndex-1-i)次
        for (BigInt i = blockIndex - 2; i >= 1; i--) {
            BigInt copies = blockIndex - 1 - i;           // 重复次数
            BigInt subBlockSize = BigInt(1) << (i - 1);   // 子块大小 = 2^(i-1)
            BigInt segmentSize = subBlockSize * copies;   // 该段的总大小
            
            // 如果n在当前段内
            if (posInBlock <= currentPos + segmentSize) {
                BigInt offset = posInBlock - currentPos;  // 在段内的偏移量
                // 计算在子块内的位置
                posInBlock = (offset - 1) % subBlockSize + 1;
                blockIndex = i;      // 递归到子块
                currentPos = 0;      // 重置当前位置
                continue;            // 重新开始循环
            }
            currentPos += segmentSize;
        }
        
        // 处理额外的0：有(blockIndex-1)个0
        if (posInBlock <= currentPos + (blockIndex - 1)) {
            return 0;
        }
        
        // 最后一个是blockIndex
        return blockIndex;
    }
    
    // 第一块只有一个元素1
    return 1;
}

int main() {
    string input;
    
    // 处理多个测试用例，直到输入0为止
    while (cin >> input && input != "0") {
        // 将字符串转换为BigInt
        BigInt n = 0;
        for (char c : input) {
            n = n * 10 + (c - '0');
        }
        
        // 计算并输出结果
        printBigInt(solveHendrie(n));
        cout << "\n";
    }
    
    return 0;
}
