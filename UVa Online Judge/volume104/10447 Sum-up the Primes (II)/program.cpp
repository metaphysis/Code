// Sum-up the Primes (II)
// UVa ID: 10447
// Verdict: Accepted
// Submission Date: 2025-10-14
// UVa Run Time: 0.290s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 素数数组，按字符串字典序排序，便于输出字典序最小的解
int primes[] = {
    101, 103, 107, 109, 11, 113, 127, 13, 131, 137, 139, 149, 
    151, 157, 163, 167, 17, 173, 179, 181, 19, 191, 193, 197, 
    199, 2, 211, 223, 227, 229, 23, 233, 239, 241, 251, 257, 
    263, 269, 271, 277, 281, 283, 29, 293, 3, 31, 37, 41, 43, 
    47, 5, 53, 59, 61, 67, 7, 71, 73, 79, 83, 89, 97
};

// 输入频率限制对应的素数顺序（61 个奇数素数）
int primeOrder[] = {
    3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 
    59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 
    113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 
    181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 
    251, 257, 263, 269, 271, 277, 281, 283, 293
};

int frequencyLimit[62];    // 每个素数的使用频率限制
int usageCount[62];        // 记录每个素数当前已使用的次数
int solution[14];          // 存储当前找到的解
int primeTwoIndex;         // 素数 2 在 primes 数组中的索引位置
int targetSum;             // 目标和 N
int primeCount;            // 需要使用的素数个数 t

// 深度优先搜索寻找解
bool dfs(int depth, int remainingSum, int startIndex) {
    // 已选择足够数量的素数
    if (depth == primeCount) {
        if (remainingSum == 0) {
            // 输出找到的解
            cout << solution[0];
            for (int i = 1; i < depth; i++) {
                cout << "+" << solution[i];
            }
            cout << "\n";
            return true;
        }
        return false;
    }
    // 关键剪枝：如果不能使用素数 2，检查剩余和的奇偶性是否与剩余素数个数的奇偶性匹配
    // 因为奇数个奇素数的和为奇数，偶数个奇素数的和为偶数
    if (frequencyLimit[primeTwoIndex] == 0 && (primeCount - depth) % 2 != remainingSum % 2) return false;
    // 遍历所有可用的素数
    for (int primeIndex = startIndex; primeIndex < 62; primeIndex++) {
        // 检查当前素数是否超过使用频率限制
        if (usageCount[primeIndex] >= frequencyLimit[primeIndex]) continue;
        int currentPrime = primes[primeIndex];
        // 特殊处理素数 2
        if (currentPrime == 2) {
            // 如果使用 2 会导致奇偶性矛盾，跳过
            if (remainingSum % 2 == (primeCount - depth) % 2) continue;
            // 必须使用 2 的情况
            solution[depth] = 2;
            usageCount[primeIndex]++;
            if (remainingSum >= 2 && dfs(depth + 1, remainingSum - 2, primeIndex + 1)) return true;
            usageCount[primeIndex]--;
            return false; // 2 是唯一选择，如果失败则直接返回
        }
        // 处理普通奇数素数
        solution[depth] = currentPrime;
        usageCount[primeIndex]++;
        if (remainingSum - currentPrime >= 0 && dfs(depth + 1, remainingSum - currentPrime, primeIndex)) return true;
        usageCount[primeIndex]--;
    }
    return false;
}

int main(int argc, char* argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int blockCount;     // 数据块数量 B
    int queryCount;     // 每个块的查询数量 Q
    cin >> blockCount;
    for (int currentBlock = 1; currentBlock <= blockCount; currentBlock++) {
        cout << "Block " << currentBlock << ":\n";
        // 读取61个奇数素数的频率限制
        for (int i = 0; i < 61; i++) {
            // 找到素数 p[i] 在 primes 数组中的位置 k
            int k = find(primes, primes + 62, primeOrder[i]) - primes;
            cin >> frequencyLimit[k];
        }
        // 找到素数 2 在 primes 数组中的位置
        for (primeTwoIndex = 0; primes[primeTwoIndex] != 2; primeTwoIndex++);
        cin >> queryCount;
        for (int currentQuery = 1; currentQuery <= queryCount; currentQuery++) {
            cout << "Query " << currentQuery << ":\n";
            // 读取查询参数：目标和N，素数个数 t，是否能使用 2
            cin >> targetSum >> primeCount >> frequencyLimit[primeTwoIndex];
            // 重置使用计数
            memset(usageCount, 0, sizeof(usageCount));
            // 搜索解
            if (!dfs(0, targetSum, 0)) cout << "No Solution.\n";
        }
        cout << "\n";
    }
    return 0;
}
