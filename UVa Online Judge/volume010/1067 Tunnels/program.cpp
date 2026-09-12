// Tunnels
// UVa ID: 1067
// Verdict: Accepted
// Submission Date: 2026-08-03
// UVa Run Time: 0.120s

#include <bits/stdc++.h>
using namespace std;

const int maxN = 128;
const int inf = 0x3f3f3f3f;

int mat[maxN][maxN];
int flow[maxN][maxN];
bool used[maxN];

int maxFlow(int n, int source, int sink) {
    if (source == sink) return 0;
    memset(flow, 0, sizeof(flow));
    int pre[maxN];
    int que[maxN];
    int dis[maxN];
    while (true) {
        memset(pre, 0, sizeof(pre));
        int front = 0;
        int rear = 0;
        que[rear++] = source;
        pre[source] = source + 1;
        dis[source] = inf;
        while (front < rear && !pre[sink]) {
            int current = que[front++];
            for (int i = 0; i < n; ++i) {
                int remain = mat[current][i] - flow[current][i];
                if (pre[i] || remain <= 0) continue;
                pre[i] = current + 1;
                dis[i] = min(dis[current], remain);
                que[rear++] = i;
                if (i == sink) break;
            }
            if (pre[sink]) break;
            for (int i = 0; i < n; ++i) {
                int remain = flow[i][current];
                if (pre[i] || remain <= 0) continue;
                pre[i] = -current - 1;
                dis[i] = min(dis[current], remain);
                que[rear++] = i;
                if (i == sink) break;
            }
        }
        if (!pre[sink]) break;
        int addFlow = dis[sink];
        for (int i = sink; i != source;) {
            if (pre[i] > 0) {
                int previous = pre[i] - 1;
                flow[previous][i] += addFlow;
                i = previous;
            } else {
                int previous = -pre[i] - 1;
                flow[i][previous] -= addFlow;
                i = previous;
            }
        }
    }
    int result = 0;
    for (int i = 0; i < n; ++i) result += flow[source][i];
    return result;
}

int main() {
    int row;
    int total;
    int testCase = 0;
    while (scanf("%d%d", &row, &total) != EOF) {
        if (!row && !total) break;
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < total; ++i) {
            int u;
            int v;
            scanf("%d%d", &u, &v);
            ++mat[u][v];
            ++mat[v][u];
        }
        int value[maxN];
        for (int i = 1; i <= row; ++i) value[i] = maxFlow(row + 1, i, 0);
        memset(used, false, sizeof(used));
        for (int step = 1; step <= row; ++step) {
            int best = inf;
            for (int i = 1; i <= row; ++i) {
                if (used[i]) continue;
                best = min(best, value[i]);
            }
            for (int i = 1; i <= row; ++i) {
                if (used[i]) continue;
                if (best != value[i]) continue;
                for (int j = 0; j <= row; ++j) {
                    mat[j][i] = 0;
                    mat[i][j] = 0;
                }
                used[i] = true;
            }
            for (int i = 1; i <= row; ++i) {
                if (used[i]) continue;
                value[i] = min(value[i], best + maxFlow(row + 1, i, 0));
            }
        }
        printf("Case %d: %d\n\n", ++testCase, value[1]);
    }
    return 0;
}
