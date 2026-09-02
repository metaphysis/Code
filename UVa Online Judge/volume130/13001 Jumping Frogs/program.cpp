#include <bits/stdc++.h>
using namespace std;

const long long Inf = (1LL << 60);

struct Line {
    long long a, b, c;
    __int128 value(long long x) const {
        return (__int128)a * x + b;
    }
};

bool slopeLess(const Line &x, const Line &y) {
    return (__int128)x.a * y.c < (__int128)y.a * x.c;
}

bool sameSlope(const Line &x, const Line &y) {
    return (__int128)x.a * y.c == (__int128)y.a * x.c;
}

bool valueLess(const Line &x, const Line &y, long long pos) {
    return x.value(pos) * y.c < y.value(pos) * x.c;
}

bool intersectionLess(const Line &x, const Line &y, const Line &z) {
    __int128 n1 = ((__int128)x.b * y.c - (__int128)y.b * x.c) * ((__int128)z.a * y.c - (__int128)y.a * z.c);
    __int128 n2 = ((__int128)y.b * z.c - (__int128)z.b * y.c) * ((__int128)y.a * x.c - (__int128)x.a * y.c);
    return n1 < n2;
}

struct Hull {
    vector<Line> lines;
    void build(vector<Line> input) {
        sort(input.begin(), input.end(), slopeLess);
        for (int i = 0; i < (int)input.size(); i++) {
            if (!lines.empty() && sameSlope(lines.back(), input[i])) {
                if (valueLess(lines.back(), input[i], 0))
                    lines.back() = input[i];
                continue;
            }
            while ((int)lines.size() >= 2 && !intersectionLess(lines[(int)lines.size() - 2], lines.back(), input[i]))
                lines.pop_back();
            lines.push_back(input[i]);
        }
    }
    Line query(long long pos) const {
        int left = 0, right = (int)lines.size() - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (valueLess(lines[mid], lines[mid + 1], pos))
                left = mid + 1;
            else
                right = mid;
        }
        return lines[left];
    }
};

long long ceilDiv(__int128 x, long long y) {
    if (x >= 0)
        return (long long)((x + y - 1) / y);
    return (long long)(-((-x) / y));
}

long long floorDiv(__int128 x, long long y) {
    if (x >= 0)
        return (long long)(x / y);
    return (long long)(-((-x + y - 1) / y));
}

long long getCeil(const Hull &h, long long pos) {
    Line line = h.query(pos);
    return ceilDiv(line.value(pos), line.c);
}

long long getMinFloor(const Hull &negHull, long long pos) {
    Line line = negHull.query(pos);
    return -ceilDiv(line.value(pos), line.c);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int r, g, n;
        cin >> r >> g >> n;
        vector<long long> redPos(r), redVel(r), greenPos(g), greenVel(g), border(n + 2);
        for (int i = 0; i < r; i++)
            cin >> redPos[i];
        for (int i = 0; i < r; i++)
            cin >> redVel[i];
        for (int i = 0; i < g; i++)
            cin >> greenPos[i];
        for (int i = 0; i < g; i++)
            cin >> greenVel[i];
        border[0] = 0;
        for (int i = 1; i <= n; i++)
            cin >> border[i];
        border[n + 1] = 1000000000LL;
        vector<Line> redMaxInput, redMinInput, greenMaxInput, greenMinInput;
        long long redFixedMin = Inf, redFixedMax = -Inf, greenFixedMin = Inf, greenFixedMax = -Inf;
        for (int i = 0; i < r; i++) {
            if (redVel[i] == 0) {
                redFixedMin = min(redFixedMin, redPos[i]);
                redFixedMax = max(redFixedMax, redPos[i]);
            } else {
                redMaxInput.push_back({1, -redPos[i], redVel[i]});
                redMinInput.push_back({-1, redPos[i], redVel[i]});
            }
        }
        for (int i = 0; i < g; i++) {
            if (greenVel[i] == 0) {
                greenFixedMin = min(greenFixedMin, greenPos[i]);
                greenFixedMax = max(greenFixedMax, greenPos[i]);
            } else {
                greenMaxInput.push_back({-1, greenPos[i], greenVel[i]});
                greenMinInput.push_back({1, -greenPos[i], greenVel[i]});
            }
        }
        Hull redMax, redMin, greenMax, greenMin;
        redMax.build(redMaxInput);
        redMin.build(redMinInput);
        greenMax.build(greenMaxInput);
        greenMin.build(greenMinInput);
        long long answer = Inf;
        for (int i = 0; i <= n; i++) {
            long long left = border[i], right = border[i + 1];
            if (redFixedMin != Inf && (left > redFixedMin || right < redFixedMax))
                continue;
            if (greenFixedMin != Inf && (left > greenFixedMin || right < greenFixedMax))
                continue;
            long long low = 0, high = Inf;
            if (!redMax.lines.empty())
                low = max(low, getCeil(redMax, left));
            if (!greenMax.lines.empty())
                low = max(low, getCeil(greenMax, right));
            if (!redMin.lines.empty())
                high = min(high, getMinFloor(redMin, right));
            if (!greenMin.lines.empty())
                high = min(high, getMinFloor(greenMin, left));
            if (low <= high)
                answer = min(answer, low);
        }
        cout << "Case " << caseId << ": ";
        if (answer == Inf)
            cout << -1 << '\n';
        else
            cout << answer << '\n';
    }
    return 0;
}
