// Dyslexic Gollum
// UVa ID: 1633
// Verdict: Accepted
// Submission Date: 2025-12-09
// UVa Run Time: 0.310s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;          // 模数
const int MAX_N = 405;               // 最大长度
const int MAX_K = 11;                // 最大K+1，用于状态表示

int dp[MAX_N][1 << MAX_K];           // dp数组
bool palK[1 << MAX_K];               // 标记长度为K的回文
bool palK1[1 << MAX_K];              // 标记长度为K+1的回文

// 检查一个二进制数的低len位是否是回文
bool checkPalindrome(int mask, int len) {
    for (int i = 0; i < len / 2; i++) {
        int left = (mask >> i) & 1;              // 第i位
        int right = (mask >> (len - 1 - i)) & 1; // 对称位置
        if (left != right) return false;
    }
    return true;
}

// 主计算函数
int solve(int N, int K) {
    // 特殊情况处理
    if (K == 1) return 0;  // 单个字符就是回文，无解
    if (K > N) {           // 不可能有长度>=K的回文
        long long ans = 1;
        for (int i = 0; i < N; i++) ans = (ans * 2) % MOD;
        return ans;
    }
    
    // 预处理回文标记
    int maxMaskK = 1 << K;         // K位状态总数
    int maxMaskK1 = 1 << (K + 1);  // K+1位状态总数
    
    // 标记所有长度为K的回文
    for (int mask = 0; mask < maxMaskK; mask++)
        palK[mask] = checkPalindrome(mask, K);
    
    // 标记所有长度为K+1的回文
    for (int mask = 0; mask < maxMaskK1; mask++)
        palK1[mask] = checkPalindrome(mask, K + 1);
    
    // 初始化dp数组
    for (int i = 0; i <= N; i++)
        for (int mask = 0; mask < maxMaskK1; mask++)
            dp[i][mask] = 0;
    
    // 初始状态：长度为1的字符串
    dp[1][0] = 1;  // 以0结尾
    dp[1][1] = 1;  // 以1结尾
    
    // 动态规划转移
    for (int i = 1; i < N; i++) {
        for (int mask = 0; mask < maxMaskK1; mask++) {
            if (dp[i][mask] == 0) continue;  // 无效状态
            
            // 尝试添加0或1
            for (int bit = 0; bit <= 1; bit++) {
                // 计算新状态：左移一位，去掉最高位，添加新位
                int newMask = ((mask << 1) & ((1 << (K + 1)) - 1)) | bit;
                
                bool valid = true;
                
                // 检查是否形成长度为K的回文
                if (i + 1 >= K) {
                    int lastK = newMask & ((1 << K) - 1);  // 取低K位
                    if (palK[lastK]) {
                        valid = false;
                    }
                }
                
                // 检查是否形成长度为K+1的回文
                if (i + 1 >= K + 1) {
                    if (palK1[newMask]) {
                        valid = false;
                    }
                }
                
                // 如果有效，更新dp值
                if (valid) {
                    dp[i + 1][newMask] = (dp[i + 1][newMask] + dp[i][mask]) % MOD;
                }
            }
        }
    }
    
    // 计算结果：所有长度为N的状态之和
    int result = 0;
    for (int mask = 0; mask < maxMaskK1; mask++)
        result = (dp[N][mask] + result) % MOD;
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        int N, K;
        cin >> N >> K;
        cout << solve(N, K) << "\n";
    }
    
    return 0;
}
