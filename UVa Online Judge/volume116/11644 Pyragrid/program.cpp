#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

struct Stick {
    Point a, b;
};

struct Line {
    long long a, b, c;
    vector<pair<long long, long long>> segs;
};

long long getGcd(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

Line getLine(Point p, Point q) {
    Line line;
    line.a = p.y - q.y;
    line.b = q.x - p.x;
    line.c = p.x * q.y - q.x * p.y;
    long long g = getGcd(abs(line.a), getGcd(abs(line.b), abs(line.c)));
    line.a /= g;
    line.b /= g;
    line.c /= g;
    if (line.a < 0 || line.a == 0 && line.b < 0) {
        line.a = -line.a;
        line.b = -line.b;
        line.c = -line.c;
    }
    return line;
}

bool getCross(Line p, Line q, Point &res) {
    long long det = p.a * q.b - q.a * p.b;
    if (det == 0) return false;
    long long x = p.b * q.c - q.b * p.c;
    long long y = p.c * q.a - q.c * p.a;
    if (x % det != 0 || y % det != 0) return false;
    res.x = x / det;
    res.y = y / det;
    return true;
}

long long getPos(const Line &line, Point p) {
    return line.b * p.x - line.a * p.y;
}

bool cover(const Line &line, Point p, Point q) {
    long long left = min(getPos(line, p), getPos(line, q)), right = max(getPos(line, p), getPos(line, q));
    vector<pair<long long, long long>> segs;
    for (auto seg : line.segs) {
        if (seg.second < left || seg.first > right) continue;
        segs.push_back({max(seg.first, left), min(seg.second, right)});
    }
    sort(segs.begin(), segs.end());
    long long cur = left;
    for (auto seg : segs) {
        if (seg.first > cur) return false;
        cur = max(cur, seg.second);
        if (cur >= right) return true;
    }
    return cur >= right;
}

bool sameLine(const Line &p, const Line &q) {
    return p.a == q.a && p.b == q.b && p.c == q.c;
}

long long solveCase(const vector<Stick> &sticks) {
    vector<Line> lines;
    map<tuple<long long, long long, long long>, int> lineId;
    for (auto stick : sticks) {
        Line line = getLine(stick.a, stick.b);
        tuple<long long, long long, long long> key = {line.a, line.b, line.c};
        if (!lineId.count(key)) {
            lineId[key] = lines.size();
            lines.push_back(line);
        }
        int id = lineId[key];
        long long p = getPos(lines[id], stick.a), q = getPos(lines[id], stick.b);
        if (p > q) swap(p, q);
        lines[id].segs.push_back({p, q});
    }
    for (auto &line : lines) {
        sort(line.segs.begin(), line.segs.end());
        vector<pair<long long, long long>> merged;
        for (auto seg : line.segs) {
            if (merged.empty() || seg.first > merged.back().second) merged.push_back(seg);
            else merged.back().second = max(merged.back().second, seg.second);
        }
        line.segs = merged;
    }
    long long ans = 0;
    int n = lines.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (lines[i].a * lines[j].b - lines[j].a * lines[i].b == 0) continue;
            for (int k = j + 1; k < n; k++) {
                if (lines[i].a * lines[k].b - lines[k].a * lines[i].b == 0) continue;
                if (lines[j].a * lines[k].b - lines[k].a * lines[j].b == 0) continue;
                Point p, q, r;
                if (!getCross(lines[i], lines[j], p)) continue;
                if (!getCross(lines[i], lines[k], q)) continue;
                if (!getCross(lines[j], lines[k], r)) continue;
                if (p.x == q.x && p.y == q.y) continue;
                if (p.x == r.x && p.y == r.y) continue;
                if (q.x == r.x && q.y == r.y) continue;
                if (!cover(lines[i], p, q)) continue;
                if (!cover(lines[j], p, r)) continue;
                if (!cover(lines[k], q, r)) continue;
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, tc = 1;
    while (cin >> n && n) {
        vector<Stick> sticks(n);
        for (int i = 0; i < n; i++) {
            cin >> sticks[i].a.x >> sticks[i].a.y >> sticks[i].b.x >> sticks[i].b.y;
            sticks[i].a.x *= 2;
            sticks[i].a.y *= 2;
            sticks[i].b.x *= 2;
            sticks[i].b.y *= 2;
        }
        cout << "Case " << tc++ << ": " << solveCase(sticks) << '\n';
    }
    return 0;
}
