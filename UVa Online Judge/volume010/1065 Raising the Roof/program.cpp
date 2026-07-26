// Raising the Roof
// UVa ID: 1065
// Verdict: Accepted
// Submission Date: 2026-07-25
// UVa Run Time: 1.810s
// https://blog.csdn.net/metaphysis/article/details/163183464

#include <bits/stdc++.h>
using namespace std;

const long double epsilon = 1e-12L;

struct Point {
    long double x;
    long double y;
};

struct Vertex {
    long double x;
    long double y;
    long double z;
};

struct Triangle {
    Point point[3];
    long double a;
    long double b;
    long double c;
    long double areaFactor;
    bool valid;
};

long double crossProduct(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool isPointOnSegment(const Point &point, const Point &a, const Point &b) {
    if (fabsl(crossProduct(a, b, point)) > epsilon) {
        return false;
    }
    return point.x >= min(a.x, b.x) - epsilon && point.x <= max(a.x, b.x) + epsilon &&
           point.y >= min(a.y, b.y) - epsilon && point.y <= max(a.y, b.y) + epsilon;
}

void addIntersectionX(const Point &a, const Point &b, const Point &c, const Point &d, vector<long double> &eventX) {
    long double abX = b.x - a.x;
    long double abY = b.y - a.y;
    long double cdX = d.x - c.x;
    long double cdY = d.y - c.y;
    long double denominator = abX * cdY - abY * cdX;
    if (fabsl(denominator) <= epsilon) {
        if (isPointOnSegment(a, c, d)) {
            eventX.push_back(a.x);
        }
        if (isPointOnSegment(b, c, d)) {
            eventX.push_back(b.x);
        }
        if (isPointOnSegment(c, a, b)) {
            eventX.push_back(c.x);
        }
        if (isPointOnSegment(d, a, b)) {
            eventX.push_back(d.x);
        }
        return;
    }
    long double acX = c.x - a.x;
    long double acY = c.y - a.y;
    long double t = (acX * cdY - acY * cdX) / denominator;
    long double u = (acX * abY - acY * abX) / denominator;
    if (t >= -epsilon && t <= 1.0L + epsilon && u >= -epsilon && u <= 1.0L + epsilon) {
        eventX.push_back(a.x + t * abX);
    }
}

void getSection(const Triangle &triangle, long double x, vector<long double> &sectionY) {
    sectionY.clear();
    for (int edge = 0; edge < 3; edge++) {
        Point first = triangle.point[edge];
        Point second = triangle.point[(edge + 1) % 3];
        long double minX = min(first.x, second.x);
        long double maxX = max(first.x, second.x);
        if (x < minX - epsilon || x > maxX + epsilon) {
            continue;
        }
        if (fabsl(first.x - second.x) <= epsilon) {
            if (fabsl(x - first.x) <= epsilon) {
                sectionY.push_back(first.y);
                sectionY.push_back(second.y);
            }
            continue;
        }
        long double ratio = (x - first.x) / (second.x - first.x);
        if (ratio >= -epsilon && ratio <= 1.0L + epsilon) {
            sectionY.push_back(first.y + ratio * (second.y - first.y));
        }
    }
    sort(sectionY.begin(), sectionY.end());
    vector<long double> uniqueY;
    for (long double y : sectionY) {
        if (uniqueY.empty() || fabsl(y - uniqueY.back()) > 1e-10L) {
            uniqueY.push_back(y);
        }
    }
    sectionY = uniqueY;
}

vector<long double> getVisibleLengths(const vector<Triangle> &triangles, long double x) {
    vector<long double> allY;
    vector<vector<long double>> sections(triangles.size());
    for (int i = 0; i < static_cast<int>(triangles.size()); i++) {
        if (!triangles[i].valid) {
            continue;
        }
        getSection(triangles[i], x, sections[i]);
        for (long double y : sections[i]) {
            allY.push_back(y);
        }
    }
    sort(allY.begin(), allY.end());
    vector<long double> uniqueY;
    for (long double y : allY) {
        if (uniqueY.empty() || fabsl(y - uniqueY.back()) > 1e-10L) {
            uniqueY.push_back(y);
        }
    }
    vector<long double> visibleLengths(triangles.size(), 0.0L);
    for (int i = 0; i + 1 < static_cast<int>(uniqueY.size()); i++) {
        long double lowerY = uniqueY[i];
        long double upperY = uniqueY[i + 1];
        if (upperY - lowerY <= epsilon) {
            continue;
        }
        long double middleY = (lowerY + upperY) / 2.0L;
        int topTriangle = -1;
        long double topZ = -1e100L;
        for (int j = 0; j < static_cast<int>(triangles.size()); j++) {
            if (!triangles[j].valid || sections[j].size() < 2) {
                continue;
            }
            if (middleY < sections[j].front() - epsilon || middleY > sections[j].back() + epsilon) {
                continue;
            }
            long double currentZ = triangles[j].a * x + triangles[j].b * middleY + triangles[j].c;
            if (topTriangle == -1 || currentZ > topZ) {
                topTriangle = j;
                topZ = currentZ;
            }
        }
        if (topTriangle != -1) {
            visibleLengths[topTriangle] += upperY - lowerY;
        }
    }
    return visibleLengths;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int vertexCount;
    int triangleCount;
    int caseNumber = 1;
    while (cin >> vertexCount >> triangleCount) {
        if (vertexCount == 0 && triangleCount == 0) {
            break;
        }
        vector<Vertex> vertices(vertexCount);
        for (int i = 0; i < vertexCount; i++) {
            cin >> vertices[i].x >> vertices[i].y >> vertices[i].z;
        }
        vector<Triangle> triangles(triangleCount);
        vector<long double> eventX;
        for (int i = 0; i < triangleCount; i++) {
            int index[3];
            cin >> index[0] >> index[1] >> index[2];
            for (int j = 0; j < 3; j++) {
                triangles[i].point[j] = {
                    vertices[index[j] - 1].x,
                    vertices[index[j] - 1].y
                };
                eventX.push_back(triangles[i].point[j].x);
            }
            long double areaTwice = crossProduct(
                triangles[i].point[0],
                triangles[i].point[1],
                triangles[i].point[2]
            );
            if (fabsl(areaTwice) <= epsilon) {
                triangles[i].valid = false;
                continue;
            }
            long double ux = vertices[index[1] - 1].x - vertices[index[0] - 1].x;
            long double uy = vertices[index[1] - 1].y - vertices[index[0] - 1].y;
            long double uz = vertices[index[1] - 1].z - vertices[index[0] - 1].z;
            long double vx = vertices[index[2] - 1].x - vertices[index[0] - 1].x;
            long double vy = vertices[index[2] - 1].y - vertices[index[0] - 1].y;
            long double vz = vertices[index[2] - 1].z - vertices[index[0] - 1].z;
            long double normalX = uy * vz - uz * vy;
            long double normalY = uz * vx - ux * vz;
            long double normalZ = ux * vy - uy * vx;
            if (fabsl(normalZ) <= epsilon) {
                triangles[i].valid = false;
                continue;
            }
            triangles[i].a = -normalX / normalZ;
            triangles[i].b = -normalY / normalZ;
            triangles[i].c = vertices[index[0] - 1].z -
                            triangles[i].a * vertices[index[0] - 1].x -
                            triangles[i].b * vertices[index[0] - 1].y;
            triangles[i].areaFactor = sqrtl(
                1.0L + triangles[i].a * triangles[i].a + triangles[i].b * triangles[i].b
            );
            triangles[i].valid = true;
        }
        for (int i = 0; i < triangleCount; i++) {
            for (int j = i + 1; j < triangleCount; j++) {
                for (int edgeA = 0; edgeA < 3; edgeA++) {
                    Point firstA = triangles[i].point[edgeA];
                    Point secondA = triangles[i].point[(edgeA + 1) % 3];
                    for (int edgeB = 0; edgeB < 3; edgeB++) {
                        Point firstB = triangles[j].point[edgeB];
                        Point secondB = triangles[j].point[(edgeB + 1) % 3];
                        addIntersectionX(firstA, secondA, firstB, secondB, eventX);
                    }
                }
            }
        }
        sort(eventX.begin(), eventX.end());
        vector<long double> uniqueX;
        for (long double x : eventX) {
            if (uniqueX.empty() || fabsl(x - uniqueX.back()) > 1e-10L) {
                uniqueX.push_back(x);
            }
        }
        vector<long double> projectedArea(triangleCount, 0.0L);
        for (int i = 0; i + 1 < static_cast<int>(uniqueX.size()); i++) {
            long double leftX = uniqueX[i];
            long double rightX = uniqueX[i + 1];
            if (rightX - leftX <= epsilon) {
                continue;
            }
            long double width = rightX - leftX;
            long double leftSample = leftX + width * 1e-8L;
            long double rightSample = rightX - width * 1e-8L;
            vector<long double> leftLengths = getVisibleLengths(triangles, leftSample);
            vector<long double> rightLengths = getVisibleLengths(triangles, rightSample);
            for (int j = 0; j < triangleCount; j++) {
                projectedArea[j] += (leftLengths[j] + rightLengths[j]) * width / 2.0L;
            }
        }
        long double answer = 0.0L;
        for (int i = 0; i < triangleCount; i++) {
            answer += projectedArea[i] * triangles[i].areaFactor;
        }
        cout << "Case " << caseNumber++ << ": " << fixed << setprecision(2)
             << static_cast<double>(answer + 1e-9L) << "\n\n";
    }
    return 0;
}
