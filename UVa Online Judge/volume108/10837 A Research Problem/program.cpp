// A Research Problem
// UVa ID: 10837
// Verdict: Accepted
// Submission Date: 2025-11-29
// UVa Run Time: 0.420s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200000000;  // n的最大值
const int PRIME_LIMIT = 100000;  // 质数上限

vector<int> primes;
bool isPrime[PRIME_LIMIT + 5];

// 生成质数表
void generatePrimes() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= PRIME_LIMIT; i++) 
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i + i; j <= PRIME_LIMIT; j += i) 
                isPrime[j] = false;
        }
}

// 检查一个数是否为质数
bool checkPrime(long long x) {
    if (x < 2) return false;
    if (x <= PRIME_LIMIT) return isPrime[x];
    for (int p : primes) {
        if ((long long)p * p > x) break;
        if (x % p == 0) return false;
    }
    return true;
}

long long answer;  // 存储当前找到的最小n

// 深度优先搜索寻找解
// current: 当前构造的n值
// remaining: 剩余的phi值需要满足
// index: 当前考虑的质数索引
void dfs(long long current, long long remaining, int index) {
    // 如果剩余值为1，找到解
    if (remaining == 1) {
        if (current < answer) answer = current;
        return;
    }
    
    // 关键修复：检查 remaining + 1 是否为质数
    if (remaining + 1 > primes[index] && checkPrime(remaining + 1)) {
        long long candidate = current * (remaining + 1);
        if (candidate < answer && candidate <= MAX_N) 
            answer = candidate;
    }
    
    // 尝试更多的质因数
    for (int i = index; i < primes.size(); i++) {
        int p = primes[i];
        
        // 如果当前质数太大，不可能找到更小的解
        if (p - 1 > remaining) break;
        
        // 检查p-1是否能整除remaining
        if (remaining % (p - 1) != 0) continue;
        
        // 使用质数p一次
        long long newCurrent = current * p;
        long long newRemaining = remaining / (p - 1);
        
        // 剪枝：如果已经超过当前最优解
        if (newCurrent >= answer || newCurrent > MAX_N) continue;
        
        dfs(newCurrent, newRemaining, i + 1);
        
        // 尝试使用当前质数的更高次幂
        long long tempCurrent = newCurrent;
        long long tempRemaining = newRemaining;
        
        while (tempRemaining % p == 0) {
            tempRemaining /= p;
            tempCurrent *= p;
            
            if (tempCurrent >= answer || tempCurrent > MAX_N) break;
            
            dfs(tempCurrent, tempRemaining, i + 1);
        }
    }
}

// 解决单个测试用例
long long solve(long long phiValue) {
    answer = LONG_LONG_MAX;
    dfs(1, phiValue, 0);
    return answer;
}

int main() {
    generatePrimes();  // 预处理质数表
    
    long long phiValue;
    int caseNumber = 1;
    
    while (cin >> phiValue && phiValue != 0) {
        long long result = solve(phiValue);
        cout << "Case " << caseNumber << ": " << phiValue << " " << result << endl;
        caseNumber++;
    }
    
    return 0;
}
