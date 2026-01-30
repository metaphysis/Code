// Euler‘s Totient Function
// UVa ID: 11073
// Verdict: Accepted
// Submission Date: 2026-01-18
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 位运算宏定义，用于高效质数筛
#define GET(x) (M[(x) >> 5] & (1 << ((x) & 0x1F)))
#define SET(x) (M[(x) >> 5] |= (1 << ((x) & 0x1F)))

const int MAXN = 100010;  // 质数筛范围
int primes[MAXN >> 3], cnt, M[MAXN >> 5] = {3};  // 位数组存储质数信息

// 线性筛法，预处理所有质数
void sieve() {
    for (int i = 2; i < MAXN; i++) {
        if (!GET(i)) primes[cnt++] = i;  // i是质数
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++) {
            SET(i * primes[j]);  // 标记合数
            if (i % primes[j] == 0) break;  // 保证每个数只被最小质因子标记
        }
    }
}

// 判断一个数是否为质数
bool isPrime(ll n) {
    if (n < 2) return false;
    if (n <= primes[cnt - 1]) return binary_search(primes, primes + cnt, n);
    // 使用预计算的质数表进行试除
    for (int p : primes) {
        if ((ll)p * p > n) break;
        if (n % p == 0) return false;
    }
    return true;
}

const int MAXX = 100000000;  // x的最大值
vector<ll> answers;  // 存储所有解

// 深度优先搜索函数
void dfs(ll x, ll n, int idx) {
    if (x == 1) {
        answers.push_back(n);  // 找到解
        if (n % 2 == 1) answers.push_back(n * 2);  // n为奇数时，2n也是解
        return;
    }
    // 如果x+1是质数且大于之前考虑的所有质数
    if (isPrime(x + 1) && (x + 1) > (idx ? primes[idx - 1] : 1))
        answers.push_back(n * (x + 1));
    
    // 枚举可能的质因子
    for (int i = idx; i < cnt; i++) {
        int p = primes[i];
        if (1LL * (p - 1) * (p - 1) > x) break;  // 剪枝
        
        if (x % (p - 1) == 0) {
            ll r = x / (p - 1), m = n * p;
            dfs(r, m, i + 1);  // 处理p^1的情况
            
            // 处理p^k (k>=2)的情况
            while (r % p == 0) {
                r /= p, m *= p;
                dfs(r, m, i + 1);
            }
        }
    }
}

// 主求解函数
void solve(ll x) {
    answers.clear();
    dfs(x, 1, 0);
    // 排序和去重
    sort(answers.begin(), answers.end());
    answers.erase(unique(answers.begin(), answers.end()), answers.end());
}

int main() {
    sieve();  // 预处理质数表
    
    ll x;
    while (cin >> x) {
        solve(x);
        if (answers.empty()) 
            cout << "No solution.\n";
        else {
            for (size_t i = 0; i < answers.size(); i++) {
                if (i) cout << ' ';
                cout << answers[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
