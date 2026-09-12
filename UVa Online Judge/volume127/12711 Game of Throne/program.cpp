// Game of Throne
// UVa ID: 12711
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100 + 10, INF = 0x3f3f3f3f;

int graph[MAXN][MAXN], indexArr[MAXN];
int matchPair[MAXN], stackNodes[MAXN];
int visited[MAXN], distVal[MAXN];
int nodeCount, edgeCount, pairCount, stackTop;

bool findCycle(int u) {
    stackNodes[stackTop++] = u;
    if (visited[u]) return true;
    visited[u] = true;
    for (int i = 1; i <= pairCount; ++i) {
        if (i != u && i != matchPair[u] && !visited[i]) {
            int v = matchPair[i];
            if (distVal[v] < distVal[u] + graph[u][i] - graph[i][v]) {
                distVal[v] = distVal[u] + graph[u][i] - graph[i][v];
                if (findCycle(v)) return true;
            }
        }
    }
    stackTop--;
    visited[u] = false;
    return false;
}

int maxWeightMatching() {
    for (int i = 1; i <= pairCount; ++i) indexArr[i] = i;
    for (int i = 1; i <= pairCount; i += 2) {
        matchPair[i] = i + 1;
        matchPair[i + 1] = i;
    }
    for (int times = 0, found; times < 3;) {
        memset(distVal, 0, sizeof(distVal));
        memset(visited, 0, sizeof(visited));
        stackTop = 0;
        found = 0;
        for (int i = 1; i <= pairCount; ++i) {
            if (findCycle(indexArr[i])) {
                found = 1;
                int t = matchPair[stackNodes[stackTop - 1]], j = stackTop - 2;
                while (stackNodes[j] != stackNodes[stackTop - 1]) {
                    matchPair[t] = stackNodes[j];
                    swap(t, matchPair[stackNodes[j]]);
                    --j;
                }
                matchPair[t] = stackNodes[j];
                matchPair[stackNodes[j]] = t;
                break;
            }
        }
        if (!found) times++;
        if (!found) random_shuffle(indexArr + 1, indexArr + pairCount + 1);
    }
    int result = 0;
    for (int i = 1; i <= pairCount; ++i)
        if (i < matchPair[i]) result += graph[i][matchPair[i]];
    return result;
}

int main() {
    int testCases;
    scanf("%d", &testCases);
    for (int caseNo = 1; caseNo <= testCases; ++caseNo) {
        scanf("%d%d%d", &nodeCount, &edgeCount, &pairCount);
        memset(graph, 0x3f, sizeof(graph));
        for (int i = 1; i <= nodeCount; ++i) graph[i][i] = 0;
        for (int i = 0; i < edgeCount; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            graph[u][v] = graph[v][u] = w;
        }
        printf("Case %d: ", caseNo);
        if (pairCount & 1) {
            puts("Impossible");
            continue;
        }
        for (int k = 1; k <= nodeCount; ++k)
            for (int i = 1; i <= nodeCount; ++i)
                for (int j = 1; j <= nodeCount; ++j)
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
        for (int i = 1; i <= pairCount; ++i) {
            for (int j = 1; j <= pairCount; ++j)
                graph[i][j] = -graph[i][j];
            graph[i][i] = -INF;
        }
        printf("%d\n", -maxWeightMatching());
    }
    return 0;
}
