// Chemical Plant
// UVa ID: 12138
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 50010, MAXE = 100010;

int V, E, W, S, T;
long long d[MAXE];
vector<int> tube_in[MAXV], tube_out[MAXV];

struct tube {
    int u, v, sst, sct, dst, dct;
    tube (int u = 0, int v = 0, int sst = 0, int sct = 0, int dst = 0, int dct = 0): u(u), v(v), sst(sst), sct(sct), dst(dst), dct(dct) {}
    bool operator<(const tube &t) const
    {
        if (sst != t.sst) return sst < t.sst;
        if (sct != t.sct) return sct < t.sct;
        if (dst != t.dst) return dst < t.dst;
        if (dct != t.dct) return dct < t.dct;
        if (u != t.u) return u < t.u;
        return v < t.v;
    }
} TS[MAXE];

int head[MAXE], edge_cnt = 0;
struct edge
{
    int v, w, nxt;
    edge (int v = 0, int w = 0, int nxt = 0): v(v), w(w), nxt(nxt) {}
} ES[MAXE << 4];

struct walk
{
    long long w;
    int v;
    walk (long long w = 0, int v = 0): w(w), v(v) {}
    bool operator<(const walk &s) const { return w > s.w; }
};

void add(int u, int v, int w)
{
    if (edge_cnt > 1000000) while (1) {}
    ES[edge_cnt] = edge(v, w, head[u]);
    head[u] = edge_cnt++;
}

void moore_dijkstra(int u)
{
    memset(d, 0x3f, sizeof d);
    d[u] = 0;
    
    priority_queue<walk> q;
    q.push(walk(u, d[u]));

    while (!q.empty())
    {
        walk s = q.top(); q.pop();
        for (int i = head[s.v]; ~i; i = ES[i].nxt)
        {
            edge e = ES[i];
            if (d[e.v] > d[s.v] + e.w)
            {
                d[e.v] = d[s.v] + e.w;
                q.push(walk(d[e.v], e.v));
            }
        }
    }
}

void build_graph()
{
    edge_cnt = 0;
    memset(head, -1, sizeof head);
    
    for (int i = 1; i <= V; i++)
    {
        for (auto u : tube_in[i])
            for (auto v : tube_out[i])
            {
                if (u > v) continue;
                if (TS[u].dct <= TS[v].sst)
                {
                    add(u, v, TS[v].sct - TS[u].dst);
                }
            }
                
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    while (cin >> V >> E >> W, V)
    {
        cin >> S >> T;

        TS[0] = tube(0, 1, 0, 0, 0, 0);
        for (int i = 1, u, v, sst, sct, dst, dct; i <= E; i++)
        {
            cin >> u >> v >> sst >> sct >> dst >> dct;
            if (dct > T) continue;
            TS[i] = tube(u, v, sst, sct, dst, dct);
            
        }
        sort(TS + 1, TS + E + 1);
        for (int i = 1; i <= V; i++)
        {
            tube_in[i].clear();
            tube_out[i].clear();
        }
        for (int i = 1; i <= E; i++)
        {
            tube_in[TS[i].v].push_back(i);
            tube_out[TS[i].u].push_back(i);
        }
        TS[E + 1] = tube(S, V + 1, T, T, T, T);
        tube_in[1].insert(tube_in[1].begin(), 0);
        tube_out[S].push_back(E + 1);

        build_graph();
        //moore_dijkstra(0);

        cout << "Plant " << cases++ << ": ";
        cout << ((W - d[E + 1]) < 0 ? 0 : (W - d[E + 1])) << '\n';
    }
    return 0;
}
