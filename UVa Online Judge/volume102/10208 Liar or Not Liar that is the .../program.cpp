// Liar or Not Liar that is the ...
// UVa ID: 10208
// Verdict: Accepted
// Submission Date: 2025-12-16
// UVa Run Time: 0.500s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 位运算宏定义，用于质数筛的位标记
#define GET(x) (B[x >> 5] & (1 << (x & 0x1F)))
#define SET(x) (B[x >> 5] |= (1 << (x & 0x1F)))

const int MAXN = 7000000, MAXB = 10000010;

int B[MAXB >> 5];           // 位数组，用于筛法
int primes[MAXN], cnt = 0;  // 存储所有质数
vector<int> primes4k3;      // 只存储4k+3形式的质数

// 线性筛法
void sieve() {
    for (int i = 2; i < MAXB; i++) {
        if (!GET(i)) {
            primes[cnt++] = i;
            if (i % 4 == 3) primes4k3.push_back(i);  // 记录4k+3质数
        }
        for (int j = 0; j < cnt && i * primes[j] < MAXB; j++) {
            SET(i * primes[j]);
            if (i % primes[j] == 0) break;
        }
    }
}

// 判断质数p在n!中的指数是否为奇数
inline bool isExponentOdd(int n, int p) {
    int exp = 0;
    while (n) { 
        n /= p; 
        exp += n; 
    }
    return (exp & 1);
}

// 判断整数n是否可以表示为两个整数的平方和
inline bool isSquares(int n) {
    for (auto p : primes4k3) {
        int cnt = 0;
        while (n % p == 0) {
            n /= p;
            cnt++;
        }
        if (cnt & 1) return false;  // 4k+3质因子指数为奇数
    }
    return true;
}

int main() {
    cin.tie(0); 
    cout.tie(0); 
    ios::sync_with_stdio(false);
    
    sieve();  // 预处理质数表
    
    string line;
    bool firstCase = true;
    
    while (cin >> line) {
        if (!firstCase) cout << '\n';
        firstCase = false;
        
        bool isFactorial = (line.back() == '!');
        int N;
        if (isFactorial) 
            N = stoi(line.substr(0, line.size() - 1));
        else 
            N = stoi(line);
        
        if (!isFactorial) {
            // 普通整数情况
            cout << (isSquares(N) ? "He might be honest.\n" : "He is a liar.\n");
        } else {
            // 阶乘情况
            vector<int> neededPrimes;
            for (auto p : primes4k3) {
                if (p > N) break;
                // 如果p在N!中的指数为奇数，则需要除去
                if (isExponentOdd(N, p) && neededPrimes.size() < 50) 
                    neededPrimes.push_back(p);
                if (neededPrimes.size() >= 50) break;  // 最多输出50个
            }
            
            if (neededPrimes.empty()) {
                cout << "He might be honest.\n";
            } else {
                cout << "He is a liar.\n";
                for (size_t i = 0; i < neededPrimes.size(); i++) {
                    if (i > 0) cout << ' ';
                    cout << neededPrimes[i];
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
