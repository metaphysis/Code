// Cells
// UVa ID: 1357
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.390s

#include <bits/stdc++.h>
using namespace std;

const int maxn = 300000 + 10;

struct Edge {
    int to, next;
} edge[maxn];

int head[maxn], dfn[maxn], eulerDepth[maxn << 2], eulerNode[maxn << 2], rmqTable[maxn << 2][20], posInEuler[maxn << 2];
int edgeCnt, dfsTime, eulerCnt;

void addEdge(int u, int to) {
    edge[edgeCnt].to = to;
    edge[edgeCnt].next = head[u];
    head[u] = edgeCnt++;
}

void init(int n) {
    for (int i = 0; i <= n; i++) {
        head[i] = -1;
        dfn[i] = 0;
    }
    edgeCnt = dfsTime = eulerCnt = 0;
}

void rmqInit(int n) {
    for (int i = 1; i <= n; i++) rmqTable[i][0] = eulerDepth[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            rmqTable[i][j] = min(rmqTable[i][j - 1], rmqTable[i + (1 << (j - 1))][j - 1]);
}

int rmqQuery(int L, int R) {
    int k = 0;
    while ((1 << (k + 1)) <= R - L + 1) k++;
    return min(rmqTable[L][k], rmqTable[R - (1 << k) + 1][k]);
}

int lca(int a, int b) {
    if (posInEuler[a] > posInEuler[b]) swap(a, b);
    int ans = rmqQuery(posInEuler[a], posInEuler[b]);
    return eulerNode[ans];
}

int stackNodes[maxn];

void dfsIterative() {
    int top = 0;
    stackNodes[++top] = 0;
    while (top) {
        int u = stackNodes[top];
        if (!dfn[u]) {
            dfn[u] = ++dfsTime;
            eulerNode[dfsTime] = u;
            posInEuler[u] = eulerCnt + 1;
        }
        eulerDepth[++eulerCnt] = dfn[u];
        bool hasChild = false;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int to = edge[i].to;
            if (!dfn[to]) {
                hasChild = true;
                stackNodes[++top] = to;
                break;
            }
        }
        if (!hasChild) top--;
    }
}

int c[maxn], nodeCount;

int binarySearch(int l, int r, int val) {
    while (l < r) {
        int mid = (l + r) / 2;
        if (c[mid] >= val) r = mid;
        else l = mid + 1;
    }
    return r;
}

void processQueries() {
    dfsIterative();
    rmqInit(eulerCnt);
    int m, u, to;
    scanf("%d", &m);
    while (m--) {
        scanf("%d%d", &u, &to);
        if (u >= nodeCount || u == to) {
            puts("No");
            continue;
        }
        int k = binarySearch(0, nodeCount - 1, to);
        puts(lca(u, k) == u ? "Yes" : "No");
    }
}

int main() {
    int t, cas = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &nodeCount);
        init(nodeCount);
        for (int i = 0; i < nodeCount; i++) scanf("%d", &c[i]);
        for (int i = 1; i < nodeCount; i++) c[i] += c[i - 1];
        for (int i = 1; i < nodeCount; i++) {
            int k = binarySearch(0, nodeCount - 1, i);
            addEdge(k, i);
        }
        printf("Case %d:\n", cas++);
        processQueries();
        if (t) puts("");
    }
    return 0;
}
