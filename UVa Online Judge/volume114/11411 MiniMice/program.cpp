// MiniMice
// UVa ID: 11411
// Verdict: Accepted
// Submission Date: 2026-01-16
// UVa Run Time: 0.510s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

// 位运算优化素数标记
#define GET(x) (B[(x) >> 5] & (1 << ((x) & 0x1F)))
#define SET(x) (B[(x) >> 5] |= (1 << ((x) & 0x1F)))

const int MAXN = 5000010;
int factors[MAXN], least[MAXN];          // factors[i]: i的因子个数, least[i]: i的最小质因子指数
int primes[MAXN >> 3], cnt;              // 素数表，MAXN内素数约348,513个，除以8足够
int B[MAXN >> 5] = {3};                  // 位数组标记合数，初始值3表示0和1被标记

// 预处理1到MAXN-1的因子个数
void initialize() {
    factors[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        if (!GET(i)) {                   // i是素数
            primes[cnt++] = i;
            factors[i] = 2;              // 素数的因子个数为2
            least[i] = 1;                // 最小质因子指数为1
        }
        // 线性筛核心
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++) {
            int n = i * primes[j];
            SET(n);                      // 标记n为合数
            if (i % primes[j] == 0) {
                // primes[j]是i的最小质因子
                least[n] = least[i] + 1;
                factors[n] = factors[i] / (least[i] + 1) * (least[n] + 1);
                break;                   // 保证每个数只被最小质因子筛去
            } else {
                // primes[j]与i互质
                least[n] = 1;
                factors[n] = factors[i] * factors[primes[j]];
            }
        }
    }
}

// 计算区间[a,b]的最小化最大争吵值
int minMaxQuarrel(int a, int b) {
    static int tmp[MAXN];                // 静态数组避免重复分配
    int n = b - a + 1;
    // 提取区间内所有数的因子个数
    for (int i = 0; i < n; i++) tmp[i] = factors[a + i];
    sort(tmp, tmp + n);                  // 排序
    if (n <= 2) return tmp[n - 1] - tmp[0]; // 特殊情况处理
    int r = 0;
    // 检查所有相隔2的元素的差
    for (int i = 0; i + 2 < n; i++) r = max(r, tmp[i + 2] - tmp[i]);
    // 检查边界情况
    r = max(r, tmp[1] - tmp[0]);
    r = max(r, tmp[n - 1] - tmp[n - 2]);
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initialize();                        // 预处理因子个数
    int T, a, b;
    cin >> T;
    while (T--) {
        cin >> a >> b;
        cout << minMaxQuarrel(a, b) << "\n";
    }
    return 0;
}
