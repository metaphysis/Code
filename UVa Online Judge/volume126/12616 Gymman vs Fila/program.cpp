// Gymman vs Fila
// UVa ID: 12616
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.050s
// https://blog.csdn.net/metaphysis/article/details/163217936

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;
vector<int> adj[MAXN];
int dfn[MAXN], low[MAXN], subSize[MAXN], compId[MAXN];
bool isCut[MAXN];
vector<int> blocks[MAXN];
int timer, compCnt;
int compSizeArr[MAXN];

void dfs(int u, int p) {
    dfn[u] = low[u] = ++timer;
    subSize[u] = 1;
    compId[u] = compCnt;
    compSizeArr[compCnt]++;
    int childCnt = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (!dfn[v]) {
            childCnt++;
            dfs(v, u);
            subSize[u] += subSize[v];
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                if (p != 0) isCut[u] = true;
                blocks[u].push_back(subSize[v]);
            }
        } else if (dfn[v] < dfn[u]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (p == 0 && childCnt >= 2) isCut[u] = true;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; caseNo++) {
        int N, M;
        scanf("%d %d", &N, &M);
        for (int i = 1; i <= N; i++) {
            adj[i].clear();
            blocks[i].clear();
        }
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(subSize, 0, sizeof(subSize));
        memset(compId, 0, sizeof(compId));
        memset(isCut, false, sizeof(isCut));
        memset(compSizeArr, 0, sizeof(compSizeArr));
        timer = 0;
        compCnt = 0;
        for (int i = 1; i <= N; i++) {
            if (!dfn[i]) {
                compCnt++;
                dfs(i, 0);
            }
        }
        long long ans = 0;
        for (int u = 1; u <= N; u++) {
            if (!isCut[u]) continue;
            long long total = compSizeArr[compId[u]] - 1;
            long long sumSq = 0;
            long long sumBlocks = 0;
            for (int s : blocks[u]) {
                sumSq += 1LL * s * s;
                sumBlocks += s;
            }
            long long remain = total - sumBlocks;
            if (remain > 0) sumSq += 1LL * remain * remain;
            ans += total * total - sumSq;
        }
        printf("Case %d: %lld\n", caseNo, ans);
    }
    return 0;
}
