//https://www.luogu.com.cn/problem/P8581


#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1000010, MAXE = 2100010;

double ri[MAXV];
int n, visited[MAXV], MH[MAXV], head[MAXV], tot;
long long w[MAXV], ai[MAXV], bi[MAXV];

struct edge { int v, nxt; } edges[MAXE];
struct NODE { double ratio; int v, lc, rc, d; };

struct MH {
    NODE nd[MAXV];
    int cnt = 0, maxHeap = 0;
    inline bool cmp(double &a, double &b) { return maxHeap ? a < b : a > b; }
    int merge(int x, int y) {
        if (!x || !y) return x | y;
        if (cmp(nd[x].ratio, nd[y].ratio)) swap(x, y);
        nd[x].rc = merge(nd[x].rc, y);
        if (nd[nd[x].lc].d < nd[nd[x].rc].d) swap(nd[x].lc, nd[x].rc);
        nd[x].d = nd[nd[x].rc].d + 1;
        return x;
    }
    int get(double ratio, int v) {
        ++cnt;
        nd[cnt].ratio = ratio;
        nd[cnt].v = v;
        nd[cnt].lc = nd[cnt].rc = nd[cnt].d = 0;
        return cnt;
    }
    int push(int x, int y) { return merge(x, y); }
    NODE top(int x) { return nd[x]; }
    int pop(int x) { return merge(nd[x].lc, nd[x].rc); }
}H;

void dfs(int u) {
    visited[u] = 1;
    ri[u] = (double)ai[u] / bi[u];
    if (head[u] == -1) return;
    for (int i = head[u]; ~i; i = edges[i].nxt) {
        int v = edges[i].v;
        if (!visited[v]) {
            dfs(v);
            int y = H.get(ri[v], v);
            if (!MH[u]) MH[u] = y;
            else MH[u] = H.push(MH[u], y);
        }
    }
    while (MH[u]) {
        NODE lt = H.top(MH[u]);
        if (H.cmp(lt.ratio, ri[u])) break;
        MH[u] = H.pop(MH[u]);
        ai[u] += ai[lt.v], bi[u] += bi[lt.v];
        ri[u] = (double)ai[u] / bi[u];
        MH[u] = H.merge(MH[u], MH[lt.v]);
    }
}

void add(int u, int v) {
    edges[tot].v = v;
    edges[tot].nxt = head[u];
    head[u] = tot++;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> n
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 2, u; i <= n; i++) { cin >> u; add(u, i); }
    for (int i = 1, av; i <= n; i++) { cin >> av; ai[i] = av; }
    for (int i = 1, bv; i <= n; i++) { cin >> bv; bi[i] = bv; }

    int R = 1;
    queue<int> q;
    q.push(R);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        dfs(u);
        w[u] = ai[u] = ceil(ri[u]), bi[u] = 1;
        head[u] = -1;
        while (MH[u]) {
            NODE lt = H.top(MH[u]);
            MH[u] = H.pop(MH[u]);
            ai[lt.v] += ai[u];
            add(u, lt.v);
            q.push(lt.v);
        }
    }

    H.cnt = 0;
    H.maxHeap = 1;
    for (int i = 1; i <= n; i++) visited[i] = 0;
    dfs(R);

    long long W = 0, t = 1;
    priority_queue<pair<double, int>> pq;
    pq.push(make_pair(ri[R], R));
    while (!pq.empty()) {
        pair<double, int> gt = pq.top(); pq.pop();
        W += t * w[gt.second];
        for (int i = head[gt.second]; ~i; i = edges[i].nxt)
        {
            int v = edges[i].v;
            pq.push(make_pair(ri[v], v));
        }
        t++;
    }
    cout << W << '\n';

    return 0;
}
