#include <bits/stdc++.h>
using namespace std;

const double INF = 1e100;
const double PI = acos(-1.0);

struct Edge {
    int u, v;
    double len;
    double ux, uy; // 单位方向向量
};

double angleBetween(const Edge& e1, const Edge& e2) {
    double dot = e1.ux * e2.ux + e1.uy * e2.uy;
    double cross = e1.ux * e2.uy - e1.uy * e2.ux;
    double ang = atan2(fabs(cross), dot);
    return ang * 180.0 / PI;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    bool firstCase = true;
    while (T--) {
        int N, M, S, F;
        double k;
        cin >> N >> M >> S >> F >> k;
        vector<pair<double, double>> coord(N + 1);
        for (int i = 1; i <= N; ++i) cin >> coord[i].first >> coord[i].second;
        vector<Edge> edges;
        edges.reserve(M);
        vector<vector<int>> outEdges(N + 1);
        for (int i = 0; i < M; ++i) {
            int A, B;
            cin >> A >> B;
            double dx = coord[B].first - coord[A].first;
            double dy = coord[B].second - coord[A].second;
            double len = sqrt(dx * dx + dy * dy);
            Edge e;
            e.u = A;
            e.v = B;
            e.len = len;
            if (len > 0) { e.ux = dx / len; e.uy = dy / len; }
            else { e.ux = 0; e.uy = 0; }
            edges.push_back(e);
            outEdges[A].push_back(i);
        }
        if (outEdges[S].empty()) {
            if (!firstCase) cout << "\n";
            cout << "Impossible\n";
            firstCase = false;
            continue;
        }
        vector<double> dist(M, INF);
        vector<int> parent(M, -1);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        for (int idx : outEdges[S]) {
            dist[idx] = edges[idx].len;
            parent[idx] = -1;
            pq.push({dist[idx], idx});
        }
        int lastEdge = -1;
        bool found = false;
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            double d = cur.first;
            int eidx = cur.second;
            if (d > dist[eidx] + 1e-12) continue;
            const Edge& curEdge = edges[eidx];
            if (curEdge.v == F) {
                lastEdge = eidx;
                found = true;
                break;
            }
            int v = curEdge.v;
            for (int nxtIdx : outEdges[v]) {
                const Edge& nxtEdge = edges[nxtIdx];
                double turn = k * angleBetween(curEdge, nxtEdge);
                double nd = d + nxtEdge.len + turn;
                if (nd < dist[nxtIdx] - 1e-12) {
                    dist[nxtIdx] = nd;
                    parent[nxtIdx] = eidx;
                    pq.push({nd, nxtIdx});
                }
            }
        }
        if (!firstCase) cout << "\n";
        if (!found) {
            cout << "Impossible\n";
        } else {
            vector<int> pathEdges;
            int e = lastEdge;
            while (e != -1) {
                pathEdges.push_back(e);
                e = parent[e];
            }
            reverse(pathEdges.begin(), pathEdges.end());
            double ans = dist[lastEdge];
            cout << fixed << setprecision(3) << ans << "\n";
            cout << S;
            for (int idx : pathEdges) cout << " " << edges[idx].v;
            cout << "\n";
        }
        firstCase = false;
    }
    return 0;
}
