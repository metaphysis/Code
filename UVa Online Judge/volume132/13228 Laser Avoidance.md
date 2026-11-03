
> **摘要**：本文讨论一道计算几何难题：在平面直角坐标系中，从原点出发到达终点 $(p,q)$，平面上分布着若干激光器，每个激光器沿给定角度发射一条无限长的单向射线，要求找出一条不被任何射线击中且长度最短的路径。由于障碍是延伸到无穷远的射线，可见性图规模可能爆炸，最优路径甚至可能包含成千上万个折点，传统做法难以奏效。文章指出，挖去射线后每个自由连通区域都是简单连通的，因此只需在正确的同伦类中保持路径局部拉紧即可得到全局最优解。基于这一观察，作者采用「增量收紧」的橡皮筋算法：用双向链表维护路径，发现射线与路径相交时插入发夹结构并标记该射线为强制，随后反复删除非约束顶点、借助 $\texttt{kd}$ 树处理三角形内部源点并构造凸包链完成局部拉紧，直至一次完整扫描无相交为止。实现层面引入 $\texttt{BVH}$ 加速射线与路径求交、违规池优先检查、路径长度下界剪枝以及动态 $\texttt{AABB}$ 树定位相交边等优化，最终将时间复杂度控制在 $O(n \log n)$、空间复杂度控制在 $O(n)$，并给出完整可运行的 $\texttt{C++}$ 代码。

## 题目描述

在平面直角坐标系中，起点位于 $(0,0)$，终点为 $(p,q)$。平面上有若干激光器，每个激光器位于点 $(x,y)$，沿与 $x$ 轴正方向夹角为 $\theta$ 的方向发射一条无限长的单向射线。求一条从起点到终点且不被任何射线击中的最短路径，输出该路径的长度。

## 输入格式

输入包含若干组测试数据，组数小于 $100$。每组数据的第一行包含三个整数 $n$、$p$、$q$，其中 $n$ 为激光器总数，$(p,q)$ 为终点坐标。随后 $n$ 行，每行包含两个整数 $x$、$y$ 与一个实数 $\theta$，描述一个激光器的位置与发射角度。数据满足 $0 \le n, p, |q|, |x|, |y| \le 10^6$，且 $\theta \in [-\pi, \pi)$。

## 输出格式

对每组测试数据输出一行，输出最短路径长度，保留 $5$ 位小数。

## 样例输入

```
3 5 5
2 1 1
3 1 2
4 1 -1.5
3 5 0
5 2 1
5 2 2
5 2 -1.5
```

## 样例输出

```
7.63441
5.00000
```

## 题目分析

每个激光器等价于一条从源点 $O=(x,y)$ 出发、方向向量为 $d=(\cos\theta,\sin\theta)$ 的半直线，即一条无限延伸的射线。路径可以经过某个源点，但不能穿过从该源点射出的射线。由于所有障碍都是延伸到无穷远的射线，把平面挖去这些射线后，每一个自由连通区域都是简单连通的。因此，只要一条路径在正确的同伦类中是局部拉紧的，它就已经是该同伦类中的全局最短路径。基于这一观察，本题无需构建可见性图，因为可见性图的规模可能非常大，最优路径可能含有成千上万个折点。正确做法是直接维护一条路径并不断把它拉紧。

## 解题思路

核心思想是增量收紧，即橡皮筋算法。把起点记为 $S$，终点记为 $T$，当前路径用双向链表维护，链表中每个结点是路径上的一个折点。

步骤 $\texttt{1}$. 初始化。令路径为连接 $S$ 与 $T$ 的直线段，强制射线集合为空。

步骤 $\texttt{2}$. 查找相交射线。若某条尚未被强制的射线在点 $X$ 处穿过路径中的边 $a \to c$，则将该射线标记为强制，并在路径中插入发夹结构 $a \to X \to O \to X \to c$，其中 $O$ 是该射线的源点。

步骤 $\texttt{3}$. 收紧路径。把受影响的部分放入工作队列，反复删除非约束顶点。发夹中的两个 $X$ 副本是自由顶点，可以直接删去；一个激光源点顶点只有当该源点的某条强制射线指向删去该折点时会被扫过的楔形区域时才保留，此时该源点是约束顶点。

步骤 $\texttt{4}$. 处理三角形内部的源点。删去 $u$ 与 $w$ 之间的非约束顶点 $v$ 时，还必须避开其他强制射线。由于 $u \to v$ 与 $v \to w$ 已经不与任何射线相交，任何会阻挡捷径 $u \to w$ 的强制射线，其源点必然落在三角形 $u v w$ 内部。用 $\texttt{kd}$ 树查出这些源点，再把这些源点按极角排序并构造相应的凸包链，用凸包链替换顶点 $v$，从而在保持路径可行的同时得到局部最短的路径。

步骤 $\texttt{5}$. 循环终止。反复执行上述操作，直到一次完整扫描发现没有任何射线与路径相交。此时路径对所有射线都可行，并且是对当前强制射线子集的最短路径，因此也是完整输入下的全局最短路径。

在实现上做如下优化。用 $\texttt{BVH}$ 对路径线段建立层次包围盒，加速射线与路径的求交。把已经相交过的射线放入违规池，在两次完整扫描之间优先检查违规池。对每条射线预处理下界 $e=\min_{X}(|S-X|+|X-T|)$，其中 $X$ 取遍射线上的点，若 $e$ 大于当前路径长度，则该射线不可能与路径相交，按 $e$ 从小到大排序后可显著减少完整扫描次数。$\texttt{kd}$ 树中维护活跃射线计数，便于跳过不含任何强制射线的子树。再使用一棵动态 $\texttt{AABB}$ 树快速定位当前相交的边。

每条射线至多被强制一次，路径折点总数与强制射线数量同阶，所有求交、三角形查询与凸包构造的总代价均为 $O(n \log n)$ 级别，因此时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。

## 代码实现

```cpp
// Laser Avoidance
// UVa ID: 13228
// Verdict: Accepted
// Submission Date: 2026-11-02
// UVa Run Time: 1.770s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <cstdio>

using namespace std;

// Fast buffered input: reads integers and reals much faster than iostream.
namespace FastIO {
    static const int BUFSIZE = 1 << 21;
    static char buf[BUFSIZE];
    static int pos = 0, len = 0;

    inline char gc() {
        if (pos >= len) {
            len = (int)fread(buf, 1, BUFSIZE, stdin);
            pos = 0;
            if (len <= 0) return 0;
        }
        return buf[pos++];
    }

    inline char skipWs() {
        char c = gc();
        while (c && c <= ' ') c = gc();
        return c;
    }

    inline bool readInt(int& out) {
        char c = skipWs();
        if (!c) return false;
        int sign = 1;
        if (c == '-') { sign = -1; c = gc(); }
        else if (c == '+') c = gc();
        int x = 0;
        while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
        out = sign * x;
        return true;
    }

    inline bool readDouble(double& out) {
        char c = skipWs();
        if (!c) return false;
        int sign = 1;
        if (c == '-') { sign = -1; c = gc(); }
        else if (c == '+') c = gc();
        long long ip = 0;
        while (c >= '0' && c <= '9') { ip = ip * 10 + (c - '0'); c = gc(); }
        double x = (double)ip;
        if (c == '.') {
            c = gc();
            long long fp = 0, sc = 1;
            while (c >= '0' && c <= '9') { fp = fp * 10 + (c - '0'); sc *= 10; c = gc(); }
            x += (double)fp / (double)sc;
        }
        if (c == 'e' || c == 'E') {
            c = gc();
            int es = 1;
            if (c == '-') { es = -1; c = gc(); }
            else if (c == '+') c = gc();
            int e = 0;
            while (c >= '0' && c <= '9') { e = e * 10 + (c - '0'); c = gc(); }
            int a = es * e;
            double m = 1.0;
            if (a > 0) { for (int i = 0; i < a; ++i) m *= 10.0; }
            else { for (int i = 0; i < -a; ++i) m *= 0.1; }
            x *= m;
        }
        out = sign * x;
        return true;
    }
}

const double EPS = 1e-9;
const double INF = 1e18;

struct Pt {
    double x, y;
    Pt(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
    inline Pt operator+(const Pt& b) const { return Pt(x + b.x, y + b.y); }
    inline Pt operator-(const Pt& b) const { return Pt(x - b.x, y - b.y); }
    inline Pt operator*(double k) const { return Pt(x * k, y * k); }
};

inline double dot(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }
inline double cross(Pt a, Pt b) { return (double)((long double)a.x * b.y - (long double)a.y * b.x); }
inline double cross(Pt o, Pt a, Pt b) { return cross(a - o, b - o); }
inline double dist_sq(Pt a, Pt b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
inline double dist(Pt a, Pt b) { return hypot(a.x - b.x, a.y - b.y); }

struct BBox {
    double x1, x2, y1, y2;
    BBox(double a = INF, double b = -INF, double c = INF, double d = -INF) : x1(a), x2(b), y1(c), y2(d) {}
    inline void expand(const BBox& b) {
        x1 = min(x1, b.x1); x2 = max(x2, b.x2);
        y1 = min(y1, b.y1); y2 = max(y2, b.y2);
    }
    inline double perim() const { return (x2 - x1) + (y2 - y1); }
};

inline BBox merge_box(const BBox& a, const BBox& b) {
    return BBox(min(a.x1, b.x1), max(a.x2, b.x2), min(a.y1, b.y1), max(a.y2, b.y2));
}

struct Node;

struct Laser {
    int id, oid;
    Pt o, d, inv_d;
    double min_d;
    bool enf, in_pool;
    Node* saved;
    Laser() : id(0), oid(-1), min_d(0), enf(false), in_pool(false), saved(nullptr) {}
};

struct Origin {
    int id, act, kd_idx;
    Pt pt;
    vector<int> lids;
    Origin(int _id = 0, Pt _pt = Pt()) : id(_id), act(0), kd_idx(-1), pt(_pt) {}
};

struct Node {
    Pt pt;
    int oid, leaf;
    Node *prev, *next;
    bool in_q, alive;
    double len;
    Node(Pt _pt = Pt(), int _oid = -1)
        : pt(_pt), oid(_oid), leaf(-1), prev(nullptr), next(nullptr), in_q(false), alive(true), len(0.0) {}
};

struct KDNode {
    int oid, act, l, r, p;
    Pt pt;
    BBox box;
    KDNode() : oid(-1), act(0), l(-1), r(-1), p(-1) {}
};

struct KDTree {
    vector<KDNode> tr;
    vector<Origin>* orgs = nullptr;

    void init(vector<Origin>& o) {
        orgs = &o;
        tr.clear();
        if (o.empty()) return;
        vector<int> ids(o.size());
        for (size_t i = 0; i < o.size(); ++i) ids[i] = i;
        tr.resize(o.size());
        int idx = 0;
        build(ids, 0, o.size(), 0, -1, idx);
    }

    int build(vector<int>& ids, int l, int r, int dep, int p, int& idx) {
        if (l >= r) return -1;
        int m = l + (r - l) / 2, ax = dep & 1;
        nth_element(ids.begin() + l, ids.begin() + m, ids.begin() + r, [&](int a, int b) {
            Pt pa = (*orgs)[a].pt, pb = (*orgs)[b].pt;
            return ax == 0 ? (pa.x != pb.x ? pa.x < pb.x : pa.y < pb.y)
                           : (pa.y != pb.y ? pa.y < pb.y : pa.x < pb.x);
        });
        int c = idx++, oid = ids[m];
        (*orgs)[oid].kd_idx = c;
        Pt pt = (*orgs)[oid].pt;
        tr[c].oid = oid; tr[c].pt = pt;
        tr[c].box = BBox(pt.x, pt.x, pt.y, pt.y);
        tr[c].act = 0; tr[c].p = p;
        tr[c].l = build(ids, l, m, dep + 1, c, idx);
        tr[c].r = build(ids, m + 1, r, dep + 1, c, idx);
        if (tr[c].l != -1) tr[c].box.expand(tr[tr[c].l].box);
        if (tr[c].r != -1) tr[c].box.expand(tr[tr[c].r].box);
        return c;
    }

    inline void activate(int oid) {
        if ((*orgs)[oid].act == 0) {
            for (int c = (*orgs)[oid].kd_idx; c != -1; c = tr[c].p) tr[c].act++;
        }
        (*orgs)[oid].act++;
    }

    void query(Pt u, Pt v, Pt w, int iu, int iv, int iw, vector<int>& out) {
        if (tr.empty() || tr[0].act == 0) return;
        BBox tb(min({u.x, v.x, w.x}) - 1e-7, max({u.x, v.x, w.x}) + 1e-7,
                min({u.y, v.y, w.y}) - 1e-7, max({u.y, v.y, w.y}) + 1e-7);
        q_rec(0, u, v, w, iu, iv, iw, cross(u, v, w), tb, out);
    }

    void q_rec(int c, Pt u, Pt v, Pt w, int iu, int iv, int iw, double ori, const BBox& tb, vector<int>& out) {
        if (c == -1 || tr[c].act == 0) return;
        const BBox& cb = tr[c].box;
        if (cb.x2 < tb.x1 || cb.x1 > tb.x2 || cb.y2 < tb.y1 || cb.y1 > tb.y2) return;
        int oid = tr[c].oid;
        if ((*orgs)[oid].act > 0 && oid != iu && oid != iv && oid != iw) {
            Pt p = tr[c].pt;
            if (p.x >= tb.x1 && p.x <= tb.x2 && p.y >= tb.y1 && p.y <= tb.y2) {
                if (dist_sq(p, u) > 1e-16 && dist_sq(p, v) > 1e-16 && dist_sq(p, w) > 1e-16) {
                    double c1 = cross(u, v, p), c2 = cross(v, w, p), c3 = cross(w, u, p);
                    if (ori > 0 ? (c1 >= -1e-7 && c2 >= -1e-7 && c3 >= -1e-7)
                                : (c1 <= 1e-7 && c2 <= 1e-7 && c3 <= 1e-7)) out.push_back(oid);
                }
            }
        }
        q_rec(tr[c].l, u, v, w, iu, iv, iw, ori, tb, out);
        q_rec(tr[c].r, u, v, w, iu, iv, iw, ori, tb, out);
    }
};

struct BVHNode {
    BBox box;
    Node* seg = nullptr;
    int p = -1, l = -1, r = -1, h = 0;
    inline bool is_leaf() const { return l == -1; }
};

struct DynamicBVH {
    vector<BVHNode> nds;
    vector<int> fl;
    int root = -1;

    void clear() { nds.clear(); fl.clear(); root = -1; }

    int alloc() {
        if (!fl.empty()) { int id = fl.back(); fl.pop_back(); nds[id] = BVHNode(); return id; }
        nds.push_back(BVHNode());
        return (int)nds.size() - 1;
    }

    int insert(Node* u) {
        int lf = alloc();
        Pt a = u->pt, b = u->next->pt;
        nds[lf].box = BBox(min(a.x, b.x) - 1e-7, max(a.x, b.x) + 1e-7,
                           min(a.y, b.y) - 1e-7, max(a.y, b.y) + 1e-7);
        nds[lf].seg = u;
        if (root == -1) return root = lf;

        int idx = root;
        while (!nds[idx].is_leaf()) {
            int l = nds[idx].l, r = nds[idx].r;
            double area = nds[idx].box.perim();
            double comb = merge_box(nds[idx].box, nds[lf].box).perim();
            double cost = 2.0 * comb, inh = 2.0 * (comb - area);
            auto calc = [&](int ch) {
                double m = merge_box(nds[lf].box, nds[ch].box).perim();
                return nds[ch].is_leaf() ? m + inh : (m - nds[ch].box.perim()) + inh;
            };
            double cl = calc(l), cr = calc(r);
            if (cost < cl && cost < cr) break;
            idx = (cl < cr) ? l : r;
        }

        int op = nds[idx].p, np = alloc();
        nds[np].p = op;
        nds[np].box = merge_box(nds[lf].box, nds[idx].box);
        nds[np].h = nds[idx].h + 1;
        if (op != -1) (nds[op].l == idx ? nds[op].l : nds[op].r) = np;
        else root = np;
        nds[np].l = idx; nds[np].r = lf;
        nds[idx].p = nds[lf].p = np;
        sync(np);
        return lf;
    }

    void remove(int lf) {
        if (lf == -1) return;
        if (lf == root) { root = -1; fl.push_back(lf); return; }
        int p = nds[lf].p, gp = nds[p].p;
        int sib = (nds[p].l == lf) ? nds[p].r : nds[p].l;
        if (gp != -1) {
            (nds[gp].l == p ? nds[gp].l : nds[gp].r) = sib;
            nds[sib].p = gp;
            fl.push_back(p);
            sync(gp);
        } else {
            root = sib; nds[sib].p = -1; fl.push_back(p);
        }
        fl.push_back(lf);
    }

    inline bool hit_box(const Laser& ray, const BBox& b, double max_t) const {
        double tmin = 0.0, tmax = max_t;
        if (ray.inv_d.x != 0.0) {
            double t1 = (b.x1 - ray.o.x) * ray.inv_d.x, t2 = (b.x2 - ray.o.x) * ray.inv_d.x;
            if (t1 > t2) swap(t1, t2);
            tmin = max(tmin, t1); tmax = min(tmax, t2);
            if (tmin > tmax) return false;
        } else if (ray.o.x < b.x1 || ray.o.x > b.x2) return false;

        if (ray.inv_d.y != 0.0) {
            double t1 = (b.y1 - ray.o.y) * ray.inv_d.y, t2 = (b.y2 - ray.o.y) * ray.inv_d.y;
            if (t1 > t2) swap(t1, t2);
            tmin = max(tmin, t1); tmax = min(tmax, t2);
            if (tmin > tmax) return false;
        } else if (ray.o.y < b.y1 || ray.o.y > b.y2) return false;
        return true;
    }

    inline bool hit_seg(const Laser& ray, Node* u, double& ot, Pt& op) const {
        Node* v = u->next;
        if (u->oid == ray.oid || v->oid == ray.oid) return false;
        Pt A = u->pt, B = v->pt;
        if (dist_sq(A, ray.o) < 1e-14 || dist_sq(B, ray.o) < 1e-14) return false;
        Pt sd = B - A;
        double den = cross(ray.d, sd);
        if (fabs(den) < 1e-12) return false;
        Pt AO = A - ray.o;
        double t = cross(AO, sd) / den;
        if (t <= 1e-9) return false;
        double s = cross(AO, ray.d) / den;
        if (s >= -1e-7 && s <= 1.0 + 1e-7) {
            ot = t; op = A + sd * max(0.0, min(1.0, s));
            return true;
        }
        return false;
    }

    bool find_hit(const Laser& ray, Node*& he, Pt& hp) const {
        if (root == -1) return false;
        double bt = INF; he = nullptr;
        if (ray.saved && ray.saved->alive && ray.saved->leaf != -1) {
            double t; Pt pt;
            if (hit_seg(ray, ray.saved, t, pt)) { bt = t; he = ray.saved; hp = pt; }
        }
        if (!hit_box(ray, nds[root].box, bt)) return he != nullptr;

        static int st[512];
        int top = 0; st[top++] = root;
        while (top > 0) {
            int c = st[--top];
            if (nds[c].is_leaf()) {
                if (nds[c].seg == ray.saved) continue;
                double t; Pt pt;
                if (hit_seg(ray, nds[c].seg, t, pt) && t < bt) { bt = t; he = nds[c].seg; hp = pt; }
            } else {
                int l = nds[c].l, r = nds[c].r;
                bool hl = hit_box(ray, nds[l].box, bt), hr = hit_box(ray, nds[r].box, bt);
                if (hl && hr) {
                    Pt cl((nds[l].box.x1 + nds[l].box.x2) * 0.5, (nds[l].box.y1 + nds[l].box.y2) * 0.5);
                    Pt cr((nds[r].box.x1 + nds[r].box.x2) * 0.5, (nds[r].box.y1 + nds[r].box.y2) * 0.5);
                    if (dist_sq(ray.o, cl) < dist_sq(ray.o, cr)) { st[top++] = r; st[top++] = l; }
                    else { st[top++] = l; st[top++] = r; }
                } else if (hl) st[top++] = l;
                else if (hr) st[top++] = r;
            }
        }
        return he != nullptr;
    }

    int balance(int A) {
        if (nds[A].is_leaf() || nds[A].h < 2) return A;
        int B = nds[A].l, C = nds[A].r, bal = nds[C].h - nds[B].h;
        if (bal > 1 || bal < -1) {
            int X = (bal > 1) ? C : B, Y = (bal > 1) ? B : C;
            int F = nds[X].l, G = nds[X].r;
            nds[X].l = A; nds[X].p = nds[A].p; nds[A].p = X;
            if (nds[X].p != -1) (nds[nds[X].p].l == A ? nds[nds[X].p].l : nds[nds[X].p].r) = X;
            else root = X;
            if (nds[F].h < nds[G].h) swap(F, G);
            nds[X].r = F;
            if (bal > 1) nds[A].r = G; else nds[A].l = G;
            nds[G].p = A;
            nds[A].box = merge_box(nds[Y].box, nds[G].box);
            nds[X].box = merge_box(nds[A].box, nds[F].box);
            nds[A].h = 1 + max(nds[Y].h, nds[G].h);
            nds[X].h = 1 + max(nds[A].h, nds[F].h);
            return X;
        }
        return A;
    }

    void sync(int idx) {
        while (idx != -1) {
            idx = balance(idx);
            int l = nds[idx].l, r = nds[idx].r;
            nds[idx].h = 1 + max(nds[l].h, nds[r].h);
            nds[idx].box = merge_box(nds[l].box, nds[r].box);
            idx = nds[idx].p;
        }
    }
};

class LaserSolver {
    int n;
    Pt S, T;
    vector<Laser> ls;
    vector<Origin> orgs;
    KDTree kdt;
    DynamicBVH bvh;
    queue<Node*> q;
    deque<Node> pool;
    double cur_len = 0.0;

    Node* new_nd(Pt pt, int oid) { pool.emplace_back(pt, oid); return &pool.back(); }
    inline void push_q(Node* nd) {
        if (nd && nd->alive && nd->prev && nd->next && !nd->in_q) { nd->in_q = true; q.push(nd); }
    }
    inline void add_e(Node* u, Node* v) {
        u->next = v; v->prev = u; u->len = dist(u->pt, v->pt);
        cur_len += u->len; u->leaf = bvh.insert(u);
    }
    inline void rem_e(Node* u) {
        if (u->leaf != -1) { bvh.remove(u->leaf); u->leaf = -1; cur_len -= u->len; u->len = 0.0; }
    }

    double min_st(Pt O, Pt D) {
        Pt OS = S - O, OT = T - O;
        double uS = dot(OS, D), vS = fabs(cross(D, OS)), uT = dot(OT, D), vT = fabs(cross(D, OT));
        double t = (vS + vT > 1e-12) ? (vS * uT + vT * uS) / (vS + vT) : 0.5 * (uS + uT);
        Pt X = O + D * max(0.0, t);
        return dist(S, X) + dist(X, T);
    }

    bool binding(Node* v) {
        if (!v->prev || !v->next) return true;
        if (v->oid == -1 || (v->prev->oid != -1 && v->prev->oid == v->next->oid)) return false;
        Pt u = v->prev->pt, o = v->pt, w = v->next->pt;
        Pt du = u - o, dw = w - o;
        double lu = hypot(du.x, du.y), lw = hypot(dw.x, dw.y);
        if (lu < 1e-12 || lw < 1e-12) return false;
        Pt duu = {du.x / lu, du.y / lu}, dww = {dw.x / lw, dw.y / lw};
        double ctn = cross(duu, dww);
        const double tol = 1e-9;
        if (fabs(ctn) < tol) return false;
        for (int lid : orgs[v->oid].lids) {
            Pt d = ls[lid].d;
            double c1 = cross(duu, d), c2 = cross(d, dww);
            if (ctn > 0 ? (c1 >= -tol && c2 >= -tol) : (c1 <= tol && c2 <= tol)) return true;
        }
        return false;
    }

    void shortcut(Node* v) {
        Node *u = v->prev, *w = v->next;
        rem_e(u); rem_e(v); v->alive = false;
        if ((u->oid != -1 && u->oid == w->oid) || dist_sq(u->pt, w->pt) < 1e-16) {
            if (u->oid == -1 && w->oid != -1) u->oid = w->oid;
            if (w->next) {
                Node* wn = w->next; rem_e(w); w->alive = false;
                add_e(u, wn); push_q(u); push_q(wn);
            } else if (u->prev) {
                Node* up = u->prev; rem_e(up); u->alive = false;
                add_e(up, w); push_q(up);
            } else add_e(u, w);
            return;
        }
        double ori = cross(u->pt, v->pt, w->pt);
        vector<int> in_oids;
        if (fabs(ori) >= 1e-11) kdt.query(u->pt, v->pt, w->pt, u->oid, v->oid, w->oid, in_oids);
        if (in_oids.empty()) { add_e(u, w); push_q(u); push_q(w); return; }

        Pt upt = u->pt;
        sort(in_oids.begin(), in_oids.end(), [&](int a, int b) {
            if (a == b) return false;
            Pt pa = orgs[a].pt, pb = orgs[b].pt;
            long double cr = (long double)(pa.x - upt.x) * (pb.y - upt.y) - (long double)(pa.y - upt.y) * (pb.x - upt.x);
            if (cr != 0) return (ori > 0) ? (cr > 0) : (cr < 0);
            return dist_sq(upt, pa) < dist_sq(upt, pb);
        });

        vector<pair<Pt, int>> hull = {{u->pt, u->oid}};
        auto bad = [&](Pt a, Pt b, Pt c) {
            double cr = cross(a, b, c);
            return (ori > 0) ? (cr <= 1e-11) : (cr >= -1e-11);
        };
        for (int oid : in_oids) {
            Pt p = orgs[oid].pt;
            while (hull.size() >= 2 && bad(hull[hull.size() - 2].first, hull.back().first, p)) hull.pop_back();
            hull.push_back({p, oid});
        }
        while (hull.size() >= 2 && bad(hull[hull.size() - 2].first, hull.back().first, w->pt)) hull.pop_back();

        Node* cur = u;
        for (size_t i = 1; i < hull.size(); ++i) {
            Node* nd = new_nd(hull[i].first, hull[i].second);
            add_e(cur, nd); push_q(cur); cur = nd;
        }
        add_e(cur, w); push_q(cur); push_q(w);
    }

    void tighten() {
        while (!q.empty()) {
            Node* v = q.front(); q.pop(); v->in_q = false;
            if (v->alive && v->prev && v->next && !binding(v)) shortcut(v);
        }
    }

    void hairpin(Node* a, Pt X, const Laser& ray) {
        Node* c = a->next;
        if (dist_sq(X, a->pt) < 1e-14 && a->prev) {
            rem_e(a);
            Node *o = new_nd(ray.o, ray.oid), *a2 = new_nd(a->pt, a->oid);
            add_e(a, o); add_e(o, a2); add_e(a2, c);
            push_q(a); push_q(o); push_q(a2); push_q(c); return;
        }
        if (dist_sq(X, c->pt) < 1e-14 && c->next) {
            rem_e(a);
            Node *c1 = new_nd(c->pt, c->oid), *o = new_nd(ray.o, ray.oid);
            add_e(a, c1); add_e(c1, o); add_e(o, c);
            push_q(a); push_q(c1); push_q(o); push_q(c); return;
        }
        rem_e(a);
        Node *x1 = new_nd(X, -1), *o = new_nd(ray.o, ray.oid), *x2 = new_nd(X, -1);
        add_e(a, x1); add_e(x1, o); add_e(o, x2); add_e(x2, c);
        push_q(a); push_q(x1); push_q(o); push_q(x2); push_q(c);
    }

public:
    void solve(int num_l, Pt sp, Pt ep, vector<Laser>& raw_l) {
        n = num_l; S = sp; T = ep; ls.swap(raw_l); pool.clear();
        for (int i = 0; i < n; ++i) {
            ls[i].min_d = min_st(ls[i].o, ls[i].d);
            ls[i].inv_d.x = (fabs(ls[i].d.x) > 1e-12) ? (1.0 / ls[i].d.x) : 0.0;
            ls[i].inv_d.y = (fabs(ls[i].d.y) > 1e-12) ? (1.0 / ls[i].d.y) : 0.0;
        }
        sort(ls.begin(), ls.end(), [](const Laser& a, const Laser& b) { return a.min_d < b.min_d; });
        for (int i = 0; i < n; ++i) ls[i].id = i;

        vector<pair<Pt, int>> s_pts(n);
        for (int i = 0; i < n; ++i) s_pts[i] = {ls[i].o, i};
        sort(s_pts.begin(), s_pts.end(), [](const pair<Pt, int>& a, const pair<Pt, int>& b) {
            return fabs(a.first.x - b.first.x) > EPS ? a.first.x < b.first.x : a.first.y < b.first.y - EPS;
        });

        orgs.clear();
        for (int i = 0; i < n; ++i) {
            if (orgs.empty() || dist_sq(orgs.back().pt, s_pts[i].first) > EPS * EPS)
                orgs.push_back(Origin((int)orgs.size(), s_pts[i].first));
            ls[s_pts[i].second].oid = orgs.back().id;
        }

        kdt.init(orgs); bvh.clear(); cur_len = 0.0;
        Node *head = new_nd(S, -1), *tail = new_nd(T, -1);
        for (const auto& o : orgs) {
            if (dist_sq(o.pt, S) < EPS * EPS) head->oid = o.id;
            if (dist_sq(o.pt, T) < EPS * EPS) tail->oid = o.id;
        }
        add_e(head, tail);

        vector<int> pool_l;
        int ptr = 0;
        auto advance_ptr = [&]() {
            while (ptr < n && ls[ptr].min_d <= cur_len + 1e-6) {
                Node* he = nullptr; Pt X;
                if (bvh.find_hit(ls[ptr], he, X)) {
                    ls[ptr].saved = he; ls[ptr].in_pool = true; pool_l.push_back(ptr);
                }
                ptr++;
            }
        };

        while (true) {
            advance_ptr();
            if (!pool_l.empty()) {
                while (!pool_l.empty()) {
                    int idx = pool_l.back(); pool_l.pop_back();
                    ls[idx].in_pool = false;
                    if (ls[idx].enf) continue;
                    Node* he = nullptr; Pt X;
                    if (bvh.find_hit(ls[idx], he, X)) {
                        ls[idx].enf = true;
                        int oid = ls[idx].oid;
                        orgs[oid].lids.push_back(idx);
                        kdt.activate(oid);
                        hairpin(he, X, ls[idx]);
                        tighten();
                        advance_ptr();
                    }
                }
                continue;
            }
            cur_len = 0.0;
            for (Node* c = head; c && c->next; c = c->next) cur_len += dist(c->pt, c->next->pt);
            advance_ptr();
            for (int i = 0; i < ptr; ++i) {
                if (ls[i].enf || ls[i].in_pool) continue;
                Node* he = nullptr; Pt X;
                if (bvh.find_hit(ls[i], he, X)) {
                    ls[i].saved = he; ls[i].in_pool = true; pool_l.push_back(i);
                }
            }
            if (pool_l.empty()) break;
        }

        double ans = 0.0;
        for (Node* c = head; c && c->next; c = c->next) ans += dist(c->pt, c->next->pt);
        cout << fixed << setprecision(5) << ans << "\n";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    int n; double p, q, x, y, th;
    LaserSolver solver;
    while (FastIO::readInt(n)) {
        FastIO::readDouble(p);
        FastIO::readDouble(q);
        vector<Laser> ls(n);
        for (int i = 0; i < n; ++i) {
            FastIO::readDouble(x);
            FastIO::readDouble(y);
            FastIO::readDouble(th);
            ls[i].id = i; ls[i].o = Pt(x, y); ls[i].d = Pt(cos(th), sin(th));
        }
        solver.solve(n, Pt(0.0, 0.0), Pt(p, q), ls);
    }
    return 0;
}

```

## 总结

本题的关键点在于把射线障碍的几何性质转化为同伦类中的局部拉紧条件，并用增量收紧替代可见性图，从而避免边数爆炸。实现中引入 $\texttt{BVH}$、$\texttt{kd}$ 树、动态 $\texttt{AABB}$ 树以及路径长度下界剪枝等数据结构与技巧，在保证正确性的同时把时间复杂度控制在 $O(n \log n)$，空间复杂度控制在 $O(n)$。
