// Eyeball Benders
// UVa ID: 1038
// Verdict: Accepted
// Submission Date: 2026-07-25
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163183325

#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-7L;

struct Point {
    long double x;
    long double y;
};

struct Segment {
    Point start;
    Point end;
};

bool isEqual(long double firstValue, long double secondValue) {
    return fabsl(firstValue - secondValue) <= eps;
}

bool isEqualPoint(const Point& firstPoint, const Point& secondPoint) {
    return isEqual(firstPoint.x, secondPoint.x) && isEqual(firstPoint.y, secondPoint.y);
}

long double getLength(const Segment& segment) {
    long double deltaX = segment.start.x - segment.end.x;
    long double deltaY = segment.start.y - segment.end.y;
    return sqrtl(deltaX * deltaX + deltaY * deltaY);
}

bool isSameSegment(const Segment& firstSegment, const Segment& secondSegment) {
    bool firstOrder = isEqualPoint(firstSegment.start, secondSegment.start) && isEqualPoint(firstSegment.end, secondSegment.end);
    bool secondOrder = isEqualPoint(firstSegment.start, secondSegment.end) && isEqualPoint(firstSegment.end, secondSegment.start);
    return firstOrder || secondOrder;
}

bool clipTest(long double p, long double q, long double& firstRatio, long double& secondRatio) {
    if (fabsl(p) <= eps) return q >= -eps;
    long double ratio = q / p;
    if (p < 0) {
        if (ratio > secondRatio + eps) return false;
        if (ratio > firstRatio) firstRatio = ratio;
    } else {
        if (ratio < firstRatio - eps) return false;
        if (ratio < secondRatio) secondRatio = ratio;
    }
    return true;
}

bool clipSegment(const Segment& segment, long double leftX, long double rightX, long double bottomY, long double topY, Segment& result) {
    long double deltaX = segment.end.x - segment.start.x;
    long double deltaY = segment.end.y - segment.start.y;
    long double firstRatio = 0;
    long double secondRatio = 1;
    if (!clipTest(-deltaX, segment.start.x - leftX, firstRatio, secondRatio)) return false;
    if (!clipTest(deltaX, rightX - segment.start.x, firstRatio, secondRatio)) return false;
    if (!clipTest(-deltaY, segment.start.y - bottomY, firstRatio, secondRatio)) return false;
    if (!clipTest(deltaY, topY - segment.start.y, firstRatio, secondRatio)) return false;
    if (firstRatio > secondRatio + eps) return false;
    result.start = {segment.start.x + deltaX * firstRatio, segment.start.y + deltaY * firstRatio};
    result.end = {segment.start.x + deltaX * secondRatio, segment.start.y + deltaY * secondRatio};
    return true;
}

bool isValidTransform(const vector<Segment>& puzzleSegments, const vector<Segment>& solutionSegments, long double scale, const Point& puzzleAnchor, const Point& solutionAnchor) {
    long double moveX = puzzleAnchor.x - scale * solutionAnchor.x;
    long double moveY = puzzleAnchor.y - scale * solutionAnchor.y;
    long double leftX = 1e100L;
    long double rightX = -1e100L;
    long double bottomY = 1e100L;
    long double topY = -1e100L;
    for (const Segment& segment : puzzleSegments) {
        leftX = min(leftX, min(segment.start.x, segment.end.x));
        rightX = max(rightX, max(segment.start.x, segment.end.x));
        bottomY = min(bottomY, min(segment.start.y, segment.end.y));
        topY = max(topY, max(segment.start.y, segment.end.y));
    }
    vector<Segment> clippedSegments;
    for (const Segment& segment : solutionSegments) {
        Segment transformedSegment;
        transformedSegment.start = {scale * segment.start.x + moveX, scale * segment.start.y + moveY};
        transformedSegment.end = {scale * segment.end.x + moveX, scale * segment.end.y + moveY};
        Segment clippedSegment;
        if (clipSegment(transformedSegment, leftX, rightX, bottomY, topY, clippedSegment)) {
            if (getLength(clippedSegment) > eps) clippedSegments.push_back(clippedSegment);
        }
    }
    if (clippedSegments.size() != puzzleSegments.size()) return false;
    vector<bool> used(clippedSegments.size(), false);
    for (const Segment& puzzleSegment : puzzleSegments) {
        bool found = false;
        for (int index = 0; index < static_cast<int>(clippedSegments.size()); index++) {
            if (used[index]) continue;
            if (isSameSegment(puzzleSegment, clippedSegments[index])) {
                used[index] = true;
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 0;
    int m, n;
    while (cin >> m >> n && (m != 0 || n != 0)) {
        vector<Segment> puzzleSegments(m);
        vector<Segment> solutionSegments(n);
        for (Segment& segment : puzzleSegments) cin >> segment.start.x >> segment.start.y >> segment.end.x >> segment.end.y;
        for (Segment& segment : solutionSegments) cin >> segment.start.x >> segment.start.y >> segment.end.x >> segment.end.y;
        vector<long double> scaleCandidates;
        scaleCandidates.push_back(1.0L);
        for (const Segment& puzzleSegment : puzzleSegments) {
            long double puzzleLength = getLength(puzzleSegment);
            for (const Segment& solutionSegment : solutionSegments) {
                long double solutionLength = getLength(solutionSegment);
                long double scale = puzzleLength / solutionLength;
                if (scale + eps >= 1.0L) scaleCandidates.push_back(scale);
            }
        }
        sort(scaleCandidates.begin(), scaleCandidates.end());
        vector<long double> uniqueScales;
        for (long double scale : scaleCandidates) {
            if (uniqueScales.empty() || !isEqual(scale, uniqueScales.back())) uniqueScales.push_back(scale);
        }
        bool valid = false;
        for (long double scale : uniqueScales) {
            if (valid) break;
            for (const Segment& puzzleSegment : puzzleSegments) {
                if (valid) break;
                for (const Segment& solutionSegment : solutionSegments) {
                    vector<Point> puzzlePoints = {puzzleSegment.start, puzzleSegment.end};
                    vector<Point> solutionPoints = {solutionSegment.start, solutionSegment.end};
                    for (const Point& puzzlePoint : puzzlePoints) {
                        if (valid) break;
                        for (const Point& solutionPoint : solutionPoints) {
                            if (isValidTransform(puzzleSegments, solutionSegments, scale, puzzlePoint, solutionPoint)) {
                                valid = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        cout << "Case " << ++caseNumber << ": ";
        if (valid) cout << "valid puzzle\n";
        else cout << "impossible\n";
        cout << '\n';
    }
    return 0;
}
