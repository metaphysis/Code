// Hide and Seek
// UVa ID: 12675
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.250s
// https://blog.csdn.net/metaphysis/article/details/163218186

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

struct Point {
    long long x, y;
};

static inline long long cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

static inline bool segmentIntersect(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
    if (min(p1.x, p2.x) > max(q1.x, q2.x) || max(p1.x, p2.x) < min(q1.x, q2.x) ||
        min(p1.y, p2.y) > max(q1.y, q2.y) || max(p1.y, p2.y) < min(q1.y, q2.y))
        return false;
    long long d1 = cross(p1, p2, q1);
    long long d2 = cross(p1, p2, q2);
    long long d3 = cross(q1, q2, p1);
    long long d4 = cross(q1, q2, p2);
    return ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
           ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int S, K, W;
    while (cin >> S >> K >> W) {
        vector<Point> kids(K);
        for (int i = 0; i < K; ++i) cin >> kids[i].x >> kids[i].y;
        vector<pair<Point, Point>> walls(W);
        for (int i = 0; i < W; ++i)
            cin >> walls[i].first.x >> walls[i].first.y >> walls[i].second.x >> walls[i].second.y;
        for (int s = 0; s < S; ++s) {
            Point P = kids[s];
            vector<Point> others;
            for (int i = 0; i < K; ++i) if (i != s) others.push_back(kids[i]);
            int M = (int)others.size();
            vector<double> ang(M);
            for (int i = 0; i < M; ++i) {
                ang[i] = atan2((double)(others[i].y - P.y), (double)(others[i].x - P.x));
                if (ang[i] < 0) ang[i] += 2 * PI;
            }
            vector<int> order(M);
            iota(order.begin(), order.end(), 0);
            sort(order.begin(), order.end(), [&](int a, int b) { return ang[a] < ang[b]; });
            vector<double> sortedAng(M);
            vector<Point> sortedPoints(M);
            for (int i = 0; i < M; ++i) {
                sortedAng[i] = ang[order[i]];
                sortedPoints[i] = others[order[i]];
            }
            vector<bool> visible(M, true);
            int blocked = 0;
            vector<int> wallOrder(W);
            iota(wallOrder.begin(), wallOrder.end(), 0);
            sort(wallOrder.begin(), wallOrder.end(), [&](int a, int b) {
                auto dist2 = [&](int idx) {
                    long long dx1 = walls[idx].first.x - P.x, dy1 = walls[idx].first.y - P.y;
                    long long dx2 = walls[idx].second.x - P.x, dy2 = walls[idx].second.y - P.y;
                    return min(dx1 * dx1 + dy1 * dy1, dx2 * dx2 + dy2 * dy2);
                };
                return dist2(a) < dist2(b);
            });
            for (int wid : wallOrder) {
                if (blocked == M) break;
                Point A = walls[wid].first, B = walls[wid].second;
                double angA = atan2((double)(A.y - P.y), (double)(A.x - P.x));
                if (angA < 0) angA += 2 * PI;
                double angB = atan2((double)(B.y - P.y), (double)(B.x - P.x));
                if (angB < 0) angB += 2 * PI;
                double diff = angB - angA;
                if (diff < 0) diff += 2 * PI;
                if (diff > PI) {
                    swap(angA, angB);
                    diff = 2 * PI - diff;
                }
                auto processRange = [&](double left, double right) {
                    if (left > right) return;
                    int l = lower_bound(sortedAng.begin(), sortedAng.end(), left) - sortedAng.begin();
                    int r = upper_bound(sortedAng.begin(), sortedAng.end(), right) - sortedAng.begin();
                    for (int i = l; i < r; ++i) {
                        if (!visible[i]) continue;
                        if (segmentIntersect(P, sortedPoints[i], walls[wid].first, walls[wid].second)) {
                            visible[i] = false;
                            ++blocked;
                        }
                    }
                };
                if (angA <= angB) processRange(angA, angB);
                else {
                    processRange(angA, 2 * PI);
                    processRange(0, angB);
                }
            }
            cout << M - blocked << "\n";
        }
    }
    return 0;
}
