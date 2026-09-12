// The Return of Carl
// UVa ID: 1081
// Verdict: Accepted
// Submission Date: 2026-08-04
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0), EPS = 1e-8, INF = 1e100;
const double EDGE = sqrt(2.0), HEIGHT = sqrt(6.0) / 2.0, SCALE = 10.0 / sqrt(2.0);

struct P3 {
    double x, y, z;
    P3 operator +(const P3& b) const { return {x + b.x, y + b.y, z + b.z}; }
    P3 operator -(const P3& b) const { return {x - b.x, y - b.y, z - b.z}; }
    P3 operator *(double k) const { return {x * k, y * k, z * k}; }
};

struct P2 {
    double x, y;
    P2 operator +(const P2& b) const { return {x + b.x, y + b.y}; }
    P2 operator -(const P2& b) const { return {x - b.x, y - b.y}; }
    P2 operator *(double k) const { return {x * k, y * k}; }
};

using Face = array<int, 3>;

vector<Face> faces;
vector<vector<int>> adj;
vector<int> route;
vector<bool> visited;
double best;

double dot(P3 a, P3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double cross(P2 a, P2 b) {
    return a.x * b.y - a.y * b.x;
}

double norm(P2 a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

// 顶点编号：0(-1,0,0)、1(1,0,0)、2(0,-1,0)、3(0,1,0)、4(0,0,-1)、5(0,0,1)
P3 vertex(int id) {
    int type = id / 2;
    double sign = (id & 1) ? 1.0 : -1.0;
    if (type == 0) return {sign, 0, 0};
    if (type == 1) return {0, sign, 0};
    return {0, 0, sign};
}

// 球面坐标射线与 |x|+|y|+|z|=1 的交点
P3 surfacePoint(int theta, int phi) {
    double t = theta * PI / 180.0, p = phi * PI / 180.0;
    P3 d = {sin(p) * cos(t), sin(p) * sin(t), cos(p)};
    return d * (1.0 / (fabs(d.x) + fabs(d.y) + fabs(d.z)));
}

// 计算点在指定面中的重心坐标
bool barycentric(P3 p, int id, double& a, double& b, double& c) {
    P3 x = vertex(faces[id][0]), y = vertex(faces[id][1]), z = vertex(faces[id][2]);
    P3 normal = x + y + z, u = y - x, v = z - x, w = p - x;
    if (fabs(dot(normal, p) - 1.0) > 1e-7) return false;
    double uu = dot(u, u), uv = dot(u, v), vv = dot(v, v), wu = dot(w, u), wv = dot(w, v);
    double det = uu * vv - uv * uv;
    if (fabs(det) < EPS) return false;
    b = (wu * vv - wv * uv) / det;
    c = (wv * uu - wu * uv) / det;
    a = 1.0 - b - c;
    return a >= -EPS && b >= -EPS && c >= -EPS;
}

vector<int> containingFaces(P3 p) {
    vector<int> result;
    for (int i = 0; i < 8; i++) {
        double a, b, c;
        if (barycentric(p, i, a, b, c)) result.push_back(i);
    }
    return result;
}

// 将三维面内点映射到展开后的二维三角形
P2 mapToPlane(P3 p, int faceId, const array<P2, 3>& pos) {
    double a, b, c;
    barycentric(p, faceId, a, b, c);
    return pos[0] * a + pos[1] * b + pos[2] * c;
}

bool insideTriangle(P2 p, P2 a, P2 b, P2 c) {
    double x = cross(b - a, p - a), y = cross(c - b, p - b), z = cross(a - c, p - c);
    return (x >= -EPS && y >= -EPS && z >= -EPS) || (x <= EPS && y <= EPS && z <= EPS);
}

// 求交点 p+t(q-p) 中的参数 t
bool segmentIntersection(P2 p, P2 q, P2 a, P2 b, double& t) {
    P2 r = q - p, s = b - a;
    double det = cross(r, s);
    if (fabs(det) < EPS) return false;
    t = cross(a - p, s) / det;
    double u = cross(a - p, r) / det;
    return t >= -EPS && t <= 1.0 + EPS && u >= -EPS && u <= 1.0 + EPS;
}

// 将路径中的第 index 个面展开
bool unfold(int index, vector<array<P2, 3>>& pos) {
    if (index == 0) {
        pos[0] = {{{0.0, 0.0}, {EDGE, 0.0}, {EDGE / 2.0, HEIGHT}}};
        return true;
    }
    Face pre = faces[route[index - 1]], cur = faces[route[index]];
    vector<int> common, fresh;
    for (int x : cur) {
        bool found = false;
        for (int y : pre) {
            if (x == y) {
                found = true;
                break;
            }
        }
        if (found) common.push_back(x);
        else fresh.push_back(x);
    }
    if (common.size() != 2 || fresh.size() != 1) return false;
    int uId = common[0], vId = common[1], wId = fresh[0], uIndex = -1, vIndex = -1, oldIndex = -1;
    for (int i = 0; i < 3; i++) {
        if (pre[i] == uId) uIndex = i;
        else if (pre[i] == vId) vIndex = i;
        else oldIndex = i;
    }
    P2 u = pos[index - 1][uIndex], v = pos[index - 1][vIndex], old = pos[index - 1][oldIndex];
    P2 mid = (u + v) * 0.5, dir = v - u, normal = {-dir.y, dir.x};
    P2 c1 = mid + normal * (HEIGHT / EDGE), c2 = mid - normal * (HEIGHT / EDGE), w = c1;
    if (cross(dir, old - u) * cross(dir, c1 - u) >= -EPS) w = c2;
    for (int i = 0; i < 3; i++) {
        if (cur[i] == uId) pos[index][i] = u;
        else if (cur[i] == vId) pos[index][i] = v;
        else pos[index][i] = w;
    }
    return true;
}

// 检查当前面路径展开后是否为合法路径
double evaluate(P3 start, P3 finish) {
    int n = route.size();
    vector<array<P2, 3>> pos(n);
    for (int i = 0; i < n; i++) {
        if (!unfold(i, pos)) return INF;
    }
    P2 s = mapToPlane(start, route.front(), pos.front()), t = mapToPlane(finish, route.back(), pos.back());
    vector<double> cut(n + 1);
    cut[n] = 1.0;
    for (int i = 0; i + 1 < n; i++) {
        Face a = faces[route[i]], b = faces[route[i + 1]];
        vector<int> common;
        for (int x : a) {
            for (int y : b) {
                if (x == y) common.push_back(x);
            }
        }
        if (common.size() != 2) return INF;
        int x = -1, y = -1;
        for (int j = 0; j < 3; j++) {
            if (a[j] == common[0]) x = j;
            if (a[j] == common[1]) y = j;
        }
        double value;
        if (segmentIntersection(s, t, pos[i][x], pos[i][y], value)) {
            if (value < cut[i] - EPS) return INF;
            cut[i + 1] = value;
        } else {
            if (fabs(cross(t - s, pos[i][y] - pos[i][x])) > EPS) return INF;
            cut[i + 1] = cut[i];
        }
    }
    for (int i = 0; i < n; i++) {
        double middle = (cut[i] + cut[i + 1]) * 0.5;
        P2 p = s + (t - s) * middle;
        if (!insideTriangle(p, pos[i][0], pos[i][1], pos[i][2])) return INF;
    }
    return norm(t - s);
}

void dfs(int current, int target, P3 start, P3 finish) {
    if (current == target) {
        best = min(best, evaluate(start, finish));
        return;
    }
    for (int next : adj[current]) {
        if (visited[next]) continue;
        visited[next] = true;
        route.push_back(next);
        dfs(next, target, start, finish);
        route.pop_back();
        visited[next] = false;
    }
}

void buildGraph() {
    for (int sx : {-1, 1}) {
        for (int sy : {-1, 1}) {
            for (int sz : {-1, 1}) {
                faces.push_back({sx == -1 ? 0 : 1, sy == -1 ? 2 : 3, sz == -1 ? 4 : 5});
            }
        }
    }
    adj.assign(8, {});
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            int common = 0;
            for (int x : faces[i]) {
                for (int y : faces[j]) {
                    if (x == y) common++;
                }
            }
            if (common == 2) adj[i].push_back(j), adj[j].push_back(i);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildGraph();
    int theta1, phi1, theta2, phi2, caseId = 1;
    while (cin >> theta1 >> phi1 >> theta2 >> phi2) {
        if (theta1 < 0 && phi1 < 0 && theta2 < 0 && phi2 < 0) break;
        P3 start = surfacePoint(theta1, phi1), finish = surfacePoint(theta2, phi2);
        vector<int> startFaces = containingFaces(start), finishFaces = containingFaces(finish);
        best = INF;
        for (int s : startFaces) {
            for (int t : finishFaces) {
                route.clear();
                visited.assign(8, false);
                route.push_back(s);
                visited[s] = true;
                dfs(s, t, start, finish);
            }
        }
        cout << "Case " << caseId++ << ": " << fixed << setprecision(3) << best * SCALE + 1e-9 << '\n';
    }
    return 0;
}
