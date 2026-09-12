#include <bits/stdc++.h>
using namespace std;

using Point = complex<double>;
using Line = pair<Point, Point>;

const double eps = 1e-8;
const int maxN = 300000;

int n, answer;
double curX;
Line lines[maxN];
int typeFlag[maxN], depth[maxN];

int signValue(double x) {
    return x < -eps ? -1 : x > eps;
}

double cross(Point a, Point b, Point c) {
    return imag(conj(b - a) * (c - a));
}

double dot(Point a, Point b, Point c) {
    return real(conj(b - a) * (c - a));
}

bool segmentIntersect(Line a, Line b) {
    int d1 = signValue(cross(a.first, a.second, b.first));
    int d2 = signValue(cross(a.first, a.second, b.second));
    int d3 = signValue(cross(b.first, b.second, a.first));
    int d4 = signValue(cross(b.first, b.second, a.second));
    if (!d1 && signValue(dot(b.first, a.first, a.second)) <= 0) return true;
    if (!d2 && signValue(dot(b.second, a.first, a.second)) <= 0) return true;
    if (!d3 && signValue(dot(a.first, b.first, b.second)) <= 0) return true;
    if (!d4 && signValue(dot(a.second, b.first, b.second)) <= 0) return true;
    return d1 * d2 == -1 && d3 * d4 == -1;
}

double getY(double x, const Line &line) {
    double dx = real(line.second - line.first), dy = imag(line.second - line.first);
    if (!signValue(dx)) return imag(line.first);
    return imag(line.first) + (x - real(line.first)) / dx * dy;
}

struct Event {
    double x;
    int type, a, b;
    bool operator < (const Event &event) const {
        if (signValue(x - event.x)) return x < event.x;
        return type < event.type;
    }
};

struct Compare {
    bool operator () (int a, int b) const {
        double ya = getY(curX, lines[a]), yb = getY(curX, lines[b]);
        if (signValue(ya - yb)) return ya < yb;
        return typeFlag[a] < typeFlag[b];
    }
};

Event events[maxN];
set<int, Compare> sweep;
set<int, Compare>::iterator positions[maxN];

bool solve() {
    sort(events, events + n);
    sweep.clear();
    answer = 0;
    fill(depth, depth + n, 0);
    for (int i = 0; i < n; ++i) {
        curX = events[i].x;
        int a = events[i].a, b = events[i].b;
        if (events[i].type == 0) {
            auto it = sweep.lower_bound(a);
            depth[a] = depth[b] = it == sweep.end() ? 1 : depth[*it] + typeFlag[*it];
            answer = max(answer, depth[a]);
            if (it != sweep.end()) {
                if (segmentIntersect(lines[a], lines[*it]) || segmentIntersect(lines[b], lines[*it])) return false;
            }
            if (it != sweep.begin()) {
                --it;
                if (segmentIntersect(lines[a], lines[*it]) || segmentIntersect(lines[b], lines[*it])) return false;
            }
            positions[a] = sweep.insert(a).first;
            positions[b] = sweep.insert(b).first;
        } else if (events[i].type == 1) {
            depth[b] = depth[a];
            sweep.erase(positions[a]);
            auto it = sweep.lower_bound(b);
            if (it != sweep.end() && b / 3 != *it / 3 && segmentIntersect(lines[b], lines[*it])) return false;
            if (it != sweep.begin()) {
                --it;
                if (b / 3 != *it / 3 && segmentIntersect(lines[b], lines[*it])) return false;
            }
            positions[b] = sweep.insert(b).first;
        } else {
            sweep.erase(positions[a]);
            sweep.erase(positions[b]);
            auto it = sweep.lower_bound(a);
            if (it != sweep.end() && it != sweep.begin()) {
                int c = *it, d = *prev(it);
                if (c / 3 != d / 3 && segmentIntersect(lines[c], lines[d])) return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase = 0;
    while (cin >> n && n != -1) {
        n *= 3;
        for (int i = 0; i < n; i += 3) {
            Point p[3];
            for (int j = 0; j < 3; ++j) {
                double x, y;
                cin >> x >> y;
                p[j] = Point(x, y);
            }
            if (p[1].real() < p[0].real()) swap(p[0], p[1]);
            if (p[2].real() < p[0].real()) swap(p[0], p[2]);
            if (p[2].real() < p[1].real()) swap(p[1], p[2]);
            lines[i] = Line(p[0], p[1]);
            lines[i + 1] = Line(p[1], p[2]);
            lines[i + 2] = Line(p[0], p[2]);
            bool reversed = cross(p[0], p[1], p[2]) < 0;
            typeFlag[i] = typeFlag[i + 1] = reversed;
            typeFlag[i + 2] = !reversed;
            events[i] = {p[0].real(), 0, i, i + 2};
            events[i + 1] = {p[1].real(), 1, i, i + 1};
            events[i + 2] = {p[2].real(), 2, i + 1, i + 2};
        }
        cout << "Case " << ++testCase << ": ";
        if (solve()) cout << answer + 1 << " shades\n";
        else cout << "ERROR\n";
    }
    return 0;
}
