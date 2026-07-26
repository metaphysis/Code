// Covering Whole Holes
// UVa ID: 1022
// Verdict: Accepted
// Submission Date: 2026-07-25
// UVa Run Time: 0.010s
// https://blog.csdn.net/metaphysis/article/details/163183078

#include <bits/stdc++.h>
using namespace std;

const long double epsilonValue = 1e-10L;

struct Point {
    long long x;
    long long y;
};

bool isBetween(long double value, long double leftValue, long double rightValue) {
    return value + epsilonValue >= min(leftValue, rightValue) && value - epsilonValue <= max(leftValue, rightValue);
}

bool isOnSegment(const Point& firstPoint, const Point& secondPoint, long double pointX, long double pointY) {
    long double crossValue = (long double)(secondPoint.x - firstPoint.x) * (pointY - firstPoint.y) - (long double)(secondPoint.y - firstPoint.y) * (pointX - firstPoint.x);
    if (fabsl(crossValue) > epsilonValue) return false;
    return isBetween(pointX, firstPoint.x, secondPoint.x) && isBetween(pointY, firstPoint.y, secondPoint.y);
}

bool isInsideOrOnBoundary(const vector<Point>& polygon, long double pointX, long double pointY, long long moveX, long long moveY) {
    bool inside = false;
    int polygonSize = polygon.size();
    for (int i = 0; i < polygonSize; i++) {
        Point firstPoint = polygon[i];
        Point secondPoint = polygon[(i + 1) % polygonSize];
        long double firstX = firstPoint.x + moveX;
        long double firstY = firstPoint.y + moveY;
        long double secondX = secondPoint.x + moveX;
        long double secondY = secondPoint.y + moveY;
        Point translatedFirstPoint{(long long)firstX, (long long)firstY};
        Point translatedSecondPoint{(long long)secondX, (long long)secondY};
        if (isOnSegment(translatedFirstPoint, translatedSecondPoint, pointX, pointY)) return true;
        if ((firstY > pointY) != (secondY > pointY)) {
            long double intersectX = firstX + (secondX - firstX) * (pointY - firstY) / (secondY - firstY);
            if (intersectX > pointX) inside = !inside;
        }
    }
    return inside;
}

void addParameter(vector<long double>& parameters, long double parameter) {
    if (parameter < -epsilonValue || parameter > 1.0L + epsilonValue) return;
    parameter = max(0.0L, min(1.0L, parameter));
    parameters.push_back(parameter);
}

void collectIntersectionParameters(const Point& holeFirstPoint, const Point& holeSecondPoint, const Point& coverFirstPoint, const Point& coverSecondPoint, long long moveX, long long moveY, vector<long double>& parameters) {
    long double holeX1 = holeFirstPoint.x;
    long double holeY1 = holeFirstPoint.y;
    long double holeX2 = holeSecondPoint.x;
    long double holeY2 = holeSecondPoint.y;
    long double coverX1 = coverFirstPoint.x + moveX;
    long double coverY1 = coverFirstPoint.y + moveY;
    long double coverX2 = coverSecondPoint.x + moveX;
    long double coverY2 = coverSecondPoint.y + moveY;
    long double holeDeltaX = holeX2 - holeX1;
    long double holeDeltaY = holeY2 - holeY1;
    long double coverDeltaX = coverX2 - coverX1;
    long double coverDeltaY = coverY2 - coverY1;
    if (fabsl(holeDeltaX) > epsilonValue && fabsl(coverDeltaY) > epsilonValue) {
        long double parameter = (coverX1 - holeX1) / holeDeltaX;
        long double otherParameter = (holeY1 + parameter * holeDeltaY - coverY1) / coverDeltaY;
        if (isBetween(otherParameter, 0.0L, 1.0L)) addParameter(parameters, parameter);
    } else if (fabsl(holeDeltaY) > epsilonValue && fabsl(coverDeltaX) > epsilonValue) {
        long double parameter = (coverY1 - holeY1) / holeDeltaY;
        long double otherParameter = (holeX1 + parameter * holeDeltaX - coverX1) / coverDeltaX;
        if (isBetween(otherParameter, 0.0L, 1.0L)) addParameter(parameters, parameter);
    } else if (fabsl(holeDeltaY) <= epsilonValue && fabsl(coverDeltaY) <= epsilonValue && fabsl(holeY1 - coverY1) <= epsilonValue) {
        if (fabsl(holeDeltaX) > epsilonValue) {
            addParameter(parameters, (coverX1 - holeX1) / holeDeltaX);
            addParameter(parameters, (coverX2 - holeX1) / holeDeltaX);
        }
    } else if (fabsl(holeDeltaX) <= epsilonValue && fabsl(coverDeltaX) <= epsilonValue && fabsl(holeX1 - coverX1) <= epsilonValue) {
        if (fabsl(holeDeltaY) > epsilonValue) {
            addParameter(parameters, (coverY1 - holeY1) / holeDeltaY);
            addParameter(parameters, (coverY2 - holeY1) / holeDeltaY);
        }
    }
}

bool canCover(const vector<Point>& hole, const vector<Point>& cover, long long moveX, long long moveY) {
    for (const Point& point : hole) {
        long double pointX = point.x;
        long double pointY = point.y;
        if (!isInsideOrOnBoundary(cover, pointX, pointY, moveX, moveY)) return false;
    }
    int holeSize = hole.size();
    int coverSize = cover.size();
    for (int i = 0; i < holeSize; i++) {
        Point holeFirstPoint = hole[i];
        Point holeSecondPoint = hole[(i + 1) % holeSize];
        vector<long double> parameters{0.0L, 1.0L};
        for (int j = 0; j < coverSize; j++) {
            Point coverFirstPoint = cover[j];
            Point coverSecondPoint = cover[(j + 1) % coverSize];
            collectIntersectionParameters(holeFirstPoint, holeSecondPoint, coverFirstPoint, coverSecondPoint, moveX, moveY, parameters);
        }
        sort(parameters.begin(), parameters.end());
        vector<long double> uniqueParameters;
        for (long double parameter : parameters) {
            if (uniqueParameters.empty() || fabsl(parameter - uniqueParameters.back()) > epsilonValue) uniqueParameters.push_back(parameter);
        }
        for (int j = 0; j + 1 < (int)uniqueParameters.size(); j++) {
            long double leftParameter = uniqueParameters[j];
            long double rightParameter = uniqueParameters[j + 1];
            if (rightParameter - leftParameter <= epsilonValue) continue;
            long double middleParameter = (leftParameter + rightParameter) / 2.0L;
            long double pointX = holeFirstPoint.x + (holeSecondPoint.x - holeFirstPoint.x) * middleParameter;
            long double pointY = holeFirstPoint.y + (holeSecondPoint.y - holeFirstPoint.y) * middleParameter;
            if (!isInsideOrOnBoundary(cover, pointX, pointY, moveX, moveY)) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int holeCount;
    int coverCount;
    int caseNumber = 1;
    while (cin >> holeCount >> coverCount && (holeCount != 0 || coverCount != 0)) {
        vector<Point> hole(holeCount);
        vector<Point> cover(coverCount);
        for (Point& point : hole) cin >> point.x >> point.y;
        for (Point& point : cover) cin >> point.x >> point.y;
        long long holeMinX = hole[0].x;
        long long holeMaxX = hole[0].x;
        long long holeMinY = hole[0].y;
        long long holeMaxY = hole[0].y;
        long long coverMinX = cover[0].x;
        long long coverMaxX = cover[0].x;
        long long coverMinY = cover[0].y;
        long long coverMaxY = cover[0].y;
        for (const Point& point : hole) {
            holeMinX = min(holeMinX, point.x);
            holeMaxX = max(holeMaxX, point.x);
            holeMinY = min(holeMinY, point.y);
            holeMaxY = max(holeMaxY, point.y);
        }
        for (const Point& point : cover) {
            coverMinX = min(coverMinX, point.x);
            coverMaxX = max(coverMaxX, point.x);
            coverMinY = min(coverMinY, point.y);
            coverMaxY = max(coverMaxY, point.y);
        }
        set<long long> moveXValues;
        set<long long> moveYValues;
        for (const Point& holePoint : hole) {
            for (const Point& coverPoint : cover) {
                moveXValues.insert(holePoint.x - coverPoint.x);
                moveYValues.insert(holePoint.y - coverPoint.y);
            }
        }
        bool possible = false;
        for (long long moveX : moveXValues) {
            if (moveX < holeMaxX - coverMaxX || moveX > holeMinX - coverMinX) continue;
            for (long long moveY : moveYValues) {
                if (moveY < holeMaxY - coverMaxY || moveY > holeMinY - coverMinY) continue;
                if (canCover(hole, cover, moveX, moveY)) {
                    possible = true;
                    break;
                }
            }
            if (possible) break;
        }
        cout << "Hole " << caseNumber++ << ": " << (possible ? "Yes" : "No") << '\n';
    }
    return 0;
}
