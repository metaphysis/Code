#include <bits/stdc++.h>
using namespace std;

const long long Mod = 1000000007LL;

struct Rect {
	long long x1, y1, x2, y2;
};

struct Cell {
	long long left, right;
};

long long countLe(long long l1, long long r1, long long l2, long long r2, long long limit) {
	if (l1 > r1 || l2 > r2) return 0;
	long long midLeft = max(l1, l2 - limit);
	long long midRight = min(r1, r2 - limit - 1);
	long long fullLeft = max(l1, r2 - limit);
	long long fullRight = r1;
	__int128 result = 0;
	if (midLeft <= midRight) {
		__int128 count = midRight - midLeft + 1;
		__int128 first = midLeft + limit - l2 + 1;
		__int128 last = midRight + limit - l2 + 1;
		result += count * (first + last) / 2;
	}
	if (fullLeft <= fullRight) result += (__int128)(fullRight - fullLeft + 1) * (r2 - l2 + 1);
	return (long long)result;
}

long long countWidth(long long l1, long long r1, long long l2, long long r2, long long minWidth, long long maxWidth) {
	long long result = countLe(l1, r1, l2, r2, maxWidth) - countLe(l1, r1, l2, r2, minWidth - 1);
	return result % Mod;
}

vector<Cell> makeCells(long long low, long long high, vector<long long> cuts) {
	vector<Cell> cells;
	cuts.push_back(low);
	cuts.push_back(high + 1);
	sort(cuts.begin(), cuts.end());
	cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());
	for (int i = 0; i + 1 < (int)cuts.size(); i++) {
		long long left = max(low, cuts[i]);
		long long right = min(high + 1, cuts[i + 1]) - 1;
		if (left <= right) cells.push_back({left, right});
	}
	return cells;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testCases;
	cin >> testCases;
	while (testCases--) {
		long long width, height;
		cin >> width >> height;
		long long maxWidth, minWidth, maxHeight, minHeight;
		cin >> maxWidth >> minWidth >> maxHeight >> minHeight;
		int rectCount;
		cin >> rectCount;
		vector<Rect> rects(rectCount);
		for (int i = 0; i < rectCount; i++) cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
		vector<long long> leftCuts, rightCuts, bottomCuts, topCuts;
		for (int i = 0; i < rectCount; i++) {
			leftCuts.push_back(rects[i].x2);
			rightCuts.push_back(rects[i].x1 + 1);
			bottomCuts.push_back(rects[i].y2);
			topCuts.push_back(rects[i].y1 + 1);
		}
		vector<Cell> leftCells = makeCells(0, width - minWidth, leftCuts);
		vector<Cell> rightCells = makeCells(minWidth, width, rightCuts);
		vector<Cell> bottomCells = makeCells(0, height - minHeight, bottomCuts);
		vector<Cell> topCells = makeCells(minHeight, height, topCuts);
		map<unsigned long long, long long> xCount, yCount;
		for (const Cell &leftCell : leftCells) {
			for (const Cell &rightCell : rightCells) {
				long long ways = countWidth(leftCell.left, leftCell.right, rightCell.left, rightCell.right, minWidth, maxWidth);
				if (ways == 0) continue;
				unsigned long long mask = 0;
				long long leftValue = leftCell.left;
				long long rightValue = rightCell.left;
				for (int i = 0; i < rectCount; i++)
					if (leftValue < rects[i].x2 && rightValue > rects[i].x1) mask |= 1ULL << i;
				xCount[mask] = (xCount[mask] + ways) % Mod;
			}
		}
		for (const Cell &bottomCell : bottomCells) {
			for (const Cell &topCell : topCells) {
				long long ways = countWidth(bottomCell.left, bottomCell.right, topCell.left, topCell.right, minHeight, maxHeight);
				if (ways == 0) continue;
				unsigned long long mask = 0;
				long long bottomValue = bottomCell.left;
				long long topValue = topCell.left;
				for (int i = 0; i < rectCount; i++)
					if (bottomValue < rects[i].y2 && topValue > rects[i].y1) mask |= 1ULL << i;
				yCount[mask] = (yCount[mask] + ways) % Mod;
			}
		}
		long long answer = 0;
		for (const auto &xItem : xCount)
			for (const auto &yItem : yCount)
				if ((xItem.first & yItem.first) == 0)
					answer = (answer + xItem.second * yItem.second) % Mod;
		cout << answer << '\n';
	}
	return 0;
}
