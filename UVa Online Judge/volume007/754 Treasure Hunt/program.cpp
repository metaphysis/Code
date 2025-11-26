
// Treasure Hunt
// UVa ID: 754
// Verdict: Accepted
// Submission Date: 2025-11-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return fabs(x - other.x) < EPS && fabs(y - other.y) < EPS;
    }
};

struct Segment {
    Point p1, p2;
    Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};

double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool onSegment(Point p, Point q, Point r) {
    if (fabs(cross(p, q, r)) > EPS) return false;
    return q.x <= max(p.x, r.x) + EPS && q.x >= min(p.x, r.x) - EPS &&
           q.y <= max(p.y, r.y) + EPS && q.y >= min(p.y, r.y) - EPS;
}

Point getIntersection(Point a, Point b, Point c, Point d) {
    double a1 = b.y - a.y, b1 = a.x - b.x, c1 = a1 * a.x + b1 * a.y;
    double a2 = d.y - c.y, b2 = c.x - d.x, c2 = a2 * c.x + b2 * c.y;
    double det = a1 * b2 - a2 * b1;
    if (fabs(det) < EPS) return Point(-1, -1);
    return Point((b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det);
}

vector<vector<Point>> cutPolygon(const vector<Point>& poly, Point a, Point b) {
    vector<Point> left, right;
    int n = poly.size();
    
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];
        
        double cross1 = cross(a, b, p1);
        double cross2 = cross(a, b, p2);
        
        if (cross1 > -EPS) left.push_back(p1);
        if (cross1 < EPS) right.push_back(p1);
        
        if (cross1 * cross2 < -EPS) {
            Point inter = getIntersection(a, b, p1, p2);
            left.push_back(inter);
            right.push_back(inter);
        }
    }
    
    vector<vector<Point>> result;
    if (left.size() >= 3) result.push_back(left);
    if (right.size() >= 3) result.push_back(right);
    return result;
}

vector<Point> removeDuplicatePoints(const vector<Point>& poly) {
    vector<Point> result;
    for (const Point& p : poly) {
        if (result.empty() || !(result.back() == p)) {
            result.push_back(p);
        }
    }
    if (result.size() >= 2 && result.front() == result.back()) {
        result.pop_back();
    }
    return result;
}

vector<vector<Point>> buildPolygonsByCutting(vector<Segment>& walls) {
    vector<vector<Point>> polygons = {
        {Point(0, 0), Point(0, 100), Point(100, 100), Point(100, 0)}
    };
    
    for (auto& wall : walls) {
        vector<vector<Point>> newPolygons;
        
        for (auto& poly : polygons) {
            vector<vector<Point>> parts = cutPolygon(poly, wall.p1, wall.p2);
            for (auto& part : parts) {
                part = removeDuplicatePoints(part);
                if (part.size() >= 3) {
                    if (!(part.front() == part.back())) {
                        part.push_back(part.front());
                    }
                    newPolygons.push_back(part);
                }
            }
        }
        
        polygons = newPolygons;
    }
    
    return polygons;
}

bool pointInPolygon(Point p, const vector<Point>& poly) {
    int n = poly.size();
    int count = 0;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];
        
        if (onSegment(p1, p, p2)) return true;
        
        if ((p1.y > p.y) != (p2.y > p.y) &&
            p.x < (p2.x - p1.x) * (p.y - p1.y) / (p2.y - p1.y) + p1.x) {
            count++;
        }
    }
    return count % 2 == 1;
}

bool shareWall(const vector<Point>& poly1, const vector<Point>& poly2) {
    for (int i = 0; i < poly1.size(); i++) {
        Point a = poly1[i], b = poly1[(i + 1) % poly1.size()];
        for (int j = 0; j < poly2.size(); j++) {
            Point c = poly2[j], d = poly2[(j + 1) % poly2.size()];
            if ((a == c && b == d) || (a == d && b == c)) {
                return true;
            }
        }
    }
    return false;
}

bool hasExternalWall(const vector<Point>& poly) {
    for (int i = 0; i < poly.size(); i++) {
        Point a = poly[i], b = poly[(i + 1) % poly.size()];
        if ((fabs(a.x) < EPS && fabs(b.x) < EPS) ||
            (fabs(a.x - 100) < EPS && fabs(b.x - 100) < EPS) ||
            (fabs(a.y) < EPS && fabs(b.y) < EPS) ||
            (fabs(a.y - 100) < EPS && fabs(b.y - 100) < EPS)) {
            return true;
        }
    }
    return false;
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<Segment> walls;
        for (int i = 0; i < n; i++) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            walls.push_back(Segment(Point(x1, y1), Point(x2, y2)));
        }
        
        double tx, ty;
        cin >> tx >> ty;
        Point treasure(tx, ty);
        
        vector<vector<Point>> polygons = buildPolygonsByCutting(walls);
        int treasureRoom = -1;
        for (int i = 0; i < polygons.size(); i++) {
            if (pointInPolygon(treasure, polygons[i])) {
                treasureRoom = i;
                break;
            }
        }
        
        if (treasureRoom == -1) {
            cout << "Number of doors = 1" << endl;
        } else {
            int polyCount = polygons.size();
            vector<vector<int>> graph(polyCount);
            
            for (int i = 0; i < polyCount; i++) {
                for (int j = i + 1; j < polyCount; j++) {
                    if (shareWall(polygons[i], polygons[j])) {
                        graph[i].push_back(j);
                        graph[j].push_back(i);
                    }
                }
            }
            
            vector<int> dist(polyCount, -1);
            queue<int> q;
            q.push(treasureRoom);
            dist[treasureRoom] = 0;
            
            int answer = INT_MAX;
            while (!q.empty()) {
                int current = q.front();
                q.pop();
                
                if (hasExternalWall(polygons[current])) {
                    answer = min(answer, dist[current] + 1);
                }
                
                for (int neighbor : graph[current]) {
                    if (dist[neighbor] == -1) {
                        dist[neighbor] = dist[current] + 1;
                        q.push(neighbor);
                    }
                }
            }
            
            if (answer == INT_MAX) answer = 1;
            cout << "Number of doors = " << answer << endl;
        }
        
        if (t > 0) cout << endl;
    }
    
    return 0;
}
