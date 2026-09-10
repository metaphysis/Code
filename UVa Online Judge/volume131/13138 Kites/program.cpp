#include <bits/stdc++.h>
using namespace std;

struct VerticalLine {
	long long x, y, len;
};

struct HorizontalLine {
	long long x, y, len;
};

class FenwickTree {
public:
	int size;
	vector<long long> tree;
	FenwickTree(int n) {
		size = n;
		tree.assign(n + 1,0);
	}
	void add(int pos, long long value) {
		for (int i = pos; i <= size; i += i & -i)
			tree[i] += value;
	}
	long long sum(int pos) {
		long long result = 0;
		for (int i = pos; i > 0; i -= i & -i)
			result += tree[i];
		return result;
	}
};

int n, m;
vector<VerticalLine> verticalLines;
vector<HorizontalLine> horizontalLines;
vector<int> verticalOrder;

long long countValid(long long d) {
	long long twoD = d * 2;
	vector<long long> values;
	vector<int> leftOrder, rightOrder;
	values.reserve(m + 2 * n);
	leftOrder.reserve(m);
	rightOrder.reserve(m);
	for (int i = 0; i < m; ++i) {
		if (horizontalLines[i].len < twoD) continue;
		values.push_back(horizontalLines[i].y);
		leftOrder.push_back(i);
		rightOrder.push_back(i);
	}
	for (int i = 0; i < n; ++i) {
		if (verticalLines[i].len < twoD) continue;
		values.push_back(verticalLines[i].y + d);
		values.push_back(verticalLines[i].y + verticalLines[i].len - d);
	}
	if (leftOrder.empty()) return 0;
	sort(values.begin(), values.end());
	values.erase(unique(values.begin(), values.end()), values.end());
	sort(leftOrder.begin(), leftOrder.end(), [](int a, int b) {
		if (horizontalLines[a].x != horizontalLines[b].x) return horizontalLines[a].x < horizontalLines[b].x;
		return horizontalLines[a].x + horizontalLines[a].len < horizontalLines[b].x + horizontalLines[b].len;
	});
	sort(rightOrder.begin(), rightOrder.end(), [](int a, int b) {
		long long rightA = horizontalLines[a].x + horizontalLines[a].len;
		long long rightB = horizontalLines[b].x + horizontalLines[b].len;
		if (rightA != rightB) return rightA < rightB;
		return horizontalLines[a].x < horizontalLines[b].x;
	});
	FenwickTree bit(values.size());
	int addPos = 0, removePos = 0;
	long long result = 0;
	for (int orderPos = 0; orderPos < n; ++orderPos) {
		int verticalId = verticalOrder[orderPos];
		VerticalLine &vertical = verticalLines[verticalId];
		if (vertical.len < twoD) continue;
		while (addPos < (int)leftOrder.size()) {
			int horizontalId = leftOrder[addPos];
			HorizontalLine &horizontal = horizontalLines[horizontalId];
			if (horizontal.x + d > vertical.x) break;
			int pos = lower_bound(values.begin(), values.end(), horizontal.y) - values.begin() + 1;
			bit.add(pos, 1);
			++addPos;
		}
		while (removePos < (int)rightOrder.size()) {
			int horizontalId = rightOrder[removePos];
			HorizontalLine &horizontal = horizontalLines[horizontalId];
			if (horizontal.x + horizontal.len - d >= vertical.x) break;
			int pos = lower_bound(values.begin(), values.end(), horizontal.y) - values.begin() + 1;
			bit.add(pos, -1);
			++removePos;
		}
		long long lowValue = vertical.y + d;
		long long highValue = vertical.y + vertical.len - d;
		int lowPos = lower_bound(values.begin(), values.end(), lowValue) - values.begin() + 1;
		int highPos = upper_bound(values.begin(), values.end(), highValue) - values.begin();
		if (lowPos <= highPos) result += bit.sum(highPos) - bit.sum(lowPos -1);
	}
	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	while (cin >> n >> m) {
		verticalLines.resize(n);
		horizontalLines.resize(m);
		for (int i = 0; i < n; ++i)	cin >> verticalLines[i].x >> verticalLines[i].y >> verticalLines[i].len;
		for (int i = 0; i < m; ++i)	cin >> horizontalLines[i].x >> horizontalLines[i].y >> horizontalLines[i].len;
		verticalOrder.resize(n);
		iota(verticalOrder.begin(), verticalOrder.end(), 0);
		sort(verticalOrder.begin(), verticalOrder.end(), [](int a, int b) {
			if (verticalLines[a].x != verticalLines[b].x)
				return verticalLines[a].x < verticalLines[b].x;
			return verticalLines[a].y < verticalLines[b].y;
		});
		long long low = 0, high = 500000000;
		while (low < high) {
			long long mid = (low + high + 1) /2;
			if (countValid(mid) > 0) low = mid;
			else high = mid - 1;
		}
		if (low == 0) {
			cout << "0 0\n";
			continue;
		}
		cout << low * 2 << ' ' << countValid(low) << '\n';
	}
	return 0;
}
