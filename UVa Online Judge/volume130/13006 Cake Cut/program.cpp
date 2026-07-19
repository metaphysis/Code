// Cake Cut
// UVa ID: 13006
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.220s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<Point> P(N);
        for (int i = 0; i < N; ++i) cin >> P[i].x >> P[i].y;
        vector<Point> P2(2 * N);
        for (int i = 0; i < 2 * N; ++i) P2[i] = P[i % N];
        vector<long long> S(2 * N, 0);
        for (int k = 1; k < 2 * N; ++k) S[k] = S[k - 1] + cross(P2[k - 1], P2[k]);
        long long total = S[N];                     // 整个多边形的叉积和（体积）
        auto calcA = [&](int i, int j) -> long long {
            return S[j] - S[i] + cross(P2[j], P2[i]);
        };
        long long bestCarol = 0;
        for (int i = 0; i < N; ++i) {
            int left = i + 2;
            int right = i + N - 2;
            // 二分查找第一个使 2*A >= total 的 j
            int lo = left, hi = right;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                long long A = calcA(i, mid);
                if (2 * A >= total) hi = mid - 1;
                else lo = mid + 1;
            }
            long long bestDiff = LLONG_MAX;
            auto consider = [&](int j) {
                if (j < left || j > right) return;
                long long A = calcA(i, j);
                long long diff = llabs(2 * A - total);
                if (diff < bestDiff) bestDiff = diff;
            };
            if (lo <= right) {
                consider(lo);
                if (lo - 1 >= left) consider(lo - 1);
            } else {
                consider(right);
            }
            long long carolForThisV = (total + bestDiff) / 2;
            if (carolForThisV > bestCarol) bestCarol = carolForThisV;
        }
        long long carla = total - bestCarol;
        cout << bestCarol << " " << carla << "\n";
    }
    return 0;
}
