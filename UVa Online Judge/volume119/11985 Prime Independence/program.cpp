// Prime Independence
// UVa ID: 11985
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 500000;

vector<int> spf(MAXV + 1), omega(MAXV + 1);

// 线性筛：最小质因子 + 质因子总数（带重数）
void preprocess() {
    vector<int> primes;
    for (int i = 2; i <= MAXV; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
            omega[i] = 1;
        }
        for (int p : primes) {
            if (p > spf[i] || i * p > MAXV) break;
            spf[i * p] = p;
            omega[i * p] = omega[i] + 1;
        }
    }
}

// 获取 x 的所有不同质因子
vector<int> getDistinctPrimes(int x) {
    vector<int> res;
    while (x > 1) {
        int p = spf[x];
        res.push_back(p);
        while (x % p == 0) x /= p;
    }
    return res;
}

// Hopcroft–Karp 二分图最大匹配
class HopcroftKarp {
public:
    int L, R;
    vector<vector<int>> adj;
    vector<int> pairU, pairV, dist;

    HopcroftKarp(int L_, int R_) : L(L_), R(R_), adj(L_), pairU(L_, -1), pairV(R_, -1), dist(L_) {}

    void addEdge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < L; ++u) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else dist[u] = -1;
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int u2 = pairV[v];
                if (u2 == -1) found = true;
                else if (dist[u2] == -1) {
                    dist[u2] = dist[u] + 1;
                    q.push(u2);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int u2 = pairV[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int maxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < L; ++u)
                if (pairU[u] == -1 && dfs(u)) ++matching;
        }
        return matching;
    }
};

int main() {
    preprocess();
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        scanf("%d", &N);
        vector<int> arr(N);
        vector<int> leftIdx(MAXV + 1, -1), rightIdx(MAXV + 1, -1);
        vector<int> leftNodes, rightNodes;

        for (int i = 0; i < N; ++i) {
            scanf("%d", &arr[i]);
            int x = arr[i];
            if (omega[x] & 1) {
                leftIdx[x] = (int)leftNodes.size();
                leftNodes.push_back(x);
            } else {
                rightIdx[x] = (int)rightNodes.size();
                rightNodes.push_back(x);
            }
        }

        int L = leftNodes.size(), R = rightNodes.size();
        HopcroftKarp hk(L, R);

        for (int x : arr) {
            vector<int> primes = getDistinctPrimes(x);
            for (int p : primes) {
                if (x % p != 0) continue;
                int y = x / p;
                if (y < 1) continue;
                if (omega[x] & 1) {
                    if (rightIdx[y] != -1) hk.addEdge(leftIdx[x], rightIdx[y]);
                } else {
                    if (leftIdx[y] != -1) hk.addEdge(leftIdx[y], rightIdx[x]);
                }
            }
        }

        int match = hk.maxMatching();
        printf("Case %d: %d\n", tc, N - match);
    }
    return 0;
}
