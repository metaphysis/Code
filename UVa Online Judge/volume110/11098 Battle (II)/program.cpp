// Battle II
// UVa ID: 11098
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Bomb { int x, y, r, e; };

int n;
vector<Bomb> bombs;
vector<vector<int>> adj;
vector<int> dfn, low, stk, inStack, sccId;
int dfsClock, sccCnt;

void tarjan(int u) {
    dfn[u] = low[u] = ++dfsClock;
    stk.push_back(u);
    inStack[u] = 1;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        int v;
        do {
            v = stk.back(); stk.pop_back();
            inStack[v] = 0;
            sccId[v] = sccCnt;
        } while (v != u);
        sccCnt++;
    }
}

int main() {
    int N;
    cin >> N;
    for (int caseNo = 1; caseNo <= N; ++caseNo) {
        cin >> n;
        bombs.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> bombs[i].x >> bombs[i].y >> bombs[i].r >> bombs[i].e;

        // 建图
        adj.assign(n, {});
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                long long dx = bombs[i].x - bombs[j].x;
                long long dy = bombs[i].y - bombs[j].y;
                long long dist2 = dx * dx + dy * dy;
                long long rhs = (long long)bombs[i].e + bombs[i].r + bombs[j].r;
                if (dist2 <= rhs * rhs)
                    adj[i].push_back(j);
            }

        // Tarjan 求 SCC
        dfn.assign(n, 0); low.assign(n, 0); inStack.assign(n, 0); sccId.assign(n, -1);
        stk.clear(); dfsClock = 0; sccCnt = 0;
        for (int i = 0; i < n; ++i)
            if (!dfn[i]) tarjan(i);

        // 每个 SCC 的最小 E 和对应炸弹编号
        vector<int> minE(sccCnt, INT_MAX), bestNode(sccCnt, -1);
        for (int i = 0; i < n; ++i) {
            int c = sccId[i];
            if (bombs[i].e < minE[c]) {
                minE[c] = bombs[i].e;
                bestNode[c] = i;
            }
        }

        // 缩点建 DAG，去重边
        vector<int> indeg(sccCnt, 0);
        vector<vector<int>> dag(sccCnt);
        vector<vector<bool>> has(sccCnt, vector<bool>(sccCnt, false));
        for (int u = 0; u < n; ++u)
            for (int v : adj[u]) {
                int cu = sccId[u], cv = sccId[v];
                if (cu != cv && !has[cu][cv]) {
                    has[cu][cv] = true;
                    dag[cu].push_back(cv);
                    indeg[cv]++;
                }
            }

        // 必选源 SCC
        vector<int> chosenScc;
        long long totalCost = 0;
        int totalCount = 0;
        for (int c = 0; c < sccCnt; ++c)
            if (indeg[c] == 0) {
                chosenScc.push_back(c);
                totalCost += minE[c];
                totalCount++;
            }

        // 可选非源 SCC，按成本排序
        vector<pair<int,int>> optional;
        for (int c = 0; c < sccCnt; ++c)
            if (indeg[c] != 0)
                optional.push_back({minE[c], c});
        sort(optional.begin(), optional.end());

        // 贪心加入能降低平均值的可选 SCC
        for (auto &p : optional) {
            int cost = p.first, cid = p.second;
            if ((long long)cost * totalCount <= totalCost) {
                chosenScc.push_back(cid);
                totalCost += cost;
                totalCount++;
            } else
                break;
        }

        // 拓扑排序（用于逆序输出）
        vector<int> indegCopy = indeg;
        queue<int> q;
        for (int c = 0; c < sccCnt; ++c)
            if (indegCopy[c] == 0) q.push(c);
        vector<int> topo;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (int v : dag[u]) {
                indegCopy[v]--;
                if (indegCopy[v] == 0) q.push(v);
            }
        }

        vector<bool> isChosen(sccCnt, false);
        for (int c : chosenScc) isChosen[c] = true;

        vector<int> ans;
        for (int i = (int)topo.size() - 1; i >= 0; --i) {
            int c = topo[i];
            if (isChosen[c])
                ans.push_back(bestNode[c]);
        }

        cout << "Case #" << caseNo << ":";
        for (int id : ans)
            cout << ' ' << id;
        cout << '\n';
    }
    return 0;
}
