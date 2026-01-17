// Remember the A La Mode
// UVa ID: 1049
// Verdict: Accepted
// Submission Date: 2026-01-10
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 105; // 最多 50+50+2 个节点

struct Edge {
    int to, cap, flow, cost, next;
} edges[100005];
int head[MAXN], edgeCnt;
int pre[MAXN], dist[MAXN];
bool inQueue[MAXN];
int nodeCnt;

void initGraph(int n) {
    nodeCnt = n;
    edgeCnt = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int cap, int cost) {
    edges[edgeCnt] = {v, cap, 0, cost, head[u]};
    head[u] = edgeCnt++;
    edges[edgeCnt] = {u, 0, 0, -cost, head[v]};
    head[v] = edgeCnt++;
}

bool spfa(int s, int t, int& flow, int& cost) {
    queue<int> q;
    memset(dist, 0x3f, sizeof(dist));
    memset(inQueue, false, sizeof(inQueue));
    dist[s] = 0;
    pre[s] = -1;
    q.push(s);
    inQueue[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inQueue[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].next) {
            Edge& e = edges[i];
            if (e.cap > e.flow && dist[e.to] > dist[u] + e.cost) {
                dist[e.to] = dist[u] + e.cost;
                pre[e.to] = i;
                if (!inQueue[e.to]) {
                    q.push(e.to);
                    inQueue[e.to] = true;
                }
            }
        }
    }
    if (dist[t] == INF) return false;
    int aug = INF;
    for (int u = t; u != s; u = edges[pre[u] ^ 1].to)
        aug = min(aug, edges[pre[u]].cap - edges[pre[u]].flow);
    flow += aug;
    cost += dist[t] * aug;
    for (int u = t; u != s; u = edges[pre[u] ^ 1].to) {
        edges[pre[u]].flow += aug;
        edges[pre[u] ^ 1].flow -= aug;
    }
    return true;
}

int minCostMaxFlow(int s, int t) {
    int flow = 0, cost = 0;
    while (spfa(s, t, flow, cost));
    return cost;
}

int main() {
    int P, I, caseNo = 1;
    while (scanf("%d %d", &P, &I) == 2 && (P || I)) {
        vector<int> pieCount(P), iceCount(I);
        for (int i = 0; i < P; i++) scanf("%d", &pieCount[i]);
        for (int i = 0; i < I; i++) scanf("%d", &iceCount[i]);
        vector<vector<double>> profit(P, vector<double>(I));
        for (int i = 0; i < P; i++)
            for (int j = 0; j < I; j++)
                scanf("%lf", &profit[i][j]);
        
        // 建图：节点编号：0~P-1 为派类型，P~P+I-1 为冰淇淋类型，P+I 为源点，P+I+1 为汇点
        int S = P + I, T = P + I + 1;
        initGraph(P + I + 2);
        
        // 源点到派类型
        for (int i = 0; i < P; i++) addEdge(S, i, pieCount[i], 0);
        // 冰淇淋类型到汇点
        for (int j = 0; j < I; j++) addEdge(P + j, T, iceCount[j], 0);
        // 派类型到冰淇淋类型（仅当利润不为-1）
        for (int i = 0; i < P; i++)
            for (int j = 0; j < I; j++)
                if (profit[i][j] >= 0) addEdge(i, P + j, INF, (int)(profit[i][j] * 100 + 0.5));
        
        int minProfit = minCostMaxFlow(S, T);
        
        // 重新建图求最大费用最大流（将费用取负）
        initGraph(P + I + 2);
        for (int i = 0; i < P; i++) addEdge(S, i, pieCount[i], 0);
        for (int j = 0; j < I; j++) addEdge(P + j, T, iceCount[j], 0);
        for (int i = 0; i < P; i++)
            for (int j = 0; j < I; j++)
                if (profit[i][j] >= 0) addEdge(i, P + j, INF, -(int)(profit[i][j] * 100 + 0.5));
        
        int maxProfit = -minCostMaxFlow(S, T);
        
        printf("Problem %d: %.2f to %.2f\n", caseNo++, minProfit / 100.0, maxProfit / 100.0);
    }
    return 0;
}
