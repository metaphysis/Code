#include <bits/stdc++.h>
using namespace std;

struct Line {
    long double height, slope;
};

long double solveCase() {
    int n, len;
    cin >> n >> len;
    vector<long double> x(n), y(n), slope(n - 1), prefix(n, 0), events;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    for (int i = 0; i < n - 1; i++) {
        slope[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
        prefix[i + 1] = prefix[i] + (y[i] + y[i + 1]) * (x[i + 1] - x[i]) / 2;
    }
    long double inf = 1e100L, ans = inf, domainRight = x[n - 1] - len;
    if (domainRight == x[0]) return max(0.0L, prefix[n - 1] - len * *min_element(y.begin(), y.end()));
    events.push_back(x[0]);
    events.push_back(domainRight);
    for (int i = 0; i < n; i++) {
        if (x[i] > x[0] && x[i] < domainRight) events.push_back(x[i]);
        if (x[i] - len > x[0] && x[i] - len < domainRight) events.push_back(x[i] - len);
    }
    sort(events.begin(), events.end());
    events.erase(unique(events.begin(), events.end()), events.end());
    for (int idx = 0; idx + 1 < (int)events.size(); idx++) {
        long double left = events[idx], right = events[idx + 1], mid = (left + right) / 2, minY = inf, hLeft, hRight, baseArea, deltaSlope;
        int leftSeg = (int)(upper_bound(x.begin(), x.end(), mid) - x.begin()) - 1, rightSeg = (int)(upper_bound(x.begin(), x.end(), mid + len) - x.begin()) - 1;
        hLeft = y[leftSeg] + slope[leftSeg] * (left - x[leftSeg]);
        hRight = y[rightSeg] + slope[rightSeg] * (left + len - x[rightSeg]);
        baseArea = prefix[rightSeg] + (y[rightSeg] + hRight) * (left + len - x[rightSeg]) / 2;
        baseArea -= prefix[leftSeg] + (y[leftSeg] + hLeft) * (left - x[leftSeg]) / 2;
        deltaSlope = slope[rightSeg] - slope[leftSeg];
        for (int i = leftSeg + 1; i <= rightSeg; i++) minY = min(minY, y[i]);
        vector<Line> lines;
        vector<long double> cuts;
        lines.push_back({hLeft, slope[leftSeg]});
        lines.push_back({hRight, slope[rightSeg]});
        if (minY < inf) lines.push_back({minY, 0});
        cuts.push_back(0);
        cuts.push_back(right - left);
        for (int i = 0; i < (int)lines.size(); i++) {
            for (int j = i + 1; j < (int)lines.size(); j++) {
                long double diffSlope = lines[i].slope - lines[j].slope, cross;
                if (diffSlope == 0) continue;
                cross = (lines[j].height - lines[i].height) / diffSlope;
                if (cross > 0 && cross < right - left) cuts.push_back(cross);
            }
        }
        sort(cuts.begin(), cuts.end());
        cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());
        for (int i = 0; i + 1 < (int)cuts.size(); i++) {
            long double lo = cuts[i], hi = cuts[i + 1], center = (lo + hi) / 2, linear, constant, pos;
            int best = 0;
            for (int j = 1; j < (int)lines.size(); j++) if (lines[j].height + lines[j].slope * center < lines[best].height + lines[best].slope * center) best = j;
            linear = hRight - hLeft - len * lines[best].slope;
            constant = baseArea - len * lines[best].height;
            ans = min(ans, constant + linear * lo + deltaSlope * lo * lo / 2);
            ans = min(ans, constant + linear * hi + deltaSlope * hi * hi / 2);
            if (deltaSlope > 0) {
                pos = -linear / deltaSlope;
                if (pos > lo && pos < hi) ans = min(ans, constant + linear * pos + deltaSlope * pos * pos / 2);
            }
        }
    }
    return max(0.0L, ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    cout << fixed << setprecision(4);
    while (testCount--) cout << solveCase() << '\n';
    return 0;
}
