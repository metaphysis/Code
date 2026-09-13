#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-12L;
const int maxN = 105;
const int maxCand = 10200;

struct Point {
    long double x, y, z;
    Point operator + (const Point &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    Point operator - (const Point &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    Point operator * (long double value) const {
        return {x * value, y * value, z * value};
    }
};

int n, candCnt, bestCnt;
long double limitVal[maxN];
Point dir[maxN], cand[maxCand];
int bestAns[maxN];

long double dotProduct(Point a, Point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point crossProduct(Point a, Point b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

long double length(Point a) {
    return sqrtl(dotProduct(a, a));
}

void addCandidate(Point p) {
    long double len = length(p);
    if (len <= eps) return;
    cand[candCnt++] = p * (1.0L / len);
}

void buildCandidates() {
    candCnt = 0;
    for (int i = 0; i < n; i++)
        addCandidate(dir[i]);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Point normal = crossProduct(dir[i], dir[j]);
            long double normalLen = length(normal);
            if (normalLen <= eps) continue;
            long double cosVal = dotProduct(dir[i], dir[j]);
            long double det = 1.0L - cosVal * cosVal;
            if (det <= eps) continue;
            long double coefA = (limitVal[i] - limitVal[j] * cosVal) / det;
            long double coefB = (limitVal[j] - limitVal[i] * cosVal) / det;
            Point base = dir[i] * coefA + dir[j] * coefB;
            long double baseLen2 = dotProduct(base, base);
            long double remain = 1.0L - baseLen2;
            if (remain < -eps) continue;
            remain = max(0.0L, remain);
            Point unitNormal = normal * (1.0L / normalLen);
            long double height = sqrtl(remain);
            addCandidate(base + unitNormal * height);
            if (height > eps)
                addCandidate(base - unitNormal * height);
        }
    }
}

void findAnswer() {
    bestCnt = 0;
    for (int i = 0; i < candCnt; i++) {
        int curCnt = 0;
        for (int j = 0; j < n; j++)
            if (dotProduct(cand[i], dir[j]) + eps >= limitVal[j])
                curCnt++;
        if (curCnt > bestCnt) {
            bestCnt = curCnt;
            int pos = 0;
            for (int j = 0; j < n; j++)
                if (dotProduct(cand[i], dir[j]) + eps >= limitVal[j])
                    bestAns[pos++] = j + 1;
        }
    }
}

int solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        long double x, y, z, radius;
        cin >> x >> y >> z >> radius;
        Point center = {x, y, z};
        long double centerLen = length(center);
        dir[i] = center * (1.0L / centerLen);
        limitVal[i] = sqrtl(max(0.0L, centerLen * centerLen - radius * radius)) / centerLen;
    }
    if (n == 0) {
        cout << 0 << '\n';
        return 0;
    }
    buildCandidates();
    findAnswer();
    cout << bestCnt << '\n';
    for (int i = 0; i < bestCnt; i++) {
        if (i > 0) cout << ' ';
        cout << bestAns[i];
    }
    cout << '\n';
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseCnt;
    cin >> caseCnt;
    for (int caseId = 0; caseId < caseCnt; caseId++) {
        if (caseId > 0) cout << '\n';
        solve();
    }
    return 0;
}
