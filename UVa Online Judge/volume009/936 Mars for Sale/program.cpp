#include <bits/stdc++.h>
using namespace std;

struct Point {
	long long x, y;
};

struct Interval {
	Point left, right;
};

bool pointLess(const Point &a, const Point &b) {
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

bool intervalLess(const Interval &a, const Interval &b) {
	return pointLess(a.left, b.left);
}

bool hasIntersection(vector<Interval> &intervals) {
	int i, n = intervals.size();
	sort(intervals.begin(), intervals.end(), intervalLess);
	Point maxRight = intervals[0].right;
	for (i =1; i < n; i++) {
		if (pointLess(intervals[i].left, maxRight))
			return true;
		if (pointLess(maxRight, intervals[i].right))
			maxRight = intervals[i].right;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testCount, caseIndex, n;
	cin >> testCount;
	for (caseIndex =0; caseIndex < testCount; caseIndex++) {
		cin >> n;
		vector<Interval> intervals(n);
		int i;
		for (i =0; i < n; i++) {
			Point firstPoint, secondPoint;
			cin >> firstPoint.x >> firstPoint.y >> secondPoint.x >> secondPoint.y;
			if (pointLess(secondPoint, firstPoint)) {
				intervals[i].left = secondPoint;
				intervals[i].right = firstPoint;
			} else {
				intervals[i].left = firstPoint;
				intervals[i].right = secondPoint;
			}
		}
		if (hasIntersection(intervals))
			cout << "Difficult problem(s)\n";
		else cout << "No problem\n";
	}
	return 0;
}
