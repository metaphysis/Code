#include <bits/stdc++.h>
using namespace std;

using Real = long double;

const Real EPS = 1e-9L,  INF = 1e100L;

struct Point {
	Real x, y;
	Point() : x(0), y(0) {}
	Point(Real xValue, Real yValue) : x(xValue), y(yValue) {}
	Point operator + (const Point& other) const { return Point(x + other.x, y + other.y); }
	Point operator - (const Point& other) const { return Point(x - other.x, y - other.y); }
	Point operator * (Real value) const { return Point(x * value, y * value); }
	Point operator / (Real value) const { return Point(x / value, y / value); }
};

int n;
Point robot;
Point points[105];
Real dist[105][105];
Real dp[105][105][2];

int nextIndex(int index) { return (index + 1) % n; }

int previousIndex(int index) { return (index + n - 1) % n; }

Real dot(const Point& first, const Point& second) {
	return first.x * second.x + first.y * second.y;
}

Real cross(const Point& first, const Point& second) {
	return first.x * second.y - first.y * second.x;
}

Real pointLength(const Point& point) {
	return sqrtl(dot(point, point));
}

Real pointDistance(const Point& first, const Point& second) {
	return pointLength(first - second);
}

Point reflectPoint(const Point& point, const Point& lineStart, const Point& lineEnd) {
	Point direction = lineEnd - lineStart;
	Point relative = point - lineStart;
	Real ratio = dot(relative, direction) / dot(direction, direction);
	Point projection = lineStart + direction * ratio;
	return projection * 2.0L - point;
}

bool pointOnRay(const Point& start, const Point& end, const Point& point) {
	return dot(point - start, end - start) > -EPS;
}

bool pointOnSegment(const Point& start, const Point& end, const Point& point) {
	return pointOnRay(start, end, point) && pointOnRay(end, start, point);
}

bool getIntersection(const Point& firstStart, const Point& firstEnd, const Point& secondStart, const Point& secondEnd, Point& intersection) {
	Point direction = secondEnd - secondStart;
	Real firstSide = cross(firstStart - secondStart, direction);
	Real secondSide = cross(firstEnd - secondStart, direction);
	Real denominator = firstSide - secondSide;
	if (fabsl(denominator) < EPS)
		return false;
	intersection = (firstEnd * firstSide - firstStart * secondSide) / denominator;
	return true;
}

Real getDist(int startEdge, int endEdge, Point startPoint, Point endPoint, int edgeCount) {
	for (int edge = endEdge, count = edgeCount; count > 0; --count, edge = previousIndex(edge)) {
		int previous = previousIndex(edge);
		endPoint = reflectPoint(endPoint, points[previous], points[edge]);
	}
	Real result = pointDistance(startPoint, endPoint);
	for (int edge = startEdge, count = edgeCount; count > 0; --count, edge = nextIndex(edge)) {
		int next = nextIndex(edge);
		Point intersection;
		if (!getIntersection(startPoint, endPoint, points[next], points[edge], intersection))
			return INF;
		if (!pointOnSegment(points[next], points[edge], intersection) || !pointOnSegment(startPoint, endPoint, intersection))
			return INF;
		startPoint = intersection;
		endPoint = reflectPoint(endPoint, points[next], points[edge]);
	}
	return result;
}

void initialize() {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			dist[i][j] = -1.0L;
			dp[i][j][0] = -1.0L;
			dp[i][j][1] = -1.0L;
		}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			int startEdge = nextIndex(i);
			int endEdge = previousIndex(j);
			int edgeCount = (endEdge - startEdge + n) % n;
			dist[i][j] = getDist(startEdge, endEdge, points[i], points[j], edgeCount);
		}
}

Real dfs(int startVertex, int currentVertex, int sameStart) {
	if (nextIndex(currentVertex) == startVertex || (currentVertex + 1 + sameStart) % n == startVertex)
		return pointDistance(robot, points[currentVertex]);
	Real& result = dp[startVertex][currentVertex][sameStart];
	if (result > -0.5L)
		return result;
	result = INF;
	for (int nextVertex = nextIndex(currentVertex), count = -1; nextVertex != startVertex; nextVertex = nextIndex(nextVertex), ++count) {
		int startEdge = nextIndex(currentVertex);
		int endEdge = previousIndex(nextVertex);
		int edgeCount = max(count, 0);
		Real segmentCost;
		if ((endEdge - startEdge + n) % n == edgeCount)
			segmentCost = dist[currentVertex][nextVertex];
		else
			segmentCost = getDist(startEdge, endEdge, points[currentVertex], points[nextVertex], edgeCount);
		result = min(result, segmentCost + dfs(startVertex, nextVertex, sameStart));
	}
	int startEdge = nextIndex(currentVertex);
	int endEdge = (startVertex - sameStart + n) % n;
	int edgeCount = (endEdge - startEdge + n) % n;
	result = min(result, getDist(startEdge, endEdge, robot, points[currentVertex], edgeCount));
	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int caseNumber = 1;
	Real x, y;
	while (cin >> n >> x >> y) {
		robot = Point(x, y);
		for (int i = 0; i < n; ++i) {
			cin >> x >> y;
			points[i] = Point(x, y);
		}
		initialize();
		Real answer = INF;
		for (int startEdge = 0; startEdge < n; ++startEdge) {
			answer = min(answer, getDist(startEdge, startEdge, robot, robot, n));
			for (int firstVertex = startEdge, count = n, offset = -1; count > 0; --count, firstVertex = nextIndex(firstVertex), ++offset) {
				int endEdge = previousIndex(firstVertex);
				int edgeCount = max(offset, 0);
				Real firstSegment = getDist(startEdge, endEdge, robot, points[firstVertex], edgeCount);
				Real remainingSegment = dfs(startEdge, firstVertex, startEdge == firstVertex);
				answer = min(answer, firstSegment + remainingSegment);
			}
		}
		cout << "Case " << caseNumber++ << ": " << fixed << setprecision(2) << (double)answer << '\n';
	}
	return 0;
}
