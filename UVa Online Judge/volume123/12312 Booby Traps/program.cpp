#include <bits/stdc++.h>
using namespace std;

const double Eps = 1e-10;
const int LeafSize = 4;

struct Vec3 {
    double v[3];
    Vec3(double x = 0, double y = 0, double z = 0) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }
    Vec3 operator + (const Vec3 &o) const {
        return Vec3(v[0] + o.v[0], v[1] + o.v[1], v[2] + o.v[2]);
    }
    Vec3 operator - (const Vec3 &o) const {
        return Vec3(v[0] - o.v[0], v[1] - o.v[1], v[2] - o.v[2]);
    }
    Vec3 operator * (double k) const {
        return Vec3(v[0] * k, v[1] * k, v[2] * k);
    }
};

struct Ray {
    Vec3 o, d;
};

struct Tri {
    int a, b, c, id;
    Vec3 mn, mx, cen;
};

struct Node {
    Vec3 mn, mx;
    int l, r, lc, rc;
};

vector<Vec3> points;
vector<Tri> tris;
vector<int> triIds;
vector<Node> nodes;

Vec3 crossVec(const Vec3 &a, const Vec3 &b) {
    return Vec3(a.v[1] * b.v[2] - a.v[2] * b.v[1], a.v[2] * b.v[0] - a.v[0] * b.v[2], a.v[0] * b.v[1] - a.v[1] * b.v[0]);
}

double dotVec(const Vec3 &a, const Vec3 &b) {
    return a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2];
}

int buildTree(int l, int r) {
    int id = (int)nodes.size();
    nodes.push_back(Node());
    nodes[id].l = l;
    nodes[id].r = r;
    nodes[id].lc = -1;
    nodes[id].rc = -1;
    nodes[id].mn = Vec3(1e100, 1e100, 1e100);
    nodes[id].mx = Vec3(-1e100, -1e100, -1e100);
    for (int i = l; i < r; i++) {
        const Tri &tri = tris[triIds[i]];
        for (int k = 0; k < 3; k++) {
            nodes[id].mn.v[k] = min(nodes[id].mn.v[k], tri.mn.v[k]);
            nodes[id].mx.v[k] = max(nodes[id].mx.v[k], tri.mx.v[k]);
        }
    }
    if (r - l <= LeafSize)
        return id;
    int axis = 0;
    if (nodes[id].mx.v[1] - nodes[id].mn.v[1] > nodes[id].mx.v[axis] - nodes[id].mn.v[axis])
        axis = 1;
    if (nodes[id].mx.v[2] - nodes[id].mn.v[2] > nodes[id].mx.v[axis] - nodes[id].mn.v[axis])
        axis = 2;
    int mid = (l + r) / 2;
    nth_element(triIds.begin() + l, triIds.begin() + mid, triIds.begin() + r, [axis](int x, int y) { return tris[x].cen.v[axis] < tris[y].cen.v[axis]; });
    nodes[id].lc = buildTree(l, mid);
    nodes[id].rc = buildTree(mid, r);
    return id;
}

bool boxHit(int id, const Ray &ray, double limit, double &nearT) {
    double left = 0, right = limit, t0, t1, tmp;
    for (int k = 0; k < 3; k++) {
        if (fabs(ray.d.v[k]) < Eps) {
            if (ray.o.v[k] < nodes[id].mn.v[k] - Eps || ray.o.v[k] > nodes[id].mx.v[k] + Eps)
                return false;
            continue;
        }
        t0 = (nodes[id].mn.v[k] - ray.o.v[k]) / ray.d.v[k];
        t1 = (nodes[id].mx.v[k] - ray.o.v[k]) / ray.d.v[k];
        if (t0 > t1) {
            tmp = t0;
            t0 = t1;
            t1 = tmp;
        }
        left = max(left, t0);
        right = min(right, t1);
        if (left > right + Eps)
            return false;
    }
    nearT = left;
    return right >= -Eps;
}

bool hitTri(const Ray &ray, const Tri &tri, double &t) {
    Vec3 e1 = points[tri.b] - points[tri.a], e2 = points[tri.c] - points[tri.a];
    Vec3 p = crossVec(ray.d, e2);
    double det = dotVec(e1, p), invDet, u, v, tt;
    if (fabs(det) < Eps)
        return false;
    invDet = 1.0 / det;
    Vec3 s = ray.o - points[tri.a];
    u = dotVec(s, p) * invDet;
    if (u < -Eps || u > 1.0 + Eps)
        return false;
    Vec3 q = crossVec(s, e1);
    v = dotVec(ray.d, q) * invDet;
    if (v < -Eps || u + v > 1.0 + Eps)
        return false;
    tt = dotVec(e2, q) * invDet;
    if (tt < Eps)
        return false;
    t = tt;
    return true;
}

void walkTree(int id, const Ray &ray, double &best, int &ans) {
    Node &node = nodes[id];
    if (node.lc == -1) {
        for (int i = node.l; i < node.r; i++) {
            const Tri &tri = tris[triIds[i]];
            double t;
            if (hitTri(ray, tri, t) && t < best) {
                best = t;
                ans = tri.id;
            }
        }
        return;
    }
    double leftT, rightT;
    bool hitLeft = boxHit(node.lc, ray, best, leftT);
    bool hitRight = boxHit(node.rc, ray, best, rightT);
    if (hitLeft && hitRight) {
        if (leftT < rightT) {
            walkTree(node.lc, ray, best, ans);
            if (rightT <= best + Eps)
                walkTree(node.rc, ray, best, ans);
        } else {
            walkTree(node.rc, ray, best, ans);
            if (leftT <= best + Eps)
                walkTree(node.lc, ray, best, ans);
        }
    } else if (hitLeft) {
        walkTree(node.lc, ray, best, ans);
    } else if (hitRight) {
        walkTree(node.rc, ray, best, ans);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int p;
    while (cin >> p && p) {
        points.resize(p);
        for (int i = 0; i < p; i++)
            cin >> points[i].v[0] >> points[i].v[1] >> points[i].v[2];
        int t;
        cin >> t;
        tris.resize(t);
        triIds.resize(t);
        for (int i = 0; i < t; i++) {
            cin >> tris[i].a >> tris[i].b >> tris[i].c;
            tris[i].id = i;
            tris[i].mn = Vec3(1e100, 1e100, 1e100);
            tris[i].mx = Vec3(-1e100, -1e100, -1e100);
            for (int k = 0; k < 3; k++) {
                tris[i].mn.v[k] = min(tris[i].mn.v[k], points[tris[i].a].v[k]);
                tris[i].mn.v[k] = min(tris[i].mn.v[k], points[tris[i].b].v[k]);
                tris[i].mn.v[k] = min(tris[i].mn.v[k], points[tris[i].c].v[k]);
                tris[i].mx.v[k] = max(tris[i].mx.v[k], points[tris[i].a].v[k]);
                tris[i].mx.v[k] = max(tris[i].mx.v[k], points[tris[i].b].v[k]);
                tris[i].mx.v[k] = max(tris[i].mx.v[k], points[tris[i].c].v[k]);
            }
            tris[i].cen = (points[tris[i].a] + points[tris[i].b] + points[tris[i].c]) * (1.0 / 3.0);
            triIds[i] = i;
        }
        nodes.clear();
        nodes.reserve(2 * t);
        int root = buildTree(0, t);
        int q;
        cin >> q;
        cout << fixed << setprecision(6);
        for (int i = 0; i < q; i++) {
            Ray ray;
            cin >> ray.o.v[0] >> ray.o.v[1] >> ray.o.v[2] >> ray.d.v[0] >> ray.d.v[1] >> ray.d.v[2];
            ray.d = ray.d - ray.o;
            double best = 1e100, rootT;
            int ans = -1;
            if (boxHit(root, ray, best, rootT))
                walkTree(root, ray, best, ans);
            if (ans == -1) {
                cout << -1 << '\n';
            } else {
                Vec3 hit = ray.o + ray.d * best;
                cout << ans << ' ' << hit.v[0] << ' ' << hit.v[1] << ' ' << hit.v[2] << '\n';
            }
        }
    }
    return 0;
}
