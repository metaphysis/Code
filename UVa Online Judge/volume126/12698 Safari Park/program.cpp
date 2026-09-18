#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

struct Triangle {
    Point p[3];
    int xMin, xMax;
};

struct Fraction {
    long long num, den;
};

enum class Position {
    Below,
    Above,
    Boundary,
    Inside,
    OutsideX
};

int compareFraction(const Fraction &first, const Fraction &second) {
    __int128 leftValue = static_cast<__int128>(first.num) * second.den;
    __int128 rightValue = static_cast<__int128>(second.num) * first.den;
    if (leftValue < rightValue) return -1;
    if (leftValue > rightValue) return 1;
    return 0;
}

int compareIntFraction(long long value, const Fraction &fraction) {
    __int128 leftValue = static_cast<__int128>(value) * fraction.den;
    if (leftValue < fraction.num) return -1;
    if (leftValue > fraction.num) return 1;
    return 0;
}

Fraction valueOnEdge(Point first, Point second, long long doubleX) {
    if (first.x > second.x) swap(first, second);
    long long dx = second.x - first.x;
    long long dy = second.y - first.y;
    return {2LL * first.y * dx + dy * (doubleX - 2LL * first.x), 2LL * dx};
}

pair<Fraction, Fraction> intervalAtX(const Triangle &triangle, long long doubleX) {
    bool hasValue = false;
    Fraction low{0, 1}, high{0, 1};
    for (int i = 0; i < 3; ++i) {
        Point first = triangle.p[i], second = triangle.p[(i + 1) % 3];
        if (first.x == second.x) {
            if (2LL * first.x != doubleX) continue;
            Fraction firstValue{first.y, 1}, secondValue{second.y, 1};
            Fraction lower = firstValue, upper = secondValue;
            if (compareFraction(lower, upper) > 0) swap(lower, upper);
            if (!hasValue) {
                low = lower;
                high = upper;
                hasValue = true;
            } else {
                if (compareFraction(lower, low) < 0) low = lower;
                if (compareFraction(upper, high) > 0) high = upper;
            }
            continue;
        }
        long long leftX = 2LL * min(first.x, second.x);
        long long rightX = 2LL * max(first.x, second.x);
        if (leftX <= doubleX && doubleX <= rightX) {
            Fraction value = valueOnEdge(first, second, doubleX);
            if (!hasValue) {
                low = high = value;
                hasValue = true;
            } else {
                if (compareFraction(value, low) < 0) low = value;
                if (compareFraction(value, high) > 0) high = value;
            }
        }
    }
    return {low, high};
}

Position locatePoint(const Triangle &triangle, long long x, long long y) {
    if (x < triangle.xMin || x > triangle.xMax) return Position::OutsideX;
    pair<Fraction, Fraction> interval = intervalAtX(triangle, 2LL * x);
    int lowCompare = compareIntFraction(y, interval.first);
    int highCompare = compareIntFraction(y, interval.second);
    if (lowCompare < 0) return Position::Below;
    if (highCompare > 0) return Position::Above;
    if (x == triangle.xMin || x == triangle.xMax) return Position::Boundary;
    if (lowCompare == 0 || highCompare == 0) return Position::Boundary;
    return Position::Inside;
}

bool triangleLess(const Triangle &first, const Triangle &second, long long doubleX) {
    pair<Fraction, Fraction> firstInterval = intervalAtX(first, doubleX);
    pair<Fraction, Fraction> secondInterval = intervalAtX(second, doubleX);
    int highLowCompare = compareFraction(firstInterval.second, secondInterval.first);
    if (highLowCompare < 0) return true;
    int otherHighLowCompare = compareFraction(secondInterval.second, firstInterval.first);
    if (otherHighLowCompare < 0) return false;
    int lowCompare = compareFraction(firstInterval.first, secondInterval.first);
    if (lowCompare != 0) return lowCompare < 0;
    return compareFraction(firstInterval.second, secondInterval.second) < 0;
}

class Solver {
private:
    static const int maxX = 100000;
    vector<Triangle> triangles;
    vector<int> segmentRoot;
    vector<int> leftChild;
    vector<int> rightChild;
    vector<unsigned> priority;
    vector<int> nodeTriangle;
    mt19937 randomGenerator;

    int addTreapNode(int triangleId) {
        leftChild.push_back(0);
        rightChild.push_back(0);
        priority.push_back(randomGenerator());
        nodeTriangle.push_back(triangleId);
        return static_cast<int>(nodeTriangle.size()) - 1;
    }

    void split(int root, int triangleId, long long doubleX, int &leftRoot, int &rightRoot) {
        if (root == 0) {
            leftRoot = rightRoot = 0;
            return;
        }
        if (triangleLess(triangles[nodeTriangle[root]], triangles[triangleId], doubleX)) {
            split(rightChild[root], triangleId, doubleX, rightChild[root], rightRoot);
            leftRoot = root;
        } else {
            split(leftChild[root], triangleId, doubleX, leftRoot, leftChild[root]);
            rightRoot = root;
        }
    }

    void insertTreap(int &root, int nodeId, long long doubleX) {
        if (root == 0) {
            root = nodeId;
            return;
        }
        if (priority[nodeId] > priority[root]) {
            split(root, nodeTriangle[nodeId], doubleX, leftChild[nodeId], rightChild[nodeId]);
            root = nodeId;
            return;
        }
        if (triangleLess(triangles[nodeTriangle[nodeId]], triangles[nodeTriangle[root]], doubleX)) insertTreap(leftChild[root], nodeId, doubleX);
        else insertTreap(rightChild[root], nodeId, doubleX);
    }

    void addTriangleOnRange(int node, int left, int right, int queryLeft, int queryRight, int triangleId) {
        if (queryLeft <= left && right <= queryRight) {
            long long doubleX = left == right ? 2LL * left : 2LL * left + 1;
            int treeNode = addTreapNode(triangleId);
            insertTreap(segmentRoot[node], treeNode, doubleX);
            return;
        }
        int middle = (left + right) >> 1;
        if (queryLeft <= middle) addTriangleOnRange(node << 1, left, middle, queryLeft, queryRight, triangleId);
        if (queryRight > middle) addTriangleOnRange(node << 1 | 1, middle + 1, right, queryLeft, queryRight, triangleId);
    }

    int searchTreap(int root, int x, int y) const {
        while (root != 0) {
            Position position = locatePoint(triangles[nodeTriangle[root]], x, y);
            if (position == Position::Boundary) return -1;
            if (position == Position::Inside) return nodeTriangle[root];
            if (position == Position::Below) root = leftChild[root];
            else if (position == Position::Above) root = rightChild[root];
            else return 0;
        }
        return 0;
    }

    int queryPoint(int node, int left, int right, int x, int y) const {
        int result = searchTreap(segmentRoot[node], x, y);
        if (result != 0) return result;
        if (left == right) return 0;
        int middle = (left + right) >> 1;
        if (x <= middle) return queryPoint(node << 1, left, middle, x, y);
        return queryPoint(node << 1 | 1, middle + 1, right, x, y);
    }

public:
    Solver() : segmentRoot(4 * (maxX + 1), 0), randomGenerator(712367821) {
        triangles.push_back({});
        leftChild.push_back(0);
        rightChild.push_back(0);
        priority.push_back(0);
        nodeTriangle.push_back(0);
    }

    int addTriangle(Point first, Point second, Point third) {
        Triangle triangle;
        triangle.p[0] = first;
        triangle.p[1] = second;
        triangle.p[2] = third;
        triangle.xMin = static_cast<int>(min(first.x, min(second.x, third.x)));
        triangle.xMax = static_cast<int>(max(first.x, max(second.x, third.x)));
        triangles.push_back(triangle);
        int triangleId = static_cast<int>(triangles.size()) - 1;
        addTriangleOnRange(1, 0, maxX, triangle.xMin, triangle.xMax, triangleId);
        return triangleId;
    }

    int query(int x, int y) const {
        return queryPoint(1, 0, maxX, x, y);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        int commandCount;
        cin >> commandCount;
        Solver solver;
        vector<Point> firstPoint(1, {0, 0});
        int lastAnswer = 0;
        cout << "Case " << caseId << ":\n";
        for (int commandId = 0; commandId < commandCount; ++commandId) {
            char command;
            cin >> command;
            Point shift = lastAnswer > 0 ? firstPoint[lastAnswer] : Point{0, 0};
            if (command == 'R') {
                Point first, second, third;
                cin >> first.x >> first.y >> second.x >> second.y >> third.x >> third.y;
                first.x += shift.x;
                first.y += shift.y;
                second.x += shift.x;
                second.y += shift.y;
                third.x += shift.x;
                third.y += shift.y;
                int triangleId = solver.addTriangle(first, second, third);
                if (static_cast<int>(firstPoint.size()) <= triangleId) firstPoint.resize(triangleId + 1);
                firstPoint[triangleId] = first;
            } else {
                int x, y;
                cin >> x >> y;
                x += static_cast<int>(shift.x);
                y += static_cast<int>(shift.y);
                lastAnswer = solver.query(x, y);
                cout << lastAnswer << '\n';
            }
        }
    }
    return 0;
}
