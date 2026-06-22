// Goldbach's Cardinality
// UVa ID: 12039
// Verdict: Accepted
// Submission Date: 2026-06-22
// UVa Run Time: 0.590s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000000;
vector<int> primes;
vector<int> piCnt;          // piCnt[i] = 素数个数 ≤ i
vector<char> isPrime;

// 埃氏筛
void sieve(int n) {
    isPrime.assign(n + 1, true);
    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) isPrime[j] = false;
        }
    }
    primes.clear();
    for (int i = 2; i <= n; ++i)
        if (isPrime[i]) primes.push_back(i);

    piCnt.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i)
        piCnt[i] = piCnt[i - 1] + (isPrime[i] ? 1 : 0);
}

// 计算 T(x) = sum_{m=1}^{x} GC(2m)
// 枚举所有奇素数 p (p < x)，累加 piCnt[2x-p] - piCnt[p]
long long calcT(int x) {
    if (x < 3) return 0;
    long long res = 0;
    // 从索引 1 开始，跳过 primes[0] = 2
    for (int i = 1; i < (int)primes.size() && primes[i] < x; ++i) {
        int p = primes[i];
        res += piCnt[2 * x - p] - piCnt[p];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<int, int>> queries;
    int low, high, maxHigh = 0;
    while (cin >> low >> high) {
        if (low == 0 && high == 0) break;
        queries.push_back({low, high});
        if (high > maxHigh) maxHigh = high;
    }
    if (queries.empty()) return 0;

    sieve(maxHigh);

    unordered_map<int, long long> cache;
    for (auto &q : queries) {
        int low = q.first, high = q.second;
        int L = (low + 1) / 2;   // ceil(low/2)
        int R = high / 2;

        long long sumR, sumLm1;
        auto itR = cache.find(R);
        if (itR != cache.end()) sumR = itR->second;
        else {
            sumR = calcT(R);
            cache[R] = sumR;
        }

        int left = L - 1;
        auto itL = cache.find(left);
        if (itL != cache.end()) sumLm1 = itL->second;
        else {
            sumLm1 = calcT(left);
            cache[left] = sumLm1;
        }

        cout << sumR - sumLm1 << '\n';
    }

    return 0;
}
