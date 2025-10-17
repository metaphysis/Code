
// Huge Mod
// UVa ID: 10692
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
using namespace std;

// 计算欧拉函数 phi(n)
int phi(int n) {
    int result = n;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// 递归计算指数塔模 m 的值
// 返回 pair(计算结果, 是否 >= mod)
pair<int, bool> tower(const vector<int>& a, int idx, int mod) {
    // 模数为1时，任何数模1都是0，且指数>=1
    if (mod == 1) return make_pair(0, true);
    
    // 基准情况：最后一个数
    if (idx == a.size() - 1) {
        if (a[idx] >= mod) return make_pair(a[idx] % mod, true);
        else return make_pair(a[idx] % mod, false);
    }
    
    // 递归计算指数部分
    int p = phi(mod);
    pair<int, bool> next = tower(a, idx + 1, p);
    int exp_val = next.first;
    bool exp_ge = next.second;
    
    // 如果指数 >= phi(mod)，加上 phi(mod)
    if (exp_ge) exp_val += p;
    
    // 使用快速幂计算 a[idx]^exp_val % mod
    long long result = 1;
    long long base = a[idx];
    long long exp = exp_val;
    bool ge_flag = false;
    
    // 快速幂算法
    while (exp > 0) {
        if (exp & 1) {
            result = result * base;
            if (result >= mod) {
                result %= mod;
                ge_flag = true;
            }
        }
        base = base * base;
        if (base >= mod) {
            base %= mod;
            ge_flag = true;
        }
        exp >>= 1;
    }
    
    // 特殊情况：底数 >= mod 且指数 > 0，则结果 >= mod
    if (!ge_flag && a[idx] >= mod && exp_val > 0) {
        ge_flag = true;
    }
    
    return make_pair(result, ge_flag);
}

int main() {
    string line;
    int case_num = 1;
    
    while (true) {
        getline(cin, line);
        if (line == "#") break;
        
        int m, n;
        vector<int> a;
        
        // 使用 stringstream 解析输入
        stringstream ss(line);
        ss >> m >> n;
        for (int i = 0; i < n; i++) {
            int x;
            ss >> x;
            a.push_back(x);
        }
        
        // 计算并输出结果
        pair<int, bool> res = tower(a, 0, m);
        cout << "Case #" << case_num << ": " << res.first << endl;
        case_num++;
    }
    
    return 0;
}
