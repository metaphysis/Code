#include <bits/stdc++.h>
using namespace std;

const int maxN = 55;
const int maxK = 205;
const long long inf = (1LL << 60);

int n, m, kth, startNode, targetNode, srcNode;
int edgeW[maxN][maxN];
bool banNode[maxN], banEdge[maxN][maxN];

struct Path {
    long long cost;
    int node[maxN], len;
};

struct PathCmp {
    bool operator()(const Path &a, const Path &b) const {
        int i, lim;
        if (a.cost != b.cost)
            return a.cost < b.cost;
        lim = min(a.len, b.len);
        for (i = 0; i < lim; i++)
            if (a.node[i] != b.node[i])
                return a.node[i] < b.node[i];
        return a.len < b.len;
    }
};

Path got[maxK], tmpPath;
set<Path, PathCmp> cand;

bool getShortest() {
    long long dist[maxN];
    bool used[maxN];
    int i, u, v, nxt;
    for (i = 1; i <= n; i++) {
        dist[i] = inf;
        used[i] = false;
    }
    if (banNode[srcNode] || banNode[targetNode])
        return false;
    dist[targetNode] = 0;
    for (i = 1; i <= n; i++) {
        u = 0;
        for (v = 1; v <= n; v++)
            if (!banNode[v] && !used[v] && (u == 0 || dist[v] < dist[u]))
                u = v;
        if (u == 0 || dist[u] == inf)
            break;
        used[u] = true;
        for (v = 1; v <= n; v++)
            if (!banNode[v] && edgeW[v][u] && !banEdge[v][u] && dist[v] > dist[u] + edgeW[v][u])
                dist[v] = dist[u] + edgeW[v][u];
    }
    if (dist[srcNode] == inf)
        return false;
    tmpPath.cost = dist[srcNode];
    tmpPath.len = 0;
    u = srcNode;
    tmpPath.node[tmpPath.len++] = u;
    while (u != targetNode) {
        nxt = 0;
        for (v = 1; v <= n; v++)
            if (edgeW[u][v] && !banNode[v] && !banEdge[u][v] && dist[v] != inf && dist[u] == edgeW[u][v] + dist[v]) {
                nxt = v;
                break;
            }
        if (nxt == 0)
            return false;
        u = nxt;
        tmpPath.node[tmpPath.len++] = u;
    }
    return true;
}

bool sameRoot(int x, int y, int pos) {
    int i;
    for (i = 0; i <= pos; i++)
        if (got[x].node[i] != got[y].node[i])
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int i, j, pos, cnt;
    long long rootCost;
    Path cur, newPath;
    while (cin >> n >> m >> kth >> startNode >> targetNode) {
        if (n == 0 && m == 0 && kth == 0 && startNode == 0 && targetNode == 0)
            break;
        memset(edgeW, 0, sizeof(edgeW));
        for (i = 0; i < m; i++) {
            int x, y, d;
            cin >> x >> y >> d;
            edgeW[x][y] = d;
        }
        memset(banNode, 0, sizeof(banNode));
        memset(banEdge, 0, sizeof(banEdge));
        cand.clear();
        srcNode = startNode;
        if (!getShortest()) {
            cout << "None\n";
            continue;
        }
        got[0] = tmpPath;
        cnt = 1;
        while (cnt < kth) {
            cur = got[cnt - 1];
            rootCost = 0;
            for (pos = 0; pos + 1 < cur.len; pos++) {
                memset(banNode, 0, sizeof(banNode));
                memset(banEdge, 0, sizeof(banEdge));
                for (i = 0; i < pos; i++)
                    banNode[cur.node[i]] = true;
                for (j = 0; j < cnt; j++)
                    if (got[j].len > pos + 1 && sameRoot(j, cnt - 1, pos))
                        banEdge[got[j].node[pos]][got[j].node[pos + 1]] = true;
                srcNode = cur.node[pos];
                if (getShortest()) {
                    newPath.cost = rootCost + tmpPath.cost;
                    newPath.len = pos + tmpPath.len;
                    for (i = 0; i < pos; i++)
                        newPath.node[i] = cur.node[i];
                    for (i = 0; i < tmpPath.len; i++)
                        newPath.node[pos + i] = tmpPath.node[i];
                    cand.insert(newPath);
                }
                rootCost += edgeW[cur.node[pos]][cur.node[pos + 1]];
            }
            if (cand.empty())
                break;
            got[cnt] = *cand.begin();
            cand.erase(cand.begin());
            cnt++;
        }
        if (cnt < kth) {
            cout << "None\n";
            continue;
        }
        for (i = 0; i < got[kth - 1].len; i++) {
            if (i > 0)
                cout << '-';
            cout << got[kth - 1].node[i];
        }
        cout << '\n';
    }
    return 0;
}
