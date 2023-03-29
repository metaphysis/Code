// Island Hopping
// UVa ID: 1013
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 60;

struct edge {
    int u, v;
    double w;
    bool operator<(const edge &e) { return w < e.w; }
} g[MAXN * MAXN];

int cnt, xi[MAXN], yi[MAXN], mi[MAXN];

int ranks[MAXN], parent[MAXN];

int findSet(int x) {
    return x == parent[x] ? x : parent[x] = findSet(parent[x]);
}

void unionSet(int x, int y) {
    x = findSet(x), y = findSet(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) {
            parent[y] = x;
            mi[x] += mi[y];
        }
        else {
            parent[x] = y;
            mi[y] += mi[x];
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, cases = 1;
    while (cin >> n, n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> xi[i] >> yi[i] >> mi[i];
            parent[i] = i;
            ranks[i] = 1;
            sum += mi[i];
        }
        cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                g[cnt++] = edge{i, j, hypot(xi[i] - xi[j], yi[i] - yi[j])};
        sort(g, g + cnt);
        double r = 0;
        for (int i = 0; i < cnt; i++) {
            if (findSet(g[i].u) != findSet(g[i].v)) {
                if (findSet(g[i].u) == findSet(0)) r += mi[findSet(g[i].v)] * g[i].w;
                if (findSet(g[i].v) == findSet(0)) r += mi[findSet(g[i].u)] * g[i].w;
                unionSet(g[i].u, g[i].v);
            }
        }
        r /= sum;
        cout << "Island Group: " << cases++ << " Average ";
        cout << fixed << setprecision(2) << r << '\n';
        cout << '\n';
    }
    return 0;
}
