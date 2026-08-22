#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long a, b;
    long long get(long long x) const {
        return a * x + b;
    }
};

long long floorDiv(long long a, long long b) {
    if (b < 0) {
        a = -a;
        b = -b;
    }
    if (a >= 0) return a / b;
    return -((-a + b - 1) / b);
}

long long solve(long long r, long long t, long long n) {
    if (r <= 1) return 0;
    vector<Line> lowLine, highLine;
    lowLine.push_back({0, 1});
    lowLine.push_back({1, 0});
    lowLine.push_back({n, t - n * r});
    highLine.push_back({0, t - 1});
    highLine.push_back({n, 0});
    highLine.push_back({1, t - r});
    vector<long long> point;
    point.push_back(1);
    point.push_back(r);
    vector<Line> allLine = lowLine;
    allLine.insert(allLine.end(), highLine.begin(), highLine.end());
    for (int i = 0; i < (int)allLine.size(); i++) {
        for (int j = i + 1; j < (int)allLine.size(); j++) {
            long long da = allLine[i].a - allLine[j].a;
            long long db = allLine[j].b - allLine[i].b;
            if (da == 0) continue;
            long long q = floorDiv(db, da);
            for (long long d = -2; d <= 2; d++) {
                long long x = q + d;
                if (x >= 1 && x <= r - 1) point.push_back(x);
            }
        }
    }
    sort(point.begin(), point.end());
    point.erase(unique(point.begin(), point.end()), point.end());
    long long ans = 0;
    for (int i = 0; i + 1 < (int)point.size(); i++) {
        long long left = point[i], right = point[i + 1] - 1;
        if (left > right) continue;
        long long mid = left + (right - left) / 2;
        int lowId = 0, highId = 0;
        for (int j = 1; j < (int)lowLine.size(); j++)
            if (lowLine[j].get(mid) > lowLine[lowId].get(mid)) lowId = j;
        for (int j = 1; j < (int)highLine.size(); j++)
            if (highLine[j].get(mid) < highLine[highId].get(mid)) highId = j;
        long long first = highLine[highId].get(left) - lowLine[lowId].get(left) + 1;
        long long delta = highLine[highId].a - lowLine[lowId].a;
        long long len = right - left + 1;
        long long last = first + delta * (len - 1);
        if (first > 0 && last > 0)
            ans += len * (first + last) / 2;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long r, t, n;
    while (cin >> r >> t >> n && (r || t || n))
        cout << solve(r, t, n) << '\n';
    return 0;
}
