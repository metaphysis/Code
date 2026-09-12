#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-10L;

struct Point {
    long double x, y;
};

long double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long double crossVec(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

Point subPoint(Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

Point addPoint(Point a, Point b) {
    return {a.x + b.x, a.y + b.y};
}

Point mulPoint(Point a, long double k) {
    return {a.x * k, a.y * k};
}

int getPointId(vector<Point>& points, Point p) {
    for (int i = 0; i < (int)points.size(); i++)
        if (fabsl(points[i].x - p.x) < eps && fabsl(points[i].y - p.y) < eps)
            return i;
    points.push_back(p);
    return (int)points.size() - 1;
}

bool equalPoint(Point a, Point b) {
    return fabsl(a.x - b.x) < eps && fabsl(a.y - b.y) < eps;
}

long double polygonArea(const vector<int>& face, const vector<Point>& points) {
    long double area = 0;
    int m = face.size();
    for (int i = 0; i < m; i++) {
        Point a = points[face[i]], b = points[face[(i + 1) % m]];
        area += a.x * b.y - a.y * b.x;
    }
    return area / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<Point> origin(n), points;
        vector<vector<pair<long double, int>>> onEdge(n);
        for (int i = 0; i < n; i++) {
            cin >> origin[i].x >> origin[i].y;
            int id = getPointId(points, origin[i]);
            onEdge[i].push_back({0, id});
        }
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            int id = getPointId(points, origin[j]);
            onEdge[i].push_back({1, id});
        }
        for (int i = 0; i < n; i++) {
            int ni = (i + 1) % n;
            Point a = origin[i], b = origin[ni], ab = subPoint(b, a);
            for (int j = i + 1; j < n; j++) {
                int nj = (j + 1) % n;
                Point c = origin[j], d = origin[nj], cd = subPoint(d, c);
                long double den = crossVec(ab, cd);
                if (fabsl(den) < eps) continue;
                Point ca = subPoint(c, a);
                long double t = crossVec(ca, cd) / den;
                long double u = crossVec(ca, ab) / den;
                if (t < -eps || t > 1 + eps || u < -eps || u > 1 + eps) continue;
                Point p = addPoint(a, mulPoint(ab, t));
                int id = getPointId(points, p);
                onEdge[i].push_back({t, id});
                onEdge[j].push_back({u, id});
            }
        }
        set<pair<int, int>> edgeSet;
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; i++) {
            sort(onEdge[i].begin(), onEdge[i].end());
            vector<pair<long double, int>> parts;
            for (auto item : onEdge[i])
                if (parts.empty() || item.second != parts.back().second)
                    parts.push_back(item);
            for (int j = 0; j + 1 < (int)parts.size(); j++) {
                int a = parts[j].second, b = parts[j + 1].second;
                if (a == b) continue;
                if (a > b) swap(a, b);
                if (edgeSet.insert({a, b}).second)
                    edges.push_back({a, b});
            }
        }
        int m = points.size(), e = edges.size();
        vector<vector<int>> out(m);
        vector<int> from(2 * e), to(2 * e), nxt(2 * e);
        for (int i = 0; i < e; i++) {
            int a = edges[i].first, b = edges[i].second;
            from[2 * i] = a;
            to[2 * i] = b;
            from[2 * i + 1] = b;
            to[2 * i + 1] = a;
            out[a].push_back(2 * i);
            out[b].push_back(2 * i + 1);
        }
        for (int i = 0; i < m; i++) {
            sort(out[i].begin(), out[i].end(), [&](int a, int b) {
                Point va = subPoint(points[to[a]], points[from[a]]);
                Point vb = subPoint(points[to[b]], points[from[b]]);
                long double aa = atan2l(va.y, va.x), ab = atan2l(vb.y, vb.x);
                return aa < ab;
            });
        }
        for (int h = 0; h < 2 * e; h++) {
            int v = to[h], rev = h ^ 1;
            int pos = 0;
            while (out[v][pos] != rev) pos++;
            nxt[h] = out[v][(pos - 1 + out[v].size()) % out[v].size()];
        }
        vector<bool> used(2 * e, false);
        vector<vector<int>> faces;
        vector<long double> areas;
        for (int h = 0; h < 2 * e; h++) {
            if (used[h]) continue;
            vector<int> face;
            int cur = h;
            do {
                used[cur] = true;
                face.push_back(from[cur]);
                cur = nxt[cur];
            } while (cur != h);
            faces.push_back(face);
            areas.push_back(polygonArea(face, points));
        }
        int outer = 0;
        for (int i = 1; i < (int)faces.size(); i++)
            if (areas[i] < areas[outer])
                outer = i;
        vector<int> borderId;
        int sz = faces[outer].size();
        borderId.push_back(faces[outer][0]);
        for (int i = 1; i < sz; i++)
            borderId.push_back(faces[outer][sz - i]);
        vector<Point> answer;
        for (int id : borderId)
            answer.push_back(points[id]);
        bool changed = true;
        while (changed && answer.size() >= 3) {
            changed = false;
            int len = answer.size();
            for (int i = 0; i < len; i++) {
                int pre = (i - 1 + len) % len, nex = (i + 1) % len;
                if (equalPoint(answer[pre], answer[i])) {
                    answer.erase(answer.begin() + i);
                    changed = true;
                    break;
                }
                if (fabsl(cross(answer[pre], answer[i], answer[nex])) < eps) {
                    answer.erase(answer.begin() + i);
                    changed = true;
                    break;
                }
            }
        }
        cout << answer.size() << '\n';
        cout << fixed << setprecision(4);
        for (Point p : answer) {
            if (fabsl(p.x) < 0.00005L) p.x = 0;
            if (fabsl(p.y) < 0.00005L) p.y = 0;
            cout << (double)p.x << ' ' << (double)p.y << '\n';
        }
    }
    return 0;
}
