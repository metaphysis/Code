#include <bits/stdc++.h>
using namespace std;

const long double pi = acosl(-1.0L);
const long double twoPi = 2.0L * pi;

struct Ring {
    int x, y, innerR, outerR;
};

void addInterval(vector<pair<long double, int>> &events, long double leftAngle, long double rightAngle, int delta) {
    events.emplace_back(leftAngle, delta);
    events.emplace_back(rightAngle, -delta);
}

void addDisk(vector<pair<long double, int>> &events, int x, int y, int radius, const Ring &ring, int diskR, int delta) {
    if (diskR == 0) return;
    int dx = ring.x - x, dy = ring.y - y, distSq = dx * dx + dy * dy;
    int sumR = radius + diskR, diffR = radius - diskR;
    if (diskR >= radius && distSq <= diffR * diffR) {
        addInterval(events, 0.0L, twoPi, delta);
        return;
    }
    if (distSq >= sumR * sumR) return;
    if (radius >= diskR && distSq <= diffR * diffR) return;
    long double dist = sqrtl(static_cast<long double>(distSq));
    long double cosValue = (static_cast<long double>(distSq) + radius * radius - diskR * diskR) / (2.0L * dist * radius);
    cosValue = max(-1.0L, min(1.0L, cosValue));
    long double baseAngle = atan2l(static_cast<long double>(dy), static_cast<long double>(dx)), halfAngle = acosl(cosValue);
    if (baseAngle < 0.0L) baseAngle += twoPi;
    long double leftAngle = baseAngle - halfAngle, rightAngle = baseAngle + halfAngle;
    if (leftAngle < 0.0L) {
        addInterval(events, 0.0L, rightAngle, delta);
        addInterval(events, leftAngle + twoPi, twoPi, delta);
    } else if (rightAngle > twoPi) {
        addInterval(events, leftAngle, twoPi, delta);
        addInterval(events, 0.0L, rightAngle - twoPi, delta);
    } else addInterval(events, leftAngle, rightAngle, delta);
}

long double arcArea(int x, int y, int radius, long double leftAngle, long double rightAngle) {
    long double r = radius;
    return (r * r * (rightAngle - leftAngle) + r * x * (sinl(rightAngle) - sinl(leftAngle)) + r * y * (cosl(leftAngle) - cosl(rightAngle))) / 2.0L;
}

long double solveCase(const vector<Ring> &rings) {
    map<tuple<int, int, int>, int> circleTypes;
    for (const Ring &ring : rings) {
        circleTypes[make_tuple(ring.x, ring.y, ring.outerR)] |= 1;
        if (ring.innerR > 0) circleTypes[make_tuple(ring.x, ring.y, ring.innerR)] |= 2;
    }
    vector<pair<long double, int>> events;
    events.reserve(rings.size() * 8 + 2);
    long double answer = 0.0L;
    for (const auto &entry : circleTypes) {
        if (entry.second == 3) continue;
        int x = get<0>(entry.first), y = get<1>(entry.first), radius = get<2>(entry.first);
        int sign = entry.second == 1 ? 1 : -1, coverCount = 0;
        events.clear();
        events.emplace_back(0.0L, 0);
        events.emplace_back(twoPi, 0);
        for (const Ring &ring : rings) {
            if (ring.x == x && ring.y == y && (ring.outerR == radius || ring.innerR == radius)) continue;
            addDisk(events, x, y, radius, ring, ring.outerR, 1);
            addDisk(events, x, y, radius, ring, ring.innerR, -1);
        }
        sort(events.begin(), events.end());
        long double lastAngle = 0.0L;
        for (const auto &event : events) {
            if (coverCount == 0 && event.first > lastAngle) answer += sign * arcArea(x, y, radius, lastAngle, event.first);
            coverCount += event.second;
            lastAngle = event.first;
        }
    }
    return max(0.0L, answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, n, wireLen, headLen;
    cin >> testCount;
    cout << fixed << setprecision(6);
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        cin >> n;
        vector<Ring> rings(n);
        for (Ring &ring : rings) {
            cin >> ring.x >> ring.y >> wireLen >> headLen;
            ring.innerR = max(0, wireLen - headLen);
            ring.outerR = wireLen + headLen;
        }
        cout << "Case " << caseId << ": " << solveCase(rings) << '\n';
    }
    return 0;
}
