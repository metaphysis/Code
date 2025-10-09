// Integer Transmission
// UVa ID: 1228
// Verdict: Accepted
// Submission Date: 2025-10-09
// UVa Run Time: 0.090s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 66;

// 全局变量定义
int zeroPositions[MAX_N];    // 存储所有0比特的传输位置（时间）
int onePositions[MAX_N];     // 存储所有1比特的传输位置（时间）
int zeroCount;               // 0比特的总数量
int oneCount;                // 1比特的总数量
int bitLength;               // 总比特数n
int maxDelay;                // 最大延迟d
unsigned long long originalValue; // 原始传输的整数k
long long dp[MAX_N][MAX_N];  // DP数组，dp[i][j]表示放置i个0和j个1的方案数

/**
 * 初始化函数
 * 重置DP数组并将初始状态设为1
 * 注意：zeroCount和oneCount从1开始，这是为了处理数组索引的边界条件
 */
void initialize() {
    memset(dp, 0, sizeof(dp));  // 清空DP数组
    dp[0][0] = 1;               // 初始状态：没有放置任何比特时有一种方案
    zeroCount = oneCount = 1;   // 从1开始计数，0索引位置留空作为边界
}

/**
 * 计算整数的有效二进制位数（不包括前导0）
 * @param value 要计算的整数
 * @return 有效二进制位数
 * 例如：5（二进制101）返回3，0返回0
 */
int calculateBitCount(unsigned long long value) {
    return value > 0 ? calculateBitCount(value >> 1) + 1 : 0;
}

/**
 * 分析原始整数的二进制表示，记录每个0和1的传输位置
 * 位置从1开始编号，表示传输的时间顺序
 * 例如：3位整数5（二进制101）：
 *   - 没有前导0
 *   - 第1位(最高位)：1，位置1
 *   - 第2位：0，位置2  
 *   - 第3位：1，位置3
 */
void analyzeBitPositions() {
    int effectiveBits = calculateBitCount(originalValue);  // 计算有效位数
    int currentPosition = 1;  // 当前位置计数器，从1开始
    
    // 处理前导零：对于位数不足n的情况，高位自动补0
    for (int i = 0; i < bitLength - effectiveBits; i++) {
        zeroPositions[zeroCount] = currentPosition++;  // 记录前导0的位置
        zeroCount++;  // 0计数器递增
    }
    
    // 从高位到低位处理每一位有效比特
    // 注意：我们是从二进制表示的最高位开始处理
    for (int i = effectiveBits - 1; i >= 0; i--) {
        // 检查第i位是否为1（从最高位开始）
        if (originalValue & ((long long)1 << i)) {
            // 当前位是1，记录到1的位置数组中
            onePositions[oneCount] = currentPosition++;
            oneCount++;
        } else {
            // 当前位是0，记录到0的位置数组中
            zeroPositions[zeroCount] = currentPosition++;
            zeroCount++;
        }
    }
}

/**
 * 使用动态规划计算可能的不同接收整数的数量
 * 核心思想：考虑网络延迟导致的比特顺序重排可能性
 * 状态转移条件：如果某个比特的最晚到达时间 >= 另一个比特的最早到达时间，则可以交换顺序
 * @return 可能的不同整数的数量
 */
long long countPossibleValues() {
    // 遍历所有可能的0和1的放置组合
    for (int zeroIndex = 0; zeroIndex < zeroCount; zeroIndex++) {
        for (int oneIndex = 0; oneIndex < oneCount; oneIndex++) {
            // 如果可以放置下一个0：检查延迟条件是否允许
            // 条件：下一个0的最晚到达时间 >= 当前1的最早到达时间
            if (zeroIndex + 1 < zeroCount && 
                zeroPositions[zeroIndex + 1] + maxDelay >= onePositions[oneIndex]) {
                dp[zeroIndex + 1][oneIndex] += dp[zeroIndex][oneIndex];
            }
            
            // 如果可以放置下一个1：检查延迟条件是否允许
            // 条件：下一个1的最晚到达时间 >= 当前0的最早到达时间
            if (oneIndex + 1 < oneCount && 
                onePositions[oneIndex + 1] + maxDelay >= zeroPositions[zeroIndex]) {
                dp[zeroIndex][oneIndex + 1] += dp[zeroIndex][oneIndex];
            }
        }
    }
    
    // 返回最终状态：所有0和1都放置完毕的方案数
    return dp[zeroCount - 1][oneCount - 1];
}

/**
 * 构造可能的最小值或最大值
 * 通过贪心策略在高位优先放置0（最小值）或1（最大值）
 * @param priorityArray 优先考虑的比特类型数组（构造最小值时是0，最大值时是1）
 * @param secondaryArray 次要考虑的比特类型数组
 * @param bitValue 当前处理的比特值（0或1）
 * @param priorityCount 优先数组的元素数量
 * @return 构造出的整数值
 */
unsigned long long constructValue(int* priorityArray, int* secondaryArray, 
                                 int bitValue, int priorityCount) {
    unsigned long long result = 0;  // 最终结果
    int priorityIndex = 1;          // 优先数组的索引（从1开始）
    int secondaryIndex = 1;         // 次要数组的索引（从1开始）
    
    // 从高位到低位依次构造每一位
    for (int bitIndex = 0; bitIndex < bitLength; bitIndex++) {
        result <<= 1;  // 左移一位，为新的比特腾出空间
        
        // 情况1：优先数组已经用完，只能使用次要数组的比特
        if (priorityIndex == priorityCount) {
            result += bitValue ^ 1;  // 使用相反的比特值（次要数组的类型）
            secondaryIndex++;
            continue;
        } 
        // 情况2：次要数组已经用完，只能使用优先数组的比特
        else if (secondaryIndex == bitLength - priorityCount + 2) {
            result += bitValue;  // 使用优先数组的比特值
            priorityIndex++;
            continue;
        }
        
        // 情况3：根据网络延迟条件决定使用哪个比特
        // 如果次要比特的延迟条件允许（最晚到达时间 >= 优先比特的最早到达时间）
        // 就使用优先比特，否则使用次要比特
        if (secondaryArray[secondaryIndex] + maxDelay >= priorityArray[priorityIndex]) {
            result += bitValue;      // 放置优先比特
            priorityIndex++;
        } else {
            result += bitValue ^ 1;  // 放置次要比特
            secondaryIndex++;
        }
    }
    return result;
}

/**
 * 主函数：处理多个测试用例
 * 输入格式：每组数据包含n, d, k，以n=0结束
 * 输出格式：Case i: 数量 最小值 最大值
 */
int main(int argc, char* argv[]) {
    int caseNumber = 1;  // 测试用例编号
    
    // 循环处理所有测试用例，直到遇到n=0
    while (cin >> bitLength && bitLength) {
        cin >> maxDelay >> originalValue;
        
        // 初始化变量和DP数组
        initialize();
        // 分析比特位置
        analyzeBitPositions();
        // 计算可能的整数数量
        long long possibleCount = countPossibleValues();
        // 构造最小值：优先放置0
        unsigned long long minValue = constructValue(zeroPositions, onePositions, 0, zeroCount);
        // 构造最大值：优先放置1
        unsigned long long maxValue = constructValue(onePositions, zeroPositions, 1, oneCount);
        
        // 输出结果
        printf("Case %d: %lld %llu %llu\n", caseNumber++, possibleCount, minValue, maxValue);
    }
    
    return 0;
}
