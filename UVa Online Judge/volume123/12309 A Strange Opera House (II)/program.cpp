#include <bits/stdc++.h>
using namespace std;

using Ld = long double;

const Ld eps = 1e-10L, areaEps = 1e-12L;

struct Point {
    Ld x, y;
    Point operator+(const Point &p) const {
        return {x + p.x, y + p.y};
    }

    Point operator-(const Point &p) const {
        return {x - p.x, y - p.y};
    }

    Point operator*(Ld t) const {
        return {x * t, y * t};
    }

    Point operator/(Ld t) const {
        return {x / t, y / t};
    }
};

Ld cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

Ld dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

struct Line {
    Point p, d;
    Ld value(Point q) const {
        return cross(d, q - p);
    }
};

struct Triangle {
    int v[3], adj[3], adjEdge[3];
    vector<vector<Point>> rest;
};

vector<Point> vertex;
vector<Triangle> triangles;
int activeCnt;

Ld polyArea(const vector<Point> &poly) {
    Ld sum = 0;
    int size = (int)poly.size();
    for (int i = 0; i < size; i++) sum += cross(poly[i], poly[(i + 1) % size]);
    return fabsl(sum) / 2;
}

bool inTriangle(Point p, Point a, Point b, Point c) {
    return cross(b - a, p - a) >= -eps &&
           cross(c - b, p - b) >= -eps &&
           cross(a - c, p - c) >= -eps;
}

vector<Point> clipPoly(const vector<Point> &poly, const Line &line) {
    vector<Point> result;
    int size = (int)poly.size();
    if (size == 0) return result;
    for (int i = 0; i < size; i++) {
        Point a = poly[i], b = poly[(i + 1) % size];
        Ld da = line.value(a), db = line.value(b);
        bool inA = da >= 0, inB = db >= 0;
        if (inA) result.push_back(a);
        if (inA != inB) result.push_back(a + (b - a) * (da / (da - db)));
    }
    return result;
}

bool clipSegment(Point &a, Point &b, const Line &line) {
    Ld da = line.value(a), db = line.value(b);
    Point hit;
    if (da < 0 && db < 0) return false;
    if (da >= 0 && db >= 0) return true;
    hit = a + (b - a) * (da / (da - db));
    if (da < 0) a = hit;
    else b = hit;
    return true;
}

void addPiece(vector<vector<Point>> &pieces, vector<Point> poly) {
    if (poly.size() >= 3 && polyArea(poly) > areaEps) pieces.push_back(move(poly));
}

void coverTriangle(int triId, const Line &firstLine, const Line &secondLine) {
    vector<vector<Point>> nextRest;
    vector<Point> firstPart, hitPart;
    Line firstOpp = {firstLine.p, firstLine.d * -1};
    Line secondOpp = {secondLine.p, secondLine.d * -1};
    if (triangles[triId].rest.empty()) return;
    for (const auto &poly : triangles[triId].rest) {
        firstPart = clipPoly(poly, firstLine);
        hitPart = clipPoly(firstPart, secondLine);
        if (polyArea(hitPart) <= areaEps) {
            nextRest.push_back(poly);
            continue;
        }
        addPiece(nextRest, clipPoly(poly, firstOpp));
        addPiece(nextRest, clipPoly(firstPart, secondOpp));
    }
    triangles[triId].rest.swap(nextRest);
    if (triangles[triId].rest.empty()) activeCnt--;
}

Point reflectPoint(Point source, Point a, Point b) {
    Point dir = b - a, foot = a + dir * (dot(source - a, dir) / dot(dir, dir));
    return foot * 2 - source;
}

void sendBeam(int triId, int edgeId, Point source, Point a, Point b, int leftCnt);

void traceBeam(int triId, int entryId, Point source, Point a, Point b, int leftCnt) {
    Point rayA, rayB;
    Line firstLine, secondLine;
    if (activeCnt == 0) return;
    if (cross(a - source, b - source) < 0) swap(a, b);
    rayA = a - source;
    rayB = source - b;
    if (dot(rayA, rayA) <= eps * eps || dot(rayB, rayB) <= eps * eps) return;
    if (cross(a - source, b - source) == 0) return;
    firstLine = {source, rayA / sqrtl(dot(rayA, rayA))};
    secondLine = {source, rayB / sqrtl(dot(rayB, rayB))};
    coverTriangle(triId, firstLine, secondLine);
    if (activeCnt == 0) return;
    for (int edgeId = 0; edgeId < 3; edgeId++) {
        Point p, q;
        if (edgeId == entryId) continue;
        p = vertex[triangles[triId].v[edgeId]];
        q = vertex[triangles[triId].v[(edgeId + 1) % 3]];
        if (!clipSegment(p, q, firstLine)) continue;
        if (!clipSegment(p, q, secondLine)) continue;
        if (dot(q - p, q - p) <= eps * eps) continue;
        sendBeam(triId, edgeId, source, p, q, leftCnt);
        if (activeCnt == 0) return;
    }
}

void sendBeam(int triId, int edgeId, Point source, Point a, Point b, int leftCnt) {
    int nextId = triangles[triId].adj[edgeId];
    Point wallA, wallB, nextSource;
    if (activeCnt == 0) return;
    if (nextId != -1) {
        traceBeam(nextId, triangles[triId].adjEdge[edgeId], source, a, b, leftCnt);
    } else if (leftCnt > 0) {
        wallA = vertex[triangles[triId].v[edgeId]];
        wallB = vertex[triangles[triId].v[(edgeId + 1) % 3]];
        nextSource = reflectPoint(source, wallA, wallB);
        traceBeam(triId, edgeId, nextSource, a, b, leftCnt - 1);
    }
}

void addTriangle(int a, int b, int c) {
    Triangle tri;
    tri.v[0] = a;
    tri.v[1] = b;
    tri.v[2] = c;
    for (int i = 0; i < 3; i++) {
        tri.adj[i] = -1;
        tri.adjEdge[i] = -1;
    }
    tri.rest.push_back({vertex[a], vertex[b], vertex[c]});
    triangles.push_back(move(tri));
}

void buildTriangles() {
    int size = (int)vertex.size(), triCnt;
    vector<int> ids(size);
    triangles.clear();
    iota(ids.begin(), ids.end(), 0);
    while (ids.size() > 3) {
        int curSize = (int)ids.size();
        for (int i = 0; i < curSize; i++) {
            int a = ids[(i + curSize - 1) % curSize], b = ids[i], c = ids[(i + 1) % curSize];
            bool isEar = true;
            if (cross(vertex[b] - vertex[a], vertex[c] - vertex[b]) <= 0) continue;
            for (int j = 0; j < curSize; j++) {
                int p = ids[j];
                if (p == a || p == b || p == c) continue;
                if (inTriangle(vertex[p], vertex[a], vertex[b], vertex[c])) {
                    isEar = false;
                    break;
                }
            }
            if (!isEar) continue;
            addTriangle(a, b, c);
            ids.erase(ids.begin() + i);
            break;
        }
    }
    addTriangle(ids[0], ids[1], ids[2]);
    triCnt = (int)triangles.size();
    for (int i = 0; i < triCnt; i++) {
        for (int j = i + 1; j < triCnt; j++) {
            for (int a = 0; a < 3; a++) {
                for (int b = 0; b < 3; b++) {
                    if (triangles[i].v[a] == triangles[j].v[(b + 1) % 3] &&
                        triangles[i].v[(a + 1) % 3] == triangles[j].v[b]) {
                        triangles[i].adj[a] = j;
                        triangles[i].adjEdge[a] = b;
                        triangles[j].adj[b] = i;
                        triangles[j].adjEdge[b] = a;
                    }
                }
            }
        }
    }
    activeCnt = triCnt;
}

void normalizePolygon() {
    bool changed = true;
    Ld signedArea = 0;
    int size;
    while (changed && vertex.size() > 3) {
        changed = false;
        size = (int)vertex.size();
        for (int i = 0; i < size; i++) {
            Point a = vertex[(i + size - 1) % size], b = vertex[i], c = vertex[(i + 1) % size];
            if (cross(b - a, c - b) == 0) {
                vertex.erase(vertex.begin() + i);
                changed = true;
                break;
            }
        }
    }
    size = (int)vertex.size();
    for (int i = 0; i < size; i++) signedArea += cross(vertex[i], vertex[(i + 1) % size]);
    if (signedArea < 0) reverse(vertex.begin(), vertex.end());
}

Ld solve(Point source, int maxCnt) {
    Ld totalArea = polyArea(vertex), remainArea = 0;
    vector<int> starts;
    int triCnt;
    buildTriangles();
    triCnt = (int)triangles.size();
    for (int i = 0; i < triCnt; i++) {
        Point a = vertex[triangles[i].v[0]], b = vertex[triangles[i].v[1]], c = vertex[triangles[i].v[2]];
        if (inTriangle(source, a, b, c)) starts.push_back(i);
    }
    // 声源可能位于内部对角线上，需要同时从两侧出发
    for (int triId : starts) {
        triangles[triId].rest.clear();
        activeCnt--;
    }
    for (int limit = 0; limit <= maxCnt && activeCnt > 0; limit++) {
        for (int triId : starts) {
            for (int edgeId = 0; edgeId < 3; edgeId++) {
                Point a = vertex[triangles[triId].v[edgeId]], b = vertex[triangles[triId].v[(edgeId + 1) % 3]];
                if (fabsl(cross(b - a, source - a)) <= eps) continue;
                sendBeam(triId, edgeId, source, a, b, limit);
                if (activeCnt == 0) break;
            }
            if (activeCnt == 0) break;
        }
    }
    for (const auto &tri : triangles) {
        for (const auto &poly : tri.rest) remainArea += polyArea(poly);
    }
    return max(0.0L, totalArea - remainArea);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    Point source;
    cout << fixed << setprecision(2);
    while (cin >> n && n != 0) {
        cin >> k >> source.x >> source.y;
        vertex.resize(n);
        for (int i = 0; i < n; i++) cin >> vertex[i].x >> vertex[i].y;
        normalizePolygon();
        cout << solve(source, k) << '\n';
    }
    return 0;
}
