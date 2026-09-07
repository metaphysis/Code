#include <bits/stdc++.h>
using namespace std;

const int maxN = 50005;
const int maxE = 100005;
const int maxK = 101;
const int logN = 17;

struct Edge {
    int to, next, a, b;
};

int n, q, ec;
int head[maxN], dep[maxN], fa[maxN][logN];
int zeroCnt[maxN][maxK];
int ord[maxN];
double sumLog[maxN][maxK];
Edge edge[maxE];

void addEdge(int u, int v, int a, int b) {
    edge[ec] = {v, head[u], a, b};
    head[u] = ec++;
}

int getLca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int dif = dep[u] - dep[v];
    for (int i = 0; i < logN; i++)
        if (dif & (1 << i)) u = fa[u][i];
    if (u == v) return u;
    for (int i = logN - 1; i >= 0; i--)
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}

void buildTree() {
    int cnt = 0;
    ord[cnt++] = 1;
    dep[1] = 0;
    fa[1][0] = 0;
    for (int k = 0; k < maxK; k++) {
        zeroCnt[1][k] = 0;
        sumLog[1][k] = 0;
    }
    for (int i = 0; i < cnt; i++) {
        int u = ord[i];
        for (int id = head[u]; id != -1; id = edge[id].next) {
            int v = edge[id].to;
            if (v == fa[u][0]) continue;
            fa[v][0] = u;
            dep[v] = dep[u] + 1;
            ord[cnt++] = v;
            for (int k = 0; k < maxK; k++) {
                if (k < edge[id].a) {
                    zeroCnt[v][k] = zeroCnt[u][k] + 1;
                    sumLog[v][k] = sumLog[u][k];
                } else if (k < edge[id].b) {
                    double prob = 1.0 * (k - edge[id].a + 1) / (edge[id].b - edge[id].a + 1);
                    zeroCnt[v][k] = zeroCnt[u][k];
                    sumLog[v][k] = sumLog[u][k] + log(prob);
                } else {
                    zeroCnt[v][k] = zeroCnt[u][k];
                    sumLog[v][k] = sumLog[u][k];
                }
            }
        }
    }
    for (int j = 1; j < logN; j++)
        for (int i = 1; i <= n; i++)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

double getAns(int x, int y) {
    int l = getLca(x, y);
    double ans = 100;
    for (int k = 0; k < 100; k++) {
        int zeros = zeroCnt[x][k] + zeroCnt[y][k] - 2 * zeroCnt[l][k];
        if (zeros == 0) {
            double val = exp(sumLog[x][k] + sumLog[y][k] - 2 * sumLog[l][k]);
            ans -= val;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        ec = 0;
        fill(head + 1, head + n + 1, -1);
        for (int i = 1; i < n; i++) {
            int x, y, a, b;
            cin >> x >> y >> a >> b;
            addEdge(x, y, a, b);
            addEdge(y, x, a, b);
        }
        buildTree();
        cin >> q;
        while (q--) {
            int x, y;
            cin >> x >> y;
            cout << fixed << setprecision(12) << getAns(x, y) << '\n';
        }
    }
    return 0;
}
