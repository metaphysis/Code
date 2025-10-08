// Robot Crash
// UVa ID: 204
// Verdict: Accepted
// Submission Date: 2025-10-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
const double DEG_TO_RAD = PI / 180.0;
const double EPS = 1e-7;
const int LENGTH = (1 << 20);

inline int nextChar() {
    static char buffer[LENGTH], *p = buffer, *end = buffer;
    if (p == end) {
        if ((end = buffer + fread(buffer, 1, LENGTH, stdin)) == buffer) return EOF;
        p = buffer;
    }
    return *p++;
}

inline double readDouble() {
    int ch, sign = 1;
    double value = 0, decimal = 0, div = 1;
    while (isspace(ch = nextChar()));
    if (ch == '-') {
        sign = -1;
        ch = nextChar();
    } else if (ch == '+') {
        ch = nextChar();
    }
    while (isdigit(ch)) {
        value = value * 10 + (ch - '0');
        ch = nextChar();
    }
    if (ch == '.') {
        ch = nextChar();
        while (isdigit(ch)) {
            decimal = decimal * 10 + (ch - '0');
            div *= 10;
            ch = nextChar();
        }
    }
    return sign * (value + decimal / div);
}

inline bool eq(double a, double b) { return fabs(a - b) < EPS; }
inline bool le(double a, double b) { return a < b + EPS; }
inline bool ge(double a, double b) { return a + EPS > b; }

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    bool operator<(const Point& p) const {
        return eq(x, p.x) ? (y < p.y) : (x < p.x);
    }
};

struct Vector {
    double x, y;
    Vector(double x = 0, double y = 0) : x(x), y(y) {}
};

struct Segment {
    Point start, end;
    Segment() : start(Point(0,0)), end(Point(0,0)) {}
    Segment(Point s, Point e) : start(s), end(e) {}
};

struct Line {
    double a, b, c;
    Line(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {}
    Line(Point p1, Point p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = -a * p1.x - b * p1.y;
    }
    bool contains(Point p) const {
        return eq(a * p.x + b * p.y + c, 0);
    }
};

inline bool intervalsOverlap(double a1, double a2, double b1, double b2) {
    if (a1 > a2) swap(a1, a2);
    if (b1 > b2) swap(b1, b2);
    return le(max(a1, b1), min(a2, b2));
}

bool segmentsIntersect(const Segment& s1, const Segment& s2, Segment* result) {
    if (!intervalsOverlap(s1.start.x, s1.end.x, s2.start.x, s2.end.x) ||
        !intervalsOverlap(s1.start.y, s1.end.y, s2.start.y, s2.end.y)) {
        return false;
    }
    Line line1(s1.start, s1.end);
    Line line2(s2.start, s2.end);
    double det = line1.a * line2.b - line2.a * line1.b;
    if (eq(det, 0)) {
        if (!line1.contains(s2.start) || !line2.contains(s1.start)) return false;
        Point p1 = s1.start, p2 = s1.end;
        Point q1 = s2.start, q2 = s2.end;
        if (p2 < p1) swap(p1, p2);
        if (q2 < q1) swap(q1, q2);
        result->start = max(p1, q1);
        result->end = min(p2, q2);
        return true;
    }
    double x = (line2.c * line1.b - line1.c * line2.b) / det;
    double y = (line2.a * line1.c - line1.a * line2.c) / det;
    result->start = Point(x, y);
    result->end = Point(x, y);
    return le(min(s1.start.x, s1.end.x), x) && le(x, max(s1.start.x, s1.end.x)) &&
           le(min(s1.start.y, s1.end.y), y) && le(y, max(s1.start.y, s1.end.y)) &&
           le(min(s2.start.x, s2.end.x), x) && le(x, max(s2.start.x, s2.end.x)) &&
           le(min(s2.start.y, s2.end.y), y) && le(y, max(s2.start.y, s2.end.y));
}

void adjustToBounds(Point& p, Vector& v) {
    if (p.y > 10) {
        double cycles = floor(p.y * 0.05 + EPS);
        p.y -= cycles * 20;
        if (p.y > 10) {
            p.y = 20 - p.y;
            v.y = -v.y;
        }
    } else if (p.y < 0) {
        double cycles = floor(-p.y * 0.05 + EPS);
        p.y += cycles * 20;
        if (p.y < -10) {
            p.y += 20;
        } else {
            p.y = -p.y;
            v.y = -v.y;
        }
    }
}

vector<Segment> buildPath(Point pos, Vector vel, double startTime, double endTime) {
    vector<Segment> path;
    pos.x += vel.x * startTime;
    pos.y += vel.y * startTime;
    adjustToBounds(pos, vel);
    double time = startTime;
    while (true) {
        double nextTime = endTime;
        if (!eq(vel.y, 0)) {
            if (vel.y > 0) {
                nextTime = time + (10 - pos.y) / vel.y;
            } else {
                nextTime = time - pos.y / vel.y;
            }
            if (nextTime > endTime) nextTime = endTime;
        }
        Point nextPos(pos.x + vel.x * (nextTime - time), pos.y + vel.y * (nextTime - time));
        path.push_back(Segment(pos, nextPos));
        pos = nextPos;
        time = nextTime;
        vel.y = -vel.y;
        if (ge(time, endTime)) break;
    }
    return path;
}

bool checkCollisionCase(const Point& p1, const Vector& v1, const Point& p2,
                       const Vector& v2, bool flipped, double* bestTime, Point* collisionPoint) {
    double dist = p2.x - p1.x;
    if (eq(dist, 0)) {
        if (eq(p2.y, p1.y) && !flipped) {
            *bestTime = 0;
            *collisionPoint = p1;
            return true;
        }
        return false;
    }
    if (dist < 0) return false;
    double meetTime = dist / (v1.x - v2.x);
    double rightMaxTime = meetTime + v1.x / (v1.x - v2.x) * 0.5;
    if (rightMaxTime > *bestTime) {
        rightMaxTime = *bestTime;
        if (!ge(rightMaxTime, meetTime)) return false;
    }
    double leftMinTime = max(0.0, meetTime + v2.x / (v1.x - v2.x) * 0.5);
    vector<Segment> rightPath = buildPath(p2, v2, meetTime, rightMaxTime);
    vector<Segment> leftPath = buildPath(p1, v1, leftMinTime, meetTime);
    reverse(leftPath.begin(), leftPath.end());
    Segment intersection(Point(0,0), Point(0,0));
    bool found = false;
    for (const auto& seg2 : rightPath) {
        for (const auto& seg1 : leftPath) {
            if (segmentsIntersect(seg1, seg2, &intersection)) {
                found = true;
                break;
            }
        }
        if (found) break;
    }
    if (!found) return false;
    double collisionTime = (intersection.end.x - p2.x) / v2.x;
    double x = flipped ? (p1.x + p2.x - intersection.end.x) : intersection.end.x;
    if (eq(*bestTime, collisionTime)) {
        if (x < collisionPoint->x) {
            collisionPoint->x = x;
            collisionPoint->y = intersection.end.y;
        }
    } else {
        *bestTime = collisionTime;
        collisionPoint->x = x;
        collisionPoint->y = intersection.end.y;
    }
    return true;
}

bool checkCollision(Point p1, Vector v1, Point p2, Vector v2, Point* result) {
    double bestTime = numeric_limits<double>::max();
    bool found = checkCollisionCase(p1, v1, p2, v2, false, &bestTime, result);
    swap(p1.y, p2.y); swap(v1, v2);
    v1.x = -v1.x; v2.x = -v2.x;
    found |= checkCollisionCase(p1, v1, p2, v2, true, &bestTime, result);
    return found;
}

int main(int argc, char* argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int caseNum = 0;
    Point robot1, robot2, collisionPoint;
    double angle1, angle2, speed1, speed2;
    while (true) {
        robot1.x = readDouble(); robot1.y = readDouble();
        angle1 = readDouble(); speed1 = readDouble();
        robot2.x = readDouble(); robot2.y = readDouble();
        angle2 = readDouble(); speed2 = readDouble();
        if (robot1.x == 0 && robot1.y == 0 && angle1 == 0 && speed1 == 0 &&
            robot2.x == 0 && robot2.y == 0 && angle2 == 0 && speed2 == 0) break;
        angle1 *= DEG_TO_RAD;
        angle2 *= DEG_TO_RAD;
        Vector vel1(speed1 * cos(angle1), speed1 * sin(angle1));
        Vector vel2(speed2 * cos(angle2), speed2 * sin(angle2));
        if (checkCollision(robot1, vel1, robot2, vel2, &collisionPoint)) {
            printf("Robot Problem #%d: Robots collide at (%.2lf,%.2lf)\n\n",
                   ++caseNum, collisionPoint.x + EPS, collisionPoint.y + EPS);
        } else {
            printf("Robot Problem #%d: Robots do not collide.\n\n", ++caseNum);
        }
    }
    return 0;
}
