#include <bits/stdc++.h>
using namespace std;

const int maxN = 40005;
const int maxK = 62;
const int maxLog = 17;
const int maxEdge = maxN * 2;

int n, k, q;
int head[maxN], to[maxEdge], nextEdge[maxEdge], edgeCount;
int cost[maxN], bright[maxN];
int depth[maxN], parent[maxLog][maxN];
int jumpMax[maxLog][maxN][maxK];
int orderList[maxN], stackNode[maxN];
int nodeU, nodeV, nodeLca;
int bestValue[maxK];

void addEdge(int x, int y) {
    to[edgeCount] = y;
    nextEdge[edgeCount] = head[x];
    head[x] = edgeCount++;
}

void buildTree() {
    int orderCount = 0, stackCount = 0;
    stackNode[stackCount++] = 1;
    parent[0][1] = 0;
    depth[1] = 0;
    while (stackCount > 0) {
        int x = stackNode[--stackCount];
        orderList[orderCount++] = x;
        for (int edge = head[x]; edge != -1; edge = nextEdge[edge]) {
            int y = to[edge];
            if (y == parent[0][x])
                continue;
            parent[0][y] = x;
            depth[y] = depth[x] + 1;
            stackNode[stackCount++] = y;
        }
    }
    for (int i = 1; i <= n; i++)
        jumpMax[0][i][cost[i]] = bright[i];
    for (int j = 1; j < maxLog; j++) {
        for (int i = 1; i <= n; i++) {
            int mid = parent[j - 1][i];
            parent[j][i] = parent[j - 1][mid];
            for (int t = 1; t <= k; t++)
                jumpMax[j][i][t] = max(jumpMax[j - 1][i][t], jumpMax[j - 1][mid][t]);
        }
    }
}

int getLca(int x, int y) {
    if (depth[x] < depth[y])
        swap(x, y);
    int diff = depth[x] - depth[y];
    for (int j = 0; j < maxLog; j++)
        if ((diff >> j) & 1)
            x = parent[j][x];
    if (x == y)
        return x;
    for (int j = maxLog - 1; j >= 0; j--)
        if (parent[j][x] != parent[j][y]) {
            x = parent[j][x];
            y = parent[j][y];
        }
    return parent[0][x];
}

void collectPath(int x, int ancestor) {
    int diff = depth[x] - depth[ancestor];
    for (int j = maxLog - 1; j >= 0; j--) {
        if ((diff >> j) & 1) {
            for (int t = 1; t <= k; t++)
                bestValue[t] = max(bestValue[t], jumpMax[j][x][t]);
            x = parent[j][x];
        }
    }
}

void solveQuery() {
    nodeLca = getLca(nodeU, nodeV);
    for (int t = 1; t <= k; t++)
        bestValue[t] = 0;
    collectPath(nodeU, nodeLca);
    collectPath(nodeV, nodeLca);
    bestValue[cost[nodeLca]] = max(bestValue[cost[nodeLca]], bright[nodeLca]);
    long long dp[maxK] = {};
    long long sumValue = 0, xorValue = 0;
    for (int money = 1; money <= k; money++) {
        for (int t = 1; t <= money; t++)
            if (bestValue[t] > 0)
                dp[money] = max(dp[money], dp[money - t] + bestValue[t]);
        sumValue += dp[money];
        xorValue ^= dp[money];
    }
    cout << sumValue << " " << xorValue << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> k) {
        edgeCount = 0;
        for (int i = 1; i <= n; i++)
            head[i] = -1;
        for (int i = 1; i < n; i++) {
            int x, y;
            cin >> x >> y;
            addEdge(x, y);
            addEdge(y, x);
        }
        for (int i = 1; i <= n; i++)
            cin >> cost[i];
        for (int i = 1; i <= n; i++)
            cin >> bright[i];
        memset(parent, 0, sizeof(parent));
        memset(jumpMax, 0, sizeof(jumpMax));
        buildTree();
        cin >> q;
        while (q--) {
            cin >> nodeU >> nodeV;
            solveQuery();
        }
    }
    return 0;
}
