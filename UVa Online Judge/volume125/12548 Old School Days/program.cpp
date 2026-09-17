#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000003, invSix = 833336;

struct Point {
    long long x, y;
};

long long cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

bool upperHalf(const Point &p) {
    return p.y > 0 || (p.y == 0 && p.x > 0);
}

bool angleLess(const Point &a, const Point &b) {
    bool aHalf = upperHalf(a), bHalf = upperHalf(b);
    if (aHalf != bHalf) return aHalf > bHalf;
    return cross(a, b) > 0;
}

long long norm(long long value) {
    value %= mod;
    if (value < 0) value += mod;
    return value;
}

long long solveCase(const vector<Point> &points) {
    int n = points.size(), m = n - 1;
    if (n < 4) return 0;
    long long triSum = 0, innerSum = 0;
    vector<Point> vec(2 * m);
    vector<int> rightPos(2 * m);
    vector<long long> preX(2 * m + 1), preY(2 * m + 1),
        preKx(2 * m + 1), preKy(2 * m + 1);
    for (int pivot = 0; pivot < n; ++pivot) {
        int count = 0, pos = 1;
        for (int j = 0; j < n; ++j) {
            if (j == pivot) continue;
            vec[count++] = {points[j].x - points[pivot].x,
                points[j].y - points[pivot].y};
        }
        sort(vec.begin(), vec.begin() + m, angleLess);
        for (int i = 0; i < m; ++i) vec[i + m] = vec[i];
        for (int i = 0; i < m; ++i) {
            pos = max(pos, i + 1);
            while (pos < i + m && cross(vec[i], vec[pos]) > 0) ++pos;
            rightPos[i] = pos;
        }
        for (int i = 0; i < m; ++i) rightPos[i + m] = rightPos[i] + m;
        preX[0] = preY[0] = preKx[0] = preKy[0] = 0;
        for (int i = 0; i < 2 * m; ++i) {
            long long x = norm(vec[i].x), y = norm(vec[i].y);
            preX[i + 1] = (preX[i] + x) % mod;
            preY[i + 1] = (preY[i] + y) % mod;
            preKx[i + 1] = (preKx[i] + x * rightPos[i]) % mod;
            preKy[i + 1] = (preKy[i] + y * rightPos[i]) % mod;
        }
        for (int i = 0; i < m; ++i) {
            int left = i + 1, right = rightPos[i];
            long long sumX = norm(preX[right] - preX[left]),
                sumY = norm(preY[right] - preY[left]),
                sumKx = norm(preKx[right] - preKx[left]),
                sumKy = norm(preKy[right] - preKy[left]),
                areaSum = norm(vec[i].x * sumY - vec[i].y * sumX),
                weightedSum = norm(vec[i].x * sumKy - vec[i].y * sumKx);
            triSum = (triSum + areaSum) % mod;
            innerSum = norm(innerSum + weightedSum - rightPos[i] * areaSum);
        }
    }
    return (triSum * (n - 3) % mod * invSix + innerSum) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, n;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        cin >> n;
        vector<Point> points(n);
        for (int i = 0; i < n; ++i) cin >> points[i].x >> points[i].y;
        cout << "Case " << caseId << ": " << solveCase(points) << '\n';
    }
    return 0;
}
