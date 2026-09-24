#include <bits/stdc++.h>
using namespace std;

using Real = long double;

struct Vec3 {
    Real x, y, z;
    Vec3(Real xVal = 0, Real yVal = 0, Real zVal = 0) : x(xVal), y(yVal), z(zVal) {}
    Vec3 operator+(const Vec3 &other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3 &other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator*(Real scale) const {
        return Vec3(x * scale, y * scale, z * scale);
    }
};

struct Vec2 {
    Real x, y;
};

struct Edge {
    int a, b, faceA, faceB, dirA, dirB;
    Vec3 cut;
};

struct Loop {
    vector<Vec2> points;
    Real area;
    int face;
};

struct Dsu {
    vector<int> parent, sizes;
    Dsu(int n) : parent(n), sizes(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sizes[a] < sizes[b]) swap(a, b);
        parent[b] = a;
        sizes[a] += sizes[b];
    }
};

Real dot(const Vec3 &a, const Vec3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross(const Vec3 &a, const Vec3 &b) {
    return Vec3(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

Real length(const Vec3 &a) {
    return sqrtl(dot(a, a));
}

Real polygonArea(const vector<Vec2> &points) {
    Real area = 0;
    int count = points.size();
    for (int i = 1; i + 1 < count; i++) {
        Real ax = points[i].x - points[0].x, ay = points[i].y - points[0].y;
        Real bx = points[i + 1].x - points[0].x, by = points[i + 1].y - points[0].y;
        area += ax * by - ay * bx;
    }
    return fabsl(area) / 2;
}

bool isInside(const Vec2 &point, const vector<Vec2> &points) {
    bool inside = false;
    int count = points.size();
    for (int i = 0, j = count - 1; i < count; j = i++) {
        const Vec2 &a = points[i], &b = points[j];
        if ((a.y > point.y) != (b.y > point.y)) {
            Real hitX = a.x + (b.x - a.x) * (point.y - a.y) / (b.y - a.y);
            if (hitX > point.x) inside = !inside;
        }
    }
    return inside;
}

void printValues(vector<Real> &values) {
    sort(values.begin(), values.end(), greater<Real>());
    int count = values.size();
    for (int i = 0; i < count; i++) {
        if (i > 0) cout << ' ';
        cout << values[i];
    }
    cout << '\n';
}

void solve(int n, int f, int caseId) {
    vector<Vec3> vertices(n);
    vector<vector<int>> faces(f), faceEdges(f);
    vector<Edge> edges;
    map<pair<int, int>, int> edgeIds;
    for (Vec3 &point : vertices) cin >> point.x >> point.y >> point.z;
    for (int i = 0; i < f; i++) {
        int count;
        cin >> count;
        faces[i].resize(count);
        faceEdges[i].resize(count);
        for (int &vertex : faces[i]) {
            cin >> vertex;
            --vertex;
        }
        for (int j = 0; j < count; j++) {
            int a = faces[i][j], b = faces[i][(j + 1) % count];
            int low = min(a, b), high = max(a, b), direction = a == low ? 1 : -1;
            pair<int, int> key = make_pair(low, high);
            auto it = edgeIds.find(key);
            if (it == edgeIds.end()) {
                int id = edges.size();
                edgeIds[key] = id;
                edges.push_back({low, high, i, -1, direction, 0, Vec3()});
                faceEdges[i][j] = id;
            } else {
                int id = it->second;
                edges[id].faceB = i;
                edges[id].dirB = direction;
                faceEdges[i][j] = id;
            }
        }
    }
    Vec3 p1, p2, p3, p4;
    cin >> p1.x >> p1.y >> p1.z;
    cin >> p2.x >> p2.y >> p2.z;
    cin >> p3.x >> p3.y >> p3.z;
    cin >> p4.x >> p4.y >> p4.z;
    Vec3 normal = cross(p2 - p1, p3 - p1);
    normal = normal * (1 / length(normal));
    if (dot(normal, p4 - p1) < 0) normal = normal * (-1);
    Vec3 axis = fabsl(normal.x) < 0.9L ? Vec3(1, 0, 0) : Vec3(0, 1, 0);
    Vec3 basisX = cross(normal, axis);
    basisX = basisX * (1 / length(basisX));
    Vec3 basisY = cross(normal, basisX);
    vector<Real> dist(n), faceArea(f, 0), faceVolume(f, 0);
    vector<vector<pair<int, int>>> faceAdj(f);
    vector<int> faceSign(f, 0);
    vector<bool> active(f, false);
    Dsu dsu(f);
    for (int i = 0; i < n; i++) dist[i] = dot(normal, vertices[i] - p1);
    for (Edge &edge : edges) {
        int relation = -edge.dirA * edge.dirB;
        faceAdj[edge.faceA].push_back(make_pair(edge.faceB, relation));
        faceAdj[edge.faceB].push_back(make_pair(edge.faceA, relation));
        if (dist[edge.a] < 0 || dist[edge.b] < 0) dsu.unite(edge.faceA, edge.faceB);
        if ((dist[edge.a] < 0) != (dist[edge.b] < 0)) {
            Real ratio = dist[edge.a] / (dist[edge.a] - dist[edge.b]);
            edge.cut = vertices[edge.a] + (vertices[edge.b] - vertices[edge.a]) * ratio;
        }
    }
    for (int i = 0; i < f; i++) if (faceSign[i] == 0) {
        queue<int> pending;
        faceSign[i] = 1;
        pending.push(i);
        while (!pending.empty()) {
            int current = pending.front();
            pending.pop();
            for (const auto &item : faceAdj[current]) if (faceSign[item.first] == 0) {
                faceSign[item.first] = faceSign[current] * item.second;
                pending.push(item.first);
            }
        }
    }
    int edgeCount = edges.size();
    vector<vector<int>> cutAdj(edgeCount);
    for (int i = 0; i < f; i++) {
        vector<Vec3> polygon;
        vector<int> cutIds;
        int count = faces[i].size();
        for (int j = 0; j < count; j++) {
            int a = faces[i][j], b = faces[i][(j + 1) % count], id = faceEdges[i][j];
            if (dist[a] < 0) polygon.push_back(vertices[a]);
            if ((dist[a] < 0) != (dist[b] < 0)) {
                polygon.push_back(edges[id].cut);
                cutIds.push_back(id);
            }
        }
        if (!cutIds.empty()) {
            int a = cutIds[0], b = cutIds[1];
            cutAdj[a].push_back(b);
            cutAdj[b].push_back(a);
        }
        if (polygon.empty()) continue;
        active[i] = true;
        count = polygon.size();
        Vec3 base = polygon[0] - p1;
        for (int j = 1; j + 1 < count; j++) {
            Vec3 a = polygon[j] - polygon[0], b = polygon[j + 1] - polygon[0];
            faceArea[i] += length(cross(a, b)) / 2;
            faceVolume[i] += faceSign[i] * dot(base, cross(a, b)) / 6;
        }
    }
    vector<Loop> loops;
    vector<bool> visited(edgeCount, false);
    for (int i = 0; i < edgeCount; i++) {
        if (cutAdj[i].empty() || visited[i]) continue;
        Loop loop;
        loop.face = edges[i].faceA;
        int previous = -1, current = i, next;
        do {
            visited[current] = true;
            Vec3 offset = edges[current].cut - p1;
            loop.points.push_back({dot(offset, basisX), dot(offset, basisY)});
            next = cutAdj[current][0] == previous ? cutAdj[current][1] : cutAdj[current][0];
            previous = current;
            current = next;
        } while (current != i);
        loop.area = polygonArea(loop.points);
        loops.push_back(move(loop));
    }
    int loopCount = loops.size();
    vector<int> parent(loopCount, -1), depth(loopCount, 0);
    vector<Real> regionArea(loopCount, 0);
    for (int i = 0; i < loopCount; i++) {
        Real bestArea = numeric_limits<Real>::max();
        for (int j = 0; j < loopCount; j++) if (loops[j].area > loops[i].area && loops[j].area < bestArea) {
            if (!isInside(loops[i].points[0], loops[j].points)) continue;
            parent[i] = j;
            bestArea = loops[j].area;
        }
    }
    for (int i = 0; i < loopCount; i++) {
        int current = parent[i];
        while (current != -1) {
            ++depth[i];
            current = parent[current];
        }
        if (depth[i] % 2 == 0) regionArea[i] = loops[i].area;
    }
    for (int i = 0; i < loopCount; i++) if (depth[i] % 2 == 1) {
        int outer = parent[i];
        regionArea[outer] -= loops[i].area;
        dsu.unite(loops[i].face, loops[outer].face);
    }
    vector<Real> solidArea(f, 0), solidVolume(f, 0), areas, volumes, sections;
    for (int i = 0; i < f; i++) if (active[i]) {
        int root = dsu.find(i);
        solidArea[root] += faceArea[i];
        solidVolume[root] += faceVolume[i];
    }
    for (int i = 0; i < loopCount; i++) if (depth[i] % 2 == 0) {
        int root = dsu.find(loops[i].face);
        solidArea[root] += regionArea[i];
        sections.push_back(regionArea[i]);
    }
    for (int i = 0; i < f; i++) if (active[i] && dsu.find(i) == i) {
        areas.push_back(solidArea[i]);
        volumes.push_back(fabsl(solidVolume[i]));
    }
    cout << "Case " << caseId << ":\n";
    cout << volumes.size() << '\n';
    printValues(volumes);
    printValues(areas);
    cout << sections.size() << '\n';
    printValues(sections);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(3);
    int n, f, caseId = 0;
    while (cin >> n >> f) solve(n, f, ++caseId);
    return 0;
}
