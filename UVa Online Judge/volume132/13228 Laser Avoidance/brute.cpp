// 文件名: brute.cpp
// 编译: g++ -O3 brute.cpp -o brute
// 复杂度: O(V^2 * N) 建图 + O(V^2) Dijkstra，适用于 N <= 300 的精确暴力对拍
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

const double INF = 1e18;
const double PI = acos(-1.0);

struct Pt {
    double x, y;
};

inline double cross(Pt a, Pt b) { return a.x * b.y - a.y * b.x; }
inline double cross(Pt o, Pt a, Pt b) { return cross({a.x - o.x, a.y - o.y}, {b.x - o.x, b.y - o.y}); }
inline double dist(Pt a, Pt b) { return hypot(a.x - b.x, a.y - b.y); }

struct Laser {
    Pt o, d;
    double angle;
};

// 严格检验线段 A-B 是否与射线 (O, D) 相交（射线从 O + D * t_min 开始）
bool seg_intersects_ray(Pt A, Pt B, Pt O, Pt D) {
    Pt seg = {B.x - A.x, B.y - A.y};
    double denom = cross(D, seg);
    Pt AO = {A.x - O.x, A.y - O.y};

    if (fabs(denom) < 1e-12) {
        // 平行或共线：检查线段是否落在射线上
        if (fabs(cross(AO, D)) > 1e-9) return false;
        double tA = (A.x - O.x) * D.x + (A.y - O.y) * D.y;
        double tB = (B.x - O.x) * D.x + (B.y - O.y) * D.y;
        return max(tA, tB) > 1e-9;
    }

    double t = cross(AO, seg) / denom;
    double s = cross(AO, D) / denom;

    // t >= 0 表示在射线正向；s in [0, 1] 表示在线段 A-B 上
    if (t >= -1e-11 && s >= -1e-9 && s <= 1.0 + 1e-9) {
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    double p, q;
    while (cin >> n >> p >> q) {
        Pt S = {0.0, 0.0}, T = {p, q};
        vector<Laser> lasers(n);
        for (int i = 0; i < n; ++i) {
            double x, y, th;
            cin >> x >> y >> th;
            lasers[i] = {{x, y}, {cos(th), sin(th)}, th};
        }

        // 1. 合并重合的激光源点
        vector<Pt> unique_orgs;
        vector<vector<double>> org_angles;
        for (int i = 0; i < n; ++i) {
            int found = -1;
            for (size_t j = 0; j < unique_orgs.size(); ++j) {
                if (dist(lasers[i].o, unique_orgs[j]) < 1e-7) {
                    found = j;
                    break;
                }
            }
            if (found == -1) {
                unique_orgs.push_back(lasers[i].o);
                org_angles.push_back({lasers[i].angle});
            } else {
                org_angles[found].push_back(lasers[i].angle);
            }
        }

        // 2. 构建图顶点：
        // 节点 0 是起点 S，节点 1 是终点 T。
        // 对于每个唯一源点 O，收集它发出的所有射线角度并排序。
        // 在相邻两条射线的扇区角平分线方向（如果是单条射线，则在它的正背面 theta + PI 以及左右两侧 theta +/- PI/2）
        // 距离源点 R = 1e-7 处放置“微距绕行顶点”。
        // 这样既能紧贴源点 O 绕过（距离误差 < 1e-7），又能利用射线本身天然阻断任何跨过射线的非法连线！
        vector<Pt> nodes;
        nodes.push_back(S);
        nodes.push_back(T);

        const double R = 1e-7;
        for (size_t i = 0; i < unique_orgs.size(); ++i) {
            Pt O = unique_orgs[i];
            auto& angs = org_angles[i];
            for (double& a : angs) {
                a = atan2(sin(a), cos(a)); // 归一化到 [-PI, PI]
            }
            sort(angs.begin(), angs.end());

            // 在每两个相邻射线夹角之间插入 3 个微距探针点（25%, 50%, 75% 分位角），确保进入和离开该扇区的凸转弯畅通无阻
            int m = angs.size();
            for (int j = 0; j < m; ++j) {
                double a1 = angs[j];
                double a2 = (j + 1 < m) ? angs[j + 1] : (angs[0] + 2.0 * PI);
                double gap = a2 - a1;
                if (gap < 1e-6) continue; // 重合射线跳过

                int steps = (m == 1) ? 8 : 3;
                for (int k = 1; k <= steps; ++k) {
                    double mid_a = a1 + gap * ((double)k / (steps + 1));
                    nodes.push_back({O.x + R * cos(mid_a), O.y + R * sin(mid_a)});
                }
            }
        }

        int V = nodes.size();
        vector<vector<pair<int, double>>> adj(V);

        // 3. 暴力检查所有点对 (u, v) 之间是否可见（不与任何一条激光射线相交）
        for (int u = 0; u < V; ++u) {
            for (int v = u + 1; v < V; ++v) {
                bool ok = true;
                for (int k = 0; k < n; ++k) {
                    if (seg_intersects_ray(nodes[u], nodes[v], lasers[k].o, lasers[k].d)) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    double w = dist(nodes[u], nodes[v]);
                    adj[u].push_back({v, w});
                    adj[v].push_back({u, w});
                }
            }
        }

        // 4. 标准 Dijkstra 求最短路
        vector<double> d(V, INF);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        d[0] = 0.0;
        pq.push({0.0, 0});

        while (!pq.empty()) {
            auto [du, u] = pq.top();
            pq.pop();
            if (du > d[u] + 1e-12) continue;
            if (u == 1) break;
            for (auto& [v, w] : adj[u]) {
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    pq.push({d[v], v});
                }
            }
        }

        cout << fixed << setprecision(5) << d[1] << "\n";
    }
    return 0;
}
