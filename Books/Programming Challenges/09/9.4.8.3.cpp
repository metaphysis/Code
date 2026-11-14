#include <bits/stdc++.h>

using namespace std;

const int MAXV = 50010;

struct EDGE { int u, v, used, nxt; } g[MAXV << 1];

struct edge {
    int u, v;
    bool operator==(const edge e) const {
        return (e.u == u && e.v == v) || (e.u == v && e.v == u);
    }
};

int idx, head[MAXV];

void addEdge(int u, int v) {
    g[idx] = EDGE{u, v, 0, head[u]}; head[u] = idx++;
    g[idx] = EDGE{v, u, 0, head[v]}; head[v] = idx++;
}


int vbcc = 0;
vector<edge> vbc[MAXV];
stack<edge> stk;

int dfn[MAXV], ic[MAXV], dfstime = 0;

int dfs(int u, int parent) {
    int lowu = dfn[u] = ++dfstime, lowv, children = 0;
    for (int i = head[u]; ~i; i = g[i].nxt) {
        if (g[i].used) continue;
        g[i].used = g[i ^ 1].used = 1;
        edge eu = edge{g[i].u, g[i].v};
        stk.push(eu);
        int v = g[i].v;
        if (!dfn[v]) {
            ++children, lowu = min(lowu, lowv = dfs(v, u));
            if (lowv >= dfn[u]) {
                ic[u] = 1;
                vbc[vbcc].clear();
                while (stk.size()) {
                    edge ev = stk.top();
                    stk.pop();
                    vbc[vbcc].push_back(ev);
                    if (ev == eu) break;
                }
                vbcc++;
            }
        } else lowu = min(lowu, dfn[v]);
    }
    if (parent < 0) ic[u] = children > 1;
    return lowu;
}

int main(int argc, char* argv[]) {
    return 0;
}
