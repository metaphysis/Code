#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

vector<int> d;
vector<long long> fact, invFact;

long long modPow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    struct Query { int N, K; };
    vector<Query> queries(T);
    int maxN = 0, maxK = 0;
    for (int i = 0; i < T; ++i) {
        cin >> queries[i].N >> queries[i].K;
        maxN = max(maxN, queries[i].N);
        maxK = max(maxK, queries[i].K);
    }

    // 预处理每个数的真因子个数
    d.assign(maxN + 1, 0);
    for (int i = 1; i <= maxN; ++i)
        for (int j = i * 2; j <= maxN; j += i)
            ++d[j];

    // 预处理阶乘和逆元
    fact.assign(maxN + 1, 1);
    invFact.assign(maxN + 1, 1);
    for (int i = 1; i <= maxN; ++i) fact[i] = fact[i - 1] * i % MOD;
    invFact[maxN] = modPow(fact[maxN], MOD - 2);
    for (int i = maxN; i >= 1; --i) invFact[i - 1] = invFact[i] * i % MOD;

    // 按K分组查询
    vector<vector<int>> byK(maxK + 1);
    for (int idx = 0; idx < T; ++idx)
        byK[queries[idx].K].push_back(idx);

    vector<int> ansEdges(T), ansWays(T);
    vector<vector<int>> pos(maxN + 1); // pos[N] 存储当前K下N对应的查询索引
    vector<int> usedN;

    for (int k = 1; k <= maxK; ++k) {
        if (byK[k].empty()) continue;
        // 将当前K的所有查询按N插入pos
        for (int idx : byK[k]) {
            int n = queries[idx].N;
            if (pos[n].empty()) usedN.push_back(n);
            pos[n].push_back(idx);
        }
        long long sum = 0, prod = 1;
        for (int i = 1; i <= maxN; ++i) {
            int di = d[i];
            int add = (k < di) ? k : di;
            sum += add;
            if (sum >= MOD) sum %= MOD;
            if (di > k) {
                long long c = comb(di, k);
                prod = prod * c % MOD;
            }
            if (!pos[i].empty()) {
                for (int idx : pos[i]) {
                    ansEdges[idx] = (int)sum;
                    ansWays[idx] = (int)prod;
                }
            }
        }
        // 清空pos中使用的N
        for (int n : usedN) pos[n].clear();
        usedN.clear();
    }

    for (int i = 0; i < T; ++i)
        cout << ansEdges[i] << ' ' << ansWays[i] << '\n';

    return 0;
}
