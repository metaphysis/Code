#include <bits/stdc++.h>
using namespace std;

struct Time {
    long long num, den;
};

struct Point {
    long long value;
};

bool pointLess(const Point &a, const Point &b) {
    return a.value < b.value;
}

Time readTime(long long n) {
    string timeStr, fractionStr;
    cin >> timeStr >> fractionStr;
    size_t colonPos = timeStr.find(':');
    size_t slashPos = fractionStr.find('/');
    long long hour = stoll(timeStr.substr(0, colonPos)), minute = stoll(timeStr.substr(colonPos + 1));
    long long num = stoll(fractionStr.substr(0, slashPos)), den = stoll(fractionStr.substr(slashPos + 1));
    return {(hour * n + minute) * den + num, den};
}

vector<Point> buildPoints(long long m) {
    vector<Point> points;
    long long base = m * m - 1;
    for (long long hour = 0; hour < m; hour++) {
        for (long long k = -m; k <= m; k++) {
            long long value = hour + k * m;
            if (value < 0 || value >= base) continue;
            if ((__int128)(m - 1) * value == (__int128)hour * base) continue;
            points.push_back({hour * m + k});
        }
    }
    sort(points.begin(), points.end(), pointLess);
    points.erase(unique(points.begin(), points.end(), [](const Point &a, const Point &b) {
        return a.value == b.value;
    }), points.end());
    return points;
}

long long countLessEqual(const vector<Point> &points, const Time &time, long long m, long long n) {
    long long base = m * m - 1, totalMinutes = m * n;
    long long left = 0, right = points.size();
    while (left < right) {
        long long middle = (left + right) / 2;
        __int128 pointValue = (__int128)totalMinutes * points[middle].value * time.den;
        __int128 timeValue = (__int128)time.num * base;
        if (pointValue <= timeValue) left = middle + 1;
        else right = middle;
    }
    return left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long m, n, nq;
    int caseNum = 1;
    bool firstCase = true;
    while (cin >> m >> n >> nq) {
        if (m == 0 && n == 0 && nq == 0) break;
        if (!firstCase) cout << '\n';
        firstCase = false;
        cout << "Planet " << caseNum++ << ":\n";
        if (m == 1) {
            for (long long i = 0; i < nq; i++) {
                Time leftTime = readTime(n), rightTime = readTime(n);
                cout << "0\n";
            }
            continue;
        }
        vector<Point> points = buildPoints(m);
        for (long long i = 0; i < nq; i++) {
            Time leftTime = readTime(n), rightTime = readTime(n);
            long long leftCount = countLessEqual(points, leftTime, m, n);
            long long rightCount = countLessEqual(points, rightTime, m, n);
            cout << rightCount - leftCount << '\n';
        }
    }
    return 0;
}
