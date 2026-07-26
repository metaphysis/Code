// The Queue
// UVa ID: 12257
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.040s
// https://blog.csdn.net/metaphysis/article/details/163173953

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 1000;

vector<int> fact(MAXN + 1), invNum(MAXN + 1);

// 预处理阶乘和逆元（线性求逆元）
void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i) fact[i] = (long long)fact[i - 1] * i % MOD;
    invNum[1] = 1;
    for (int i = 2; i <= MAXN; ++i)
        invNum[i] = (long long)(MOD - MOD / i) * invNum[MOD % i] % MOD;
}

vector<vector<int>> children;
vector<int> subSize;

// DFS 计算子树大小
int dfs(int u) {
    int sz = 1;
    for (int v : children[u]) sz += dfs(v);
    subSize[u] = sz;
    return sz;
}

int main() {
    precompute();
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        scanf("%d", &N);
        children.assign(N + 1, vector<int>());
        vector<int> inDeg(N + 1, 0);
        for (int i = 0; i < N - 1; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            children[a].push_back(b);
            inDeg[b]++;
        }
        int root = 1;
        for (int i = 1; i <= N; ++i)
            if (inDeg[i] == 0) { root = i; break; }
        subSize.assign(N + 1, 0);
        dfs(root);
        long long ans = fact[N];
        for (int i = 1; i <= N; ++i)
            ans = ans * invNum[subSize[i]] % MOD;
        printf("Case %d: %lld\n", tc, ans);
    }
    return 0;
}
