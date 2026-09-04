#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000009LL;

struct Point {
    long long x, y;
};

long long cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

int getHalf(const Point &a) {
    if (a.y > 0 || (a.y == 0 && a.x > 0))
        return 0;
    return 1;
}

long long solveCase() {
    int n, k;
    cin >> n;
    Point points[1005], base;
    for (int i = 0; i < n; i++)
        cin >> points[i].x >> points[i].y;
    cin >> k;
    base = points[k - 1];
    vector<Point> vec;
    for (int i = 0; i < n; i++) {
        if (i == k - 1)
            continue;
        vec.push_back({points[i].x - base.x, points[i].y - base.y});
    }
    sort(vec.begin(), vec.end(), [](const Point &a, const Point &b) {
        int halfA = getHalf(a), halfB = getHalf(b);
        if (halfA != halfB)
            return halfA < halfB;
        return cross(a, b) > 0;
    });
    int m = n - 1;
    vector<Point> allVec(2 * m);
    for (int i = 0; i < 2 * m; i++)
        allVec[i] = vec[i % m];
    long long power[1005];
    power[0] = 1;
    for (int i = 1; i <= m; i++)
        power[i] = power[i - 1] * 2 % mod;
    long long answer = 0;
    int right = 1;
    for (int left = 0; left < m; left++) {
        if (right <= left)
            right = left + 1;
        while (right < left + m && cross(allVec[left], allVec[right]) > 0)
            right++;
        int count = right - left - 1;
        answer = (answer + power[count] - 1 + mod) % mod;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        cout << solveCase() << '\n';
    return 0;
}
