// Convex Hull of the Polygon
// UVa ID: 675
// Verdict: Accepted
// Submission Date: 2017-06-07
// UVa Run Time: 0.110s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
    bool operator<(const point &p) const {
        if (y != p.y) return y < p.y;
        return x < p.x;
    }
    bool operator==(const point &p) const {
        return x == p.x && y == p.y;
    }
};

const int MAX_VERTICES = 100005;
typedef vector<point> polygon;

int cp(point &a, point &b, point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool ccwOrCollinear(point &a, point &b, point &c) {
    return cp(a, b, c) >= 0;
}

polygon andrewConvexHull(polygon &vertices) {
    sort(vertices.begin(), vertices.end());
    point ch[MAX_VERTICES];
    int top = 0;
    for (int i = 0; i < vertices.size(); i++) {
        while (top >= 2 && ccwOrCollinear(ch[top - 2], ch[top - 1], vertices[i]))
            top--;
        ch[top++] = vertices[i];
    }
    for (int i = vertices.size() - 1, upper = top + 1; i >= 0; i--) {
        while (top >= upper && ccwOrCollinear(ch[top - 2], ch[top - 1], vertices[i]))
            top--;
        ch[top++] = vertices[i];
    }
    polygon pg;
    for (int i = 0; i < top - 1; i++) pg.push_back(ch[i]);
    return pg;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    string separator;
    istringstream iss;
    int cases = 0;
    while (getline(cin, line), line.length() > 0) {
        polygon source, vertices;
        do {
            int x1 = 0, y1 = 0;
            iss.clear(); iss.str(line);
            iss >> x1 >> separator >> y1;
            vertices.push_back(point{x1, y1});
            source.push_back(point{x1, y1});
        } while (getline(cin, line), line.length() > 0);
        polygon convexHull = andrewConvexHull(vertices);
        int start = -1;
        for (int i = 0; i < source.size() && start == -1; i++)
            for (int j = 0; j < convexHull.size(); j++)
                if (source[i] == convexHull[j]) {
                    start = j;
                    break;
                }
        if (cases++ > 0) cout << '\n';
        int total = convexHull.size();
        for (int i = 0; i < total; i++) {
            int j = (total + start - i) % total;
            cout << convexHull[j].x << ", " << convexHull[j].y << '\n';
        }
        cout << convexHull[start].x << ", " << convexHull[start].y << '\n';
    }
    return 0;
}
