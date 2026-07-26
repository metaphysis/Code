// The Maximum Term
// UVa ID: 10836
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.200s
// https://blog.csdn.net/metaphysis/article/details/163173845

#include <bits/stdc++.h>
using namespace std;

// 全局常量与数组
const int MAXN = 300;
const int MAXP = 70;          // 300 以内的质数个数不超过 62

int primeIdx[MAXN + 1];       // 数值到质数下标的映射
vector<int> primes;           // 质数列表
int factorExp[MAXN + 1][MAXP]; // factorExp[x][p] = x 中质数 p 的指数
int factExp[MAXN + 1][MAXP];  // factExp[n][p] = n! 中质数 p 的指数
double logFact[MAXN + 1];     // logFact[n] = ln(n!)
double logPrimes[MAXP];       // 每个质数的自然对数

// 预处理：筛素数、分解质因数、计算阶乘质因数指数、对数表
void init() {
    // 筛法求 300 以内素数
    bool comp[MAXN + 1] = {false};
    for (int i = 2; i <= MAXN; ++i) {
        if (!comp[i]) {
            primes.push_back(i);
            if ((long long)i * i <= MAXN) {
                for (int j = i * i; j <= MAXN; j += i)
                    comp[j] = true;
            }
        }
    }
    // 建立数值到下标映射
    for (int idx = 0; idx < (int)primes.size(); ++idx)
        primeIdx[primes[idx]] = idx;

    // 分解 1..300 每个数的质因数
    for (int num = 1; num <= MAXN; ++num) {
        int tmp = num;
        for (int p : primes) {
            int cnt = 0;
            while (tmp % p == 0) {
                tmp /= p;
                ++cnt;
            }
            factorExp[num][primeIdx[p]] = cnt;
        }
    }

    // 阶乘的质因数指数
    for (int p : primes) factExp[0][primeIdx[p]] = 0;
    for (int n = 1; n <= MAXN; ++n) {
        for (int p : primes) {
            int id = primeIdx[p];
            factExp[n][id] = factExp[n - 1][id] + factorExp[n][id];
        }
    }

    // 对数表
    logFact[0] = 0.0;
    for (int n = 1; n <= MAXN; ++n)
        logFact[n] = logFact[n - 1] + log((double)n);

    // 质数的对数
    for (int idx = 0; idx < (int)primes.size(); ++idx)
        logPrimes[idx] = log((double)primes[idx]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int n, w, x, y, z;
    while (cin >> n >> w >> x >> y >> z) {
        if (n == 0 && w == 0 && x == 0 && y == 0 && z == 0)
            break;

        // 各变量的对数
        double logW = log((double)w);
        double logX = log((double)x);
        double logY = log((double)y);
        double logZ = log((double)z);

        double bestLog = -1e100;
        int bestI = 0, bestJ = 0, bestK = 0, bestL = 0;

        // 枚举 i 和 j，对每个 (i,j) 在 k 的连续最优附近检查
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n - i; ++j) {
                int s = n - i - j;          // 剩余可分配给 k 和 l
                // 连续最优值：k ≈ s * y / (y + z)
                double k0 = (double)s * y / (y + z);
                int start = max(0, (int)floor(k0) - 8);
                int end   = min(s, (int)floor(k0) + 8);
                for (int k = start; k <= end; ++k) {
                    int l = s - k;
                    double val = logFact[n]
                               - logFact[i] - logFact[j] - logFact[k] - logFact[l]
                               + i * logW + j * logX + k * logY + l * logZ;
                    if (val > bestLog) {
                        bestLog = val;
                        bestI = i; bestJ = j; bestK = k; bestL = l;
                    }
                }
            }
        }

        int i = bestI, j = bestJ, k = bestK, l = bestL; // 用实际变量名简化

        // 计算该组合的质因数指数
        int expArr[MAXP] = {0};
        int primeCnt = (int)primes.size();
        for (int idx = 0; idx < primeCnt; ++idx) {
            int p = primes[idx];
            int id = primeIdx[p];
            expArr[idx] = factExp[n][id]
                        - factExp[i][id] - factExp[j][id] - factExp[k][id] - factExp[l][id]
                        + i * factorExp[w][id] + j * factorExp[x][id]
                        + k * factorExp[y][id] + l * factorExp[z][id];
        }

        // 去掉末尾的 0：即减去 min(exp2, exp5) 对 (2,5)
        int id2 = primeIdx[2];
        int id5 = primeIdx[5];
        int t = min(expArr[id2], expArr[id5]);
        expArr[id2] -= t;
        expArr[id5] -= t;

        // 计算去掉末尾 0 后的数值（若小于 10^7 则精确，否则只保留模 10^8）
        long long exactVal = 1;      // 仅当数值 < 10^7 时有效
        long long modVal = 1;        // 模 10^8 的值
        bool big = false;            // 标记数值是否 >= 10^7

        for (int idx = 0; idx < primeCnt; ++idx) {
            int p = primes[idx];
            int e = expArr[idx];
            while (e--) {
                modVal = (modVal * p) % 100000000LL;
                if (!big) {
                    exactVal *= p;
                    if (exactVal >= 10000000LL)   // 10^7 为 8 位数的下界
                        big = true;
                }
            }
        }
        // 输出
        if (!big) cout << exactVal << '\n';
        else {
            int last8 = (int)(modVal % 100000000LL);
            cout << setw(8) << setfill('0') << last8 << '\n';
        }
    }
    return 0;
}
