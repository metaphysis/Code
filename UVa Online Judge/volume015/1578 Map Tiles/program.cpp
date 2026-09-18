#include <bits/stdc++.h>
using namespace std;

const double geomEps = 1e-12, tileEps = 1e-9;
const long long keyScale = 10000000000LL;
const int gridSize = 11, maskSize = 1 << gridSize;
int bitCount[maskSize];

struct Point {
    double x, y;
    Point operator + (const Point &other) const {
        return {x + other.x, y + other.y};
    }

    Point operator - (const Point &other) const {
        return {x - other.x, y - other.y};
    }

    Point operator * (double value) const {
        return {x * value, y * value};
    }
};

struct Edge {
    Point a, b;
    double slope;
};

struct Segment {
    Point a, b, dir;
    double minX, maxX, minY, maxY;
};

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

void addCandidate(vector<pair<long long, long long>> &candidates, Point p) {
    long long keyX = llround(p.x * keyScale), keyY = llround(p.y * keyScale);
    keyX %= keyScale;
    keyY %= keyScale;
    if (keyX < 0) keyX += keyScale;
    if (keyY < 0) keyY += keyScale;
    candidates.emplace_back(keyX, keyY);
}

void addSegment(vector<Segment> &segments, Point a, Point b) {
    Point dir = b - a;
    if (max(fabs(dir.x), fabs(dir.y)) < geomEps) return;
    segments.push_back({a, b, dir, min(a.x, b.x), max(a.x, b.x), min(a.y, b.y), max(a.y, b.y)});
}

bool clipAxis(double start, double delta, double &low, double &high) {
    if (fabs(delta) < geomEps) return start >= -geomEps && start <= 1.0 + geomEps;
    double first = -start / delta, last = (1.0 - start) / delta;
    if (first > last) swap(first, last);
    low = max(low, first);
    high = min(high, last);
    return low <= high;
}

void addClippedSegment(vector<Segment> &segments, Point a, Point b) {
    Point dir = b - a;
    double low = 0.0, high = 1.0;
    if (!clipAxis(a.x, dir.x, low, high)) return;
    if (!clipAxis(a.y, dir.y, low, high)) return;
    addSegment(segments, a + dir * low, a + dir * high);
}

bool getIntersection(const Segment &first, const Segment &second, Point &point) {
    if (first.maxX < second.minX - geomEps || second.maxX < first.minX - geomEps) return false;
    if (first.maxY < second.minY - geomEps || second.maxY < first.minY - geomEps) return false;
    double denominator = cross(first.dir, second.dir);
    if (denominator == 0.0) return false;
    Point delta = second.a - first.a;
    double firstT = cross(delta, second.dir) / denominator, secondT = cross(delta, first.dir) / denominator;
    if (firstT < -geomEps || firstT > 1.0 + geomEps) return false;
    if (secondT < -geomEps || secondT > 1.0 + geomEps) return false;
    firstT = max(0.0, min(1.0, firstT));
    point = first.a + first.dir * firstT;
    return true;
}

int markRange(unsigned int &mask, double left, double right) {
    int first = max(0, (int)floor(left + tileEps)), last = min(gridSize - 1, (int)ceil(right - tileEps) - 1);
    if (first > last) return 0;
    unsigned int added = ((1u << (last + 1)) - (1u << first)) & ~mask;
    mask |= added;
    return bitCount[added];
}

int countTiles(const vector<Edge> &edges, double offsetX, double offsetY, int best) {
    unsigned int border[gridSize] = {}, inside[gridSize] = {};
    double shiftX = 1.0 - offsetX, shiftY = 1.0 - offsetY;
    int borderCount = 0, answer = 0;
    for (const Edge &edge : edges) {
        double ax = edge.a.x + shiftX, ay = edge.a.y + shiftY;
        double bx = edge.b.x + shiftX, by = edge.b.y + shiftY;
        int firstRow = max(0, (int)floor(ay + tileEps)), lastRow = min(gridSize - 1, (int)ceil(by - tileEps) - 1);
        if (firstRow > lastRow) continue;
        if (edge.a.y == edge.b.y) {
            borderCount += markRange(border[firstRow], min(ax, bx), max(ax, bx));
        } else {
            for (int row = firstRow; row <= lastRow; row++) {
                double lowY = max(ay, (double)row), highY = min(by, row + 1.0);
                double lowX = ax + (lowY - ay) * edge.slope, highX = ax + (highY - ay) * edge.slope;
                borderCount += markRange(border[row], min(lowX, highX), max(lowX, highX));
                double centerY = row + 0.5;
                if (ay <= centerY && centerY < by) {
                    double crossX = ax + (centerY - ay) * edge.slope;
                    int count = max(0, min(gridSize, (int)ceil(crossX - 0.5)));
                    inside[row] ^= (1u << count) - 1;
                }
            }
        }
        if (borderCount >= best) return best;
    }
    for (int row = 0; row < gridSize; row++) {
        answer += bitCount[border[row] | inside[row]];
        if (answer >= best) return best;
    }
    return answer;
}

vector<Edge> buildEdges(const vector<Point> &polygon) {
    vector<Edge> edges;
    int n = polygon.size();
    edges.reserve(n);
    for (int i = 0; i < n; i++) {
        Point a = polygon[i], b = polygon[(i + 1) % n];
        if (a.y > b.y) swap(a, b);
        double slope = a.y == b.y ? 0.0 : (b.x - a.x) / (b.y - a.y);
        edges.push_back({a, b, slope});
    }
    return edges;
}

vector<Segment> buildSegments(const vector<Point> &polygon, vector<double> verticals, vector<double> horizontals) {
    vector<Segment> segments;
    int n = polygon.size();
    verticals.push_back(0.0);
    verticals.push_back(1.0);
    horizontals.push_back(0.0);
    horizontals.push_back(1.0);
    sort(verticals.begin(), verticals.end());
    sort(horizontals.begin(), horizontals.end());
    verticals.erase(unique(verticals.begin(), verticals.end()), verticals.end());
    horizontals.erase(unique(horizontals.begin(), horizontals.end()), horizontals.end());
    for (double x : verticals) addSegment(segments, {x, 0.0}, {x, 1.0});
    for (double y : horizontals) addSegment(segments, {0.0, y}, {1.0, y});
    for (int i = 0; i < n; i++) {
        Point a = polygon[i], b = polygon[(i + 1) % n];
        if (a.x == b.x || a.y == b.y) continue;
        int firstX = (int)ceil(min(a.x, b.x) - 1.0 - geomEps), lastX = (int)floor(max(a.x, b.x) + geomEps);
        int firstY = (int)ceil(min(a.y, b.y) - 1.0 - geomEps), lastY = (int)floor(max(a.y, b.y) + geomEps);
        for (int x = firstX; x <= lastX; x++) {
            for (int y = firstY; y <= lastY; y++) {
                Point shift = {(double)x, (double)y};
                addClippedSegment(segments, a - shift, b - shift);
            }
        }
    }
    return segments;
}

int solveCase(vector<Point> polygon, int width, int height) {
    int n = polygon.size(), answer = gridSize * gridSize + 1;
    double areaSum = 0.0;
    vector<double> verticals, horizontals;
    for (int i = 0; i < n; i++) areaSum += cross(polygon[i], polygon[(i + 1) % n]);
    long long twiceArea = llround(fabs(areaSum)), twiceTileArea = 2LL * width * height;
    int lowerBound = (int)((twiceArea + twiceTileArea - 1) / twiceTileArea);
    for (Point &point : polygon) {
        verticals.push_back(((int)point.x % width) / (double)width);
        horizontals.push_back(((int)point.y % height) / (double)height);
        point.x /= width;
        point.y /= height;
    }
    vector<Edge> edges = buildEdges(polygon);
    for (int i = 0; i < n; i++) {
        answer = min(answer, countTiles(edges, verticals[i], horizontals[i], answer));
        if (answer == lowerBound) return answer;
    }
    vector<Segment> segments = buildSegments(polygon, verticals, horizontals);
    vector<pair<long long, long long>> candidates;
    int segmentCount = segments.size();
    candidates.reserve((size_t)segmentCount * segmentCount / 4 + 2 * segmentCount);
    for (const Segment &segment : segments) {
        addCandidate(candidates, segment.a);
        addCandidate(candidates, segment.b);
    }
    for (int i = 0; i < segmentCount; i++) {
        for (int j = i + 1; j < segmentCount; j++) {
            Point point;
            if (getIntersection(segments[i], segments[j], point)) addCandidate(candidates, point);
        }
    }
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
    for (const auto &candidate : candidates) {
        double offsetX = candidate.first / (double)keyScale, offsetY = candidate.second / (double)keyScale;
        answer = min(answer, countTiles(edges, offsetX, offsetY, answer));
        if (answer == lowerBound) return answer;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int mask = 1; mask < maskSize; mask++) bitCount[mask] = bitCount[mask >> 1] + (mask & 1);
    int n, width, height;
    while (cin >> n >> width >> height) {
        vector<Point> polygon(n);
        for (Point &point : polygon) cin >> point.x >> point.y;
        cout << solveCase(polygon, width, height) << '\n';
    }
    return 0;
}
