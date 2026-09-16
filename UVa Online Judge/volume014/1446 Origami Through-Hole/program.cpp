#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

struct Point {
    double x, y;
    Point operator + (const Point &other) const {
        return {x + other.x, y + other.y};
    }
    Point operator - (const Point &other) const {
        return {x - other.x, y - other.y};
    }
    Point operator * (double rate) const {
        return {x * rate, y * rate};
    }
    Point operator / (double rate) const {
        return {x / rate, y / rate};
    }
};

struct Vertex {
    Point pos, src;
};

struct Facet {
    vector<Vertex> vertices;
};

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double length(Point a) {
    return sqrt(dot(a, a));
}

double lineDist(Point p, Point mid, Point normal) {
    return dot(p - mid, normal);
}

Vertex interpolate(const Vertex &a, const Vertex &b, double rate) {
    return {a.pos + (b.pos - a.pos) * rate, a.src + (b.src - a.src) * rate};
}

Facet clipFacet(const Facet &facet, Point mid, Point normal, int side) {
    Facet result;
    int n = facet.vertices.size();
    for (int i = 0; i < n; i++) {
        const Vertex &a = facet.vertices[i], &b = facet.vertices[(i + 1) % n];
        double da = side * lineDist(a.pos, mid, normal);
        double db = side * lineDist(b.pos, mid, normal);
        bool inA = da >= -eps, inB = db >= -eps;
        if (inA) result.vertices.push_back(a);
        if (inA != inB) result.vertices.push_back(interpolate(a, b, da / (da - db)));
    }
    vector<Vertex> cleaned;
    for (const Vertex &vertex : result.vertices) {
        if (cleaned.empty() || length(vertex.pos - cleaned.back().pos) > eps) cleaned.push_back(vertex);
    }
    if (cleaned.size() > 1 && length(cleaned.front().pos - cleaned.back().pos) <= eps) cleaned.pop_back();
    if (cleaned.size() < 3) cleaned.clear();
    result.vertices.swap(cleaned);
    return result;
}

bool containsPoint(const Facet &facet, Point p) {
    int n = facet.vertices.size();
    for (int i = 0; i < n; i++) {
        Point a = facet.vertices[i].pos, b = facet.vertices[(i + 1) % n].pos;
        if (cross(b - a, p - a) < -eps * length(b - a)) return false;
    }
    return true;
}

bool hasSeparatingAxis(const Facet &a, const Facet &b) {
    int n = a.vertices.size();
    for (int i = 0; i < n; i++) {
        Point start = a.vertices[i].pos;
        Point edge = a.vertices[(i + 1) % n].pos - start;
        double edgeLen = length(edge), maxDist = -numeric_limits<double>::max();
        for (const Vertex &vertex : b.vertices) maxDist = max(maxDist, cross(edge, vertex.pos - start));
        if (maxDist <= eps * edgeLen) return true;
    }
    return false;
}

bool isOverlap(const Facet &a, const Facet &b) {
    return !hasSeparatingAxis(a, b) && !hasSeparatingAxis(b, a);
}

bool hasMovingHinge(const Facet &a, const Facet &b, Point mid, Point normal) {
    int n = a.vertices.size(), m = b.vertices.size();
    for (int i = 0; i < n; i++) {
        const Vertex &aStart = a.vertices[i], &aEnd = a.vertices[(i + 1) % n];
        Point edge = aEnd.src - aStart.src;
        double edgeLen = length(edge);
        if (edgeLen <= eps) continue;
        Point unit = edge / edgeLen;
        for (int j = 0; j < m; j++) {
            Point bStart = b.vertices[j].src, bEnd = b.vertices[(j + 1) % m].src;
            double distA = abs(cross(unit, bStart - aStart.src));
            double distB = abs(cross(unit, bEnd - aStart.src));
            if (distA > eps || distB > eps) continue;
            double projA = dot(bStart - aStart.src, unit);
            double projB = dot(bEnd - aStart.src, unit);
            double left = max(0.0, min(projA, projB));
            double right = min(edgeLen, max(projA, projB));
            if (right - left <= eps) continue;
            Point hingeStart = aStart.pos + (aEnd.pos - aStart.pos) * (left / edgeLen);
            Point hingeEnd = aStart.pos + (aEnd.pos - aStart.pos) * (right / edgeLen);
            if (abs(lineDist(hingeStart, mid, normal)) > eps || abs(lineDist(hingeEnd, mid, normal)) > eps) return true;
        }
    }
    return false;
}

void reflectFacet(Facet &facet, Point mid, Point normal) {
    for (Vertex &vertex : facet.vertices) vertex.pos = vertex.pos - normal * (2.0 * lineDist(vertex.pos, mid, normal));
    reverse(facet.vertices.begin(), facet.vertices.end());
}

void processFold(vector<Facet> &facets, Point p, Point q) {
    Point mid = (p + q) / 2.0, normal = p - q;
    normal = normal / length(normal);
    vector<Facet> parts;
    for (const Facet &facet : facets) {
        Facet posPart = clipFacet(facet, mid, normal, 1);
        Facet negPart = clipFacet(facet, mid, normal, -1);
        if (!posPart.vertices.empty()) parts.push_back(move(posPart));
        if (!negPart.vertices.empty()) parts.push_back(move(negPart));
    }
    int n = parts.size(), top = -1;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        if (containsPoint(parts[i], p)) top = i;
        for (int j = i + 1; j < n; j++) {
            if (hasMovingHinge(parts[i], parts[j], mid, normal)) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            } else if (isOverlap(parts[i], parts[j])) graph[i].push_back(j);
        }
    }
    vector<char> moved(n, 0);
    queue<int> bfs;
    moved[top] = 1;
    bfs.push(top);
    while (!bfs.empty()) {
        int u = bfs.front();
        bfs.pop();
        for (int v : graph[u]) {
            if (moved[v]) continue;
            moved[v] = 1;
            bfs.push(v);
        }
    }
    vector<Facet> result;
    result.reserve(n);
    for (int i = 0; i < n; i++) {
        if (!moved[i]) result.push_back(move(parts[i]));
    }
    for (int i = n - 1; i >= 0; i--) {
        if (moved[i]) {
            reflectFacet(parts[i], mid, normal);
            result.push_back(move(parts[i]));
        }
    }
    facets.swap(result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    while (cin >> k && k) {
        Facet initial;
        initial.vertices = {
            {{0, 0}, {0, 0}},
            {{100, 0}, {100, 0}},
            {{100, 100}, {100, 100}},
            {{0, 100}, {0, 100}}
        };
        vector<Facet> facets(1, initial);
        for (int i = 0; i < k; i++) {
            Point p, q;
            cin >> p.x >> p.y >> q.x >> q.y;
            processFold(facets, p, q);
        }
        Point hole;
        cin >> hole.x >> hole.y;
        int answer = 0;
        for (const Facet &facet : facets) {
            if (containsPoint(facet, hole)) answer++;
        }
        cout << answer << '\n';
    }
    return 0;
}
