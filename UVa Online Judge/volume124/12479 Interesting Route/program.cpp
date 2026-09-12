#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30009, MAXE = 60009;
int head[MAXN], fr[MAXE], tov[MAXE], nxt[MAXE], low[MAXN], dfn[MAXN], used[MAXN], col[MAXN];
int N, M, ecnt, timer, roadAns, cityAns, topStk;
pair<int,int> stk[MAXE], store[MAXE];
vector<int> g[MAXN];

void addEdge(int u, int v) {
    fr[ecnt] = u; tov[ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt++;
    fr[ecnt] = v; tov[ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

void solveBcc(int u, int v) {
    int tot = 0, nu, nv;
    pair<int,int> e;
    while (topStk) {
        e = stk[--topStk];
        nu = e.first; nv = e.second;
        g[nu].clear(); g[nv].clear();
        store[tot++] = e;
        if ((nu == u && nv == v) || (nu == v && nv == u)) break;
    }
    if (tot <= 1) return;
    memset(col, 0, sizeof(col));
    for (int i = 0; i < tot; ++i) {
        nu = store[i].first; nv = store[i].second;
        used[nu] = used[nv] = 1;
        g[nu].push_back(nv);
        g[nv].push_back(nu);
    }
    queue<int> q;
    q.push(nu); col[nu] = 1;
    while (!q.empty()) {
        int uu = q.front(); q.pop();
        for (int i = 0; i < (int)g[uu].size(); ++i) {
            int vv = g[uu][i];
            if (col[vv] == 0) {
                col[vv] = 3 - col[uu];
                q.push(vv);
            } else if (col[uu] == col[vv]) return;
        }
    }
    roadAns++;
}

void dfsTarjan(int u, int p) {
    low[u] = dfn[u] = ++timer;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = tov[i];
        if (v == p) continue;
        if (dfn[v] == 0) {
            stk[topStk++] = make_pair(u, v);
            dfsTarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) solveBcc(u, v);
        } else if (dfn[v] < dfn[u]) {
            stk[topStk++] = make_pair(u, v);
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void bcc() {
    memset(dfn, 0, sizeof(dfn));
    memset(used, 0, sizeof(used));
    timer = roadAns = cityAns = topStk = 0;
    for (int i = 0; i < N; ++i) if (dfn[i] == 0) dfsTarjan(i, i);
    for (int i = 0; i < N; ++i) if (used[i] == 0) { roadAns += 3; cityAns += 2; }
}

int main() {
    int T, cas = 0;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        memset(head, -1, sizeof(head));
        ecnt = 0;
        for (int i = 0, u, v; i < M; ++i) {
            scanf("%d%d", &u, &v);
            addEdge(u, v);
        }
        bcc();
        printf("Case %d: %d %d\n", ++cas, roadAns, cityAns);
    }
    return 0;
}
