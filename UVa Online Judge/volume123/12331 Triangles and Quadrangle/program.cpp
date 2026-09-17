#include <bits/stdc++.h>
using namespace std;

struct IntPoint {
    long long x, y;
};

struct FloatPoint {
    long double x, y;
};

long long getCross(const IntPoint &a, const IntPoint &b, const IntPoint &c) {
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}

long long getDist2(const IntPoint &a, const IntPoint &b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

array<long long, 3> getIntSides(const IntPoint &a, const IntPoint &b, const IntPoint &c) {
    array<long long, 3> sides = {getDist2(a, b), getDist2(a, c), getDist2(b, c)};
    sort(sides.begin(), sides.end());
    return sides;
}

long double getDist2(const FloatPoint &a, const FloatPoint &b) {
    long double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

array<long double, 3> getFloatSides(const FloatPoint &a, const FloatPoint &b, const FloatPoint &c) {
    array<long double, 3> sides = {getDist2(a, b), getDist2(a, c), getDist2(b, c)};
    sort(sides.begin(), sides.end());
    return sides;
}

FloatPoint toFloatPoint(const IntPoint &p) {
    return {(long double)p.x, (long double)p.y};
}

bool sameFloat(long double a, long double b) {
    long double scale = max(1.0L, max(fabsl(a), fabsl(b)));
    return fabsl(a - b) <= 1e-10L * scale;
}

bool sameFloatTriangle(const array<long double, 3> &a, const array<long double, 3> &b) {
    for (int i = 0; i < 3; i++)
        if (!sameFloat(a[i], b[i])) return false;
    return true;
}

bool checkIntPair(const array<long long, 3> &a, const array<long long, 3> &b, const array<long long, 3> &triA, const array<long long, 3> &triB) {
    return (a == triA && b == triB) || (a == triB && b == triA);
}

bool checkFloatPair(const array<long double, 3> &a, const array<long double, 3> &b, const array<long double, 3> &triA, const array<long double, 3> &triB) {
    return (sameFloatTriangle(a, triA) && sameFloatTriangle(b, triB)) || (sameFloatTriangle(a, triB) && sameFloatTriangle(b, triA));
}

bool getIntersection(const IntPoint &a, const IntPoint &b, const IntPoint &c, const IntPoint &d, FloatPoint &p) {
    long double a1 = b.y - a.y, b1 = a.x - b.x, c1 = a1 * a.x + b1 * a.y;
    long double a2 = d.y - c.y, b2 = c.x - d.x, c2 = a2 * c.x + b2 * c.y;
    long double det = a1 * b2 - a2 * b1;
    if (det == 0) return false;
    p.x = (c1 * b2 - c2 * b1) / det;
    p.y = (a1 * c2 - a2 * c1) / det;
    return true;
}

bool checkConvex(const IntPoint quad[4], const array<long long, 3> &triA, const array<long long, 3> &triB) {
    array<long long, 3> partA, partB;
    partA = getIntSides(quad[0], quad[1], quad[2]);
    partB = getIntSides(quad[0], quad[2], quad[3]);
    if (checkIntPair(partA, partB, triA, triB)) return true;
    partA = getIntSides(quad[1], quad[2], quad[3]);
    partB = getIntSides(quad[1], quad[3], quad[0]);
    return checkIntPair(partA, partB, triA, triB);
}

bool checkConcave(const IntPoint quad[4], int concaveId, const array<long long, 3> &triA, const array<long long, 3> &triB) {
    IntPoint p[4];
    FloatPoint a, b, c, d, e, f;
    array<long long, 3> partA, partB;
    array<long double, 3> floatTriA, floatTriB;
    for (int i = 0; i < 4; i++) p[i] = quad[(concaveId + i) % 4];
    partA = getIntSides(p[0], p[1], p[2]);
    partB = getIntSides(p[0], p[2], p[3]);
    if (checkIntPair(partA, partB, triA, triB)) return true;
    for (int i = 0; i < 3; i++) {
        floatTriA[i] = triA[i];
        floatTriB[i] = triB[i];
    }
    a = toFloatPoint(p[0]);
    b = toFloatPoint(p[1]);
    c = toFloatPoint(p[2]);
    d = toFloatPoint(p[3]);
    if (getIntersection(p[0], p[1], p[2], p[3], e)) {
        array<long double, 3> first = getFloatSides(a, d, e), second = getFloatSides(b, c, e);
        if (checkFloatPair(first, second, floatTriA, floatTriB)) return true;
    }
    if (getIntersection(p[0], p[3], p[1], p[2], f)) {
        array<long double, 3> first = getFloatSides(a, b, f), second = getFloatSides(c, d, f);
        if (checkFloatPair(first, second, floatTriA, floatTriB)) return true;
    }
    return false;
}

bool checkLengthSum(long long x2, long long y2, long long z2) {
    __int128 diff, left, right;
    if (z2 <= x2 + y2) return false;
    diff = (__int128)z2 - x2 - y2;
    left = diff * diff;
    right = (__int128)4 * x2 * y2;
    return left == right;
}

bool checkSupplementary(long long c2, long long x2, long long a2, long long y2, long long b2) {
    __int128 valueA = (__int128)c2 + x2 - a2, valueB = (__int128)c2 + y2 - b2;
    __int128 left, right;
    if (valueA * valueB > 0) return false;
    left = valueA * valueA * y2;
    right = valueB * valueB * x2;
    return left == right;
}

bool checkDegenerateOrder(const array<long long, 3> &first, const array<long long, 3> &second, long long fixedFirst, long long fixedSecond, long long base) {
    for (int i = 0; i < 3; i++) {
        if (first[i] != fixedFirst) continue;
        for (int j = 0; j < 3; j++) {
            if (second[j] != fixedSecond) continue;
            for (int commonFirst = 0; commonFirst < 3; commonFirst++) {
                if (commonFirst == i) continue;
                int pieceFirst = 3 - i - commonFirst;
                for (int commonSecond = 0; commonSecond < 3; commonSecond++) {
                    if (commonSecond == j) continue;
                    int pieceSecond = 3 - j - commonSecond;
                    if (first[commonFirst] != second[commonSecond]) continue;
                    if (!checkLengthSum(first[pieceFirst], second[pieceSecond], base)) continue;
                    if (checkSupplementary(first[commonFirst], first[pieceFirst], fixedFirst, second[pieceSecond], fixedSecond)) return true;
                }
            }
        }
    }
    return false;
}

bool checkDegenerate(const IntPoint quad[4], int collinearId, const array<long long, 3> &triA, const array<long long, 3> &triB) {
    IntPoint tri[3];
    for (int i = 0, j = 0; i < 4; i++)
        if (i != collinearId) tri[j++] = quad[i];
    for (int apex = 0; apex < 3; apex++) {
        int left = (apex + 1) % 3, right = (apex + 2) % 3;
        long long fixedLeft = getDist2(tri[apex], tri[left]), fixedRight = getDist2(tri[apex], tri[right]);
        long long base = getDist2(tri[left], tri[right]);
        if (checkDegenerateOrder(triA, triB, fixedLeft, fixedRight, base)) return true;
        if (checkDegenerateOrder(triB, triA, fixedLeft, fixedRight, base)) return true;
    }
    return false;
}

bool canForm(const IntPoint quad[4], const array<long long, 3> &triA, const array<long long, 3> &triB) {
    long long turn[4], area2 = 0;
    int collinearId = -1, concaveId = -1;
    for (int i = 0; i < 4; i++) {
        turn[i] = getCross(quad[(i + 3) % 4], quad[i], quad[(i + 1) % 4]);
        if (turn[i] == 0) collinearId = i;
        area2 += quad[i].x * quad[(i + 1) % 4].y - quad[i].y * quad[(i + 1) % 4].x;
    }
    if (collinearId != -1) return checkDegenerate(quad, collinearId, triA, triB);
    for (int i = 0; i < 4; i++)
        if ((turn[i] > 0) != (area2 > 0)) concaveId = i;
    if (concaveId == -1) return checkConvex(quad, triA, triB);
    return checkConcave(quad, concaveId, triA, triB);
}

int solve() {
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        IntPoint tri[2][3], quad[4];
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 3; j++)
                cin >> tri[i][j].x >> tri[i][j].y;
        for (int i = 0; i < 4; i++) cin >> quad[i].x >> quad[i].y;
        array<long long, 3> triA = getIntSides(tri[0][0], tri[0][1], tri[0][2]);
        array<long long, 3> triB = getIntSides(tri[1][0], tri[1][1], tri[1][2]);
        cout << "Case #" << caseId << ": " << (canForm(quad, triA, triB) ? "Yes" : "No") << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
