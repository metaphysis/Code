#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;
const double pi = acos(-1.0);

struct Point {
    double x, y;
    Point operator + (const Point &p) const {
        return {x + p.x, y + p.y};
    }
    Point operator - (const Point &p) const {
        return {x - p.x, y - p.y};
    }
    Point operator * (double k) const {
        return {x * k, y * k};
    }
};

struct Interval {
    double l, r;
};

int n, maxRef;
vector<Point> poly;
vector<vector<Interval>> reached;

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double length(Point a) {
    return sqrt(dot(a, a));
}

Point getPoint(int edgeId, double t) {
    Point a = poly[edgeId], b = poly[(edgeId + 1) % n];
    return a + (b - a) * t;
}

Point reflectPoint(Point p, int edgeId) {
    Point a = poly[edgeId], b = poly[(edgeId + 1) % n], e = b - a;
    double t = dot(p - a, e) / dot(e, e);
    Point foot = a + e * t;
    return foot * 2.0 - p;
}

bool raySegmentIntersect(Point s, Point d, Point a, Point b, double &u, double &t) {
    Point e = b - a;
    double den = cross(d, e);
    if (fabs(den) < eps) return false;
    u = cross(a - s, e) / den;
    t = cross(a - s, d) / den;
    return t > -eps && t < 1.0 + eps;
}

int firstHit(Point s, Point d, double minU) {
    int hitEdge = -1;
    double bestU = 1e100;
    for (int i = 0; i < n; i++) {
        double u, t;
        if (!raySegmentIntersect(s, d, poly[i], poly[(i + 1) % n], u, t)) continue;
        if (u > minU + eps && u < bestU) {
            bestU = u;
            hitEdge = i;
        }
    }
    return hitEdge;
}

bool getEdgeParam(Point s, Point d, int edgeId, double &t) {
    double u;
    if (!raySegmentIntersect(s, d, poly[edgeId], poly[(edgeId + 1) % n], u, t)) return false;
    return true;
}

vector<Interval> mergeIntervals(vector<Interval> intervals) {
    vector<Interval> result;
    if (intervals.empty()) return result;
    for (Interval &it : intervals) {
        if (it.l > it.r) swap(it.l, it.r);
        it.l = max(0.0, min(1.0, it.l));
        it.r = max(0.0, min(1.0, it.r));
    }
    sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
        if (fabs(a.l - b.l) > eps) return a.l < b.l;
        return a.r < b.r;
    });
    for (Interval it : intervals) {
        if (it.r - it.l < eps) continue;
        if (result.empty() || it.l > result.back().r + eps) result.push_back(it);
        else result.back().r = max(result.back().r, it.r);
    }
    return result;
}

void addIntervals(int edgeId, const vector<Interval> &intervals) {
    for (Interval it : intervals) reached[edgeId].push_back(it);
}

void traceBeam(int curEdge, Point virtualSource, double left, double right, int remain) {
    vector<double> cuts = {left, right};
    Point a = poly[curEdge], e = poly[(curEdge + 1) % n] - a;
    for (int i = 0; i < n; i++) {
        Point d = poly[i] - virtualSource;
        double den = cross(d, e);
        if (fabs(den) < eps) continue;
        double u = cross(a - virtualSource, e) / den;
        double t = cross(a - virtualSource, d) / den;
        if (u > eps && u < 1.0 + eps && t > left + eps && t < right - eps) cuts.push_back(t);
    }
    sort(cuts.begin(), cuts.end());
    vector<double> uniqueCuts;
    for (double t : cuts)
        if (uniqueCuts.empty() || fabs(t - uniqueCuts.back()) > eps) uniqueCuts.push_back(t);
    vector<vector<Interval>> nextIntervals(n);
    for (int i = 0; i + 1 < (int)uniqueCuts.size(); i++) {
        double l = uniqueCuts[i], r = uniqueCuts[i + 1], mid = (l + r) * 0.5;
        if (r - l < eps) continue;
        Point midPoint = getPoint(curEdge, mid), d = midPoint - virtualSource;
        int nextEdge = firstHit(virtualSource, d, 1.0);
        if (nextEdge == -1) continue;
        Point leftPoint = getPoint(curEdge, l), rightPoint = getPoint(curEdge, r);
        double leftParam, rightParam;
        if (!getEdgeParam(virtualSource, leftPoint - virtualSource, nextEdge, leftParam)) continue;
        if (!getEdgeParam(virtualSource, rightPoint - virtualSource, nextEdge, rightParam)) continue;
        leftParam = max(0.0, min(1.0, leftParam));
        rightParam = max(0.0, min(1.0, rightParam));
        nextIntervals[nextEdge].push_back({min(leftParam, rightParam), max(leftParam, rightParam)});
    }
    for (int edgeId = 0; edgeId < n; edgeId++) {
        vector<Interval> intervals = mergeIntervals(nextIntervals[edgeId]);
        if (intervals.empty()) continue;
        addIntervals(edgeId, intervals);
        if (remain > 1) {
            Point nextSource = reflectPoint(virtualSource, edgeId);
            for (Interval it : intervals) traceBeam(edgeId, nextSource, it.l, it.r, remain - 1);
        }
    }
}

void processDirect(Point source) {
    vector<double> angles;
    for (Point p : poly) {
        double angle = atan2(p.y - source.y, p.x - source.x);
        if (angle < 0.0) angle += 2.0 * pi;
        angles.push_back(angle);
    }
    sort(angles.begin(), angles.end());
    vector<double> uniqueAngles;
    for (double angle : angles)
        if (uniqueAngles.empty() || fabs(angle - uniqueAngles.back()) > eps) uniqueAngles.push_back(angle);
    vector<vector<Interval>> directIntervals(n);
    int angleCount = uniqueAngles.size();
    for (int i = 0; i < angleCount; i++) {
        double leftAngle = uniqueAngles[i], rightAngle = uniqueAngles[(i + 1) % angleCount];
        if (i + 1 == angleCount) rightAngle += 2.0 * pi;
        double midAngle = (leftAngle + rightAngle) * 0.5;
        Point midDir = {cos(midAngle), sin(midAngle)};
        int edgeId = firstHit(source, midDir, 0.0);
        if (edgeId == -1) continue;
        Point leftDir = {cos(leftAngle), sin(leftAngle)}, rightDir = {cos(rightAngle), sin(rightAngle)};
        double leftParam, rightParam;
        if (!getEdgeParam(source, leftDir, edgeId, leftParam)) continue;
        if (!getEdgeParam(source, rightDir, edgeId, rightParam)) continue;
        leftParam = max(0.0, min(1.0, leftParam));
        rightParam = max(0.0, min(1.0, rightParam));
        directIntervals[edgeId].push_back({min(leftParam, rightParam), max(leftParam, rightParam)});
    }
    for (int edgeId = 0; edgeId < n; edgeId++) {
        vector<Interval> intervals = mergeIntervals(directIntervals[edgeId]);
        if (intervals.empty()) continue;
        addIntervals(edgeId, intervals);
        if (maxRef > 0) {
            Point virtualSource = reflectPoint(source, edgeId);
            for (Interval it : intervals) traceBeam(edgeId, virtualSource, it.l, it.r, maxRef);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 0;
    while (cin >> n && n) {
        int stageX, stageY;
        cin >> maxRef >> stageX >> stageY;
        poly.resize(n);
        for (Point &p : poly) cin >> p.x >> p.y;
        reached.assign(n, {});
        processDirect({(double)stageX, (double)stageY});
        double answer = 0.0;
        for (int i = 0; i < n; i++) {
            vector<Interval> intervals = mergeIntervals(reached[i]);
            double ratio = 0.0;
            for (Interval it : intervals) ratio += it.r - it.l;
            answer += ratio * length(poly[(i + 1) % n] - poly[i]);
        }
        if (fabs(answer) < 0.0005) answer = 0.0;
        cout << "Case " << ++caseId << ": " << fixed << setprecision(2) << answer + 1e-9 << '\n';
    }
    return 0;
}
